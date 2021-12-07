#ifndef ut__h
#define ut__h

/***************************************************************************/

/* ==========================================================================
**
** ut.h
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/




/***************************************************************************/
/*

[용어]
# 테스트리절트(testresult)
- 테스트결과

# 테스트픽쳐(testfixture)
- 테스트를 위한 설비라는 의미
- testfixture.setup()   : 테스트가 시작하기 전에 호출 되어 수행
- testfixture.teardown(): 테스트가 종료시 호출 되어 수행

# 테스트케이스(testcase)
- 테스트하기위한 가장 기본 단위
- 테스트케이스를 수행하기 위해서 테스트픽쳐 형태로 등록 할 수 있음

# 테스트슈트(testsuite)
- 테스트케이스를 모아놓은 그룹
- 테스트슈트를 수행하기 위해서 테스트픽쳐 형태로 등록 할 수 있음

# 테스트컨텍스트(testcontext)
- 테스트러너에 의한 테스트동작 관련 정보

# 테스트러너(testrunner)
- 테스트슈트를 수행
- 테스트결과를 작성
- 테스트보고서를 작성

# 테스트어썰트(testassert)
- 테스트의 기대값 확인
- 테스트의 확인

# 테스트리포트(testreport)
- 테스트의 보고서



# 테스트더블(testdouble)
- 테스트 환경구축을 위한 가짜 함수/객체/변수 또는 감시도구 들
- 종류
  1. Dummy
     가짜 파라메터 정보
  2. Fake
     SUT 내부에서 호출되어지는 객체/함수를 가짜로 만든 객체/함수
     가짜로 만든 객체/함수는 SUT에서 호출하는 함수와 동일한 동작을 수행
  3. Stub
     SUT가 호출 하는 함수들을 테스트틀 위해서 구현한 함수
     테스트를 하기 위해서 응답(동작)이 고정적으로 동작하도록 구성
  4. Spy
     SUT을 감시(예: 수행횟수)
  5. Mock
     Fake 다르게 기대 값을 반환하도록 한 객체/함수
- REF URL
  https://jesusvalerareales.medium.com/testing-with-test-doubles-7c3abb9eb3f2
  https://blog.pragmatists.com/test-doubles-fakes-mocks-and-stubs-1a7491dfa3da
  http://xunitpatterns.com/Test%20Double.html
  https://martinfowler.com/bliki/TestDouble.html

# SUT
- SYSTEM UNDER TEST
- 테스트 대상





# ISTQB
- International Software Testing Qualifications Board



*/
/***************************************************************************/





/***************************************************************************/
/*=========================================================================*/
/*-------------------------------------------------------------------------*/
#define UT_VERSION_STRING "1.0.0.1"





/***************************************************************************/
#include "ut_type.h"
#include "ut_print.h"
#include "ut_time.h"

#include "ut_test_struct.h"
#include "ut_test_macro.h"
#include "ut_test.h"

#include "ut_runtime.h"





/***************************************************************************/

#endif


