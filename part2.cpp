#include<unordered_map>
#include<cassert>
#include<cstdio>
#include<cstring>
#include<map>
#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<iomanip>
#include<fcntl.h>
#include<sys/wait.h>

using namespace std;

vector<size_t> *malloc_data = NULL;

/* declare the following functions to have "C" linkage, so that
 * we can see them from C code without doing name demangling. */
extern "C"
{
	void so_deallocate()
	{
		delete malloc_data;
	}

	void so_allocate()
	{
		if(malloc_data == NULL)
		{
			malloc_data = new vector<size_t>();
		}
	}

    /* dump() - output the contents of the malloc_data */
    void malloc_dump()
	{
		for(auto& data : *malloc_data)
		{
			printf("Allocations made: %ld.\n", data);
		}
	}

	/* insert() - when malloc() is called, the interpositioning library
     *            stores the size of the request.	*/
	int malloc_insert(size_t size)
	{
		so_allocate();
		malloc_data->push_back(size);
	}
}
