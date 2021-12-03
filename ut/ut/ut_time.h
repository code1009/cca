#ifndef ut_time__h
#define ut_time__h

/***************************************************************************/

/* ==========================================================================
**
** ut_time.h
**
** created by MOON, Eui-kwon.
** created on DEC-2nd, 2021.
**
** ==========================================================================
**/



/***************************************************************************/
typedef struct _ut_timespec_t
{
	ut_uint_t second;
	ut_uint_t nanosecond;
}
ut_timespec_t;



/***************************************************************************/
void ut_get_clocktime(ut_timespec_t* t);

void ut_time_add(ut_timespec_t* t1, ut_timespec_t* t2, ut_timespec_t* t);
void ut_time_diff(ut_timespec_t* t1, ut_timespec_t* t2, ut_timespec_t* t);






/***************************************************************************/

#endif


