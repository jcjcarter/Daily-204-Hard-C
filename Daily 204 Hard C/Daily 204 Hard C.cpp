// Daily 204 Hard C.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int getMinDouble(target)
{
	int retVal = 0;
	while ((target /= 2) > 1) retVal++;
	return retVal;
}

bool getNext(int* chain, int nextIndex, int maxSize, int target, int reqDouble)
{
	int addsLeft = maxSize - nextIndex;
	int lastVal = chain[nextIndex - 1];

	if (addsLeft == 0)
		return lastVal == target;
	if (addsLeft < 0)
		return false;
	if (lastVal >= target)
		return false;

	// Try double first
	chain[nextIndex] = lastVal * 2;
	if (getNext(chain, nextIndex + 1, maxSize, target, reqDouble - 1))
		return true;

	// If double failed but haven't achieved minimum number of doubles,
	// no need to try anything else
	if (reqDouble < addsLeft)
	{
		int i;
		for (i = 0; i < nextIndex; i++)
		{
			int j;
			for (j = i; j < nextIndex; j++)
			{
				int newVal = chain[i] + chain[j];
				if (newVal <= lastVal || (i == j && i == nextIndex - 1))
					continue;
				chain[nextIndex] = newVal;
				if (getNext(chain, nextIndex + 1, maxSize, target, reqDouble))
					return true;
			}
		}
		chain[nextIndex] = 0;
	}
	return false;
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("USAGE: %s sizeOfChain target\n", argv[0]);
		return 1;
	}

	int size = atoi(argv[1]);
	int target = atoi(argv[2]);
	if (size <= 0 || target <= 0)
	{
		printf("addition size and target must be positive integers\n");
		return 1;
	}
	size++;

	int* chain = malloc(size*sizeof(int));
	memset(chain, 0, size*sizeof(int));

	int minDouble = getMinDouble(target - size) - 1;

	chain[0] = 1;
	chain[1] = 2;
	if (getNext(chain, 2, size, target, minDouble))
	{
		int i;
		for (i = 0; i < size; i++)
		{
			printf("%d\n", chain[i]);
		}
	}
	else
	{
		printf("NOT FOUND\n");
	}

	return 0;
}
