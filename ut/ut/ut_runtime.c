﻿// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com



/* ==========================================================================
**
** ut_runtime.c
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
#include "ut.h"

#include <stdio.h>
#include <stdarg.h>

#include <string.h>
#include <stdlib.h>

#include <signal.h>
#include <setjmp.h>

#ifdef _MSC_VER
#include <Windows.h>
#endif





/***************************************************************************/
/*=========================================================================*/
typedef void (*ut_signal_handler_t)(int signal);

/*=========================================================================*/
static ut_signal_handler_t _ut_rt_previous_signal_handler_SIGSEGV = ut_nullptr;
static ut_signal_handler_t _ut_rt_previous_signal_handler_SIGFPE  = ut_nullptr;
static ut_signal_handler_t _ut_rt_previous_signal_handler_SIGINT  = ut_nullptr;
static ut_signal_handler_t _ut_rt_previous_signal_handler_SIGILL  = ut_nullptr;
static ut_signal_handler_t _ut_rt_previous_signal_handler_SIGTERM = ut_nullptr;
static ut_signal_handler_t _ut_rt_previous_signal_handler_SIGABRT = ut_nullptr;

static jmp_buf _ut_rt_jump_env;





/***************************************************************************/
static void ut_rt_signal_handler(int signal)
{
	/*
	switch (signal)
	{
	case SIGSEGV:
	case SIGFPE :
	case SIGINT :
	case SIGILL :
	case SIGTERM:
	case SIGABRT:
	default:
		break;
	}
	*/

	longjmp(_ut_rt_jump_env, 1);
}

static void ut_rt_exception_handler_initalize(void)
{
	_ut_rt_previous_signal_handler_SIGSEGV = signal(SIGSEGV, ut_rt_signal_handler);
	_ut_rt_previous_signal_handler_SIGFPE  = signal(SIGFPE , ut_rt_signal_handler);
	_ut_rt_previous_signal_handler_SIGINT  = signal(SIGINT , ut_rt_signal_handler);
	_ut_rt_previous_signal_handler_SIGILL  = signal(SIGILL , ut_rt_signal_handler);
	_ut_rt_previous_signal_handler_SIGTERM = signal(SIGTERM, ut_rt_signal_handler);
	_ut_rt_previous_signal_handler_SIGABRT = signal(SIGABRT, ut_rt_signal_handler);
}

static void ut_rt_exception_handler_uninitalize(void)
{
	if (ut_nullptr!=_ut_rt_previous_signal_handler_SIGSEGV) { signal(SIGSEGV, _ut_rt_previous_signal_handler_SIGSEGV); }
	if (ut_nullptr!=_ut_rt_previous_signal_handler_SIGFPE ) { signal(SIGFPE , _ut_rt_previous_signal_handler_SIGFPE ); }
	if (ut_nullptr!=_ut_rt_previous_signal_handler_SIGINT ) { signal(SIGINT , _ut_rt_previous_signal_handler_SIGINT ); }
	if (ut_nullptr!=_ut_rt_previous_signal_handler_SIGILL ) { signal(SIGILL , _ut_rt_previous_signal_handler_SIGILL ); }
	if (ut_nullptr!=_ut_rt_previous_signal_handler_SIGTERM) { signal(SIGTERM, _ut_rt_previous_signal_handler_SIGTERM); }
	if (ut_nullptr!=_ut_rt_previous_signal_handler_SIGABRT) { signal(SIGABRT, _ut_rt_previous_signal_handler_SIGABRT); }
}



/***************************************************************************/
ut_bool_t ut_rt_execute_testcase (ut_testcase_function_t run, ut_testcontext_t* context)
{
	ut_bool_t result;

	int jmp_rval;


	result = ut_true;


	jmp_rval = setjmp(_ut_rt_jump_env);
	if (0 == jmp_rval)
	{
#ifdef _MSC_VER
		__try
		{
#endif
			run(context);
#ifdef _MSC_VER
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			result = ut_false;
		}
#endif
	}
	else
	{
		result = ut_false;
	}


	return result;
}



/***************************************************************************/
ut_int_t ut_rt_vsnprintf(ut_char_t* buffer, ut_size_t count, const ut_char_t* format, va_list va)
{
	return vsnprintf(buffer, count, format, va);
}

void ut_rt_zeromemory(void* pointer, ut_size_t size)
{
	memset(pointer, 0, size);
}

#ifdef _MSC_VER

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

#else

void ut_rt_get_clocktime(ut_timespec_t* t)
{
	struct timespec tp;
	
	int rv;


	rv = clock_gettime(CLOCK_REALTIME, &tp);
	if (0 == rv)
	{
		t->second = tp->tv_sec;
		t->nanosecond = tp->tv_nsec;
	}
	else
	{
		t->second = 0u;
		t->nanosecond = 0u;
	}
}

#endif



/***************************************************************************/
/*=========================================================================*/
#define UT_RT_CONSOLE_RAW_BUFFER_SIZE 81920

/*=========================================================================*/
static ut_char_t _ut_rt_console_raw_buffer[UT_RT_CONSOLE_RAW_BUFFER_SIZE];
static ut_size_t _ut_rt_console_raw_ptr = 0u;

/*=========================================================================*/
static void ut_rt_console_raw_output(ut_char_t* pointer, ut_size_t size)
{
	/*
	ut_size_t i;


	for (i = 0u; i < size; i++)
	{
		putc(*(pointer+i), stdout);
	}
	*/

	fwrite(pointer, size, 1, stdout);
}

static void ut_rt_console_raw_initialize(void)
{
	_ut_rt_console_raw_ptr = 0u;
}

static void ut_rt_console_raw_flush(void)
{
	if (_ut_rt_console_raw_ptr > 0u)
	{
		ut_rt_console_raw_output(_ut_rt_console_raw_buffer, _ut_rt_console_raw_ptr);
		_ut_rt_console_raw_ptr = 0u;
	}
}

static void ut_rt_console_raw_outputb(ut_char_t ch)
{
	_ut_rt_console_raw_buffer[_ut_rt_console_raw_ptr] = ch;
	_ut_rt_console_raw_ptr++;

	if (_ut_rt_console_raw_ptr == UT_RT_CONSOLE_RAW_BUFFER_SIZE)
	{
		ut_rt_console_raw_flush();
	}
}

/*=========================================================================*/
void ut_rt_console_outputb(ut_char_t ch)
{
//	putc(ch, stdout);
	ut_rt_console_raw_outputb(ch);
}



/***************************************************************************/
void ut_rt_initialize(void)
{
	ut_rt_exception_handler_initalize();

	ut_rt_console_raw_initialize();
}

void ut_rt_uninitialize(void)
{
	ut_rt_exception_handler_uninitalize();

	ut_rt_console_raw_flush();
}


