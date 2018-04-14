#include <pthread.h>		
#include <semaphore.h>		
#include <stdio.h>	
#include<math.h>

pthread_t *Students;		
pthread_t Reception;		

int out_side_Chairs = 0;
int Current_Chair_Index = 0;

sem_t recip_Sleep;
sem_t wait_Student_Sem;
sem_t out_Chairs_side_Sem[3];
pthread_mutex_t ChairsAccess;

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



void *Reception_Activity()
{
	sem_wait(&recip_Sleep);
	printf("\n\t Reception man has been awakened by a student.\t\n");

	while(1)
	{
		
		pthread_mutex_lock(&ChairsAccess);
		
		if(out_side_Chairs == 0) 
		{
		
			pthread_mutex_unlock(&ChairsAccess);
			break;
		}
		
		sem_post(&out_Chairs_side_Sem[Current_Chair_Index]);
		out_side_Chairs--;
		printf("Student left his/her chair. Remaining Chairs %d\n", 3 - out_side_Chairs);
		Current_Chair_Index = (Current_Chair_Index + 1) % 3;
		pthread_mutex_unlock(&ChairsAccess);

		printf("\t Reception man is currently helping the student.\n");
		sem_post(&wait_Student_Sem);
		sleep(3);
	}
}



void main()
{
	int cstudents;		
	int i,input;

	sem_init(&recip_Sleep, 0, 0);
	sem_init(&wait_Student_Sem, 0, 0);
	
	for(i = 0; i < 3; i++)
	{	
		sem_init(&out_Chairs_side_Sem[i], 0, 1);		
	}

	
	input=rand()%10;
	pthread_mutex_init(&ChairsAccess, NULL);
	
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
