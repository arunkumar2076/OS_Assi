#include <pthread.h>		
#include <semaphore.h>		
#include <stdio.h>	
void main()
{
	int cstudents;		
	int i,input;

	
	

	if(input<=1)
	{
		printf("Number of Students not specified. Using default (4) students.\n");
		cstudents = 4;
	}
	
	else
	{
		printf("Number of Students specified. Creating %d threads.\n",cstudents);
		cstudents = input;
	}
	
	Students = malloc(sizeof(cstudents));	
	
	pthread_create(&Reception, NULL, Reception_Activity, NULL);	
	
	for(i = 0; i <cstudents; i++)
	{
		pthread_create(&Students[i], NULL, Activity_student_thread,(void*) (long)i);
	}
	
	pthread_join(Reception, NULL);
	
	for(i = 0; i <cstudents; i++)
	{
		pthread_join(Students[i], NULL);
	}
}
void *Activity_student_thread(void *threadID) 
{

	printf(" Student %ld is doing programming assignment . \n ", (long)threadID);
	sleep(3);		

	printf(" Student %ld needs help from the TA\n", (long)threadID);

	pthread_mutex_lock(&ChairsAccess);
	int count = out_side_Chairs;
	pthread_mutex_unlock(&ChairsAccess);
	if(count < 3)		
	{
		if(count == 0)		
		sem_post(&recip_Sleep);

		else
			printf("Student %ld sat on a chair waiting for the TA to finish. \n", (long)threadID);
		
		
		pthread_mutex_lock(&ChairsAccess);
		int index = (Current_Chair_Index + out_side_Chairs) % 3;
		out_side_Chairs++;
		printf("Student sat on chair.Chairs Remaining: %d\n", 3 - out_side_Chairs);
		pthread_mutex_unlock(&ChairsAccess);

		
		sem_wait(&out_Chairs_side_Sem[index]);		
		printf("\t Student %ld is getting help from the TA. \n", (long)threadID);
		sem_wait(&wait_Student_Sem);		
		printf("Student %ld left TA room.\n",(long)threadID);
	}
	
	else 
		printf("Student %ld will return at another time. \n", (long)threadID);
	
}
