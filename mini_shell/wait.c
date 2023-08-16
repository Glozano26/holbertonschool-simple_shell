#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * main - main function.
 *
 * Return: Always 0.
 */


int main()
{
	int i;
	pid_t son_pid;
	int status;

	for (i = 0; i < 5; i++)
	{
		son_pid = fork();

		if (son_pid == -1)
		{
			perror("Fork failed");
			exit(1);
		}
		else if (son_pid == 0)/*Codigo del proceso hijo*/
		{
			son_pid = getpid();
			printf("Son %u executing ls -l /tmp:\n", son_pid);
			char *args[] = {"ls", "-l", "/tmp", NULL};
			execve("/bin/ls", args, NULL);
			perror("Execve failed"); /* Solo se ejecuta el execve falla*/
			exit(1);
		}
		else /*Codigo del proceso padre*/
		{
			son_pid = getppid();
			wait(&status);
			printf("father %u exited\n", son_pid);
		}
	}
	return (0);
}
