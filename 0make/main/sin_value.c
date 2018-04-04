#include <stdio.h>
#include <math.h>
#define pi 3.14159
float angle;

void sin_value(void)
{
	float value;
	value = sin ( angle / 180. * pi );
	printf ("\nThe Sin is: %5.2f\n",value);
}
