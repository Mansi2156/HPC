#include <iostream>
//#include <vector>
#include <omp.h>
#include <climits> //defining integer limits
using namespace std;

void min_reduction(int arr[], int n) 
{
	int min_value = INT_MAX;
  	#pragma omp parallel for reduction(min: min_value)
	//min=operation,min_value=variable that will hold the result of the reduction operation
  	for (int i = 0; i < n; i++) 
	{
		if (arr[i] < min_value) {
  			min_value = arr[i];
		}
  	}
  	cout << "Minimum value: " << min_value << endl;
}

void max_reduction(int arr[], int n) 
{
	int max_value = INT_MIN;
  	#pragma omp parallel for reduction(max: max_value)
  	for (int i = 0; i < n; i++) 
	{
		if (arr[i] > max_value) {
  			max_value = arr[i];
		}
  	}
  	cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(int arr[], int n) 
{
	int sum = 0;
   	#pragma omp parallel for reduction(+: sum)
   	for (int i = 0; i < n; i++) 
	{
		sum += arr[i];
  	}
  	cout << "Sum: " << sum << endl;
}

void average_reduction(int arr[], int n) {
	int sum = 0;
  	#pragma omp parallel for reduction(+: sum)
  	for (int i = 0; i < n; i++) {
		sum += arr[i];
  	}
  	cout << "Average: " << (double)sum / (n-1) << endl;
}

int main() 
{
	omp_set_num_threads(4);
	
	int arr[] = {73, 85, 66, 40, 80, 81, 99, 97, 12, 85, 191, 47, 20, 100, 325, 184, 412, 7, 22, 89
	,78, 221, 2, 67, 50, 90, 101, 441, 133, 216, 141, 16, 127, 53, 4, 65, 235, 71, 35, 73, 6, 10, 44, 98
	, 108, 22, 38, 7, 51, 79, 100, 81, 25, 48, 9, 86, 18, 432, 5, 14, 36, 344, 333, 159, 84, 175, 193,
	20, 88, 13, 31, 65, 12, 9, 46, 75, 208, 76, 410, 70, 124, 11, 3, 142, 29, 32, 52, 47, 54, 92, 74,
	56, 65, 38, 22, 18, 20, 30, 40, 50};
	
    	int n = 100;
    	double start,end;
	start=omp_get_wtime();

	min_reduction(arr, n);
	max_reduction(arr, n);
	sum_reduction(arr, n);
	average_reduction(arr, n);

	end=omp_get_wtime();

	printf("\n-------------------------\n Time Parallel= %f",(end-start));
}
