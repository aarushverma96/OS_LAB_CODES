#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int n=1;
sem_t t1,t2;

void **even(void)
{
	int i;
	for(i=0;i<25;i++)
	{
		sem_wait(&t1);
		while(n%2!=0)
		{
			n++;
		}
		printf("%d",n);
		sem_post(&t2);
	}
}

void **odd(void)
{
	int i;
	for(i=0;i<25;i++)
	{
		sem_wait(&t2);
		while(n%2==0)
		{
			n++;
		}
		printf("%d",n);
		sem_post(&t1);
	}
}





int main()
{
	pthread_t tid1;
	pthread_t tid2;
	sem_init(&t1,0,0);
	sem_init(&t2,0,1);
	pthread_create(&tid1,NULL,even,NULL);
	pthread_create(&tid2,NULL,odd,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

}