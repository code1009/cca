// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com



/***************************************************************************/
#include "ut/ut.h"

#include "ut_test_1/ut_test_1.h"
#include "ut_test_2/ut_test_2.hpp"
#include "ut_test_3/ut_test_my_app.h"

#include <sstream>
#include <iostream>


const char* _rawstring=
R"__rawstring__(	동해물과 백두산이 마르고 닳도록
하느님이 보우하사 우리나라만세
"따옴표"
\역슬래쉬
바로 됩니다.
)__rawstring__";
	


/***************************************************************************/
int main()
{
	// 릴리즈모드 컴파일 후 실행파일을 trojan / Win.Generic.C4516440 바이러스로
	// 잘못 탐지하는 것을 막기 위해서 std::out 사용
	std::cout << "Hello World!\n";


	std::ostringstream _oss;
	_oss << _rawstring;
	std::cout << _oss.str();


	ut_rt_initialize();

	ut_test_1();
	ut_test_2();
	ut_test_my_app();

	ut_rt_uninitialize();

	return 0;
}
