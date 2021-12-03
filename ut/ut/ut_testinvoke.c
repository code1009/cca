/* ==========================================================================
**
** ut_testinvoke.c
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
#include "ut.h"

#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

#ifdef _MSC_VER
#include <Windows.h>
#endif



/***************************************************************************/
/*=========================================================================*/
typedef void (*ut_signal_handler_t)(int);

/*=========================================================================*/
static ut_signal_handler_t _ut_previous_signal_handler_SIGSEGV = ut_nullptr;
static ut_signal_handler_t _ut_previous_signal_handler_SIGFPE = ut_nullptr;
static ut_signal_handler_t _ut_previous_signal_handler_SIGINT = ut_nullptr;
static ut_signal_handler_t _ut_previous_signal_handler_SIGILL = ut_nullptr;
static ut_signal_handler_t _ut_previous_signal_handler_SIGTERM = ut_nullptr;
static ut_signal_handler_t _ut_previous_signal_handler_SIGABRT = ut_nullptr;
static jmp_buf _ut_jump_env;



/***************************************************************************/
static void ut_signal_handler(int signal)
{
	/*
	if (signal == SIGABRT) 
	{
	}
	else 
	{
	}
	*/
	longjmp(_ut_jump_env, 1);
}



/***************************************************************************/
void ut_testinvoke_initialize(void)
{
	_ut_previous_signal_handler_SIGSEGV = signal(SIGSEGV, ut_signal_handler);
	_ut_previous_signal_handler_SIGFPE = signal(SIGFPE, ut_signal_handler);
	_ut_previous_signal_handler_SIGINT = signal(SIGINT, ut_signal_handler);
	_ut_previous_signal_handler_SIGILL = signal(SIGILL, ut_signal_handler);
	_ut_previous_signal_handler_SIGTERM = signal(SIGTERM, ut_signal_handler);
	_ut_previous_signal_handler_SIGABRT = signal(SIGABRT, ut_signal_handler);
}


void ut_testinvoke(ut_testsuite_case_t* test, ut_testcontext_t* context)
{
	ut_testcase_function_t run;

	int jmp_rval;


	run = test->test->run;

	jmp_rval = setjmp(_ut_jump_env);
	if (0 == jmp_rval)
	{
#ifdef _MSC_VER
		__try
		{
#endif
			run(context);
#ifdef _MSC_VER
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
			ut_testrunner_case_exception(context);
		}
#endif
	}
	else
	{
		ut_testrunner_case_exception(context);
	}
}


