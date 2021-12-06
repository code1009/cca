/***************************************************************************/
#include "../ut/ut.h"
#include "ut_testsut_my_app.h"



/***************************************************************************/
/* 테스트더블 */
#define my_div ut_testdouble__my_div__skeleton
#include "my_app_main.c"
#undef my_div

#include "my_app_module.c"

/*-------------------------------------------------------------------------*/
typedef int (*ut_testdouble__my_div)(int a, int b);

/*-------------------------------------------------------------------------*/
ut_testdouble__my_div _ut_testdouble__my_div = ut_nullptr;
int _ut_testdouble__my_div__runcount = 0;
int _ut_testdouble__my_div__return = 0;
int _ut_testdouble__my_div__arg__a = 0;
int _ut_testdouble__my_div__arg__b = 0;

/*-------------------------------------------------------------------------*/
MY_API int ut_testdouble__my_div__skeleton (int a, int b)
{
	_ut_testdouble__my_div__runcount++;

	_ut_testdouble__my_div__arg__a = a;
	_ut_testdouble__my_div__arg__b = b;

	if (ut_nullptr!=_ut_testdouble__my_div)
	{
		_ut_testdouble__my_div__return = _ut_testdouble__my_div(a, b);
	}

	return _ut_testdouble__my_div__return;
}



/***************************************************************************/
/* 테스트케이스 */
ut_testcase(my_app_case1, ut_nullptr)
{
	_ut_testdouble__my_div = my_div;


	ut_testassert(0 == my_app_main());
	ut_testassert(1 == _ut_testdouble__my_div__arg__a);
	ut_testassert(2 == _ut_testdouble__my_div__arg__b);
	ut_testassert(0 == _ut_testdouble__my_div__return);


	_ut_testdouble__my_div = ut_nullptr;


	_ut_testdouble__my_div__return = 100;
	ut_testassert(0 == my_app_main());
	ut_testassert(1 == _ut_testdouble__my_div__arg__a);
	ut_testassert(2 == _ut_testdouble__my_div__arg__b);

	_ut_testdouble__my_div__return = 101;
	ut_testassert(1 == my_app_main());
	ut_testassert(1 == _ut_testdouble__my_div__arg__a);
	ut_testassert(2 == _ut_testdouble__my_div__arg__b);

	ut_testassert(3 == _ut_testdouble__my_div__runcount);
}



/***************************************************************************/
/* 테스트케이스 */
ut_testcase(my_app_case2, ut_nullptr)
{
	ut_testassert(1 == my_div(1, 1));

	ut_testassert(1 == my_div(1, 0)); // Division by zero
}



/***************************************************************************/
/* 테스트슈트 */
ut_testsuite_case_begin(my_app_suite1)
ut_testsuite_case(my_app_case1)
ut_testsuite_case(my_app_case2)
ut_testsuite_case_end()

ut_testsuite(my_app_suite1, ut_nullptr)



/***************************************************************************/
/* 테스트SUT */
void ut_testsut_my_app(void)
{
	ut_print_endline();
	ut_println("#############################################################################");
	ut_print_endline();
	ut_println("TESTSUT my_app");
	ut_print_endline();
	ut_println("#############################################################################");



	ut_testrunner(ut_testsuite_instance(my_app_suite1), ut_nullptr);
}

