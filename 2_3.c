#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <wiringPi.h>
#include <stdlib.h>
//#include <fcntl.h>
#include <math.h>
#include <time.h>

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
		if(num > 15 || num < -1){
			printf("Not in the range\n");
			num = 0;
		}
		//sleep(0.5);
	}
	pthread_exit(NULL);
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
	//if(num == -1) pthread_exit((void*)1);
	if(num > 15 || num < -1){}
	else{
		while(1){
			if(ctr > num){
				ctr--;
			}else if(ctr < num){
				ctr++;
			}
			convertToBinary(ctr, arr);
			execute(arr);
		}
	}
	pthread_exit(NULL);	
}

void *opFile(void* arg){
	double result = 0;
	char line[10];
	FILE *fp;
	clock_t t;
	double time_spend;
	fp = fopen("data.txt","r");
	t = clock();
	while(fgets(line, sizeof(line), fp)){
		//printf("%s\n",line);
		double fNumber = atof(line);
		result = result + fNumber;
		fNumber = atan(tan(fNumber));
		//printf("fNUmber is : %lf\n", fNumber);
	}
	t = clock() - t;
	time_spend = (double)t/CLOCKS_PER_SEC;
	printf("the duration is : %lf\n", time_spend);
	printf("the result is : %lf\n",result);
	fclose(fp);
	/**************why wrong ***********************/
	//int fd = open("data.txt", O_RDWR);
	//if(fd == -1){
	//	perror("doesn`t open the file");
	//	exit(2);
	//}else{
		
		//int fdlen = lseek(fd, 0, SEEK_END);
		//printf("the len is : %d\n", fdlen);
		//sleep(3);
		//while((i = read(fd, line, sizeof(line)))> 0){
		//	read(fd, line, i);
		//	double fNumber = atof(line);
		//	sleep(1);
		//	printf("line: %s \n",line);
			//sleep(1);
		//	printf("float is %lf", fNumber);
			//sleep(1);
		//}
		//close(fd);
	//}
	/**************************************************/
	pthread_exit(0);
}

int main(int argc, char* argv[]){
	wiringPiSetup();
	pthread_t p1, p2, p3;
        pthread_create(&p1, NULL, check, NULL);
	pthread_create(&p2, NULL, count, NULL);
	pthread_create(&p3, NULL, opFile, NULL);
	pthread_join(p1,NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	return 0;
}
