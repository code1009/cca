/***************************************************************************/
#include "ut/ut.h"

#include "ut_test_1/ut_test_1.h"
#include "ut_test_2/ut_test_2.hpp"
#include "ut_test_3/ut_test_my_app.h"

#include <iostream>



/***************************************************************************/
int main()
{
	// 릴리즈모드 컴파일 후 실행파일을 trojan / Win.Generic.C4516440 바이러스로
	// 잘못 탐지하는 것을 막기 위해서 std::out 사용
	std::cout << "Hello World!\n";

	ut_rt_initialize();

	ut_test_1();
	ut_test_2();
	ut_test_my_app();

	return 0;
}


