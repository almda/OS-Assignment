#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  int exit_status;
  argint(0, &exit_status);
  exit(exit_status);

  //exit(); //We wont use this kind of exit anymore
  return 0;  // not reached
}

int
sys_wait(void)
{
  //return wait(); old command before change
  int child_exit_status = 0;
  argptr(0, (char **) &child_exit_status, 0);
  return wait(&child_exit_status);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//New Syscalls

// return size of the running process memory in bytes
int
sys_memsize(void)
{
  return myproc()->sz;
}

int
sys_set_ps_priority(void)
{
  int pri;
  argint(0, &pri); // put argument from user
  return set_ps_priority(pri);
}


int
sys_set_cfs_priority(void)
{
  int pri;
  argint(0, &pri);
  return set_cfs_priority(pri);
}

int
sys_policy(void)
{
  int selected_pol;
  argint(0, &selected_pol);

  if( (selected_pol < 0) || (selected_pol > 2))
    return -1;

  sched_type = selected_pol;
  return 0;
}
int
sys_proc_info(void)
{
  int ptr;
  struct perf* perfomance;
  if(argint(0,&ptr)<0)
    return -1;
  perfomance = (struct perf*)ptr;
  //acquire(&tickslock);
  proc_info(perfomance);
  //release(&tickslock);
  return 0;
}