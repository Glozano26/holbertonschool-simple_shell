#include <stdio.h>

int main(int ac, char **av) 
{
	for (int i = 0; i < ac; i++)
	{
	printf("El argumento %d es: %s\n", i, av[i]);
	}

	return (0);
}
