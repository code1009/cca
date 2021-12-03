/* ==========================================================================
**
** ut_string.c
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
#include "ut.h"

#include <stdio.h>
#include <string.h>

#include <Windows.h>



/***************************************************************************/
void ut_rt_putch(ut_char_t ch)
{
	putc(ch, stdout);
}

void ut_rt_zeromemory(void* pointer, ut_size_t size)
{
	memset(pointer, 0, size);
}

void ut_rt_get_clocktime(ut_timespec_t* t)
{
	__int64 wintime;


	GetSystemTimeAsFileTime((FILETIME*)&wintime);

	// 1jan1601 to 1jan1970
	wintime -= 116444736000000000i64;

#pragma warning(push)
#pragma warning(disable : 4244)
	t->second = wintime / 10000000i64;
#pragma warning(pop)
	t->nanosecond = wintime % 10000000i64 * 100;
}


