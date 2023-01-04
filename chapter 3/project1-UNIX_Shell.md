# 1. Overview

This shell program is organized into several parts.

1. Creating the child process and executing the command in the child
2. Providing a history feature
3. Adding support of input and output redirection
4. Allowing the parent and child processes to communicate via a pipe

Additionally, I aslo implemented a seriallized command `;`.

# 2. Executing Command in a Child Process

If you enter the ps -ael command at the osh> prompt, the following is saved in the args array.

```c
args[0] = "ps"
args[1] = "-ael"
args[2] = NULL
```

To execute it, simply pass it to the execvp() function.

```c
execvp(args[0], args);
```

At this time, it should be checked whether the user inputs `&`.

If & is present in the input, the parent process does not wait for the child process.

# 3. Creating a History Feature

It provides a `history` feature to allow a user to execute the most recent command by entering `!!`.

# 4. Redirecting Input and Output

Redirection operators `>` and `<` are also available.

If you type `ls > out.txt`, the result of ls is output to out.txt.

If `sort < in.txt` is entered, the contents of in.txt are sorted and displayed in the shell.

You can implement this using the `dup2()` function.

```c
dup2(file, STDOUT_FILENO);
dup2(file, STDIN_FILENO);
```

# 5.  Communication via a Pipe

The output of one command can be used as the input of another command by using the pipe `|` command.

To implement this, we use the `pipe()` function.

```c
int fd[2];
pipe(fd);
```
