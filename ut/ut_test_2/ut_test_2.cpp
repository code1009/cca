// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com



/***************************************************************************/
#include "../ut/ut.h"
#include "../ut_test_1/ut_test_1.h"

#include "ut_test_2.hpp"



/***************************************************************************/
/* 테스트케이스1 */
/* 아래 함수 순서를 지켜야 함  */
ut_testfixture_setup(case1)
{
	ut_printsln("case1-setup");
}

ut_testfixture_teardown(case1)
{
	ut_printsln("case1-teardown");
}

ut_testcase_fixture
(
	case1,
	"case1-description",
	ut_testfixture_setup_instance(case1), 
	ut_testfixture_teardown_instance(case1)
)
{
	ut_printsln("case1");

	ut_testassert(1);
}

/***************************************************************************/
/* 테스트케이스2 */
ut_testcase(case2, "case2-description")
{
	ut_printsln("case2");
	ut_testassert(0);
	ut_testassert(1);
}

/***************************************************************************/
/* 테스트케이스3 */
ut_testcase(case3, ut_nullptr)
{
	ut_printsln("case3");
}

/***************************************************************************/
/* 테스트케이스4 */
ut_testcase(case4, ut_nullptr)
{
	ut_printsln("case4");
}



/***************************************************************************/
/* 테스트슈트1 */
/* 아래 함수 순서를 지켜야 함  */
ut_testfixture_setup(suite1)
{
	ut_printsln("suite1-setup");
}

ut_testfixture_teardown(suite1)
{
	ut_printsln("suite1-teardown");
}

ut_testsuite_case_begin(suite1)
ut_testsuite_case(case1)
ut_testsuite_case(case2)
ut_testsuite_case(case3)
ut_testsuite_case(case4)
ut_testsuite_case_end()

ut_testsuite_fixture
(
	suite1, 
	"suite1-description", 
	ut_testfixture_setup_instance(suite1), 
	ut_testfixture_teardown_instance(suite1)
)



/***************************************************************************/
/* 테스트슈트2 */
ut_testsuite_case_begin(suite2)
//ut_testsuite_case(case1)
ut_testsuite_case(case2)
ut_testsuite_case(case3)
ut_testsuite_case(simple_case1)
ut_testsuite_case_end()

ut_testsuite(suite2, ut_nullptr)





/***************************************************************************/
UT_FUNC_IMPL void ut_test_2(void)
{
	ut_test_print("2");


	int param = 1;

	ut_testreport_t report;


#if (UT_CONFIG_ENABLE_TESTREPORT_WRITER==1)

	report.writer = ut_nullptr;
	
	/* or */
	report.writer = &_ut_testreport_writer_default;

	/* or */
	report.writer = &_ut_testreport_writer_xml;
#endif

	ut_testreport_begin(&report, &param);

	ut_testrunner(ut_testsuite_instance(suite1), ut_nullptr, &report);
	ut_testrunner(ut_testsuite_instance(suite2), &param, &report);

	ut_testrunner(ut_testsuite_instance(simple_suite1), &param, &report);

	ut_testreport_end(&report, &param);
}


