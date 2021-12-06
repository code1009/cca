/***************************************************************************/
#include "ut/ut.h"

#include "ut_testsut_1/ut_testsut_1.h"
#include "ut_testsut_2/ut_testsut_2.hpp"
#include "ut_testsut_3/ut_testsut_my_app.h"



/***************************************************************************/
int main()
{
	ut_rt_initialize();

	ut_testsut_1();
	ut_testsut_2();
	ut_testsut_my_app();

	return 0;
}


