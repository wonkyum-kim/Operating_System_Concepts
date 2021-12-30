#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int value = 5;

int main()
{
  pid_t pid, pid1;
  pid = fork();
  if (pid == 0) {   // child process
      pid1 = getpid();
      printf("child: pid = %d\n", pid);     // A
      printf("child: pid1 = %d\n", pid1);   // B
  }
  else if (pid > 0) {   // parent process
      pid1 = getpid();
      printf("parent: pid = %d\n", pid);     // c
      printf("parent: pid1 = %d\n", pid1);   // d
      wait(NULL);
  }
  return 0;
}
