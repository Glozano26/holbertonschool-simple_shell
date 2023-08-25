#include "main.h"

/**
 * findpath - find the path directory of the function
 * @argument0: argument to serch
 * @newpath: buffer to the route of the path
 * Return: 0 if it find, 1 if not.
 */
int findpath(char *argument0, char *newpath)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		snprintf(newpath, 50, "%s/%s", token, argument0);
		if (access(newpath, X_OK) == 0)
		{
			return (0);
		}
		token = strtok(NULL, ":");
	}
	return (1);
}

/**
 * checkcommand - function to check the command that the user give.
 * @line: buffer that have the command
 * Return: void.
 */

void checkcommand(char *line)
{
	pid_t child_pid;
	int i, status;
	char *args[10];

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (child_pid == 0)
	{ /* Codigo del proceso hijo */
		/* Analiza la linea de comandos en argumentos */
		i = 0;
		args[i] = strtok(line, " ");
		while (args[i] != NULL)
		{
			i++;
			args[i] = strtok(NULL, " ");
		}
		args[i] = NULL; /* Termina la lista de argumentos */
		/*Valida si debe buscar la ruta en el PAHT*/
		if (args[0] && !strchr(args[0], '/'))
		{
			char newpath[50];

			if (findpath(args[0], newpath) == 0)
				args[0] = newpath;
		}
		/* Ejecuta el comando */
		execve(args[0], args, environ);
		perror("./shell");
		exit(1);
	}
	else
	{
		wait(&status);
	}
}
