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
typedef void (*ut_testfixture_setup_function_t) (void* context);
typedef void (*ut_testfixture_teardown_function_t) (void* context);

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
/* 테스트리포트 */
/***************************************************************************/
typedef struct _ut_testreport_t
{
	ut_uint_t     assertion_success;
	ut_uint_t     assertion_fail;
	ut_uint_t     assertion_exception;
	ut_uint_t     case_success;
	ut_uint_t     case_fail;
	ut_uint_t     case_exception;
	ut_uint_t     case_count;
	ut_uint_t     suite_count;
	ut_timespec_t runtime;
}
ut_testreport_t;





/***************************************************************************/

#endif


