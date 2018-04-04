#include <stdio.h>
#define pi 3.14159
char name[15];
float angle;

int main(void)
{
	printf ("\n\nPlease input your name: ");
	scanf  ("%s", &name );
	printf ("\nPlease enter the degree angle (ex> 90): " );
	scanf  ("%f", &angle );
	haha( name );
	sin_value( angle );
	cos_value( angle );
}
