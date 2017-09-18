#include <stdio.h>
#include <string.h>
#include "ros/ros.h"
int main(){
int i;
unsigned int a=-1,b=7;
printf("%x\n",a);
std::string c="#abcdefgh";
i=c.find("ab");
printf("find ab %d\n",i);
i=c.find("ad");
printf("find ad %d\n",i);
i=c.length();
printf("length %d\n",i);
if(c.find("adb")<=c.length()){
	printf("true\n");
}else if(c.find("abc")<=c.length()){
	printf("true2\n");
}else{
	printf("false\n");
}
if(a<=7){
printf("1\n");
}else{
printf("-1\n");
}
return 0;
}
