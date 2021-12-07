/***************************************************************************/
#include "ut/ut.h"

#include "ut_test_1/ut_test_1.h"
#include "ut_test_2/ut_test_2.hpp"
#include "ut_test_3/ut_test_my_app.h"

#include <iostream>



/***************************************************************************/
int main()
{
	// 릴리즈모드 컴파일시 trojan / Win.Generic.C4516440 오탐지 방지;;;
	std::cout << "Hello World!\n";

	ut_rt_initialize();

	ut_test_1();
	ut_test_2();
	ut_test_my_app();

	return 0;
}


