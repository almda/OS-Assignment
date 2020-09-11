#include "types.h"
#include "stat.h"
#include "user.h"
//#include "proc.h"

struct perf {
  int ps_priority;
  int stime;
  int retime;
  int rtime;
};

void busy_wait();
int fib(int n);

int main(int argc, char** argv){
	struct perf performance;
	printf(1,"%s\t%s\t%s\t%s\t%s\n","PID", "PS_PRIORITY", "STIME", "RETIME", "RTIME");
	int pid[3];


	for(int n=0;n<3;n++){
		pid[n] = fork();

		if(pid[n] < 0){
			exit(1);
		}

		else if(pid[n]==0){

				if(n==0){
					set_ps_priority(10);
					set_cfs_priority(3);
				}

				else if(n==1){
					set_ps_priority(5);
					set_cfs_priority(2);
				}
				else{
					set_ps_priority(1);
					set_cfs_priority(1);
				}

			fib(20);
			proc_info(&performance);

			printf(1,"%d\t%d\t\t%d\t%d\t%d\n",getpid(), performance.ps_priority, performance.stime, performance.retime, performance.rtime);
			exit(0);
		}
	}
	wait(&pid[0]);
	wait(&pid[1]);
	wait(&pid[2]);
	exit(0);
}

void busy_wait(){
	int i = 1000000;
	int dummy = 0;
	while(i--){
		dummy+=i;
	}	
}

int fib(int n){
	if(n<=1) return n;
	else{
		return fib(n-1) + fib(n-2);
	}
}