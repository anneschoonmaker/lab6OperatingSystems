#include <stdint.h>
#include <pthread.h>

#include "circle.h"

#define WAITING_FOR_SAMPLE -1
#define OUTSIDE_CIRCLE 0
#define INSIDE_CIRCLE 1

#define WORKER_COUNT 5
#define NITERS 10000

/* shared variable for the threads to update */
volatile int var = WAITING_FOR_SAMPLE;
pthread_mutex_t lock;
static void * pthread_fn(void *arg){
	//need a lock
	while(1){
	printf("%s", "in thread \n");
	while( var != WAITING_FOR_SAMPLE);
	pthread_mutex_lock(&lock);
	if(var == WAITING_FOR_SAMPLE){
			var = circle();
	pthread_mutex_unlock(&lock);
	}
	// var = circle();
	// pthread_mutex_unlock(&lock);
	}
	//need to unlocl 
	return NULL;
}
int main(void)
{
	pthread_t thread1;
	uint32_t total_in_arc = 0;
	//pthread create makes a thread and has a function associated with it 
	//for loop that creates processes ?
	for(int i = 0 ; i < WORKER_COUNT; i++){
		// pthread_create();
		pthread_create(&thread1, NULL, &pthread_fn, NULL);
	}
	
	for (uint32_t i = 0; i < NITERS; i++)
	{
		//just need to spin 
		while(var == WAITING_FOR_SAMPLE){
		}
		pthread_mutex_lock(&lock);
		//critical section
		//must be ready and have a sample 
		//while(waiting for sample)
		if (circle() == INSIDE_CIRCLE)
		{
			total_in_arc++;
		}
		pthread_mutex_unlock(&lock);
	}
	// if(pthread_join(thread1))

	/* We multiply by four because circle() uses an 1/4 circular arc */
	printf("The value of pi is: %f\n", (double)total_in_arc / NITERS * 4);

	return 0;

}

