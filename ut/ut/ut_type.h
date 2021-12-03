#ifndef ut_type__h
#define ut_type__h

/***************************************************************************/

/* ==========================================================================
**
** ut_type.h
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef void* ut_pointer_t; // 4 bytes



//===========================================================================
typedef signed   int ut_int_t;
typedef unsigned int ut_uint_t;

typedef signed             char ut_int8_t; //                       -128 ~ +127
typedef signed   short     int  ut_int16_t; //                    -32,768 ~ +32,767
typedef signed   long      int  ut_int32_t; //             -2,147,483,648 ~ +2,147,483,647
typedef signed   long long int  ut_int64_t; // -9,223,372,036,854,775,808 ~ +9,223,372,036,854,775,807
typedef unsigned           char ut_uint8_t; // 0 ~ 255
typedef unsigned short     int  ut_uint16_t; // 0 ~ 65,535
typedef unsigned long      int  ut_uint32_t; // 0 ~ 4,294,967,295
typedef unsigned long long int  ut_uint64_t; // 0 ~ 18,446,744,073,709,551,615



//===========================================================================
typedef float  ut_float_t;
typedef double ut_double_t;


/*
IEEE 754

1. 플로팅포인트 표현에서 모든 비트가 0인 수는 0으로 정의
2. 지수부의 모든 비트가 0인 수는 가수의 정수부분을 0으로 계산
3. 지수부의 모든 비트가 1이고, 가수부의 모든 비트가 0이면 무한대로 정의
4. 지수부의 모든 비트가 1이고, 가수부가 0이 아니면 NaN (Not a Number)로 정의하여 예외를 발생
*/

// 부호   (sign    ) : bit31       -  1비트
// 가수부 (exponent) : bit30~bit23 -  8비트 
// 지수부 (mantissa) : bit22~bit0  - 23비트
typedef float ut_float32_t; // 3.4E+/-38 ( 7개의 자릿수) 

// 부호   (sign    ) : bit63       -  1비트
// 가수부 (exponent) : bit62~bit52 - 11비트
// 지수부 (mantissa) : bit51~bit0  - 52비트
typedef double ut_double64_t; // 1.7E+/-308(15개의 자릿수)



//===========================================================================
typedef char ut_char_t;

typedef ut_uint8_t  ut_uchar8_t;
typedef ut_uint16_t ut_uchar16_t;
typedef ut_uint32_t ut_uchar32_t;

/*
char16_t std-C++11 정의됨
char32_t std-C++11 정의됨
char     a   = '\x30';                      // character, no semantics
wchar_t  b   = L'\xFFEF';                   // wide character, no semantics
char16_t c   = u'\u00F6';                   // 16-bit, assumed UTF16
char32_t d   = U'\U0010FFFF';               // 32-bit, assumed UCS-4
char     A[] =  "Hello\x0A";                // byte string (narrow)
wchar_t  B[] = L"Hell\xF6\x0A";             // wide string
char16_t C[] = u"Hell\u00F6";               //
char32_t D[] = U"Hell\U000000F6\U0010FFFF"; //
auto     E[] = u8"\u00F6\U0010FFFF";        //
*/



//===========================================================================
typedef ut_uint8_t ut_bool_t;



//===========================================================================
typedef unsigned char ut_byte_t;



//===========================================================================
typedef ut_uint32_t ut_size_t;
typedef ut_int32_t  ut_time_t;



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#ifndef ut_true
#define ut_true 1u
#endif

#ifndef ut_false
#define ut_false 0u
#endif

#ifndef ut_nullptr
#define ut_nullptr 0u
#endif



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if defined ( __cplusplus )
#	define UT_API extern "C"
#else
#	define UT_API extern
#endif





/***************************************************************************/

#endif


