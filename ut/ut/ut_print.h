#ifndef ut_print__h
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
UT_API void ut_print_char(ut_char_t ch);
UT_API void ut_print_string(ut_char_t* pointer, ut_size_t size);
UT_API void ut_print_endline(void);

UT_API void ut_print(const ut_char_t* message);
UT_API void ut_println(const ut_char_t* message);

UT_API void ut_printf(const ut_char_t* format, ...);
UT_API void ut_printfln(const ut_char_t* format, ...);





/***************************************************************************/

#endif


