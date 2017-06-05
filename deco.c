#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "constantes.h"
#include "types.h"
#include "comunes.h"
#include "deco.h"
#include "pelicula.h"



int main(int argc, char const *argv[])
{
	FILE *ptrbin;
	peli_t peli_imprimir;


	if(validarCantArg(CANT_PARAM_DECO, argc) != ST_OK) return EXIT_FAILURE;
	if(openFile(&ptrbin,argv[FILE_DECO_POS],"rb") != ST_OK)  return EXIT_FAILURE;

	while((fread(&peli_imprimir, sizeof(peli_t), CANT_PELI_A_IMPRIMIR, ptrbin)) == CANT_PELI_A_IMPRIMIR)
	{
		if(ferror(ptrbin))
		{
			handle_error(ST_UNABLE_TO_READ_FROM_FILE);
			fclose(ptrbin);
			return EXIT_FAILURE;
		}
		imprimir_peli_csv(&peli_imprimir, stdout);
	}
	fclose(ptrbin);
	return EXIT_SUCCESS;
}

void imprimir_peli_csv(const peli_t *peli, FILE *pf)
{

    char fecha[CANT_TOTAL_CHAR_FECHA+1];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d",localtime(&(peli->fecha)));
    fprintf(pf, "%lu%c%s%c%s%c%s%c%s%c%.2f%c%lu\n", peli ->id, SEPARADOR_LINEAS, peli ->titulo, SEPARADOR_LINEAS, peli ->guion, SEPARADOR_LINEAS, peli ->director, SEPARADOR_LINEAS, fecha,  SEPARADOR_LINEAS, peli ->puntaje,  SEPARADOR_LINEAS, peli ->reviews);
}
