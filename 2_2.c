#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <wiringPi.h>
#include <stdlib.h>

#define LED1 7
#define LED2 0
#define LED3 2
#define LED4 3

int num = 0;
int ctr = 0;

void *check(void *arg){
	while(1){
		scanf("%d", &num);
		printf("your numberr: %d\n", num);
		if(num == -1) exit(0);
		if(num > 15 || num < -1)printf("Not in the range\n");
	}
	return 0;
}

void convertToBinary(int ctr, int arr[4]){
	arr[0] = 0; arr[1] = 0; arr[2]= 0; arr[3] = 0;
	int i = 0;
	while(ctr > 0){
		arr[i] = ctr % 2;
		ctr = ctr / 2;
		i++;
	}
}

void execute(int arr[4]){
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED4, OUTPUT);
	digitalWrite(LED1, arr[0]);
	digitalWrite(LED2, arr[1]);
	digitalWrite(LED3, arr[2]);
	digitalWrite(LED4, arr[3]);
	sleep(0.2);
	digitalWrite(LED1, 0);
	digitalWrite(LED2, 0);
	digitalWrite(LED3, 0);
	digitalWrite(LED4, 0);
}

void *count(void *arg){
	int arr[4] = {0, 0, 0, 0};
	
	while(1){
		if(num > 15 || num < -1){}
		else{
			if(ctr > num){
				ctr--;
			}else if(ctr < num){
				ctr++;
			}
			convertToBinary(ctr, arr);
			execute(arr);
		}
	}	
}

int main(int argc, char* argv[]){
	wiringPiSetup();
	pthread_t p1, p2;
        pthread_create(&p1, NULL, check, NULL);
	pthread_create(&p2, NULL, count, NULL);
	pthread_join(p1,NULL);
	pthread_join(p2, NULL);
	return 0;
}
