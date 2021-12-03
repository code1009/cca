/* ==========================================================================
**
** ut_timespec.c
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
#include "ut.h"




/***************************************************************************/
void ut_get_clocktime(ut_timespec_t* t)
{
	ut_rt_get_clocktime(t);
}

void ut_time_diff(ut_timespec_t* t1, ut_timespec_t* t2, ut_timespec_t* t)
{
	ut_timespec_t* temp;


	if (t2->second < t1->second)
	{
		temp = t1;
		t1 = t2;
		t2 = temp;
	}


	t->second = t2->second - t1->second;

	if (t1->nanosecond <= t2->nanosecond)
	{
		t->nanosecond = t2->nanosecond - t1->nanosecond;
	}
	else
	{
		t->nanosecond = 1000000000U - t1->nanosecond + t2->nanosecond;
		t->second--;
	}

	if (t->nanosecond >= 1000000000U)
	{
		t->second += (t->nanosecond / 1000000000U);
		t->nanosecond = t->nanosecond % 1000000000U;
	}
}

void ut_time_add(ut_timespec_t* t1, ut_timespec_t* t2, ut_timespec_t* t)
{
	t->second = t1->second + t2->second;
	t->nanosecond = t1->nanosecond + t2->nanosecond;

	if (t->nanosecond >= 1000000000U)
	{
		t->second += (t->nanosecond / 1000000000U);
		t->nanosecond = t->nanosecond % 1000000000U;
	}
}

