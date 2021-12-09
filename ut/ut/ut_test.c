// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com



/* ==========================================================================
**
** ut_testrunner.c
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
#include "ut.h"





/***************************************************************************/
/* 테스트 */
/***************************************************************************/
void ut_test_print(const ut_char_t* name)
{
	//-----------------------------------------------------------------------
	ut_print_endline();
	ut_println("#############################################################################");
	ut_print_endline();
	ut_printfln("[%s]", name);
	ut_print_endline();
	ut_println("#############################################################################");
	ut_print_endline();
}



#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
/***************************************************************************/
/* 테스트리포트-작성자 */
/***************************************************************************/
void ut_testreport_writer_xml_begin(void* param)
{
	ut_println("<?xml version=\"1.0\" standalone=\"yes\"?>");
	ut_print_endline();
	ut_println("<report>");
	ut_print_endline();
}

void ut_testreport_writer_xml_end(void* param, ut_testreport_summary_t* summary)
{
	//-----------------------------------------------------------------------
	ut_uint_t  total_number;
	ut_uint_t  total_count;
	ut_float_t total_percent;


	//-----------------------------------------------------------------------
	total_number = summary->assertion_success;
	total_count = summary->assertion_success + summary->assertion_fail + summary->assertion_exception;
	if (total_count > 0u)
	{
		total_percent = total_number * 100.0f / total_count;
	}
	else
	{
		total_percent = 0.0f;
	}


	//-----------------------------------------------------------------------
	ut_println ("  <summary ");
	ut_printfln("   count=\"%u\" ", summary->count);
	ut_printfln("   testsuite_runtime=\"%u.%09u\" ", summary->runtime.second, summary->runtime.nanosecond);
	ut_printfln("   testsuite_success=\"%.2f\" "   , total_percent);
	ut_printfln("   testcase_count=\"%u\" "        , summary->case_count);
	ut_printfln("   testcase_success=\"%u\" "      , summary->case_success);
	ut_printfln("   testcase_fail=\"%u\" "         , summary->case_fail);
	ut_printfln("   testcase_halt=\"%u\" "         , summary->case_exception);
	ut_printfln("   testassert_success=\"%u\" "    , summary->assertion_success);
	ut_printfln("   testassert_fail=\"%u\" "       , summary->assertion_fail);
	ut_printfln("   testassert_halt=\"%u\" "       , summary->assertion_exception);
	ut_println ("   />");


	//-----------------------------------------------------------------------
	ut_print_endline();
	ut_println("</report>");
	ut_print_endline();
}

void ut_testreport_writer_xml_exception(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	ut_println("     ]]>");
	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_println ("      <exception ");
	ut_printfln("       suite=\"%s\" ", ctx->suite->name);
	if (ut_nullptr != ctx->suite_case->test->name)
	{
		ut_printfln("       case=\"%s\" ", ctx->suite_case->test->name);
	}
	ut_println("       />");


	//-----------------------------------------------------------------------
	ut_print_endline();
	ut_println("    <![CDATA[");
}

void ut_testreport_writer_xml_assert_condition(void* context,
	ut_bool_t condition,
	const ut_char_t* expression,
	const ut_char_t* file,
	const ut_uint_t  line,
	const ut_char_t* function)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	if (!condition)
	{
		//-----------------------------------------------------------------------
		ut_println("     ]]>");
		ut_print_endline();


		//-----------------------------------------------------------------------
		ut_println ("      <assertion status=\"fail\" ");
		ut_printfln("       suite=\"%s\" ", ctx->suite->name);
		if (ut_nullptr != ctx->suite_case->test->name)
		{
			ut_printfln("       case=\"%s\" ", ctx->suite_case->test->name);
		}
		ut_printfln("       file=\"%s\" ", file);
		ut_printfln("       line=\"%u\" ", line);
		ut_printfln("       function=\"%s\" ", function);
		ut_println ("       />");


		//-----------------------------------------------------------------------
		ut_print_endline();
		ut_println("    <![CDATA[");
	}
}

void ut_testreport_writer_xml_suite_begin(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	ut_println ("  <suite ");
	ut_printfln("   name=\"%s\" ", ctx->suite->name);
	if (ut_nullptr != ctx->suite->description)
	{
		ut_printfln("   description=\"%s\" ", ctx->suite->description);
	}
	ut_println("   >");
	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_println("    <![CDATA[");
}

void ut_testreport_writer_xml_suite_end(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
}

void ut_testreport_writer_xml_suite_case_begin(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	ut_println ("     ]]>");
	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_println ("    <case ");
	ut_printfln("     name=\"%s\" ", ctx->suite_case->test->name);
	if (ut_nullptr != ctx->suite_case->test->description)
	{
		ut_printfln("     description=\"%s\" ", ctx->suite_case->test->description);
	}
	ut_println("     >");


	//-----------------------------------------------------------------------
	ut_print_endline();
	ut_println("    <![CDATA[");
}

void ut_testreport_writer_xml_suite_case_end(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	ut_println("     ]]>");
	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_println("    </case>");
	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_println("    <![CDATA[");
}

void ut_testreport_writer_xml_suite_result_begin(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	ut_println("     ]]>");
	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_println("  </suite>");
	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_println ("  <suiteresult ");
	ut_printfln("   name=\"%s\" ", ctx->suite->name);
	if (ut_nullptr != ctx->suite->description)
	{
		ut_printfln("   description=\"%s\" ", ctx->suite->description);
	}
	ut_println ("   >");
}

void ut_testreport_writer_xml_suite_result_end(void* context, ut_testreport_summary_t* summary)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------


	//-----------------------------------------------------------------------
	ut_uint_t  total_number;
	ut_uint_t  total_count;
	ut_float_t total_percent;


	//-----------------------------------------------------------------------
	total_number = summary->assertion_success;
	total_count = summary->assertion_success + summary->assertion_fail + summary->assertion_exception;
	if (total_count > 0u)
	{
		total_percent = total_number * 100.0f / total_count;
	}
	else
	{
		total_percent = 0.0f;
	}


	//-----------------------------------------------------------------------
	ut_println ("    <summary ");
	ut_printfln("     testsuite_runtime=\"%u.%09u\" ", summary->runtime.second, summary->runtime.nanosecond);
	ut_printfln("     testsuite_success=\"%.2f\" "   , total_percent);
	ut_printfln("     testcase_count=\"%u\" "        , summary->case_count);
	ut_printfln("     testcase_success=\"%u\" "      , summary->case_success);
	ut_printfln("     testcase_fail=\"%u\" "         , summary->case_fail);
	ut_printfln("     testcase_halt=\"%u\" "         , summary->case_exception);
	ut_printfln("     testassert_success=\"%u\" "    , summary->assertion_success);
	ut_printfln("     testassert_fail=\"%u\" "       , summary->assertion_fail);
	ut_printfln("     testassert_halt=\"%u\" "       , summary->assertion_exception);
	ut_println ("     />");


	//-----------------------------------------------------------------------
	ut_println("  </suiteresult>");


	//-----------------------------------------------------------------------
	ut_print_endline();
	ut_print_endline();
	ut_print_endline();
}

void ut_testreport_writer_xml_suite_result_case(void* context,
	ut_int_t assertion,
	ut_timespec_t* runtime)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	const ut_char_t* assertion_string;


	switch (assertion)
	{
	case  0: assertion_string = ""; break;
	case  1: assertion_string = "OK"; break;
	case -1: assertion_string = "FAIL"; break;
	case -2: assertion_string = "HALT"; break;
	default: assertion_string = " "; break;
		break;
	}


	//-----------------------------------------------------------------------
	const ut_char_t* name;
	const ut_char_t* description;


	name = ctx->suite_case->test->name;
	description = ctx->suite_case->test->description;
	if (ut_nullptr == description)
	{
		description = " ";
	}


	//-----------------------------------------------------------------------
	ut_println ("    <case ");
	ut_printfln("     name=\"%s\" "        , name);
	ut_printfln("     description=\"%s\" " , description);
	ut_printfln("     assertion=\"%s\" "   , assertion_string);
	ut_printfln("     runtime=\"%u.%09u\" ", runtime->second, runtime->nanosecond);
	ut_printfln("     success=\"%u\" "     , ctx->suite_case->result.success);
	ut_printfln("     fail=\"%u\" "        , ctx->suite_case->result.fail);
	ut_printfln("     exception=\"%u\" "   , ctx->suite_case->result.exception);
	ut_println ("     />");
}

/*=========================================================================*/
UT_GVAR_IMPL ut_testreport_writer_t _ut_testreport_writer_xml =
{
	ut_testreport_writer_xml_begin,
	ut_testreport_writer_xml_end,
	ut_testreport_writer_xml_exception,
	ut_testreport_writer_xml_assert_condition,
	ut_testreport_writer_xml_suite_begin,
	ut_testreport_writer_xml_suite_end,
	ut_testreport_writer_xml_suite_case_begin,
	ut_testreport_writer_xml_suite_case_end,
	ut_testreport_writer_xml_suite_result_begin,
	ut_testreport_writer_xml_suite_result_end,
	ut_testreport_writer_xml_suite_result_case
};



/***************************************************************************/
void ut_testreport_writer_default_begin(void* param)
{
	ut_print_endline();


	ut_println("#############################################################################");

	ut_print_endline();

	ut_print("UT ");
	ut_printf("%s ", UT_VERSION_STRING);
	ut_print_endline();

	ut_print_endline();

	ut_println("#############################################################################");


	ut_print_endline();
}

void ut_testreport_writer_default_end(void* param, ut_testreport_summary_t* summary)
{
	//-----------------------------------------------------------------------
	ut_uint_t  total_number;
	ut_uint_t  total_count;
	ut_float_t total_percent;


	//-----------------------------------------------------------------------
	total_number = summary->assertion_success;
	total_count = summary->assertion_success + summary->assertion_fail + summary->assertion_exception;
	if (total_count > 0u)
	{
		total_percent = total_number * 100.0f / total_count;
	}
	else
	{
		total_percent = 0.0f;
	}


	//-----------------------------------------------------------------------
	ut_print_endline();
	ut_println("#############################################################################");
	ut_print_endline();
	ut_println("TESTREPORT SUMMARY");
	ut_print_endline();
	ut_println("#############################################################################");
	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_printfln("TOTAL TESTSUITE COUNT    : %u", summary->count);
	ut_printfln("TOTAL TESTSUITE RUNTIME  : %u.%09u", summary->runtime.second, summary->runtime.nanosecond);
	ut_printfln("TOTAL TESTSUITE SUCCESS  : %.2f %% (%u/%u)",
		total_percent,
		total_number,
		total_count
	);

	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_printfln("TOTAL TESTCASE COUNT     : %u", summary->case_count);
	ut_printfln("TOTAL TESTCASE SUCCESS   : %u", summary->case_success);
	ut_printfln("TOTAL TESTCASE FAIL      : %u", summary->case_fail);
	ut_printfln("TOTAL TESTCASE HALT      : %u", summary->case_exception);

	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_printfln("TOTAL TESTASSERT SUCCESS : %u", summary->assertion_success);
	ut_printfln("TOTAL TESTASSERT FAIL    : %u", summary->assertion_fail);
	ut_printfln("TOTAL TESTASSERT HALT    : %u", summary->assertion_exception);

	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_print_endline();
	ut_print_endline();
	ut_print_endline();
}

void ut_testreport_writer_default_exception(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	ut_println("# TEST EXCEPTION");
	ut_printfln("  TESTSUITE : %s", ctx->suite->name);

	if (ut_nullptr != ctx->suite_case)
	{
		ut_printfln("  TESTCASE  : %s", ctx->suite_case->test->name);
	}
}

void ut_testreport_writer_default_assert_condition(void* context,
	ut_bool_t condition,
	const ut_char_t* expression,
	const ut_char_t* file,
	const ut_uint_t  line,
	const ut_char_t* function)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	if (!condition)
	{
		ut_println("# TEST ASSERTION FAILED");
		ut_printfln("  TESTSUITE : %s", ctx->suite->name);

		if (ut_nullptr != ctx->suite_case)
		{
			ut_printfln("  TESTCASE  : %s", ctx->suite_case->test->name);
		}

		ut_printfln("  FILE      : %s", file);
		ut_printfln("  LINE      : %u", line);
		ut_printfln("  FUNCTION  : %s", function);
		ut_printfln("  EXPRESSION: %s", expression);
	}
}

void ut_testreport_writer_default_suite_begin(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	ut_println("*****************************************************************************");
	ut_printfln("# [%s] TESTSUITE BEGIN",
		ctx->suite->name
	);

	if (ut_nullptr != ctx->suite->description)
	{
		ut_print("  :");
		ut_println(ctx->suite->description);
	}


	//-----------------------------------------------------------------------
	ut_timespec_t t;


	ut_get_clocktime(&t);
	ut_printfln("  time = %u.%09u sec", t.second, t.nanosecond);


	//-----------------------------------------------------------------------
	ut_println("*****************************************************************************");
}

void ut_testreport_writer_default_suite_end(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	ut_println("*****************************************************************************");


	//-----------------------------------------------------------------------
	ut_printfln("# [%s] TESTSUITE END ",
		ctx->suite->name
	);


	//-----------------------------------------------------------------------
	ut_timespec_t t;


	ut_get_clocktime(&t);
	ut_printfln("  time = %u.%09u sec", t.second, t.nanosecond);


	//-----------------------------------------------------------------------
	ut_print_endline();
}

void ut_testreport_writer_default_suite_case_begin(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	ut_println("-----------------------------------------------------------------------------");

	ut_printfln("# [%s] TESTCASE BEGIN ",
		ctx->suite_case->test->name
	);

	if (ut_nullptr != ctx->suite_case->test->description)
	{
		ut_print("  :");
		ut_println(ctx->suite_case->test->description);
	}
}

void ut_testreport_writer_default_suite_case_end(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	ut_printfln("# [%s] TESTCASE END",
		ctx->suite_case->test->name
	);

	ut_print_endline();
}

void ut_testreport_writer_default_suite_result_begin(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	ut_println("*****************************************************************************");
	ut_printfln("# [%s] TESTSUITE RESULT",
		ctx->suite->name
	);

	if (ut_nullptr != ctx->suite->description)
	{
		ut_print("  :");
		ut_println(ctx->suite->description);
	}


	//-----------------------------------------------------------------------
	ut_print_endline();

	ut_println("---------+---------------+-------+-------+-------+---------------------------");
	ut_println(" RESULT  | RUNTIME       | OK    | FAIL  | HALT  | TESTCASE");
	ut_println("---------+---------------+-------+-------+-------+---------------------------");
}

void ut_testreport_writer_default_suite_result_end(void* context, ut_testreport_summary_t* summary)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	ut_println("---------+---------------+-------+-------+-------+---------------------------");
	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_uint_t  total_number;
	ut_uint_t  total_count;
	ut_float_t total_percent;


	//-----------------------------------------------------------------------
	total_number = summary->assertion_success;
	total_count = summary->assertion_success + summary->assertion_fail + summary->assertion_exception;
	if (total_count > 0u)
	{
		total_percent = total_number * 100.0f / total_count;
	}
	else
	{
		total_percent = 0.0f;
	}


	//-----------------------------------------------------------------------
	ut_printfln("TESTSUITE RUNTIME  : %u.%09u", summary->runtime.second, summary->runtime.nanosecond);
	ut_printfln("TESTSUITE SUCCESS  : %.2f %% (%u/%u)",
		total_percent,
		total_number,
		total_count
	);

	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_printfln("TESTCASE COUNT     : %u", summary->case_count);
	ut_printfln("TESTCASE SUCCESS   : %u", summary->case_success);
	ut_printfln("TESTCASE FAIL      : %u", summary->case_fail);
	ut_printfln("TESTCASE HALT      : %u", summary->case_exception);

	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_printfln("TESTASSERT SUCCESS : %u", summary->assertion_success);
	ut_printfln("TESTASSERT FAIL    : %u", summary->assertion_fail);
	ut_printfln("TESTASSERT HALT    : %u", summary->assertion_exception);

	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_print_endline();
	ut_print_endline();
	ut_print_endline();
}

void ut_testreport_writer_default_suite_result_case(void* context,
	ut_int_t assertion,
	ut_timespec_t* runtime)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	const ut_char_t* assertion_string;


	switch (assertion)
	{
	case  0: assertion_string = " "   ; break;
	case  1: assertion_string = "OK"  ; break;
	case -1: assertion_string = "FAIL"; break;
	case -2: assertion_string = "HALT"; break;
	default: assertion_string = " "   ; break;
		break;
	}


	//-----------------------------------------------------------------------
	const ut_char_t* name;
	const ut_char_t* description;


	name = ctx->suite_case->test->name;
	description = ctx->suite_case->test->description;
	if (ut_nullptr == description)
	{
		description = " ";
	}


	//-----------------------------------------------------------------------
	ut_printfln("[ %-4s ] | %3u.%09u | %5u | %5u | %5u | [%s] %s",
		assertion_string,

		runtime->second,
		runtime->nanosecond,

		ctx->suite_case->result.success,
		ctx->suite_case->result.fail,
		ctx->suite_case->result.exception,

		name,
		description
	);
}

/*=========================================================================*/
UT_GVAR_IMPL ut_testreport_writer_t _ut_testreport_writer_default =
{
	ut_testreport_writer_default_begin,
	ut_testreport_writer_default_end,
	ut_testreport_writer_default_exception,
	ut_testreport_writer_default_assert_condition,
	ut_testreport_writer_default_suite_begin,
	ut_testreport_writer_default_suite_end,
	ut_testreport_writer_default_suite_case_begin,
	ut_testreport_writer_default_suite_case_end,
	ut_testreport_writer_default_suite_result_begin,
	ut_testreport_writer_default_suite_result_end,
	ut_testreport_writer_default_suite_result_case
};
#endif




/***************************************************************************/
/* 테스트리포트 */
/***************************************************************************/
void ut_testreport_begin(ut_testreport_t* report, void* param)
{
	//-----------------------------------------------------------------------
	report->summary.assertion_success = 0u;
	report->summary.assertion_fail = 0u;
	report->summary.assertion_exception = 0u;
	report->summary.case_success = 0u;
	report->summary.case_fail = 0u;
	report->summary.case_exception = 0u;
	report->summary.case_count = 0u;

	report->summary.runtime.second = 0u;
	report->summary.runtime.nanosecond = 0u;

	report->summary.count = 0u;


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
	//-----------------------------------------------------------------------
	ut_testreport_writer_t* w;


	w = report->writer;


	//-----------------------------------------------------------------------
	if (ut_nullptr != w)
	{
		if (ut_nullptr != w->begin)
		{
			w->begin(param);
		}
	}
#endif


	//-----------------------------------------------------------------------
#if 0
	ut_println("#############################################################################");
	ut_println("*****************************************************************************");
	ut_println("=============================================================================");
	ut_println("-----------------------------------------------------------------------------");
#endif


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
	//-----------------------------------------------------------------------
	ut_print_endline();


	ut_println("#############################################################################");

	ut_print_endline();

	ut_print("UT ");
	ut_printf("%s ", UT_VERSION_STRING);
	ut_print_endline();

	ut_print_endline();

	ut_println("#############################################################################");


	ut_print_endline();
#endif
}

void ut_testreport_end(ut_testreport_t* report, void* param)
{
#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
	//-----------------------------------------------------------------------
	ut_testreport_writer_t* w;


	w = report->writer;


	//-----------------------------------------------------------------------
	if (ut_nullptr != w)
	{
		if (ut_nullptr != w->end)
		{
			w->end(param, &report->summary);
		}
	}
#endif


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
	//-----------------------------------------------------------------------
	ut_uint_t  total_number;
	ut_uint_t  total_count;
	ut_float_t total_percent;


	//-----------------------------------------------------------------------
	total_number = report->summary.assertion_success;
	total_count = report->summary.assertion_success + report->summary.assertion_fail + report->summary.assertion_exception;
	if (total_count > 0u)
	{
		total_percent = total_number * 100.0f / total_count;
	}
	else
	{
		total_percent = 0.0f;
	}


	//-----------------------------------------------------------------------
	ut_print_endline();
	ut_println("#############################################################################");
	ut_print_endline();
	ut_println("TESTREPORT SUMMARY");
	ut_print_endline();
	ut_println("#############################################################################");
	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_printfln("TOTAL TESTSUITE COUNT    : %u", report->summary.count);
	ut_printfln("TOTAL TESTSUITE RUNTIME  : %u.%09u", report->summary.runtime.second, report->summary.runtime.nanosecond);
	ut_printfln("TOTAL TESTSUITE SUCCESS  : %.2f %% (%u/%u)",
		total_percent,
		total_number,
		total_count
	);

	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_printfln("TOTAL TESTCASE COUNT     : %u", report->summary.case_count);
	ut_printfln("TOTAL TESTCASE SUCCESS   : %u", report->summary.case_success);
	ut_printfln("TOTAL TESTCASE FAIL      : %u", report->summary.case_fail);
	ut_printfln("TOTAL TESTCASE HALT      : %u", report->summary.case_exception);

	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_printfln("TOTAL TESTASSERT SUCCESS : %u", report->summary.assertion_success);
	ut_printfln("TOTAL TESTASSERT FAIL    : %u", report->summary.assertion_fail);
	ut_printfln("TOTAL TESTASSERT HALT    : %u", report->summary.assertion_exception);

	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_print_endline();
	ut_print_endline();
	ut_print_endline();
#endif
}





/***************************************************************************/
/* 테스트리절트 */
/***************************************************************************/
void ut_testresult_reset(ut_testresult_t* result)
{
	result->fail = 0u;
	result->success = 0u;
	result->exception = 0u;

	result->runtime.begin.second = 0u;
	result->runtime.begin.nanosecond = 0u;
	result->runtime.end.second = 0u;
	result->runtime.end.nanosecond = 0u;
}





/***************************************************************************/
/* 테스트러너 */
/***************************************************************************/
/*=========================================================================*/
ut_uint_t ut_testrunner_get_suite_case_count(ut_testsuite_t* suite)
{
	//-----------------------------------------------------------------------
	ut_uint_t count;


	count = 0u;


	//-----------------------------------------------------------------------
	ut_testsuite_case_t* current;


	current = suite->test;
	while (ut_nullptr != current->test)
	{
		current++;

		count++;
	}

	return count;
}

/*=========================================================================*/
void ut_testrunner_exception(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	if (ut_nullptr != ctx->suite_case)
	{
		ctx->suite_case->result.exception++;
	}


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
	//-----------------------------------------------------------------------
	ut_println("# TEST EXCEPTION");
	ut_printfln("  TESTSUITE : %s", ctx->suite->name);

	if (ut_nullptr != ctx->suite_case)
	{
		ut_printfln("  TESTCASE  : %s", ctx->suite_case->test->name);
	}
#endif


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
	//-----------------------------------------------------------------------
	ut_testreport_writer_t* w;


	w = ut_nullptr;
	if (ut_nullptr != ctx->suite->report)
	{
		w = ctx->suite->report->writer;
	}
	else
	{
		w = &_ut_testreport_writer_default;
	}


	//-----------------------------------------------------------------------
	if (ut_nullptr != w)
	{
		if (ut_nullptr != w->exception)
		{
			w->exception(ctx);
		}
	}
#endif
}

void ut_testrunner_assert_condition(
	void* context,
	ut_bool_t condition,
	const ut_char_t* expression,
	const ut_char_t* file,
	const ut_uint_t  line,
	const ut_char_t* function
)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	//-----------------------------------------------------------------------
	if (!condition)
	{
		if (ut_nullptr != ctx->suite_case)
		{
			ctx->suite_case->result.fail++;
		}
	}
	else
	{
		if (ut_nullptr != ctx->suite_case)
		{
			ctx->suite_case->result.success++;
		}
	}


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
	//-----------------------------------------------------------------------
	if (!condition)
	{
		ut_println("# TEST ASSERTION FAILED");
		ut_printfln("  TESTSUITE : %s", ctx->suite->name);

		if (ctx->suite_case)
		{
			ut_printfln("  TESTCASE  : %s", ctx->suite_case->test->name);
		}

		ut_printfln("  FILE      : %s", file);
		ut_printfln("  LINE      : %u", line);
		ut_printfln("  FUNCTION  : %s", function);
		ut_printfln("  EXPRESSION: %s", expression);
	}
#endif


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
	//-----------------------------------------------------------------------
	ut_testreport_writer_t* w;


	w = ut_nullptr;
	if (ut_nullptr != ctx->suite->report)
	{
		w = ctx->suite->report->writer;
	}
	else
	{
		w = &_ut_testreport_writer_default;
	}


	//-----------------------------------------------------------------------
	if (ut_nullptr != w)
	{
		if (ut_nullptr != w->assert_condition)
		{
			w->assert_condition(ctx,
				condition,
				expression,
				file,
				line,
				function);
		}
	}
#endif
}

/*=========================================================================*/
void ut_testrunner_print_suite_result(ut_testcontext_t* context)
{
	//-----------------------------------------------------------------------
	ut_testsuite_t* suite;


	suite = context->suite;



#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
	//-----------------------------------------------------------------------
	ut_testreport_writer_t* w;


	w = ut_nullptr;
	if (ut_nullptr != context->suite->report)
	{
		w = context->suite->report->writer;
	}
	else
	{
		w = &_ut_testreport_writer_default;
	}


	//-----------------------------------------------------------------------
	if (ut_nullptr != w)
	{
		if (ut_nullptr != w->suite_result_begin)
		{
			w->suite_result_begin(context);
		}
	}
#endif


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
	//-----------------------------------------------------------------------
	ut_println("*****************************************************************************");
	ut_printfln("# [%s] TESTSUITE RESULT",
		suite->name
	);

	if (ut_nullptr != suite->description)
	{
		ut_print("  :");
		ut_println(suite->description);
	}
#endif


	//-----------------------------------------------------------------------
	ut_testsuite_case_t* current;


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
	//-----------------------------------------------------------------------
	const ut_char_t* assertion;

	const ut_char_t* assertion_success   = "OK";
	const ut_char_t* assertion_fail      = "FAIL";
	const ut_char_t* assertion_exception = "HALT";
	const ut_char_t* assertion_blank     = " ";

	//-----------------------------------------------------------------------
	const ut_char_t* name;
	const ut_char_t* description;
	const ut_char_t* spliter;

	const ut_char_t* blank = " ";
	const ut_char_t* colon = ":";
#endif


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
	//-----------------------------------------------------------------------
	ut_int_t assertion;

	const ut_int_t assertion_success = 1;
	const ut_int_t assertion_fail = -1;
	const ut_int_t assertion_exception = -2;
	const ut_int_t assertion_blank = 0;
#endif


	//-----------------------------------------------------------------------
	ut_timespec_t runtime;

	//-----------------------------------------------------------------------
	ut_timespec_t total_runtime;

	//-----------------------------------------------------------------------
	ut_uint_t     total_assertion_success;
	ut_uint_t     total_assertion_fail;
	ut_uint_t     total_assertion_exception;

	//-----------------------------------------------------------------------
	ut_uint_t     total_case_success;
	ut_uint_t     total_case_fail;
	ut_uint_t     total_case_exception;

	ut_uint_t     total_case_count;


	//-----------------------------------------------------------------------
	total_runtime.second = 0u;
	total_runtime.nanosecond = 0u;

	//-----------------------------------------------------------------------
	total_assertion_success = 0u;
	total_assertion_fail = 0u;
	total_assertion_exception = 0u;

	//-----------------------------------------------------------------------
	total_case_success = 0u;
	total_case_fail = 0u;
	total_case_exception = 0u;

	total_case_count = 0u;


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
	//-----------------------------------------------------------------------
	ut_print_endline();

	ut_println("---------+---------------+-------+-------+-------+---------------------------");
	ut_println(" RESULT  | RUNTIME       | OK    | FAIL  | HALT  | TESTCASE");
	ut_println("---------+---------------+-------+-------+-------+---------------------------");
#endif


	//-----------------------------------------------------------------------
	current = suite->test;
	while (ut_nullptr != current->test)
	{
		//-------------------------------------------------------------------
		total_case_count++;


		//-------------------------------------------------------------------
		ut_time_diff(&current->result.runtime.begin, &current->result.runtime.end, &runtime);
		ut_time_add(&total_runtime, &runtime, &total_runtime);


		//-------------------------------------------------------------------
		total_assertion_success += current->result.success;
		total_assertion_fail += current->result.fail;
		total_assertion_exception += current->result.exception;


		//-------------------------------------------------------------------
		if (current->result.exception > 0u)
		{
			assertion = assertion_exception;

			total_case_exception++;
		}
		else if (current->result.fail > 0u)
		{
			assertion = assertion_fail;

			total_case_fail++;
		}
		else if (current->result.success > 0u)
		{
			assertion = assertion_success;

			total_case_success++;
		}
		else
		{
			assertion = assertion_blank;
		}


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
		//-------------------------------------------------------------------
		name = current->test->name;
		description = current->test->description;
		if (ut_nullptr == description)
		{
			description = blank;
			spliter     = blank;
		}
		else
		{
			spliter = colon;
		}
#endif


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
		//-----------------------------------------------------------------------
		if (ut_nullptr != w)
		{
			if (ut_nullptr != w->suite_result_case)
			{
				ut_testcontext_t c;


				c.suite = context->suite;
				c.suite_case = current;
				c.param = context->param;

				w->suite_result_case(&c, assertion, &runtime);
			}
		}
#endif


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
		//-------------------------------------------------------------------
		ut_printfln("[ %-4s ] | %3u.%09u | %5u | %5u | %5u | [%s] %s",
			assertion,

			runtime.second,
			runtime.nanosecond,

			current->result.success,
			current->result.fail,
			current->result.exception,

			name,
			description
		);
#endif


		//-------------------------------------------------------------------
		current++;
	}


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
	//-----------------------------------------------------------------------
	if (ut_nullptr != w)
	{
		if (ut_nullptr != w->suite_result_case)
		{
			ut_testreport_summary_t summary;


			summary.assertion_success   = total_assertion_success  ;
			summary.assertion_fail      = total_assertion_fail     ;
			summary.assertion_exception = total_assertion_exception;
			summary.case_success        = total_case_success       ;
			summary.case_fail           = total_case_fail          ;
			summary.case_exception      = total_case_exception     ;
			summary.case_count          = total_case_count         ;

			summary.runtime.second = total_runtime.second;
			summary.runtime.nanosecond = total_runtime.nanosecond;

			summary.count = 1u;

			w->suite_result_end(context, &summary);
		}
	}
#endif


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
	//-----------------------------------------------------------------------
	ut_println("---------+---------------+-------+-------+-------+---------------------------");
	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_uint_t  total_number;
	ut_uint_t  total_count;
	ut_float_t total_percent;


	//-----------------------------------------------------------------------
	total_number = total_assertion_success;
	total_count = total_assertion_success + total_assertion_fail + total_assertion_exception;
	if (total_count > 0u)
	{
		total_percent = total_number * 100.0f / total_count;
	}
	else
	{
		total_percent = 0.0f;
	}


	//-----------------------------------------------------------------------
	ut_printfln("TESTSUITE RUNTIME  : %u.%09u", total_runtime.second, total_runtime.nanosecond);
	ut_printfln("TESTSUITE SUCCESS  : %.2f %% (%u/%u)",
		total_percent, 
		total_number,
		total_count
	);
	
	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_printfln("TESTCASE COUNT     : %u", total_case_count);
	ut_printfln("TESTCASE SUCCESS   : %u", total_case_success);
	ut_printfln("TESTCASE FAIL      : %u", total_case_fail);
	ut_printfln("TESTCASE HALT      : %u", total_case_exception);

	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_printfln("TESTASSERT SUCCESS : %u", total_assertion_success);
	ut_printfln("TESTASSERT FAIL    : %u", total_assertion_fail);
	ut_printfln("TESTASSERT HALT    : %u", total_assertion_exception);

	ut_print_endline();


	//-----------------------------------------------------------------------
	ut_print_endline();
	ut_print_endline();
	ut_print_endline();
#endif


	//-----------------------------------------------------------------------
	if (ut_nullptr!= suite->report)
	{
		suite->report->summary.assertion_success   += total_assertion_success  ;
		suite->report->summary.assertion_fail      += total_assertion_fail     ;
		suite->report->summary.assertion_exception += total_assertion_exception;
		suite->report->summary.case_success        += total_case_success       ;
		suite->report->summary.case_fail           += total_case_fail          ;
		suite->report->summary.case_exception      += total_case_exception     ;
		suite->report->summary.case_count          += total_case_count         ;
		ut_time_add(&suite->report->summary.runtime, &total_runtime, &suite->report->summary.runtime);
		suite->report->summary.count++;
	}
}

void ut_testrunner_print_suite_begin(ut_testcontext_t* context)
{
#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
	//-----------------------------------------------------------------------
	ut_testreport_writer_t* w;


	w = ut_nullptr;
	if (ut_nullptr != context->suite->report)
	{
		w = context->suite->report->writer;
	}
	else
	{
		w = &_ut_testreport_writer_default;
	}


	//-----------------------------------------------------------------------
	if (ut_nullptr != w)
	{
		if (ut_nullptr != w->suite_result_case)
		{
			w->suite_begin(context);
		}
	}
#endif


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
	//-----------------------------------------------------------------------
	ut_println("*****************************************************************************");
	ut_printfln("# [%s] TESTSUITE BEGIN",
		context->suite->name
	);

	if (ut_nullptr != context->suite->description)
	{
		ut_print("  :");
		ut_println(context->suite->description);
	}


	//-----------------------------------------------------------------------
	ut_timespec_t t;


	ut_get_clocktime(&t);
	ut_printfln("  time = %u.%09u sec", t.second, t.nanosecond);


	//-----------------------------------------------------------------------
	ut_println("*****************************************************************************");
#endif
}

void ut_testrunner_print_suite_end(ut_testcontext_t* context)
{
#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
	//-----------------------------------------------------------------------
	ut_testreport_writer_t* w;


	w = ut_nullptr;
	if (ut_nullptr != context->suite->report)
	{
		w = context->suite->report->writer;
	}
	else
	{
		w = &_ut_testreport_writer_default;
	}


	//-----------------------------------------------------------------------
	if (ut_nullptr != w)
	{
		if (ut_nullptr != w->suite_result_case)
		{
			w->suite_end(context);
		}
	}
#endif


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
	//-----------------------------------------------------------------------
	ut_println("*****************************************************************************");


	//-----------------------------------------------------------------------
	ut_printfln("# [%s] TESTSUITE END ",
		context->suite->name
	);


	//-----------------------------------------------------------------------
	ut_timespec_t t;


	ut_get_clocktime(&t);
	ut_printfln("  time = %u.%09u sec", t.second, t.nanosecond);


	//-----------------------------------------------------------------------
	ut_print_endline();
#endif
}

void ut_testrunner_print_suite_case_begin(ut_testcontext_t* context)
{
#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
	//-----------------------------------------------------------------------
	ut_testreport_writer_t* w;


	w = ut_nullptr;
	if (ut_nullptr != context->suite->report)
	{
		w = context->suite->report->writer;
	}
	else
	{
		w = &_ut_testreport_writer_default;
}


	//-----------------------------------------------------------------------
	if (ut_nullptr != w)
	{
		if (ut_nullptr != w->suite_result_case)
		{
			w->suite_case_begin(context);
		}
	}
#endif


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
	ut_println("-----------------------------------------------------------------------------");

	ut_printfln("# [%s] TESTCASE BEGIN ",
		context->suite_case->test->name
	);

	if (ut_nullptr != context->suite_case->test->description)
	{
		ut_print("  :");
		ut_println(context->suite_case->test->description);
	}
#endif
}

void ut_testrunner_print_suite_case_end(ut_testcontext_t* context)
{
#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
	//-----------------------------------------------------------------------
	ut_testreport_writer_t* w;


	w = ut_nullptr;
	if (ut_nullptr != context->suite->report)
	{
		w = context->suite->report->writer;
	}
	else
	{
		w = &_ut_testreport_writer_default;
	}


	//-----------------------------------------------------------------------
	if (ut_nullptr != w)
	{
		if (ut_nullptr != w->suite_result_case)
		{
			w->suite_case_end(context);
		}
	}
#endif


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==0)
	//-----------------------------------------------------------------------
	ut_printfln("# [%s] TESTCASE END",
		context->suite_case->test->name
	);

	ut_print_endline();
#endif
}

/*=========================================================================*/
void ut_testrunner_suite_case_element (ut_testsuite_t* suite, ut_testsuite_case_t* element, void* param)
{
	//-----------------------------------------------------------------------
	ut_testcontext_t context;


	context.suite = suite;
	context.suite_case = element;
	context.param = param;


	//-----------------------------------------------------------------------
#if 1
	ut_bool_t rv;
	ut_testcase_function_t run;


	run = element->test->run;
#endif


	//-----------------------------------------------------------------------
	ut_testrunner_print_suite_case_begin(&context);


	//-----------------------------------------------------------------------
	ut_testresult_reset(&element->result);


	//-----------------------------------------------------------------------
	if (ut_nullptr != element->test->fixture.setup)
	{
		element->test->fixture.setup(&context);
	}


	//-----------------------------------------------------------------------
	ut_get_clocktime(&element->result.runtime.begin);


	//-----------------------------------------------------------------------
#if 1
	rv = ut_rt_execute_testcase(run, &context);
#else
	element->test->run(context);
#endif


	//-----------------------------------------------------------------------
	ut_get_clocktime(&element->result.runtime.end);


	//-----------------------------------------------------------------------
#if 1
	if (ut_false == rv)
	{
		ut_testrunner_exception(&context);
	}
#endif


	//-----------------------------------------------------------------------
	if (ut_nullptr != element->test->fixture.teardown)
	{
		element->test->fixture.teardown(&context);
	}


	//-----------------------------------------------------------------------
	ut_testrunner_print_suite_case_end(&context);
}

void ut_testrunner_suite_case_collection(ut_testsuite_t* suite, void* param)
{
	ut_testsuite_case_t* current;


	current = suite->test;
	while (ut_nullptr!= current->test)
	{
		ut_testrunner_suite_case_element(suite, current, param);

		current++;
	}
}

/*=========================================================================*/
void ut_testrunner (ut_testsuite_t* suite, void* param, ut_testreport_t* report)
{
	//-----------------------------------------------------------------------
	suite->report = report;


	//-----------------------------------------------------------------------
	ut_testcontext_t context;


	context.suite = suite;
	context.suite_case = ut_nullptr;
	context.param = param;


	//-----------------------------------------------------------------------
	ut_testrunner_print_suite_begin(&context);


	//-----------------------------------------------------------------------
	if (ut_nullptr != suite->fixture.setup)
	{
		suite->fixture.setup(&context);
	}


	ut_testrunner_suite_case_collection(suite, param);


	if (ut_nullptr != suite->fixture.teardown)
	{
		suite->fixture.teardown(&context);
	}


	//-----------------------------------------------------------------------
	ut_testrunner_print_suite_end(&context);


	//-----------------------------------------------------------------------
	ut_testrunner_print_suite_result(&context);


	//-----------------------------------------------------------------------
	suite->report = ut_nullptr;
}


