#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    const char *file_name;

    if (ac > 1)
		file_name = av[1];
	else
		file_name = "ig/msj.txt";

    FILE *file = fopen(file_name, "r");
    if (file)
	{
		fclose(file);

#ifdef __linux__
        char command[256];
        snprintf(command, sizeof(command), "xdg-open %s", file_name);

#endif

		if (system(command) != 0)
			printf("No se pudo abrir el archivo '%s'.\n", file_name);
    }
	else
   		printf("Yaja: %s: Oh oh... Prueba con otro archivo.\n", file_name);
    return 0;
}
