#ifndef DECO__H
#define DECO__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "types.h"
#include "pelicula.h"

#define CANT_PARAM_DECO 2
#define FILE_DECO_POS 1
#define CANT_TOTAL_CHAR_FECHA 10

void imprimir_peli_csv(const peli_t *peli, FILE *pf);
#endif