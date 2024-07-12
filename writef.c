#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    char * filename = argv[2];

    FILE *file = fopen(filename, "a");

    // check if the file opened successfully
    if(file == NULL)
    {
        printf("File cannot be opened !!  %s\n", filename);
        return EXIT_FAILURE;
    }
    
    // write the time, pid and ppid to the file
    int a = fprintf(file, "time: %ld, PID: %d, PPID: %d\n", time(NULL), getpid(), getppid());
    if(a < 0)
    {
        printf(" %s\n", filename);
        return EXIT_FAILURE;
    }
    else
    {
        printf("Successfully written to file '%s'\n", filename);
    }
    // close the file
    fclose(file);
    return EXIT_SUCCESS;
}