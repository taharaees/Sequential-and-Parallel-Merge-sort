#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<iostream>
#include<fstream>
#include<omp.h>
#define MAX_SIZE 10000

using namespace std;

// class for records
class studentRecord
{
   public:
   int id;
   string name;
   float cgpa;
};

void print_list(studentRecord * x, int n) 
{
   	int i;
   	for (i = 0; i < n; i++) 
   	{
      	cout << x[i].id << " ";
      	cout << x[i].name << " ";
      	cout << x[i].cgpa << " ";
   		cout << "\n";
	}
}



/*************************************************MERGESORT USING NAME********************************************************/
//Merging 2 sorted subarrays into one tmp array
void mergeName(studentRecord * X, int n, studentRecord * tmp) 
{
   	int i = 0;
   	int j = n/2;
   	int ti = 0;

	//i will iterate till first  half anf J will iterate for 2nd half of array
   	while (i<n/2 && j<n) 
   	{
    	if (X[i].name < X[j].name) 
      	{
        	tmp[ti] = X[i];
         	ti++; 
         	i++;
      	} 
      	else 
      	{
         	tmp[ti] = X[j];
         	ti++; 
	      	j++;
      	}
   	}
   
   	while (i<n/2) 
   	{  
      	/* finish up lower half */
      	tmp[ti] = X[i];
	   	ti++;
	   	i++;
   	}
   	
	while (j<n) 
   	{  
    	/* finish up upper half */
      	tmp[ti] = X[j];
      	ti++; 
      	j++;
   	}
	
	//Copy sorted array tmp back to X (Original array)
   	for(int i=0;i<n;++i)
   	{
   		X[i]=tmp[i];
   	}
}

void mergesortName(studentRecord * X, int n, studentRecord * tmp)
{
	if (n < 2)
	{
		return;
	}
		
	#pragma omp task firstprivate (X, n, tmp)
	mergesortName(X, n/2, tmp);
	
	#pragma omp task firstprivate (X, n, tmp)
	mergesortName(X+(n/2), n-(n/2), tmp);
	
	//Wait for both paralel tasks to complete execution
	#pragma omp taskwait
	/* merge sorted halves into sorted list */
	mergeName(X, n, tmp);
}
/************************************************************************************************************************/




/*************************************************MERGESORT USING ID********************************************************/
//Merging 2 sorted subarrays into one tmp array
void mergeID(studentRecord * X, int n, studentRecord * tmp) 
{
   	int i = 0;
   	int j = n/2;
   	int ti = 0;

	//i will iterate till first  half anf J will iterate for 2nd half of array
   	while (i<n/2 && j<n) 
   	{
      	if (X[i].id < X[j].id) 
      	{
         	tmp[ti] = X[i];
         	ti++; 
         	i++;
      	} 
      	else 
      	{
         	tmp[ti] = X[j];
         	ti++; 
	     	j++;
      	}		
   	}
   	while (i<n/2) 
   	{  
      	/* finish up lower half */
      	tmp[ti] = X[i];
	   	ti++;
	   	i++;
   	}
   	
	while (j<n) 
   	{  
      	/* finish up upper half */
      	tmp[ti] = X[j];
      	ti++; 
      	j++;
   	}
	
	//Copy sorted array tmp back to  X (Original array)
   	for(int i=0;i<n;++i)
   	{
   		X[i]=tmp[i];
   	}
}

void mergesortID(studentRecord * X, int n, studentRecord * tmp)
{
   	if (n < 2)
   	{
		return;
	}

	#pragma omp task firstprivate (X, n, tmp)
   	mergesortID(X, n/2, tmp);

	#pragma omp task firstprivate (X, n, tmp)
   	mergesortID(X+(n/2), n-(n/2), tmp);

	//Wait for both paralel tasks to complete execution
	#pragma omp taskwait
	/* merge sorted halves into sorted list */
   	mergeID(X, n, tmp);
}
/************************************************************************************************************************/





/*************************************************MERGESORT USING CGPA********************************************************/
//Merging 2 sorted subarrays into one tmp array
void mergeCGPA(studentRecord * X, int n, studentRecord * tmp) 
{
   	int i = 0;
   	int j = n/2;
   	int ti = 0;

	//i will iterate till first  half anf J will iterate for 2nd half of array
   	while (i<n/2 && j<n) 
   	{
      	if (X[i].cgpa < X[j].cgpa) 
      	{
         	tmp[ti] = X[i];
         	ti++; 
         	i++;
      	} 
      	else 
      	{
         	tmp[ti] = X[j];
         	ti++; 
	    	j++;
      	}
   	}
   
   	while (i<n/2) 
   	{  
      /* finish up lower half */
    	tmp[ti] = X[i];
	   	ti++;
	   	i++;
   	}
   	while (j<n) 
   	{  
      /* finish up upper half */
      tmp[ti] = X[j];
      ti++; 
      j++;
   	}
	//Copy sorted array tmp back to  X (Original array)
   	for(int i=0;i<n;++i)
   	{
   		X[i]=tmp[i];
   	}

}

void mergesortCGPA(studentRecord * X, int n, studentRecord * tmp)
{
	if (n < 2) 
	{
		return;
	}
	
	#pragma omp task firstprivate (X, n, tmp)
	mergesortCGPA(X, n/2, tmp);
	
	#pragma omp task firstprivate (X, n, tmp)
	mergesortCGPA(X+(n/2), n-(n/2), tmp);

	//Wait for both paralel tasks to complete execution
	#pragma omp taskwait
   	/* merge sorted halves into sorted list */
   	mergeCGPA(X, n, tmp);
}
/************************************************************************************************************************/






int main()
{
	int inpt;
   	int n=10000;
   	double start, stop;
	
   	studentRecord data[MAX_SIZE], tmp[MAX_SIZE];

	int i=0;
	ifstream fin("input.txt");
	while(!fin.eof())
	{
		fin>>data[i].id>>data[i].name>>data[i].cgpa; //read data from the file student
		i++;
	}
	fin.close();
   
	cout << "List Before Sorting...\n";
   	print_list(data, n);
   	cout<<"\n";
   	cout<<"1:sort by Name\n";
   	cout<<"2:sort by ID\n";
   	cout<<"3:sort by CGPA\n";
	cout<<"Please enter number:";
	cin>>inpt;
	
	// Switch case for option of mergesort type
	switch(inpt)
	{
		case 1:
			start = omp_get_wtime();   
      		mergesortName(data, n, tmp);
   			stop = omp_get_wtime();
   			break;
   		case 2:
   			start = omp_get_wtime();   
      		mergesortID(data, n, tmp);
   			stop = omp_get_wtime();
   			break;
		case 3:
			start = omp_get_wtime();   
      		mergesortCGPA(data, n, tmp);
   			stop = omp_get_wtime();
   			break;
	}

		  
   
   	cout << "\nList After Sorting...\n";
   	print_list(data, n);

	cout << "\nTime: " << stop-start;

}