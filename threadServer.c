/******************************************
 * Blocking Multithreaded Server
 * CIS 452-10 Lab 4
 * 9/27/2018
 *
 * Authors:
 * Ali Scheffler
 * Anthony Blanton
 * **************************************/

#include <pthread.h> 
#include <stdio.h> 
#include <errno.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include <signal.h>

void* getFile (void* arg); 
void sigHandlerExit();

#define MAX 64 

//Shared data
int fileCount = 0;
int fileReq = 0;

//Used to lock shared data 
static pthread_mutex_t lock;

int main() 
{ 
 	pthread_t thread1;  // thread ID holder 
 	int status;         // captures any error code
	srand(0);	    // seed random number generator

	//Install signal handler
	signal(SIGINT, sigHandlerExit);

	while(1)
	{
		//Get filename
    		printf("Please enter a filename\n");
    		char buffer[MAX];
		fgets(buffer, MAX, stdin);
		fflush(stdin);

		fileReq++;

		void* arg = (void*) buffer;

		// create and start a thread executing the "do_greeting()" function 
		// use of strdup from https://stackoverflow.com/q/5687186
		if ((status = pthread_create (&thread1, NULL,  getFile, (void *)strdup(buffer)) != 0)) { 
			fprintf (stderr, "thread create error %d: %s\n", status, strerror(status)); 
			exit (1); 
    	
		}			
		
	}

	pthread_mutex_destroy(&lock);

	return 0; 
}

void sigHandlerExit()
{
	printf("\tTerminating...\n");
	printf("File Requests Received: %d\n", fileReq);
	printf("File Requests Serviced: %d\n", fileCount);
	exit(0);
}

void* getFile (void * arg) 
{

	//Get random number between 0 and 9
	int prob = rand() % 10;
	int sleepTime = 1;

	if(prob < 8)
	{
		sleep(sleepTime);	
	}
	else{
		sleepTime = (rand() % 4) + 7;
		sleep(sleepTime);
	}

	//Lock while thread is running critical section	
	pthread_mutex_lock(&lock);
	fileCount++;
	simTime += sleepTime;
	pthread_mutex_unlock(&lock);

	printf("File found: %s\n", arg);

	return arg;
}

