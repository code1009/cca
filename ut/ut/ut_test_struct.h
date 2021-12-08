#ifndef ut_test_struct__h
#define ut_test_struct__h

/***************************************************************************/

/* ==========================================================================
**
** ut_test_struct.h
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
/* 테스트리포트-요약 */
/***************************************************************************/
typedef struct _ut_testreport_summary_t
{
	ut_uint_t     assertion_success;
	ut_uint_t     assertion_fail;
	ut_uint_t     assertion_exception;
	ut_uint_t     case_success;
	ut_uint_t     case_fail;
	ut_uint_t     case_exception;
	ut_uint_t     case_count;

	ut_timespec_t runtime;

	ut_uint_t     count;
}
ut_testreport_summary_t;

#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
/***************************************************************************/
/* 테스트리포트-작성자 */
/***************************************************************************/
UT_FUNC_DECL typedef void (*ut_testreport_writer_begin_function_t  ) (void* param);
UT_FUNC_DECL typedef void (*ut_testreport_writer_end_function_t    ) (void* param, ut_testreport_summary_t* summary);

UT_FUNC_DECL typedef void (*ut_testreport_writer_exception_function_t         ) (void* context);
UT_FUNC_DECL typedef void (*ut_testreport_writer_assert_condition_function_t  ) (
	void* context,
	ut_bool_t condition,
	const ut_char_t* expression,
	const ut_char_t* file,
	const ut_uint_t  line,
	const ut_char_t* function);

UT_FUNC_DECL typedef void (*ut_testreport_writer_suite_case_begin_function_t  ) (void* context);
UT_FUNC_DECL typedef void (*ut_testreport_writer_suite_case_end_function_t    ) (void* context);

UT_FUNC_DECL typedef void (*ut_testreport_writer_suite_begin_function_t       ) (void* context);
UT_FUNC_DECL typedef void (*ut_testreport_writer_suite_end_function_t         ) (void* context);

UT_FUNC_DECL typedef void (*ut_testreport_writer_suite_result_begin_function_t) (void* context);
UT_FUNC_DECL typedef void (*ut_testreport_writer_suite_result_end_function_t  ) (void* context, ut_testreport_summary_t* summary);
UT_FUNC_DECL typedef void (*ut_testreport_writer_suite_result_case_function_t ) (
	void* context,
	ut_int_t assertion,
	ut_timespec_t* runtime);

typedef struct _ut_testreport_writer_t
{
	ut_testreport_writer_begin_function_t              begin;
	ut_testreport_writer_end_function_t                end;
	ut_testreport_writer_exception_function_t          exception;
	ut_testreport_writer_assert_condition_function_t   assert_condition;
	ut_testreport_writer_suite_begin_function_t        suite_begin;
	ut_testreport_writer_suite_end_function_t          suite_end;
	ut_testreport_writer_suite_case_begin_function_t   suite_case_begin;
	ut_testreport_writer_suite_case_end_function_t     suite_case_end;
	ut_testreport_writer_suite_result_begin_function_t suite_result_begin;
	ut_testreport_writer_suite_result_end_function_t   suite_result_end;
	ut_testreport_writer_suite_result_case_function_t  suite_result_case;
}
ut_testreport_writer_t;
#endif

/***************************************************************************/
/* 테스트리포트 */
/***************************************************************************/
typedef struct _ut_testreport_t
{
#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)
	ut_testreport_writer_t* writer;
#endif
	ut_testreport_summary_t summary;
}
ut_testreport_t;




/***************************************************************************/
/* 테스트리절트 */
/***************************************************************************/
typedef struct _ut_testtime_t_t
{
	ut_timespec_t begin;
	ut_timespec_t end;
}
ut_testtime_t;

typedef struct _ut_testresult_t
{
	ut_testtime_t runtime;
	ut_uint_t success;
	ut_uint_t fail;
	ut_uint_t exception;
}
ut_testresult_t;



/***************************************************************************/
/* 테스트픽쳐 */
/***************************************************************************/
UT_FUNC_DECL typedef void (*ut_testfixture_setup_function_t) (void* context);
UT_FUNC_DECL typedef void (*ut_testfixture_teardown_function_t) (void* context);

typedef struct _ut_testfixture_t
{
	ut_testfixture_setup_function_t    setup;
	ut_testfixture_teardown_function_t teardown;
}
ut_testfixture_t;



/***************************************************************************/
/* 테스트케이스 */
/***************************************************************************/
typedef void (*ut_testcase_function_t) (void* context);

typedef struct _ut_testcase_t
{
	const ut_char_t* name;
	const ut_char_t* description;
	ut_testfixture_t fixture;

	ut_testcase_function_t run;
}
ut_testcase_t;



/***************************************************************************/
/* 테스트슈트 */
/***************************************************************************/
typedef struct _ut_testsuite_case_t
{
	ut_testcase_t* test;

	ut_testresult_t result;
}
ut_testsuite_case_t;

typedef struct _ut_testsuite_t
{
	const ut_char_t* name;
	const ut_char_t* description;
	ut_testfixture_t fixture;

	ut_testsuite_case_t* test;
	ut_testreport_t* report;
}
ut_testsuite_t;



/***************************************************************************/
/* 테스트컨텍스트 */
/***************************************************************************/
typedef struct _ut_testcontext_t
{
	ut_testsuite_t* suite;
	ut_testsuite_case_t* suite_case;
	void* param;
}
ut_testcontext_t;






/***************************************************************************/

#endif


