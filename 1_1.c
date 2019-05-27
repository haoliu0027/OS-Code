#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(){
	char name[7] = "Hao Liu";
	char stuNO[7]= "4807456";
	printf("Name is : %s\n", name);
	printf("Student number is : %s\n", stuNO);
	printf("ID of the process is : %d\n", getpid());
	return 0;
}
