// BranchPredictionCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream>

const unsigned arraySize = 10000;//32768;

long long branchSum( int input, long long sum ) 
{
	if (input >= 128)
		sum += input;	
	return sum;
}

long long bitwiseSum( int input, long long sum ) 
{
	int t = (input - 128) >> 31;
	sum += ~t & input;
	return sum;
}

void Sum(bool sort, long long(*condition)(int, long long)) 
{
	// generate data
	int data[arraySize];
	for (unsigned c = 0; c < arraySize; ++c)
		data[c] = std::rand() % 256;

	if (sort)
	{
		std::sort(data, data + arraySize);
	}

	// test
	clock_t start = clock();
	long long sum = 0;
	for (unsigned i = 0; i < 100000; ++i)
	{
		// primary loop
		for (unsigned c = 0; c < arraySize; ++c)
		{
			sum = branchSum(data[c], sum);
		}
	}
	double elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
	sort? std::cout<< "Sort: ": std::cout<<"No sort: ";
	std::cout << std::endl;
	std::cout << "time: " << elapsedTime << std::endl;
	std::cout << "sum = " << sum << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Sum(false, branchSum);
	Sum(true, branchSum);

	Sum(false, bitwiseSum);
	Sum(true, bitwiseSum);

	return 0;
}

