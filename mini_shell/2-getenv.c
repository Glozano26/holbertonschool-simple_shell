#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char *_getenv(const char *name)
{
	int i = 0, name_length;
	char *env_var, *equal_sign;

	while (environ[i] != NULL)
	{
		*env_var = environ[i];
		*equal_sign = strchr(env_var, '=');

		if (equal_sign != NULL)
		{
			name_length = equal_sign - env_var;

			if (strncmp(env_var, name, name_length) == 0)
			{
			return equal_sign + 1;
			}
		}
		i++;
    }
    return NULL;
}

int main()
{
	char *path = _getenv("HOME");
	if (path != NULL)
	{
        	printf("PATH = %s\n", path);
	}
	else
	{
		printf("Variable de entorno no encontrada.\n");
	}

	return 0;
}
