#include <stdio.h>

#include "my_app_define.h"
#include "my_app_main.h"
#include "my_app_module.h"

MY_API int my_app_main (void)
{
	int a;
	int b;
	int c;


	a = 1;
	b = 2;
	c = my_div(a,b);
	
	printf ("my_div(%d, %d) = %d \r\n", a, b, c);

	if ((c % 2) == 0)
	{
		return 0;
	}

	return 1;
}

