#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char **argv, char **env) 

{
    printf("Address of env (third parameter): %p\n", (void *)env);
    printf("Address of environ (global variable): %p\n", (void *)environ);

    unsigned int i = 0;
    while (env[i] != NULL) 
    {
        printf("%s\n", env[i]);
        i++;
    }
    return 0;
}
