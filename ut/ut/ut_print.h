﻿#ifndef ut_print__h
#define ut_print__h

/***************************************************************************/

/* ==========================================================================
**
** ut_print.h
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
UT_FUNC_DECL void ut_print_char(ut_char_t ch);
UT_FUNC_DECL void ut_print_string(ut_char_t* pointer, ut_size_t size);

UT_FUNC_DECL void ut_println(void);

UT_FUNC_DECL void ut_prints(const ut_char_t* message);
UT_FUNC_DECL void ut_printsln(const ut_char_t* message);

UT_FUNC_DECL void ut_printf(const ut_char_t* format, ...);
UT_FUNC_DECL void ut_printfln(const ut_char_t* format, ...);





/***************************************************************************/

#endif


