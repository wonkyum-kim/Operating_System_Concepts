#include <stdio.h>
#include <unistd.h>
#include <wait.h>

#define SIZE 5

int nums[SIZE] = {0,1,2,3,4};

int main()
{
  pid_t pid;

  pid = fork();

  if (pid == 0) {
      for (int i = 0; i < SIZE; ++i) {
          nums[i] *= -i;
          printf("CHILD: %d\n", nums[i]);    // LINE X
      }
  }
  else if (pid > 0) {
      wait(NULL);
      for (int i = 0; i < SIZE; ++i) {
          printf("PARENT: %d\n", nums[i]);   // LINE Y
      }
  }
  return 0;
}

/*
CHILD: 0
CHILD: -1
CHILD: -4
CHILD: -9
CHILD: -16
PARENT: 0
PARENT: 1
PARENT: 2
PARENT: 3
PARENT: 4
*/
