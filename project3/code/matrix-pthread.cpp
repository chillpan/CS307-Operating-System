#include <pthread.h>
#include <stdio.h>
#include <malloc.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <ctime>

#define M 1000
#define K 1000
#define N 1000
#define NUM_THREADS 100

int A[M][K];
int B[K][N];
int C[M][N];
int D[M][N];

//struct for passing data to threads
struct v
{
	int i; //row
	int j; //column
};

inline void *run(void *data)
{
	int sum=0;
	struct v *d=(struct v*)data;
	// redefine data
	int j=d->j;
	// i=d->i i = 0; To allocate the thread 
	for (int m = j; m<M ; m+=NUM_THREADS) //row
	{	
		for (int n = 0; n < N; ++n)
		{
			sum=0;
			for (int e = 0; e < K; ++e)
			{
				sum+=A[m][e]*B[e][n];
			}
			C[m][n]=sum;
		}
	}
	//printf("relative pid for %d is %g", j);
	pthread_exit(0);
}



int main(){
	printf("The number of threads: %d \n", NUM_THREADS);
	struct timeval start, end, start2, end2;
	pthread_t workers[NUM_THREADS]; //300 pthread
	pthread_attr_t attr; //To initial the pthread attrbute
	pthread_attr_init(&attr); 
	
	//initialize
	srand(unsigned(time(0)));
	for(int i=0;i<M;++i)
	{
		for(int j=0;j<N;++j)
		{
			A[i][j]=rand()%100;
			B[i][j]=rand()%100;
		}
	}
	//parallel calculate 
	gettimeofday(&start, NULL);
	int tmp = 0;
//for (int i = 0; i < 1, i + + ) 
	for(int j=0;j<NUM_THREADS;++j)
	{
		struct v *data=(struct v*)malloc(sizeof(struct v));
		data->i=0;
		data->j=j;
		pthread_create(&workers[tmp],&attr,run,data);
		//create thread, run is the start_routine and data is the arg
		++tmp;
		if(tmp==NUM_THREADS)
		{
			for(int x=0;x<NUM_THREADS;++x)
			{
				pthread_join(workers[x],NULL);
			}
		}
	}
//}
	gettimeofday(&end, NULL);
	int timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("The time of pthread is: %d usec \n", timeuse);
	
	//direct calculate 
	gettimeofday(&start2, NULL);
	int sum;
	for(int i=0;i<M;++i)
	{
		for(int j=0;j<N;++j)
		{
			sum=0;
			for(int e=0;e<K;++e)
			{
				sum+=A[i][e]*B[e][j];
			}
			D[i][j]=sum;
		}
	}
	gettimeofday(&end2, NULL);
	int timeuse2 = 1000000*(end2.tv_sec-start2.tv_sec)+end2.tv_usec-start2.tv_usec;
	printf("The time of no thread is: %d usec \n",timeuse2);
	double timeuse2_dou = timeuse2;
	printf("The speed up of threading is: %f \n", timeuse2_dou/timeuse );
	for(int i=0;i<M;++i)
	{
		for(int j=0;j<N;++j)
		{
			if(C[i][j]!=D[i][j]) 
			{
				printf("i: %d j: %d C: %d D: %d\n",i,j,C[i][j],D[i][j]);
			}
		}

	}
	return 0;
}
