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
UT_FUNC_DECL void ut_testrunner_assert_condition(
	void* context,
	ut_bool_t condition,
	const ut_char_t* expression,
	const ut_char_t* file,
	const ut_uint_t  line,
	const ut_char_t* function
	);

UT_FUNC_DECL void ut_testrunner (ut_testsuite_t* suite, void* param, ut_testreport_t* report);

UT_FUNC_DECL void ut_testreport_begin(ut_testreport_t* report, void* param);
UT_FUNC_DECL void ut_testreport_end(ut_testreport_t* report, void* param);

UT_FUNC_DECL void ut_test_print(const ut_char_t* name);



/***************************************************************************/
#if UT_CONFIG_ENABLE_TESTREPORT_WRITER==1
UT_GVAR_DECL ut_testreport_writer_t _ut_testreport_writer_default;
UT_GVAR_DECL ut_testreport_writer_t _ut_testreport_writer_xml;
#endif



/***************************************************************************/

#endif


