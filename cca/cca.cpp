/////////////////////////////////////////////////////////////////////////////
//
// header files
// 
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include <assert.h>

#include <windows.h>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class file_loader
{
public:
	std::string _file_path;

private:
	std::uint8_t* _pointer;
	std::int32_t _size;

public:
	file_loader();
	virtual ~file_loader();

public:
	void clean(void);

public:
	std::uint8_t* get_pointer(void);
	std::int32_t get_size(void);
	bool load(std::string file_path);

private:
	std::int32_t get_size(std::string file_path);
	bool load(void);
};

//===========================================================================
file_loader::file_loader()
{
	_pointer = nullptr;
	_size = -1;
}

file_loader::~file_loader()
{
	clean();
}

//---------------------------------------------------------------------------
void file_loader::clean(void)
{
	if (_pointer != nullptr)
	{
		delete[] _pointer;
	}

	_pointer = nullptr;
	_size = -1;
}

std::uint8_t* file_loader::get_pointer(void)
{
	return _pointer;
}

std::int32_t file_loader::get_size(void)
{
	return _size;
}

std::int32_t file_loader::get_size(std::string file_path)
{
	HANDLE           hFind;
	WIN32_FIND_DATAA FindData;

	HANDLE hFile;
	DWORD  dwRSize;

	BOOL   bRv;


	hFind = INVALID_HANDLE_VALUE;
	memset(&FindData, 0, sizeof(FindData));

	hFile = INVALID_HANDLE_VALUE;
	dwRSize = 0u;


	hFind = ::FindFirstFileA(file_path.c_str(), &FindData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return -1;
	}

	bRv = ::FindClose(hFind);
	if (FALSE == bRv)
	{
		printf ("fail to FindClose() : %s", file_path.c_str());
	}

	if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
	{
		printf("%s FILE_ATTRIBUTE_DIRECTORY.", file_path.c_str());
		return -1;
	}


	return (std::int32_t)FindData.nFileSizeLow;
}

bool file_loader::load(std::string file_path)
{
	_file_path = file_path;

	_size = get_size(file_path);
	if (_size < 0)
	{
		return false;
	}

	return load();
}

bool file_loader::load(void)
{
	std::uint8_t* pointer;

	bool result;


	result = true;

	pointer = new(std::nothrow) std::uint8_t[_size];
	if (nullptr == pointer)
	{
		return false;
	}


	HANDLE hFile;
	DWORD  dwRSize;

	BOOL   bRv;

	
	hFile = INVALID_HANDLE_VALUE;
	dwRSize = 0u;
	
	hFile = ::CreateFileA(_file_path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		delete[] pointer;
		return false;
	}

	bRv = ReadFile(hFile, pointer, _size, &dwRSize, NULL);
	if (FALSE == bRv)
	{
		result = false;
	}

	bRv = CloseHandle(hFile);
	if (FALSE == bRv)
	{
		printf("fail to CloseHandle() : %s", _file_path.c_str());
	}

	if (_size != static_cast<std::int32_t>(dwRSize))
	{
		result = false;
	}

	if (false == result)
	{
		delete[] pointer;
	}
	else
	{
		_pointer = pointer;
	}

	return result;
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class cca_csv_element
{
	// "filename", "funcname", line number, column number, frequency count, "comment"
public:
	std::string  _filename;
	std::string  _funcname;
	std::int32_t _line_number;
	std::int32_t _column_number;
	std::int32_t _frequency_count;
	std::string  _comment;
};


/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class cca_source_line
{
public:
	std::int32_t                  _line_number;
	std::vector<cca_csv_element*> _element_container;

public:
	cca_source_line();
	virtual ~cca_source_line();

public:
	void clean(void);
	void delete_element_container(void);

	float get_coverage(void);
	std::uint32_t get_frequency(void);
};

//===========================================================================
cca_source_line::cca_source_line()
{
	_line_number = 0;
}

cca_source_line::~cca_source_line()
{
//	clean();
}

//---------------------------------------------------------------------------
void cca_source_line::clean(void)
{
	delete_element_container();
}

void cca_source_line::delete_element_container(void)
{
#if 0
	std::vector<cca_csv_element*>::iterator i;
	cca_csv_element* e;


	for (i = _element_container.begin();
		i != _element_container.end();
		i++
		)
	{
		e = (*i);

		if (nullptr != e)
		{
			e->clean();

			delete e;
}		}

		delete e;
	}
#endif

	_element_container.clear();
}

//---------------------------------------------------------------------------
float cca_source_line::get_coverage(void)
{
	std::vector<cca_csv_element*>::iterator i;
	cca_csv_element* e;

	float total_count;
	float cover_count;


	total_count = 0.0f;
	cover_count = 0.0f;

	for (i = _element_container.begin();
		i != _element_container.end();
		i++
		)
	{
		e = (*i);

		if (e->_frequency_count > 0)
		{
			cover_count = cover_count + 1.0f;
		}
		total_count = total_count + 1.0f;
	}

	if (total_count > 0.0f)
	{
		return cover_count / total_count;
	}

	return 0.0f;
}

std::uint32_t cca_source_line::get_frequency(void)
{
	std::vector<cca_csv_element*>::iterator i;
	cca_csv_element* e;

	std::uint32_t frequency;


	frequency = 0u;

	for (i = _element_container.begin();
		i != _element_container.end();
		i++
		)
	{
		e = (*i);

		frequency += e->_frequency_count;
	}

	return frequency;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class cca_source_function
{
public:
	std::string _filename;
	std::string _funcname;
	std::map<std::int32_t, cca_source_line*> _line_container;

	std::string _report;

public:
	cca_source_function();
	virtual ~cca_source_function();

public:
	void clean(void);
	void delete_line_container(void);

	float get_coverage(void);
};

//===========================================================================
cca_source_function::cca_source_function()
{
}

cca_source_function::~cca_source_function()
{
	clean();
}

//---------------------------------------------------------------------------
void cca_source_function::clean(void)
{
	delete_line_container();
}

void cca_source_function::delete_line_container(void)
{
	std::map<std::int32_t, cca_source_line*>::iterator i;
	cca_source_line* e;


	for (i = _line_container.begin();
		i != _line_container.end();
		i++
		)
	{
		e = (*i).second;

		if (nullptr != e)
		{
			e->clean();

			delete e;
		}
	}

	_line_container.clear();
}

//---------------------------------------------------------------------------
float cca_source_function::get_coverage(void)
{
	std::map<std::int32_t, cca_source_line*>::iterator i;
	cca_source_line* e;

	float total_count;
	float cover_count;


	total_count = 0.0f;
	cover_count = 0.0f;

	for (i = _line_container.begin();
		i != _line_container.end();
		i++
		)
	{
		e = (*i).second;

		cover_count = cover_count + e->get_coverage();
		total_count = total_count + 1.0f;
	}

	if (total_count > 0.0f)
	{
		return cover_count / total_count;
	}

	return 0.0f;
}

/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class cca_source_file
{
public:
	std::string _filename;
	std::map<std::int32_t, cca_source_line*> _line_container;
	std::map<std::string, cca_source_function*> _function_container;

	std::string _report;

public:
	cca_source_file();
	virtual ~cca_source_file();

public:
	void clean(void);
	void delete_line_container(void);
	void delete_function_container(void);

	float get_coverage(void);
};

//===========================================================================
cca_source_file::cca_source_file()
{

}

cca_source_file::~cca_source_file()
{
	clean();
}

//---------------------------------------------------------------------------
void cca_source_file::clean(void)
{
	delete_line_container();
	delete_function_container();
}

void cca_source_file::delete_line_container(void)
{
	std::map<std::int32_t, cca_source_line*>::iterator i;
	cca_source_line* e;


	for (i = _line_container.begin();
		i != _line_container.end();
		i++
		)
	{
		e = (*i).second;

		if (nullptr != e)
		{
			e->clean();

			delete e;
		}
	}

	_line_container.clear();
}

void cca_source_file::delete_function_container(void)
{
	std::map<std::string, cca_source_function*>::iterator i;
	cca_source_function* e;


	for (i = _function_container.begin();
		i != _function_container.end();
		i++
		)
	{
		e = (*i).second;

		if (nullptr != e)
		{
			e->clean();

			delete e;
		}
	}

	_function_container.clear();
}

//---------------------------------------------------------------------------
float cca_source_file::get_coverage(void)
{
	std::map<std::int32_t, cca_source_line*>::iterator i;
	cca_source_line* e;

	float total_count;
	float cover_count;


	total_count = 0.0f;
	cover_count = 0.0f;

	for (i = _line_container.begin();
		i != _line_container.end();
		i++
		)
	{
		e = (*i).second;

		cover_count = cover_count + e->get_coverage();
		total_count = total_count + 1.0f;
	}

	if (total_count > 0.0f)
	{
		return cover_count / total_count;
	}

	return 0.0f;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class cca
{
public:
	std::vector<std::string> _csv_line_container;
	std::vector<cca_csv_element*> _csv_element_container;
	std::map<std::string,cca_source_file*> _source_file_container;

public:
	cca();
	virtual ~cca();

public:
	void load_from_file(std::string cca_csv_filename);
	void load_from_buffer(std::uint8_t* file_pointer, std::int32_t file_size);
	void parse_csv_line_container(void);
	void parse_csv_line(const std::string& csv_line);
	
	void make_source_file_container(void);


	void report_source_file_container(void);
	void report_source_file(cca_source_file* e);
	void report_source_file_coverage(cca_source_file* e, std::string& file_path);
	void report_source_file_function_coverage(cca_source_file* e, std::string& file_path);
	void report_source_file_contents(cca_source_file* e, std::string& file_path, std::uint8_t* file_pointer, std::int32_t file_size);
	void report_source_file_contents_line(cca_source_file* e, std::string& file_path, std::size_t line_number, std::string& line_string);

	void clean(void);
	void delete_source_file_container(void);
	void delete_csv_element_container(void);
};

//===========================================================================
cca::cca()
{

}

cca::~cca()
{
	clean();
}

//---------------------------------------------------------------------------
void cca::clean(void)
{
	delete_source_file_container();
	delete_csv_element_container();
}

void cca::delete_source_file_container(void)
{
	std::map<std::string, cca_source_file*>::iterator i;
	cca_source_file* e;


	for (i = _source_file_container.begin();
		i != _source_file_container.end();
		i++
		)
	{
		e = (*i).second;

		e->clean();

		delete e;
	}

	_source_file_container.clear();
}

void cca::delete_csv_element_container(void)
{
	std::vector<cca_csv_element*>::iterator i;
	cca_csv_element* e;
	

	for (i = _csv_element_container.begin();
		i != _csv_element_container.end();
		i++
		)
	{
		e = *i;

		delete e;
	}

	_csv_element_container.clear();
}

//---------------------------------------------------------------------------
void cca::load_from_file(std::string cca_csv_filename)
{
	file_loader fl;


	if (false == fl.load(cca_csv_filename))
	{
		return;
	}



	std::uint8_t* file_pointer;
	std::int32_t file_size;
	

	file_size = fl.get_size();
	file_pointer = fl.get_pointer();

	if (nullptr != file_pointer)
	{
		load_from_buffer(file_pointer, file_size);
	}
}

void cca::load_from_buffer(std::uint8_t* pointer, std::int32_t size)
{
	std::string line_string;

	std::int32_t count;
	std::int32_t i;
	std::uint8_t ch;


	count = size;
	for (i = 0; i < count; i++)
	{
		ch = *(pointer + i);
		if (ch == '\r')
		{

		}
		else if (ch == '\n')
		{
			_csv_line_container.push_back(line_string);
			line_string.clear();
		}
		else
		{
			line_string.push_back(ch);
		}
	}

	parse_csv_line_container();
	make_source_file_container();
}

void cca::parse_csv_line_container(void)
{
	std::size_t count;
	std::size_t i;


	count = _csv_line_container.size();
	for (i=1; i<count; i++)
	{
		parse_csv_line(_csv_line_container[i]);
	}
}

void cca::parse_csv_line(const std::string& csv_line)
{
	std::vector<std::string> element_string_container;
	std::string element_string;

	std::size_t count;
	std::size_t i;
	std::uint8_t ch;

	std::size_t comma_count;



	comma_count = 0u;


	count = csv_line.length();
	for (i = 0; i < count; i++)
	{
		ch = csv_line.at(i);
		if (ch == ',')
		{
			comma_count++;

			if (comma_count <= 5)
			{
				element_string_container.push_back(element_string);
				element_string.clear();
			}
			else
			{
				element_string.push_back(ch);
			}
		}
		else
		{
			element_string.push_back(ch);
		}
	}
	element_string_container.push_back(element_string);



	std::size_t element_count;


	element_count = element_string_container.size();
	if (6u == element_count)
	{
		cca_csv_element* e;
		
		
		e = new cca_csv_element();

		e->_filename        = element_string_container[0];
		e->_funcname        = element_string_container[1];
		e->_line_number     = atoi(element_string_container[2].c_str());
		e->_column_number   = atoi(element_string_container[3].c_str());
		e->_frequency_count = atoi(element_string_container[4].c_str());
		e->_comment         = element_string_container[5];

		_csv_element_container.push_back(e);
	}
	else
	{
		printf("error: csv line parsing \n");
		puts(csv_line.c_str());
	}
}

void cca::make_source_file_container(void)
{
	std::vector<cca_csv_element*>::iterator i;
	
	cca_csv_element* e;

	cca_source_file* source_file;
	cca_source_line* source_line;
	cca_source_function* source_function;


	for (i = _csv_element_container.begin();
		i != _csv_element_container.end();
		i++
		)
	{
		//-------------------------------------------------------------------
		e = *i;


		//-------------------------------------------------------------------
		source_file = _source_file_container[e->_filename];
		if (nullptr == source_file)
		{
			source_file = new cca_source_file();

			_source_file_container[e->_filename] = source_file;
		}


		//-------------------------------------------------------------------
		if (!source_file->_filename.empty())
		{
			assert(source_file->_filename == e->_filename);
		}
		source_file->_filename = e->_filename;



		//-------------------------------------------------------------------
		source_line = source_file->_line_container[e->_line_number];
		if (nullptr == source_line)
		{
			source_line = new cca_source_line();
			
			source_file->_line_container[e->_line_number] = source_line;
		}

		if (source_line->_line_number!=0)
		{
			assert(source_line->_line_number == e->_line_number);
		}
		source_line->_line_number = e->_line_number;

		source_line->_element_container.push_back(e);



		//-------------------------------------------------------------------
		source_function = source_file->_function_container[e->_funcname];
		if (nullptr == source_function)
		{
			source_function = new cca_source_function();

			source_file->_function_container[e->_funcname] = source_function;
		}

		if (!source_function->_filename.empty())
		{
			assert(source_function->_filename == e->_filename);
		}
		source_function->_filename = e->_filename;

		if (!source_function->_funcname.empty())
		{
			assert(source_function->_funcname == e->_funcname);
		}
		source_function->_funcname = e->_funcname;



		source_line = source_function->_line_container[e->_line_number];
		if (nullptr == source_line)
		{
			source_line = new cca_source_line();

			source_function->_line_container[e->_line_number] = source_line;
		}

		if (source_line->_line_number != 0)
		{
			assert(source_line->_line_number == e->_line_number);
		}
		source_line->_line_number = e->_line_number;



		source_line->_element_container.push_back(e);
	}
}

void cca::report_source_file_container(void)
{
	std::map<std::string, cca_source_file*>::iterator i;
	cca_source_file* e;


	for (i = _source_file_container.begin();
		i != _source_file_container.end();
		i++
		)
	{
		e = (*i).second;

		report_source_file(e);
	}
}

void cca::report_source_file(cca_source_file* e)
{
	std::string file_path;

	std::size_t count;
	std::size_t i; 
	std::uint8_t ch;


	count = e->_filename.length() - 1;
	for (i = 1; i < count; i++)
	{
		ch = e->_filename.at(i);
		file_path.push_back(ch);
	}


	file_loader fl;


	if (false == fl.load(file_path))
	{
		return;
	}


	std::uint8_t* file_pointer;
	std::int32_t file_size;


	file_size = fl.get_size();
	file_pointer = fl.get_pointer();

	if (nullptr != file_pointer)
	{
		report_source_file_coverage(e, file_path);
		report_source_file_function_coverage(e, file_path);
		report_source_file_contents(e, file_path, file_pointer, file_size);
	}
}

void cca::report_source_file_coverage(cca_source_file* e, std::string& file_path)
{
	float coverage;


	coverage = e->get_coverage() * 100.0f;


	printf("============================================================================= \n");
	printf("# source file code coverage analaysis \n");
	printf("============================================================================= \n");

	printf("file path: %s\n", file_path.c_str());
	printf("coverage : %6.2f %%\n", coverage);
	printf("\n");
}

void cca::report_source_file_function_coverage(cca_source_file* e, std::string& file_path)
{
	std::size_t function_count;
	std::map<std::string, cca_source_function*>::iterator i;
	cca_source_function* ef;
	float coverage;


	function_count = e->_function_container.size();

	printf("[function coverage] \n");
	printf("count : %d \n", function_count);
	printf("----------+------------------------------------------------------------------ \n");
	printf(" coverage | name \n");
	printf("----------+------------------------------------------------------------------ \n");

	for (i = e->_function_container.begin();
		i != e->_function_container.end();
		i++
		)
	{
		ef = (*i).second;
		
		coverage = ef->get_coverage() * 100.0f;

		printf(" %6.2f %% | %s\n", coverage, ef->_funcname.c_str());
	}
	printf("----------+------------------------------------------------------------------ \n");
	printf("\n");
}

void cca::report_source_file_contents (cca_source_file* e, std::string& file_path, std::uint8_t* file_pointer, std::int32_t file_size)
{
	std::vector<std::string> line_container;

	std::string line_string;

	std::int32_t count;
	std::int32_t i;
	std::uint8_t ch;


	count = file_size;
	for (i = 0; i < count; i++)
	{
		ch = *(file_pointer + i);
		if (ch == '\r')
		{

		}
		else if (ch == '\n')
		{
			line_container.push_back(line_string);
			line_string.clear();
		}
		else
		{
			line_string.push_back(ch);
		}
	}


	printf("[line coverage] \n");
	printf("-------+-----+------+-------------------------------------------------------- \n");
	printf(" freq  | cov | line | source \n");
	printf("-------+-----+------+-------------------------------------------------------- \n");


	std::size_t line_count;
	std::size_t line_i;


	line_count = line_container.size();
	for (line_i = 0u; line_i < line_count; line_i++)
	{
		report_source_file_contents_line(e, file_path, line_i+1, line_container[line_i]);
	}

	printf("-------+-----+------+-------------------------------------------------------- \n");

	printf("\n");
	printf("\n");
	printf("\n");
}

void cca::report_source_file_contents_line (cca_source_file* e, std::string& file_path, std::size_t line_number, std::string& line_string)
{
	cca_source_line* source_line;
	float coverage;
	std::uint32_t frequency;

	const char* line_string_pointer;
	std::size_t line_string_size;

	static const std::uint8_t text_bom_utf8[3] = {0xEF, 0xBB, 0xBF};
	

	line_string_size = line_string.length();
	line_string_pointer = line_string.c_str();
	if (line_string_size > 3u)
	{
		if (0 == memcmp(line_string_pointer, text_bom_utf8, 3))
		{
			line_string_pointer = line_string_pointer + 3;
		}
	}

	source_line = e->_line_container[line_number];
	if (nullptr != source_line)
	{
		coverage = source_line->get_coverage();
		frequency = source_line->get_frequency();

		if (1.0f == coverage)
		{
			printf("%6u | %.1f | %4d |", frequency, coverage, line_number);
			puts(line_string_pointer);
		}
		else
		{
			printf("%6u | %.1f | %4d |", frequency, coverage, line_number);
			puts(line_string_pointer);
		}
	}
	else
	{
		printf("       |     | %4d |", line_number);
		puts(line_string_pointer);
	}
//	printf("\n");
}

//===========================================================================
int main(/*int argc, char* argv[]*/)
{
	std::string cca_csv_filename = "D:/prj/hcpu/hcpu-A-002/hcpu/Debug/application.csv";
//	std::string cca_csv_filename = "application.csv";
//	std::string cca_csv_filename;

//	if (argc > 2)
	{
		cca instance;

//		cca_csv_filename = argv[1];

		instance.load_from_file(cca_csv_filename);
		instance.report_source_file_container();
		instance.clean();
	}

	return 0;
}
