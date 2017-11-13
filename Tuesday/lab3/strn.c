#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 
int arrt[10],burstt[10],remaint[10],terminateT,i,min;
int remain=0,n,time1,waitSum=0,taS=0;
int INT_MAX=9999;


void *creation(void *vargp)
{
		printf("Enter no of Processes : ");
		scanf("%d",&n);
	arrt[0] = 0;
	//bt[0] = 5;
		for(i=0;i<n;i++)
		{
		arrt[i+1] = arrt[i] + 2;
		burstt[i] = rand()%10;
				remaint[i]=burstt[i];
		}
	
	printf("\n\nProcess\t|Arrival Time\t| Burst Time");	

	for(i=0;i<n;i++)
		{
		printf("\nP[%d]\t|\t%d\t|\t%d",i+1,arrt[i],burstt[i]);		
	}

	
		return NULL;
}


void *srtn(void *vargp)
{
		printf("\n\nProcess\t|Turnaround Time| Waiting Time");
		remaint[9]=INT_MAX;
		for(time1=0;remain!=n;time1++)
		{
			min=9;
			for(i=0;i<n;i++)
			{
				if(arrt[i]<=time1 && remaint[i]<remaint[min] && remaint[i]>0)
				{
					min=i;
				}
			}
				remaint[min]--;
		if(remaint[min]==0)
			{
					remain++;
					terminateT=time1+1;
					printf("\nP[%d]\t|\t%d\t|\t%d",min+1,terminateT-arrt[min],terminateT-burstt[min]-arrt[min]);
					waitSum+=terminateT-burstt[min]-arrt[min];
					taS+=terminateT-arrt[min];
			}
		}
		printf("\n\nAverage waiting time = %f\n",waitSum*1.0/n);
		printf("Average Turnaround time = %f\n",taS*1.0/5);
		return NULL;
}



int main()
{
		pthread_t tid;
		pthread_create(&tid, NULL, creation, NULL);
		pthread_join(tid, NULL);
		pthread_create(&tid, NULL, srtn, NULL);
		pthread_join(tid, NULL);
		exit(0);
}