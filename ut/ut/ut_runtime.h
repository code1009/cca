#ifndef ut_runtime__h
#define ut_runtime__h

/***************************************************************************/

/* ==========================================================================
**
** ut_runtime.h
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
#include <stdarg.h>



/***************************************************************************/
UT_API ut_int_t  ut_rt_vsnprintf       (ut_char_t* buffer, ut_size_t count, const ut_char_t* format, va_list va);
UT_API void      ut_rt_putch           (ut_char_t ch);
UT_API void      ut_rt_zeromemory      (void* pointer, ut_size_t size);
UT_API void      ut_rt_get_clocktime   (ut_timespec_t* t);
UT_API ut_bool_t ut_rt_execute_testcase(ut_testcase_function_t run, ut_testcontext_t* context);
UT_API void      ut_rt_initialize      (void);


/***************************************************************************/

#endif


