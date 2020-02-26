#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <pthread.h>
#include <cstdlib>

using namespace std;

int *ary = new int[20];
int *sortedAry = new int[20];

void* merge(void* index)
{
	cout<<"Thread 3 created -- merge."<<endl;

	int i = 0, 
	j = *(int*)index, 
	k = 0;
	int n = j;

	while (i < n && j < n*2)
	{
		if (ary[i] < ary[j])
		{
			sortedAry[k] = ary[i];
			i++;
		}
		else
		{
			sortedAry[k] = ary[j];
			j++;
		}
		k++;
	}

	while (i < n)
	{
		sortedAry[k] = ary[i];
		i++;
		k++;
	}

	while (j < n*2)
	{
		sortedAry[k] = ary[j];
		j++;
		k++;
	}

	pthread_exit(0);
}

void* SortSublistFunc1(void* index)
{
	cout<<"Thread 1 created --sort 1."<<endl;

	int i, j;
	int n = *(int*)index;

	for(i = 0 ; i < n-1; i++)

		for(j = 0; j < n-i-1; j++)
		  if(ary[j] > ary[j+1])
		    swap(ary[j],ary[j+1]);


		pthread_exit(0);
	
}

void* SortSublistFunc2(void* index)
{
	cout<<"Thread 2 created --sort 2."<<endl;

	int j,
	    i,
	    n = *(int*)index,
	    m = n/2;
 	
	for(i = m ; i < n-1; i++)

		for(j = m ; j < (n-(i-m))-1; j++)
		  if(ary[j] > ary[j+1])
		    swap(ary[j],ary[j+1]);
			


		pthread_exit(0);
	
}

int main()
{
	const char * inputFile = "p2data.txt";
	int  i = 0, n = 0;
	string p;

	pthread_t tid1;
	pthread_t tid2;
	pthread_attr_t attr;
	pthread_attr_init(& attr);

	ifstream myfile;
	myfile.open(inputFile);

	if (myfile.is_open())
	{
		while (getline(myfile,p) ) 
			n++;
	}
	else
		cout << "Unable to open file" << endl;
	if (n == 0)
	{
		cout << "Empty File." << endl;
		cin >> n;
		return 0;
	}
	myfile.close();

	myfile.open(inputFile);
	if (myfile.is_open())
	{
		while (myfile >> p)
		{	
			ary[i] = stoi(p);
			i++;

		}
	}
	myfile.close();

	int index = n/2;

	pthread_create(&tid1,&attr,SortSublistFunc1, (void*) &index);

	pthread_create(&tid2,&attr,SortSublistFunc2, (void*) &n);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	pthread_t tid3;
	pthread_create(&tid3,&attr,merge, (void*) &index);
	pthread_join(tid3,NULL);


	cout << "Sorted Result: ";
	for (int l = 0; l < n; l++)
	{
		cout << sortedAry[l] << " ";
	}
	cout << endl;


	delete[]ary;
	ary = NULL;

	delete[]sortedAry;
	sortedAry = NULL;

	cin >> n;
	return 0;
}
