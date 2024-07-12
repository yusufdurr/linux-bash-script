#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

// defines for color
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

// there for bash call
#include <sys/types.h>
#include <sys/wait.h>

// this for read the input in proper way
#include <readline/readline.h>

// remove space right and left of the input
char *strstrip(char *s)
{
    size_t size;
    char *end;

    size = strlen(s);

    if (!size)
        return s;

    end = s + size - 1;
    while (end >= s && isspace(*end))
        end--;
    *(end + 1) = '\0';

    while (*s && isspace(*s))
        s++;

    return s;
}

// split input string space insensitive and hold them in string array
void strTerminalSplit(char *s, char *ret[1000])
{
    // after triming , for split the string
    int i = 0;
    char *token;
    /* get the first token */
    token = strtok(s, " ");
    /* walk through other tokens */
    while (token != NULL)
    {
        // if (isEqual(token, " ") == 0)
        // {
        ret[i] = token;
        i++;
        // }
        token = strtok(NULL, " ");
    }
}

// clean input string array
void cleanMatrix(char **a)
{
    int i;
    for (i = 0; i < 1000; i++)
    {
        a[i] = NULL;
    }
}

void main(int argc, char *argv[], char **envp)
{
    // clear terminal for the first time
    if (fork() == 0)
    {
        execvp("/bin/clear", NULL);
        perror("execvp");
        exit(1);
    }
    else
    {
        wait(NULL);
    }
    while (1)
    {
        // define input string , input matrix , i , j
        char *str;
        char *ret[10000];
        int i, j;

        // take input , separate command space insensitive , hold input in temp
        str = readline(CYN "myshell>>" RESET);
        // printf("%s", str);
        str = strstrip(str);
        strTerminalSplit(str, ret);

        // all input commands
        if (ret[0] == NULL)
        {
            execvp("./", ret);
        }
        else if (strcmp(ret[0], "--help") == 0 && ret[1] == NULL)
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
        else if (strcmp(ret[0], "exit") == 0 && ret[1] == NULL)
        {
            break;
        }
        else if ((strcmp(ret[0], "clear") == 0 || strcmp(ret[0], "cls") == 0) && ret[1] == NULL)
        {
            if (fork() == 0)
            {
                execvp("/bin/clear", ret);
                perror("execvp");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (strcmp(ret[0], "bash") == 0 && ret[1] == NULL)
        {
            if (fork() == 0)
            {
                execvp("/bin/bash", ret);
                perror("execvp");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (strcmp(ret[0], "cat") == 0 && ret[1] != NULL && ret[2] == NULL)
        {
            if (fork() == 0)
            {
                execvp("/bin/cat", ret);
                perror("execvp");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (strcmp(ret[0], "ls") == 0 && ret[1] == NULL)
        {
            if (fork() == 0)
            {
                execvp("/bin/ls", ret);
                perror("execvp");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (strcmp(ret[0], "writef") == 0 && strcmp(ret[1], "-f") == 0 && ret[2] != NULL && ret[3] == NULL)
        {
            if (fork() == 0)
            {
                execvp("./writef", ret);
                perror("execvp");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (strcmp(ret[0], "execx") == 0 && strcmp(ret[1], "-t") == 0 && ret[2] != NULL)
        {
            if (fork() == 0)
            {
                execvp("./execx", ret);
                perror("execvp : execx : myshell => ");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
        else
        {
            // printf(" '%s' is not recognized as an internal or external command,\n operable program or batch file.\n", str);
            printf("'%s' : command not found !! \nplease try  '--help'  command \n", str);
        }
        // clean matrix at the end
        cleanMatrix(ret);
    }
}