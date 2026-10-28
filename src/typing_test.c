#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/typing_test.h"

void typing_test_run(const char *text)
{
	int col = 1;
	size_t cont = 0;
	bool started_typing = false;
	size_t end = strlen(text);

	char c;

	while (read(STDIN_FILENO, &c, 1) == 1)
	{
		if (!started_typing)
		{
			// clock_gettime(CLOCK_MONOTONIC, &tic);
			started_typing = true;
		}

		if (c == text[cont])
		{
		  // ANSI: \033[%dG posiciona el cursor en la columna indicada.
		  // \033[32m activa el verde; %c imprime el carácter introducido.
		  // \033[0m restablece los atributos de color.
		  printf("\033[%dG\033[32m%c\033[0m", col, c);
		}
		else
		{
		  // Si el carácter es incorrecto, muestra en rojo el carácter
		  // que se esperaba en esa posición.
		  printf("\033[%dG\033[31m%c\033[0m", col, text[cont]);
		}

		col++;  		// Avanza a la siguiente columna.
		fflush(stdout); // Actualiza la pantalla después de cada tecla.
		cont++; 		// Avanza al siguiente carácter esperado.

		// Termina cuando se han procesado todos los caracteres del texto.
		if (cont == end)
		  break;
	}

	fflush(stdout);
}
