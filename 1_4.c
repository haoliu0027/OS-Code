#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
/*Both threads and processes are independent sequences of execution,
* But thread s run in a shared memory, process run in separate 
* memory space*/
void *thread_call(void *arg);

int main(){
	pthread_t thread_id;
	int ret_num;
	ret_num = pthread_create(&thread_id, NULL, thread_call, NULL);
	if(ret_num != 0){
		printf("the thread is failed");
		return -1;
	}
	pthread_join(thread_id, NULL);
}

void *thread_call(void*arg){
	system("ls");
	return NULL;
}
