#ifndef TYPES__H
#define TYPES__H

#include "constantes.h"
#include <time.h>
#define MEAN_SIZE_STR 50
typedef enum
{
	COMMAND_ALTA,
	COMMAND_BAJA,
	COMMAND_MOD
} command_t;

typedef enum
{
	ST_OK,
	ST_MEMORY_ERROR,
	ST_UNABLE_TO_READ_FROM_FILE,
	ST_ERROR_CONVERSION,
	ST_ERROR_NULL_PTR,
	ST_ERROR_COMMAND,
	ST_ERROR_INVALID_CANT_ARG,
	ST_ERROR_UNABLE_TO_OPEN_FILE,
	ST_ERROR_WRITE_FILE,
	ST_ERROR_PARAM_NOT_FOUND
} state_t;
#endif

Prueba branch