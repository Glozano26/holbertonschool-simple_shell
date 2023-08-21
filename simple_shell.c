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
        char *args[10];
        int status;
        ssize_t line_read;
        pid_t child_pid;
        int i;

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

                /* Elimina el salto de linea final */
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
                if (line[i] == '\0') /*solo se cumple si es una cadena de espacios*/
                        continue;

                child_pid = fork();
                if (child_pid == -1)
                {
                        perror("Fork failed");
                        exit(1);
                }
                else if (child_pid == 0)
                { /* Codigo del proceso hijo */
                        /* Analiza la linea de comandos en argumentos */
                        int i = 0;
                        args[i] = strtok(line, " ");
                        while (args[i] != NULL) {
                                i++;
                                args[i] = strtok(NULL, " ");
                        }
                        args[i] = NULL; /* Termina la lista de argumentos */
                        
			// Verifica si el comando es ejecutable antes de hacer el fork
			char *path = getenv("PATH");
			char *token = strtok(path, ":");
			int command_found = 0;

			while (token != NULL)
			{
				char command_path[100]; // Ajusta el tamaño según tus necesidades
				snprintf(command_path, sizeof(command_path), "%s/%s", token, args[0]);

				if (access(command_path, X_OK) == 0) // Comprueba si el comando es ejecutable
				{
					command_found = 1;
					break;
				}

				token = strtok(NULL, ":");
			}

			if (!command_found)
			{
				fprintf(stderr, "Command not found: %s\n", args[0]);
				exit(1);
			}

			/* Ejecuta el comando */
			execve(command_path, args, NULL);
			perror("execve");
			exit(1);
		}	
		else
                {
                        wait(&status);
                }
        }
        return (0);
}
