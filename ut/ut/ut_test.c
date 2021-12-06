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
void ut_testrunner_case_exception(void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);


	ut_println("# TEST EXCEPTION");
	ut_printfln("  TESTSUITE : %s", ctx->suite->name);

	if (ut_nullptr!=ctx->suite_case)
	{
		ut_printfln("  TESTCASE  : %s", ctx->suite_case->test->name);

		ctx->suite_case->result.exception++;
	}
}

void ut_testrunner_assert_condition(
	ut_bool_t condition,
	const ut_char_t* expression,
	const ut_char_t* file,
	const ut_uint_t  line,
	const ut_char_t* function,
	void* context)
{
	ut_testcontext_t* ctx;


	ctx = ut_testcontext_get(context);
	if (condition)
	{
		if (ctx->suite_case)
		{
			ctx->suite_case->result.success++;
		}
	}
	else
	{
		if (ctx->suite_case)
		{
			ctx->suite_case->result.fail++;
		}

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
}

/*=========================================================================*/
void ut_testrunner_print_report(ut_testsuite_t* suite)
{
#if 0
	//-----------------------------------------------------------------------
	//	ut_println("#############################################################################");
	//	ut_println("*****************************************************************************");
	//	ut_println("=============================================================================");
	//	ut_println("-----------------------------------------------------------------------------");


	ut_print_endline();
	ut_print_endline();
	ut_print_endline();


	ut_println("#############################################################################");

	ut_print_endline();

	ut_print("UT ");
	ut_printf("%s ", UT_VERSION_STRING);
	ut_print_endline();

	ut_print_endline();

	ut_println("#############################################################################");


	ut_print_endline();
	ut_print_endline();
	ut_print_endline();
#endif



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


	//-----------------------------------------------------------------------
	ut_testsuite_case_t* current;


	//-----------------------------------------------------------------------
	const ut_char_t* assertion;

	const ut_char_t* assertion_success   = "[ OK   ]";
	const ut_char_t* assertion_fail      = "[ FAIL ]";
	const ut_char_t* assertion_exception = "[ HALT ]";
	const ut_char_t* assertion_blank     = "[      ]";

	//-----------------------------------------------------------------------
	const ut_char_t* name;
	const ut_char_t* description;
	const ut_char_t* spliter;

	const ut_char_t* blank = " ";
	const ut_char_t* colon = ":";

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


	//-----------------------------------------------------------------------
	ut_print_endline();

	ut_println("---------+---------------+-------+-------+-------+---------------------------");
	ut_println(" RESULT  | RUNTIME       | OK    | FAIL  | HALT  | TESTCASE");
	ut_println("---------+---------------+-------+-------+-------+---------------------------");


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


		//-------------------------------------------------------------------
		ut_printfln("%s | %3u.%09u | %5u | %5u | %5u | [%s] %s",
			assertion,

			runtime.second,
			runtime.nanosecond,

			current->result.success,
			current->result.fail,
			current->result.exception,

			name,
			description
		);


		//-------------------------------------------------------------------
		current++;
	}


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
}

void ut_testrunner_print_suite_head(ut_testcontext_t* context)
{
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
}

void ut_testrunner_print_suite_tail(ut_testcontext_t* context)
{
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
}

void ut_testrunner_print_suite_case_head(ut_testcontext_t* context)
{
	ut_println("-----------------------------------------------------------------------------");

	ut_printfln("# [%s] TESTCASE BEGIN ",
		context->suite_case->test->name
	);

	if (ut_nullptr != context->suite_case->test->description)
	{
		ut_print("  :");
		ut_println(context->suite_case->test->description);
	}
}

void ut_testrunner_print_suite_case_tail(ut_testcontext_t* context)
{
	ut_printfln("# [%s] TESTCASE END",
		context->suite_case->test->name
	);

	ut_print_endline();
}

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
	ut_testrunner_print_suite_case_head(&context);


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
		ut_testrunner_case_exception(&context);
	}
#endif


	//-----------------------------------------------------------------------
	if (ut_nullptr != element->test->fixture.teardown)
	{
		element->test->fixture.teardown(&context);
	}


	//-----------------------------------------------------------------------
	ut_testrunner_print_suite_case_tail(&context);
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

void ut_testrunner (ut_testsuite_t* suite, void* param)
{
	//-----------------------------------------------------------------------
	ut_testcontext_t context;


	context.suite = suite;
	context.suite_case = ut_nullptr;
	context.param = param;


	//-----------------------------------------------------------------------
	ut_testrunner_print_suite_head(&context);


	//-----------------------------------------------------------------------
	if (ut_nullptr != suite->fixture.setup)
	{
		suite->fixture.setup(&context);
	}


	ut_testrunner_suite_case_collection (suite, param);


	if (ut_nullptr != suite->fixture.teardown)
	{
		suite->fixture.teardown(&context);
	}


	//-----------------------------------------------------------------------
	ut_testrunner_print_suite_tail(&context);


	//-----------------------------------------------------------------------
	ut_testrunner_print_report(suite);
}




