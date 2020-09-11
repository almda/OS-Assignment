#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
	if (argc!=2){
		printf(1,"%s","Please enter Policy number\n");
		exit(1);
	}

	int p = atoi(argv[1]);
	
	if(policy(p)<0){
		printf(1,"Error replacing policy, no such a policy number (%d)\n",p);
		exit(1);
	}

	if(p == 0)
		printf(1,"Policy has been successfully changed to Default Policy\n");
	else if (p == 1)
		printf(1,"Policy has been successfully changed to Priority Policy\n");
	else if(p == 2)
		printf(1,"Policy has been successfully changed to CFS Policy\n");
	
	exit(0);
}
