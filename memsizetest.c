#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
	printf(1,"The process is using: %dB\nAllocating more memory\n",memsize());
	void *ptr =(void*) malloc(2000);
	printf(1,"The process is using: %dB\nFreeing memory\n",memsize());
	free(ptr);
	printf(1,"%The process is using: %dB\n",memsize());
	exit(0);
}
