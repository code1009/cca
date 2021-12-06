#ifndef ut_test__h
#define ut_test__h

/***************************************************************************/

/* ==========================================================================
**
** ut_test.h
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
UT_API void ut_testrunner_assert_condition(
	ut_bool_t condition,
	const ut_char_t* expression,
	const ut_char_t* file,
	const ut_uint_t  line,
	const ut_char_t* function,
	void* context);

UT_API void ut_testrunner (ut_testsuite_t* suite, void* param, ut_testrunner_report_t* report);

UT_API void ut_testrunner_report_reset(ut_testrunner_report_t* r);
UT_API void ut_testrunner_report_accumulate(ut_testrunner_report_t* a, ut_testrunner_report_t* r);
UT_API void ut_testrunner_report_print(ut_testrunner_report_t* r);

UT_API void ut_testsut_print(const ut_char_t* name);



/***************************************************************************/

#endif


