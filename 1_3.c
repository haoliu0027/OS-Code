#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
	pid_t pid = fork();
	if(pid == 0){
		system("ls");
		exit(0);		
	}else{
		wait(NULL);
	}
	return 0;

}