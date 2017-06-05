#ifndef RANKING__H
#define RANKING__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "pelicula.h"

#define STR_ALTA "ALTA"
#define STR_BAJA "BAJA"
#define STR_MOD "MODIFICAR"
#define STR_ALTA_MIN "alta"
#define STR_BAJA_MIN "baja"
#define STR_MOD_MIN "modificar"
#define COMMAND_DB "-if"
#define COMMAND_FILE "-f"
#define COMMAND_LOG "-log"
#define POS_COMMAND_CLA 1

typedef enum
{
	COMMAND_ALTA,
	COMMAND_BAJA,
	COMMAND_MOD,
} command_t;

state_t validarArg(command_t* ptr_operacion, int argc, char* argv[], char ** db_filename,char ** op_filename,char ** log_filename);

size_t obtener_pos_cla(char* pos_cla,int argc, const char *argv[])

void free_and_close(peli_t *file_struct, peli_t *db_struct, FILE *log, FILE *db, FILE *pf);

state_t realizarAlta(FILE* db, FILE* pf, FILE* log);

state_t realizarBaja(FILE* db, FILE* pf, FILE* log)

state_t realizarMod(FILE* db, FILE* pf, FILE* log)

state_t leerValidar(size_t* n_db,peli_t* ptr_struct_read,FILE* pf_to_read,FILE* pf,FILE* log);

#endif