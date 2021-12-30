#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int value = 5;

int main()
{
   pid_t pid = fork();

   if (pid == 0) {
       execlp("/bin/ls", "ls", NULL);
       printf("LINE J\n");      // 실행되지 않는다.
   }
   else if (pid > 0) {
       wait(NULL);
       printf("Child Complete\n");
   }
   return 0;
}
