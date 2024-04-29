#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);

void mergesort(int a[],int i,int j)
{
	omp_set_num_threads(4);
	int mid;
	if(i<j)
	{
		//array is recursively divided into two halves
    		mid=(i+j)/2;

		//each half is sorted in parallel using OpenMP sections
    		#pragma omp parallel sections
    		{

        			#pragma omp section
        			{
            				mergesort(a,i,mid);   	 
        			}

        			#pragma omp section
        			{
            				mergesort(a,mid+1,j);    
        			}
    		}

		//// Merging the sorted halves
    		merge(a,i,mid,mid+1,j);    
	}

}
 
void merge(int a[],int i1,int j1,int i2,int j2)
{
	int temp[1000];    
	int i,j,k;
	i=i1;    
	j=i2;    
	k=0; //index of temporary array
    
	while(i<=j1 && j<=j2)    
	{
    		if(a[i]<a[j])
    		{
        			temp[k++]=a[i++];
    		}
    		else
    		{
        			temp[k++]=a[j++];
    		}    
	}
    
	while(i<=j1)    
	{
    		temp[k++]=a[i++];
	}
   	 
	while(j<=j2)    
	{
    		temp[k++]=a[j++];
	}
   	 
	for(i=i1,j=0;i<=j2;i++,j++)
	{
    		a[i]=temp[j];
	}    
}


int main()
{
	/*
	int *a,n;
    	cout<<"\n enter total no of elements=>";
    	cin>>n;
    	a=new int[n];
    	cout<<"\n enter elements=>";
    	for(int i=0;i<n;i++)
    	{
   	 	cin>>a[i];
    	}
	*/

	int SIZE =200;
 	int i,j;
    	int a[SIZE];
    
    	for(i=0;i<SIZE;i++)
    	{
        		a[i]=rand()%SIZE;
    	}
    
   	int n = SIZE;
    	double start,end;	

	start=omp_get_wtime();
	mergesort(a, 0, n-1);
	end=omp_get_wtime();

	cout<<"\n sorted array is=>";
	for(i=0;i<n;i++)
	{
    		cout<<a[i]<<”  ”;
	}
  	
	Cout<<"\n-------------------------\n Time Parallel= "<<(end-start);
	return 0;
}
