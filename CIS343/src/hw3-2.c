#include <stdio.h>
#include <string.h>
int main(void){
	int ages[10];
	printf("%d\n",(int) sizeof(ages));
	char name[6] = {'f','r','e','d','\0'};
	printf("%d\n",(int) sizeof(name));
	double costs[] = {[0] = 0.00, [9999] = 999.99};
	printf("%d\n",(int) sizeof(costs));
	int chart[3][4] = {{0,3,4},{1,2,3,}};
	printf("%d\n",(int) sizeof(chart));     	
}
