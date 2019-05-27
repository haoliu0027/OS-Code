#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <string.h>

#define LED1 7
#define LED2 0
#define LED3 2
#define LED4 3

void convertToBinary(int argc, int arr[4]){
	int i = 0;
	while(argc > 0){
		arr[i] = argc % 2;
		argc = argc / 2;
		i++;
	}
}

void execute(int arr[4]){
	wiringPiSetup();
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED4, OUTPUT);
	digitalWrite(LED1, arr[0]);
	digitalWrite(LED2, arr[1]);
	digitalWrite(LED3, arr[2]);
	digitalWrite(LED4, arr[3]);
	sleep(2);
	digitalWrite(LED1, 0);
	digitalWrite(LED2, 0);
	digitalWrite(LED3, 0);
	digitalWrite(LED4, 0);
}

int main(int argc, char* argv[]){
	int len = strlen(argv[1]);
	if(argv[1][0]=='-' || len > 2) {
		printf("Not in the range\n");
		return 0;
	}
	int num = 0;
	int arg1 = (int)argv[1][0] - '0';
	if(argv[1][1]){
		int arg2 = (int)argv[1][1] - '0';
		num = arg1 * 10 + arg2;
	}else{
		num = arg1;
		printf("num value %d\n", num);
	}
	if(num > 15 || num < 0){
		printf("Not in the range\n");
		return 0;
	}
	int arr[4] = {};
	convertToBinary(num, arr);
	execute(arr);
	return 0;	
}
