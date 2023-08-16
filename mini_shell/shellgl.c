#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_COMMAND_LENGTH 100

char *my_getline(char *lineptr, size_t *n)
{
	int c;
	size_t i = 0;

	while ((c = getchar()) != '\n' && c != EOF)
	{
		lineptr[i++] = c;
	}

	if (c == EOF)
	{
		*n = 0;
	}
	else
	{
		*n = i;
	}

	return (lineptr);
}

int main()
{
	char input[MAX_INPUT_LENGTH];
	char *comando;
	char **comando_ptr;
	size_t n;

	while (1)
	{
		printf("#cisfun$ ");
		my_getline(input, &n);

		if (strcmp(input, "exit\n") == 0)
		{
			break;
		}
      
		comando = malloc(MAX_COMMAND_LENGTH * sizeof(char));
		sscanf(input, "%s", comando);

		comando_ptr = malloc(sizeof(char *));
		comando_ptr[0] = comando;
		comando_ptr[1] = NULL;

		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("Fork failed");
			exit(1);
		}
		else if (child_pid == 0)
		{
			execve(comando, comando_ptr, NULL);
			perror("Execve failed");
			exit(1);
		}
		else
		{
			wait(NULL);
		}
	}
    
    return 0;
}

