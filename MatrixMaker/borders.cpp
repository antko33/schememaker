#include "stdafx.h"

void Expand(std::vector<UINT> *vec, int step)
{
	int vecSize = sqrt(double(vec->size()));
	int pivot = (*vec)[0];
	for (int i = -1; i <= vecSize; i++)
	{
		for (int j = -1; j <= vecSize; j++)
		{
			int elem = pivot + j + i * step;
			if (std::find(vec->begin(), vec->end(), elem) == vec->end())
			{
				vec->push_back(pivot + j + i * step);
			}
		}
	}
	std::sort(vec->begin(), vec->end());
}

void BordersInit(std::vector<UINT> *vec, int size, int step, int pivot)
{
	vec->push_back(pivot + (size - 1) / 2 + (size - 1) / 2 * step);
	vec->push_back((*vec)[0] + 1);
	vec->push_back((*vec)[0] + step);
	vec->push_back((*vec)[1] + step);
}