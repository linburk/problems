#include "hash.h"

hs_hash_T hs_get_hash(void const *data, int data_size)
{
	hs_hash_T ret = 1;
	char const *pcdata = (char const *)data;
	int const a = 471;
	int const b = 597;
	for (int i = 0; i < data_size; ++i)
		ret = (a * ret + b) + pcdata[i];
	return ret;
}

hs_get_hash(data, )
