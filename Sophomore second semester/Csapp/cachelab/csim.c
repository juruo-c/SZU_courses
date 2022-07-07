#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <limits.h>

struct CacheLine
{
    int tag;
    int lastused;  
	int valid;
};

struct Cache
{
    struct CacheLine** ptr;
    int s, E, b, S;
}cache;
char filename[1000];

void CreateCache(int s, int E, int b)
{
	cache.s = s, cache.E = E, cache.b = b;
	cache.S = (1 << s);
	cache.ptr = (struct CacheLine**)malloc(sizeof(struct CacheLine*) * cache.S);
	for (int i = 0; i < cache.S; i ++ )
		cache.ptr[i] = (struct CacheLine*)malloc(sizeof(struct CacheLine) * E);	
	for (int i = 0; i < cache.S; i ++ )
		for (int j = 0; j < cache.E; j ++ )
			cache.ptr[i][j].valid = cache.ptr[i][j].tag = cache.ptr[i][j].lastused = 0;
}

void FreeCache()
{
	for (int i = 0; i < cache.S; i ++ ) free(cache.ptr[i]);
	free(cache.ptr);
}

void update(unsigned address, int* hit, int* miss, int* exit)
{
	int s = (address >> cache.b) & ((-1U) >> (32 - cache.s));
	int t = address >> (cache.s + cache.b);
	// Hit ?
	for (int i = 0; i < cache.E; i ++ )
	{
		if (cache.ptr[s][i].valid && cache.ptr[s][i].tag == t)
		{
			cache.ptr[s][i].lastused = 0;
			(*hit) ++;
			return;	
		}
	}

	// Has empty cache line ?
	for (int i = 0; i < cache.E; i ++ )
	{
		if (!cache.ptr[s][i].valid)
		{
			cache.ptr[s][i].lastused = 0;
			(*miss) ++;
			cache.ptr[s][i].valid = 1;
			cache.ptr[s][i].tag = t;	
			return;
		}
	}
	
	// Don't have empty cache line, use LRU
	(*miss) ++, (*exit) ++;
	
	int maxx = -1, id = -1;
	for (int i = 0; i < cache.E; i ++ )
		if (cache.ptr[s][i].lastused > maxx)
		{
			maxx = cache.ptr[s][i].lastused;
			id = i;
		}
	cache.ptr[s][id].lastused = 0, cache.ptr[s][id].tag = t;
}

void updateUsed()
{
	for (int i = 0; i < cache.S; i ++ )
		for (int j = 0; j < cache.E; j ++ )
			if (cache.ptr[i][j].valid)
				cache.ptr[i][j].lastused ++;
}

void verbose()
{
	
}

int main(int argc, char** argv)
{
    int opt, s, E, b;
    while (-1 != (opt = getopt(argc, argv, "hvs:E:b:t:")))
    {
        switch(opt)
        {
            case 'h':
               	system("cat help_info");
                exit(0);
            case 'v':
                verbose();
                break;
			case 's':
				s = atoi(optarg);
				break;
			case 'E':
				E = atoi(optarg);
				break;
			case 'b':
				b = atoi(optarg);
				break;
			case 't':
				strcpy(filename, optarg);				
				break;
            default:
                printf("wrong argument\n");
                break;
        }
    }

	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "The File is wrong!\n");
		exit(-1);
	}
	
	CreateCache(s, E, b);
	
	int HitNumber = 0, MissNumber = 0, EvictionNumber = 0;
	char option;
	unsigned address;
	int size;
	while (fscanf(fp, "%c %xu,%d", &option, &address, &size) > 0)
	{
		switch (option)
		{
			case 'L':
				update(address, &HitNumber, &MissNumber, &EvictionNumber);
				break;
			case 'M':
				update(address, &HitNumber, &MissNumber, &EvictionNumber);
			case 'S':
				update(address, &HitNumber, &MissNumber, &EvictionNumber);
				break;
		}
		updateUsed();		
	}

	FreeCache();
	fclose(fp); 

	printSummary(HitNumber, MissNumber, EvictionNumber);
    return 0;
}
	
