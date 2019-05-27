#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LINE 80
#define BUFFER_SIZE 50

char history[10][BUFFER_SIZE];
int count = 0;

void displayHistory(){
	printf("Shell command history : \n");
	int i; int j = 0;
	int histCount = count;
	for(i = 0; i < 10; i++){
		printf("%d ", histCount);
		while(history[i][j] != '\n'&& history[i][j] != '\0'){
			printf("%c", history[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		histCount--;
		if(histCount == 0) break;
	}
	printf("\n");
}

int parseCommand(char inputBuffer[], char* args[], int* flag){
	
	int length;
	int i; // loop index for inputBuffer
	int start;//index of begining of next command
	int ct = 0; //index of position in args

	length = read(STDIN_FILENO, inputBuffer, MAX_LINE);
	
	for(i = 9; i>0; i --){
		strcpy(history[i], history[i-1]);
	}
	strcpy(history[0], inputBuffer);
	count ++;
	if(count > 10)count = 10;
	start = -1;
	if(length == 0) exit(0); // 0 is the exit code 
	if(length < 0){
		printf("Command can not read\n");
		exit(-1);
	}
	
	for(i = 0; i < length; i++){
		switch(inputBuffer[i]){
			case ' ':
			case '\t':   //tab
				if(start != -1){
					args[ct] = &inputBuffer[start];
					ct++;
				}
				inputBuffer[i] = '\0'; //add a NULL char at the end
				start = -1;
				break;
			case '\n':
				if(start != -1){
					args[ct] = &inputBuffer[start];
					ct++;
				}
				inputBuffer[i] = '\0';
				args[ct] = NULL; // no more args
				break;
			default:
				if(start == -1) start = i;
				if(inputBuffer[i] == '&'){
					*flag = 1;
					inputBuffer[i] = '\0';   
					inputBuffer[i+1] = '\0';   
					inputBuffer[i-1] = '\0';
				}
		}
	}
	args[ct] = NULL; //if the input line was > 80
	if(strcmp(args[0], "history") == 0){
		if(count > 0) displayHistory();
		else printf("\n No Commands in the history\n");
		return -1;
	}else if(strcmp(args[0], "!!") == 0){
		if(count > 0) printf("%s", history[1]);
		return -1;
	}else if(args[0][0] == '!'&&args[0][2] == '\0'){
		int x = args[0][1] - '0';
		if(x <= count){
			printf("%s", history[count - x]);
		}
		return -1;
	}
	
	return start;
}

int main(){
	char inputBuffer[MAX_LINE];
	char* args[MAX_LINE/2 + 1];
	int flag; // judge if follows &
	int should_run = 1;
	pid_t pid;
	int i;
	while(should_run){
		flag = 0;
		printf("osh>");
		fflush(stdout);
	if(-1!=	parseCommand(inputBuffer, args, &flag)){
		pid = fork();
		if(pid < 0){
			printf("fork failed \n");
			exit(1);
		}else if(pid == 0){
			if(execvp(args[0], args)== -1) perror("error");
			}else{
				i++;
				if(flag == 0){
					i++;
					wait(NULL);
				}		
			}
		}
	}
}
