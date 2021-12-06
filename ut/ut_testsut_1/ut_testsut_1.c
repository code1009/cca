/***************************************************************************/
#include "../ut/ut.h"
#include "ut_testsut_1.h"



/***************************************************************************/
/* 테스트케이스 */
ut_testcase(simple_case1, "단순 테스트케이스1")
{
	ut_testassert(1 == 0);
	ut_testassert(1 == 1);
}

ut_testcase(simple_case2, "단순 테스트케이스2")
{
	void* param = ut_testcontext_get_param();
	int* value = (int*)param;

	ut_printfln("파라메터: %d", *value);

	ut_testassert(3 == 3);
	ut_testassert(3 == 3);
}



/***************************************************************************/
/* 테스트슈트 */
ut_testsuite_case_begin(simple_suite1)
ut_testsuite_case(simple_case1)
ut_testsuite_case(simple_case2)
ut_testsuite_case_end()

ut_testsuite(simple_suite1, "단순 테스트슈트")



/***************************************************************************/
void ut_testsut_1(void)
{
	ut_testsut_print("1");



	int param = 3;


	ut_testrunner(ut_testsuite_instance(simple_suite1), &param, ut_nullptr);
}




