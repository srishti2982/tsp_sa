#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define INITIAL_TEMPERATURE 999999999999999
#define TEMPERATURE_UPDATE_FACTOR 0.999
#define TRIAL_LIMIT 1000000

typedef struct coordinate
{
	float x;
	float y;
}c;

void dealocate(float **edge,int n);
float cal_cost(float **edge,int path[],int n);
int minima(float a,float b,float c);
void inverse(int path[],int n,int a ,int b);
void insert(int path[],int n,int a ,int b);
void swap(int path[],int n,int a ,int b);
void print_path(int path[],int n);
void copyarr(int a[],int b[],int n);
float cal_prob(float delta,float T);

int main(){

	char type[50];
	int n;
	int a,b;
	float r,p,T;
	scanf("%s%d",type,&n);
	c city[n];
	float *edge[n];
    for (int i=0; i<n; i++)
         edge[i] = (float *)malloc(n * sizeof(float));
	int path_c[n+1];
	int path_nr[n+1];
	int path_ni[n+1];
	int path_ns[n+1];
	int path_b[n+1];
	for (int i = 0; i < n; ++i)
	{
		scanf("%f %f",&city[i].x,&city[i].y);
		path_c[i]=i;
		path_nr[i]=i;
		path_ni[i]=i;
		path_ns[i]=i;
		path_b[i]=i;
	}
	path_c[n] =0;
	path_nr[n] =0;
	path_ni[n] =0;
	path_ns[n] =0;
	path_b[n] =0;
	float cost_r,cost_c,cost_i,cost_s,cost_b,delta;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			scanf("%f",&edge[i][j]);
		}
		
	}
	 int temp,choice;	
	 int counter = 0;
	int k = 10;
	 srand ( time(NULL) );
		while(1)
		{
			
					
				  	 a = rand()%n;
				  	 b = rand()%n;

				  	 if(a > b)
				  	 {
				  	 	temp = b;
				  	 	b =a;
				  	 	a =temp;
				  	 }
				  	 //printf("a::%d  b::%d\n",a,b);
				  	 cost_c = cal_cost(edge,path_c,n); 
				  	 cost_b = cal_cost(edge,path_b,n);

				  	 
				  	 copyarr(path_nr,path_c,n);
				  	 inverse(path_nr,n,a,b);
				  	 cost_r = cal_cost(edge,path_nr,n);

				  	 copyarr(path_ni,path_c,n);
				  	 insert(path_ni,n,a,b);
				  	 cost_i = cal_cost(edge,path_ni,n);

				  	 copyarr(path_ns,path_c,n);
				  	 swap(path_ns,n,a,b);
					 cost_s = cal_cost(edge,path_ns,n);  	 

				  	 choice = minima(cost_r,cost_i,cost_s);
				  	 r = (float) (rand()/ (float) RAND_MAX);
				  	// choice =1;
				  	 switch(choice)
				  	 {
				  	 	case 1:
				  	 		delta = cost_r - cost_c;
				  	 		p = cal_prob(delta,T);
				  	 		if(p > r)
				  	 			copyarr(path_c,path_nr,n);
				  	 		break;
				  	 	case 2:
				  	 		delta = cost_i - cost_c;
				  	 		p = cal_prob(delta,T);
				  	 		if(p > r)
				  	 			copyarr(path_c,path_ni,n);
				  	 		break;
				  	 	case 3:
				  	 		delta = cost_s - cost_c;
				  			p = cal_prob(delta,T);
				  			if(p > r)
				  	 			copyarr(path_c,path_ns,n);
				  			break; 
				  	 }	
				  	 cost_c = cal_cost(edge,path_c,n);
				  	 
				  	 if(cost_c < cost_b){
				  	 	copyarr(path_b,path_c,n);
				  	 	printf("COST_BEST :: %f\n",cost_c);
				  	 	//print_path(path_b,n);
				  	 	counter=0;
				  	 }
				  	 else
				  	 	counter++;
				 

		  	 T *=  TEMPERATURE_UPDATE_FACTOR;
			 if(counter > TRIAL_LIMIT)
			 {
		     	 T = k*n;
			 	 k += k;
				 if(T>INITIAL_TEMPERATURE)
				 {
				 	T = INITIAL_TEMPERATURE;
					k = 10;
				 }
				 counter = 0 ;
				 fflush(stdout) ;
			 }

		}
	//printf("\nThe Cost is %f",cal_cost(edge,n,path_c));

	//dealocate(edge,n);
	return 0;
}

float cal_cost(float **edge,int path[],int n){
	float cost=0;;
	for (int i = 1; i < n; ++i)
	{
	 	
		 cost= cost + edge[path[i]][path[i-1]];
		 //	printf("%f",cost);		
	}
	return cost;
}
void dealocate(float **edge,int n){
	for (int i = 0; i < n; ++i)
	{	
		free(edge[i]);
	}
	free(edge);
}
void inverse(int path[],int n,int a ,int b){
	int temp;
	for (int i = 0; i <= (b-a)/2; ++i)
	{
		temp = path[a+i];
		path[a+i] = path[b-i];
		path[b-i] = temp;
	}

}
void insert(int path[],int n , int a, int b){
	int temp = path[b];
	for (int i = 0; i <= b-a-1; ++i)
	{	
		path[b-i] = path[b-(i+1)];
	}
	path[a] = temp;
}
void swap(int path[],int n, int a,int b){
	int temp;
	temp = path[a];
	path[a] = path[b];
	path[b] = temp;
}
int minima(float a,float b,float c){
	float min;
	min = a;
	if(b < min)
		min = b;
	if(c < min)
		min = c;
	if(min == a)
		return 1;
	else if (min ==b)
		return 2;
	else
		return 3;
}
void print_path(int path[],int n){
	for (int i = 0; i < n; ++i)
	{
		printf("%d",path[i]);
	}
	printf("\n");
}
void copyarr(int a[],int b[],int n){
	for (int i = 0; i < n; ++i)
	{
		a[i] = b[i];
	}
}
float cal_prob(float delta,float T){
	 return 1/(1+ exp(delta/T));

}