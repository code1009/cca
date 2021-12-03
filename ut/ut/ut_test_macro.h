#ifndef ut_test_macro__h
#define ut_test_macro__h

/***************************************************************************/

/* ==========================================================================
**
** ut_test_macro.h
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
/* 테스트픽쳐 */
/***************************************************************************/
/*=========================================================================*/
#define ut_testfixture_setup(a_id) \
UT_API void ut_testfixture_setup__##a_id (void* __context__)

#define ut_testfixture_teardown(a_id) \
UT_API void ut_testfixture_teardown__##a_id (void* __context__)

/*=========================================================================*/
#define ut_testfixture_setup_instance(a_id) \
	ut_testfixture_setup__##a_id

#define ut_testfixture_teardown_instance(a_id) \
	ut_testfixture_teardown__##a_id





/***************************************************************************/
/* 테스트케이스 */
/***************************************************************************/
/*=========================================================================*/
#define ut_testcase(a_id, a_description) \
UT_API void ut_testcase__##a_id (void* __context__); \
\
UT_API ut_testcase_t _ut_testcase__##a_id = \
{ \
	#a_id, \
	a_description, \
	{ut_nullptr, ut_nullptr}, \
	ut_testcase__##a_id \
}; \
\
UT_API void ut_testcase__##a_id (void* __context__)

/*-------------------------------------------------------------------------*/
#define ut_testcase_fixture(a_id, a_description, a_fixture_setup, a_fixture_teardown) \
UT_API void ut_testcase__##a_id (void* param); \
\
UT_API ut_testcase_t _ut_testcase__##a_id = \
{ \
	#a_id, \
	a_description, \
	{a_fixture_setup, a_fixture_teardown}, \
	ut_testcase__##a_id \
}; \
\
UT_API void ut_testcase__##a_id (void* __context__)

/*=========================================================================*/
#define ut_testcase_instance(a_id) \
	( &( _ut_testcase__##a_id ) )

/*=========================================================================*/
#define ut_testcase_extern(a_id) \
UT_API ut_testcase_t _ut_testcase__##a_id;




/***************************************************************************/
/* 테스트리절트 */
/***************************************************************************/
/*=========================================================================*/
#define ut_testresult_empty \
	{ \
		{ {0u, 0u}, {0u, 0u} }, \
		0u, \
		0u, \
		0u  \
	}





/***************************************************************************/
/* 테스트슈트-케이스 */
/***************************************************************************/
/*=========================================================================*/
#define ut_testsuite_case_begin(a_id) \
UT_API ut_testsuite_case_t _ut_testsuite_case__##a_id [] = \
{

#define ut_testsuite_case(a_id) \
	{ \
		ut_testcase_instance(a_id), \
		ut_testresult_empty \
	},

#define ut_testsuite_case_end() \
	{ \
		ut_nullptr, \
		ut_testresult_empty \
	} \
};

/*=========================================================================*/
#define ut_testsuite_case_instance(a_id) \
	( &( _ut_testsuite_case__##a_id [0]) )

/*=========================================================================*/
#define ut_testsuite_case_count(a_id) \
	( (sizeof(_ut_testsuite_case__##a_id)/sizeof(ut_testsuite_case_t))-1 )





/***************************************************************************/
/* 테스트슈트 */
/***************************************************************************/
/*=========================================================================*/
#define ut_testsuite(a_id, a_description) \
UT_API ut_testsuite_t _ut_testsuite__##a_id = \
{ \
	#a_id, \
	a_description, \
	{ut_nullptr, ut_nullptr}, \
	ut_testsuite_case_instance(a_id) \
};

/*-------------------------------------------------------------------------*/
#define ut_testsuite_fixture(a_id, a_description, a_fixture_setup, a_fixture_teardown) \
UT_API ut_testsuite_t _ut_testsuite__##a_id = \
{ \
	#a_id, \
	a_description, \
	{a_fixture_setup, a_fixture_teardown}, \
	ut_testsuite_case_instance(a_id) \
};

/*=========================================================================*/
#define ut_testsuite_instance(a_id) \
	( &( _ut_testsuite__##a_id ) )

/*=========================================================================*/
#define ut_testsuite_extern(a_id) \
UT_API ut_testsuite_t _ut_testsuite__##a_id;



/***************************************************************************/
/* 테스트컨텍스트 */
/***************************************************************************/
/*=========================================================================*/
#define ut_testcontext_get(a_context) \
	((ut_testcontext_t*)(a_context))





/***************************************************************************/
/* 테스트어설트 */
/***************************************************************************/
#define ut_testassert(X) \
	ut_testrunner_assert_condition( (X), #X, __FILE__, __LINE__, __FUNCTION__, __context__ );



/***************************************************************************/

#endif


