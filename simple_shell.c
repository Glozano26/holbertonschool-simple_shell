#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/**
 * main - main function.
 *
 * Return: Always 0.
 */

int main()
{
        char *line = NULL;
        size_t line_len = 0;
        char *args[10], *path, *token, command_path[1024];
        int status, i, command_found = 0;
	ssize_t line_read;
        pid_t child_pid;

        while (1)
        {
                if (isatty(fileno(stdin)))
                {
                        printf("#cisfun$ ");
                }

                line_read = getline(&line, &line_len, stdin);
                if (line_read == -1)
                {
                        free(line);
                        exit(0);
                }
		*path = getenv("PATH");
        	*token = strtok(path, ":");

        	while (token != NULL)
        	{
			snprintf(command_path, sizeof(command_path), "%s/%s", token, args[0]);

			if (access(command_path, X_OK) == 0)
			{
				command_found = 1;
                		child_pid = fork();

				/* Elimina el salto de línea final */
				if (line_read > 0 && line[line_read - 1] == '\n')
				{
                        		line[line_read - 1] = '\0';
                		}
				/* val si es solo una linea de espacios */
                		for (i = 0; line[i] != '\0'; i++)
				{
                        		if (line[i] != ' ')
					break;
             			}
				if (line[i] == '\0')
				{/*solo se cumple si es una cadena de espacios*/
                        		continue;
                			child_pid = fork();
				}
				if (child_pid == -1)
                		{
                        		perror("Fork failed");
                        		exit(1);
               			}
				else if (child_pid == 0)
				{ /* Código del proceso hijo */
                        	/* Analiza la línea de comandos en argumentos */
                        		int i = 0;
                        		args[i] = strtok(line, " ");
				}
                        	while (args[i] != NULL)
				{
                                	i++;
                                	args[i] = strtok(NULL, " ");
				}
                        	args[i] = NULL; /* Termina la lista de argumentos */
                        	/* Ejecuta el comando */
                        	execve(args[0], args, NULL);
                        	perror("./shell");
                        	exit(1);
                		else
                		{
                        		wait(&status);
					break;
                		}
			}
			token = strtok(NULL, ":");
		}	
        }
        return (0);
}
