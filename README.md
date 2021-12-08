
-----------------------------------------------------------------------------
# cca

## 설명
* CodeCoverage Analysis Tool
* ccs(TI Code Composer Studio) Compiler를 위한 CodeCoverage 분석기

1. 컴파일러를 통해서 코드 수행 csv파일을 아래와 같이 얻는 경우
~~~c++
"filename","funcname",line number,column number,frequency count,"comment"
"D:\prj\hcpu\hcpu-A-002\hcpu\src\app/application2.h","app_msg",3,2,1,"console_device_printfln("app_msg")"
"D:\prj\hcpu\hcpu-A-002\hcpu\src\app/application2.h","app_msg",5,2,1,"return "
"D:\prj\hcpu\hcpu-A-002\hcpu\src\app/application2.h","app_msg",2,1,1,"goto g-1#1"
~~~

2. csv파일을 읽어서 아래와 같이 분석 결과를 출력
~~~c++
=============================================================================
# source file code coverage analaysis
=============================================================================
file path: D:\prj\hcpu\hcpu-A-002\hcpu\src\app/application2.h
coverage : 100.00 %

[function coverage]
count : 1
----------+------------------------------------------------------------------
 coverage | name
----------+------------------------------------------------------------------
 100.00 % | "app_msg"
----------+------------------------------------------------------------------

[line coverage]
-------+-----+------+--------------------------------------------------------
 freq  | cov | line | source
-------+-----+------+--------------------------------------------------------
       |     |    1 |cx_bool_t app_msg (void)
     1 | 1.0 |    2 |{
     1 | 1.0 |    3 |   console_device_printfln("app_msg");
       |     |    4 |
     1 | 1.0 |    5 |   return CX_TRUE;
       |     |    6 |}
       |     |    7 |
       |     |    8 |
-------+-----+------+--------------------------------------------------------
~~~


-----------------------------------------------------------------------------
# ut

## 설명
* UnitTest Library (C)
* 마이크로 프로세서(MCU)에서 사용하기 위해서 개발 된 유닛 테스트 라이브러리



1. 아래와 같이 테스트 코드 작성 하여 실행 하면
~~~c++
/***************************************************************************/
#include "../ut/ut.h"
#include "ut_test_1.h"



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
void ut_test_1(void)
{
	int param = 3;


	ut_testrunner(ut_testsuite_instance(simple_suite1), &param, ut_nullptr);
}



/***************************************************************************/
int main()
{
	ut_rt_initialize();

	ut_test_1();

	ut_rt_uninitialize();

	return 0;
}

~~~


2. 아래와 같은 결과를 출력
~~~c++
*****************************************************************************
# [simple_suite1] TESTSUITE BEGIN
  :단순 테스트슈트
  time = 1638838733.453190800 sec
*****************************************************************************
-----------------------------------------------------------------------------
# [simple_case1] TESTCASE BEGIN
  :단순 테스트케이스1
# TEST ASSERTION FAILED
  TESTSUITE : simple_suite1
  TESTCASE  : simple_case1
  FILE      : D:\prj\cca\ut\ut_test_1\ut_test_1.c
  LINE      : 11
  FUNCTION  : ut_testcase__simple_case1
  EXPRESSION: 1 == 0
# [simple_case1] TESTCASE END

-----------------------------------------------------------------------------
# [simple_case2] TESTCASE BEGIN
  :단순 테스트케이스2
파라메터: 3
# [simple_case2] TESTCASE END

*****************************************************************************
# [simple_suite1] TESTSUITE END
  time = 1638838733.486191200 sec

*****************************************************************************
# [simple_suite1] TESTSUITE RESULT
  :단순 테스트슈트

---------+---------------+-------+-------+-------+---------------------------
 RESULT  | RUNTIME       | OK    | FAIL  | HALT  | TESTCASE
---------+---------------+-------+-------+-------+---------------------------
[ FAIL ] |   0.008000700 |     1 |     1 |     0 | [simple_case1] 단순 테스트케이스1
[ OK   ] |   0.001000400 |     2 |     0 |     0 | [simple_case2] 단순 테스트케이스2
---------+---------------+-------+-------+-------+---------------------------

TESTSUITE RUNTIME  : 0.009001100
TESTSUITE SUCCESS  : 75.00 % (3/4)

TESTCASE COUNT     : 2
TESTCASE SUCCESS   : 1
TESTCASE FAIL      : 1
TESTCASE HALT      : 0

TESTASSERT SUCCESS : 3
TESTASSERT FAIL    : 1
TESTASSERT HALT    : 0


~~~
