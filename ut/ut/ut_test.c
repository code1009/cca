/* ==========================================================================
**
** ut_test.c
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
#include "ut.h"



/***************************************************************************/
void ut_testresult_reset(ut_testresult_t* result)
{
	result->fail = 0u;
	result->success = 0u;
	result->exception = 0u;

	result->runtime.begin.second = 0u;
	result->runtime.begin.nanosecond = 0u;
	result->runtime.end.second = 0u;
	result->runtime.end.nanosecond = 0u;
}


