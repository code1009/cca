/***************************************************************************/
#include "ut/ut.h"

#include "ut_test_1/ut_test_1.h"
#include "ut_test_2/ut_test_2.hpp"
#include "ut_test_3/ut_test_my_app.h"



/***************************************************************************/
int main()
{
	ut_rt_initialize();

	ut_test_1();
	ut_test_2();
	ut_test_my_app();

	return 0;
}


