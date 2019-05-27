#include <stdio.h>
char *strcpy(char *dst,char *src)
{
	char *return_point=dst;
	for (;*src!='\0';*dst++=*src++);
	*dst='\0';  //断截dst的原有字符串 
	return return_point;   //return_point储存dst最开始指向的地址 
}
char *strcat(char *dst,char *src)
{
	char *retrun_point=dst;
	for(;*dst!='\0';dst++);
	for(;*src!='\0';*dst++=*src++);
	return retrun_point;
}
int strlen(char *src)
{
	int length=0;
	for(;*src!='\0';src++)
	{
		length++;
	}
	return length;
}
int strindex(char *src,char ch)
{
	int index=0;
	for(;*src!='\0';src++)
	{
		if(*src==ch)
		{
			return index;
		}
		index++;
	}
	return -1;
}
int main()
{
	char dst[100]="Hello This is Test,rihgt?";
	char src[]="Nope";
	char test='z';
	int a=strindex(dst,test);
	printf("%d",a);
	return 0;
}
