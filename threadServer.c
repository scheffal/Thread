#include <pthread.h> 
#include <stdio.h> 
#include <errno.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include <signal.h>

void* getFile (void* arg); 
// arguments:    arg is an untyped pointer 
// returns:         a pointer to whatever was passed in to arg 
// side effects:  prints a greeting message
void sigHandlerExit();

#define MAX 64 

int fileCount = 0;
static pthread_mutex_t lock;

int main() 
{ 
 	pthread_t thread1;  // thread ID holder 
 	int status;         // captures any error code
	srand(0);
	signal(SIGINT, sigHandlerExit);

	while(1)
	{

    		printf("Please enter a filename\n");
    		char buffer[MAX];
		fgets(buffer, MAX, stdin);
		fflush(stdin);

		void* arg = (void*) buffer;

		// create and start a thread executing the "do_greeting()" function 
    		if ((status = pthread_create (&thread1, NULL,  getFile, arg) != 0)) { 
        		fprintf (stderr, "thread create error %d: %s\n", status, strerror(status)); 
        		exit (1); 
    	
		}			
	

	}

	pthread_mutex_destroy(&lock);

	return 0; 
}

void sigHandlerExit()
{
	printf("\tTerminating... File count: %d\n", fileCount);
	exit(0);
}

void* getFile (void * arg) 
{

	int prob = rand() % 10;

	if(prob < 8)
	{
		sleep(1);	
	}
	else{
		int sleepTime = rand() % 4;
		sleep(sleepTime + 7);
	}
	
	pthread_mutex_lock(&lock);
	fileCount++;
	pthread_mutex_unlock(&lock);

	printf("File found: %s\n", arg);

	

	return arg;
}
