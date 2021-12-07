﻿/* ==========================================================================
**
** ut_print.c
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
#include "ut.h"



/***************************************************************************/
#define UT_PRINT_FORMAT_BUFFER_SIZE 256

#define UT_PRINT_ENDLINE "\n"
#define UT_PRINT_ENDLINE_LENGTH 1


/***************************************************************************/
static ut_char_t _ut_print_format_buffer[UT_PRINT_FORMAT_BUFFER_SIZE] = { 0 };



/***************************************************************************/
/*=========================================================================*/
void ut_print_char(ut_char_t ch)
{
	ut_rt_putch(ch);
}

void ut_print_string(ut_char_t* pointer, ut_size_t size)
{
	ut_size_t i;


	for (i = 0u; i < size; i++)
	{
		ut_print_char(*(pointer + i));
	}
}

void ut_print_endline(void)
{
	ut_print_string(UT_PRINT_ENDLINE, UT_PRINT_ENDLINE_LENGTH);
}

/*=========================================================================*/
void ut_print(const ut_char_t* message)
{
	while (*message != 0)
	{
		ut_print_char(*message);
		message++;
	}
}

void ut_println(const ut_char_t* message)
{
	ut_print(message);
	ut_print_endline();
}

/*=========================================================================*/
void ut_printf(const ut_char_t* format, ...)
{
	ut_size_t max_count;
	ut_int_t length;
	va_list args;


	max_count = sizeof(_ut_print_format_buffer);
	va_start(args, format);
	length = ut_rt_vsnprintf(_ut_print_format_buffer, max_count, format, args);
	va_end(args);

	if (length > 0)
	{
		ut_print_string(_ut_print_format_buffer, length);
	}
}

void ut_printfln(const ut_char_t* format, ...)
{
	ut_size_t max_count;
	ut_int_t length;
	va_list args;


	max_count = sizeof(_ut_print_format_buffer);
	va_start(args, format);
	length = ut_rt_vsnprintf(_ut_print_format_buffer, max_count, format, args);
	va_end(args);

	if (length > 0)
	{
		ut_print_string(_ut_print_format_buffer, length);
		ut_print_endline();
	}
}


