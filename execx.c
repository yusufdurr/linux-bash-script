#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // control if input occur time is negative
    char *time = argv[2];
    int t;
    if ((atoi(time) * -1) < 0)
    {
        t = atoi(time);
    }
    else
    {
        printf("!!%s!! Please enter positive integer\n", argv[2]);
        return 0;
    }

    // set string array for after the default 'execx -t 4' command
    char **newargv;
    newargv = (argv + 3);

    // perform the command t time
    int i;
    for (i = 0; i < t; i++)
    {
        // all the input controls
        if (newargv[0] == NULL)
        {
            printf("'%s' : command not found !! \nplease try  '--help'  command \n", newargv[0]);
            execvp("./", newargv);
            break;
        }
        else if (strcmp(newargv[0], "--help") == 0 && newargv[1] == NULL)
        {
            printf("\n----------------------------------Commands------------------------------------:\n");
            printf("'cat'                                      - command for print file content\n");
            printf("'clear'                                    - command for clear terminal \n");
            printf("'ls'                                       - command for print all files in current directory\n");
            printf("'exit'                                     - command for exit terminal\n");
            printf("'bash'                                     - command for call default system bash\n");
            printf("'writef -f [filename]'                     - command for call default system bash\n");
            printf("'execx -t [occur time(integer)] [command]' - command for call default system bash\n");
            printf("\n");
        }
        else if ((strcmp(newargv[0], "clear") == 0 || strcmp(newargv[0], "cls") == 0) && newargv[1] == NULL)
        {
            if (fork() == 0)
            {
                execvp("/bin/clear", newargv);
                perror("execvp");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (strcmp(newargv[0], "bash") == 0 && newargv[1] == NULL)
        {
            if (fork() == 0)
            {
                execvp("/bin/bash", newargv);
                perror("execvp");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (strcmp(newargv[0], "cat") == 0 && newargv[1] != NULL && newargv[2] == NULL)
        {
            if (fork() == 0)
            {
                execvp("/bin/cat", newargv);
                perror("execvp");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (strcmp(newargv[0], "ls") == 0 && newargv[1] == NULL)
        {
            if (fork() == 0)
            {
                execvp("/bin/ls", newargv);
                perror("execvp");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (strcmp(newargv[0], "writef") == 0 && strcmp(newargv[1], "-f") == 0 && newargv[2] != NULL && newargv[3] == NULL)
        {
            if (fork() == 0)
            {
                execvp("./writef", newargv);
                perror("execvp");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (strcmp(newargv[0], "execx") == 0 && strcmp(newargv[1], "-t") == 0 && newargv[2] != NULL)
        {
            if (fork() == 0)
            {
                execvp("./execx", newargv);
                perror("execvp : execx : execx => ");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
        else
        {
            printf("'%s' : command not found !! \nplease try  '--help'  command \n", newargv[0]);
            return 0;
        }
    }

    return EXIT_SUCCESS;
}