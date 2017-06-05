#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "constantes.h"
#include "types.h"
#include "comunes.h"
#include "deco.h"
#include "pelicula.h"
#include "ranking.h"

int main(int argc, char const *argv[])
{
	command_t operacion;
	
	char db_filename[MEAN_SIZE_STR],op_filename[MEAN_SIZE_STR],log_filename[MEAN_SIZE_STR];
	
	size_t used_size, alloc_size;
	
	state_t st;

	reading_st estado;
	
	FILE *db, *pf, *log;

	peli_t db_struct, file_struct, db_temp;

	if( (validarArg(&operacion, argc, argv, &db_filename, &op_filename , &log_filename) ) != ST_OK ) return EXIT_FAILURE;

	if ( (openFile(&db, db_filename,"rb") ) !=ST_OK ){return EXIT_FAILURE;}
	if ( (openFile(&pf, op_filename,"rb")) !=ST_OK ){return EXIT_FAILURE;}
	if ( (openFile(&log, log_filename,"a")) !=ST_OK ){return EXIT_FAILURE;}

	switch(operacion){
		case COMMAND_ALTA:
			if (realizarAlta() != ST_OK)
			{
				return EXIT_FAILURE;
			}
			break;
		case COMMAND_BAJA:
			if (realizarBaja() != ST_OK)
				{
					return EXIT_FAILURE;
				}
			break;
		case COMMAND_MOD:
			if (realizarMod() != ST_OK)
				{
					return EXIT_FAILURE;
				}
			break;
	}
	return EXIT_SUCCESS;	

	used_size = INT_NULL_VALUE;
	alloc_size = INIT_CHOP;


state_t realizarAlta(FILE* db, FILE* pf, FILE* log){
	peli_t db_struct, file_struct, db_temp;

	size_t n_db, n_pf;
	/* No se hacen validaciones sobre los punteros porque ya se hicieron en open file*/

	n_db = fread(&db_struct, sizeof(peli_t), 1, db);
	n_pf = fread(&file_struct, sizeof(peli_t), 1, pf);

	while(n_db && n_pf){
		if(db_struct.id < file_struct.id){
	/*guardar db*/
			if(leerValidar(&n_db,&db_struct,db,pf,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
		}else if(db_struct.id == file_struct.id){
			/*guardar db*/
			imprimir_peli(&file_struct,log);
			if(leerValidar(&n_db,&db_struct,db,pf,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
			if(leerValidar(&n_pf,&file_struct,pf,db,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
		}else{
			/*guardar pf*/
			if(leerValidar(&n_pf,&file_struct,pf,db,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
		}
	}
	while(n_db){
		/*guardar db*/
		if(leerValidar(&n_db,&db_struct,db,pf,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
	}
	while(n_pf){
		/*guardar pf*/
		if(leerValidar(&n_pf,&file_struct,pf,db,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
	}
	return ST_OK;
}


state_t realizarBaja(FILE* db, FILE* pf, FILE* log){
	peli_t db_struct, file_struct, db_temp;

	size_t n_db, n_pf;
	/* No se hacen validaciones sobre los punteros porque ya se hicieron en open file*/

	n_db = fread(&db_struct, sizeof(peli_t), 1, db);
	n_pf = fread(&file_struct, sizeof(peli_t), 1, pf);

	while(n_db && n_pf){
		if(db_struct.id < file_struct.id){
			/*guardar db*/
			if(leerValidar(&n_db,&db_struct,db,pf,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
		}else if(db_struct.id == file_struct.id){
			if(leerValidar(&n_db,&db_struct,db,pf,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
			if(leerValidar(&n_pf,&file_struct,pf,db,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
		}else{
			/*guardar db*/
			imprimir_peli(&file_struct,log);
			if(leerValidar(&n_pf,&file_struct,pf,db,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
		}
	}
	while(n_db){
		/*guardar db*/
		if(leerValidar(&n_db,&db_struct,db,pf,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
	}
	while(n_pf){
		imprimir_peli(&file_struct,log);
		if(leerValidar(&n_pf,&file_struct,pf,db,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
	}
	return ST_OK;
}


state_t realizarMod(FILE* db, FILE* pf, FILE* log){
	peli_t db_struct, file_struct, db_temp;

	size_t n_db, n_pf;
	/* No se hacen validaciones sobre los punteros porque ya se hicieron en open file*/

	n_db = fread(&db_struct, sizeof(peli_t), 1, db);
	n_pf = fread(&file_struct, sizeof(peli_t), 1, pf);

	while(n_db && n_pf){
		if(db_struct.id < file_struct.id){
			/*guardar db*/
			if(leerValidar(&n_db,&db_struct,db,pf,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
		}else if(db_struct.id == file_struct.id){
			/*guardar pf*/
			if(leerValidar(&n_db,&db_struct,db,pf,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
			if(leerValidar(&n_pf,&file_struct,pf,db,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
		}else{
			/*guardar db*/
			imprimir_peli(&file_struct,log);
			if(leerValidar(&n_pf,&file_struct,pf,db,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
		}
	}
	while(n_db){
		/*guardar db*/
		if(leerValidar(&n_db,&db_struct,db,pf,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
	}
	while(n_pf){
		imprimir_peli(&file_struct,log);
		if(leerValidar(&n_pf,&file_struct,pf,db,log) != OK) return ST_UNABLE_TO_READ_FROM_FILE;
	}
	return ST_OK;
}











	do
	{

		switch(estado)
		{
			case READ_BOTH_FILES:
				if ((fread(db_struct, sizeof(peli_t), CANT_ELEMENTOS_LEIDOS,db)) != CANT_ELEMENTOS_LEIDOS)
				{
						if(ferror(db))
						{
							fprintf(stderr, "%s:%s\n", ERROR, ERROR_LOAD);
							free_and_close(file_struct, db_struct, log, pf, db);
							return EXIT_FAILURE;
						}/*SI no hay error significa que ya no hay más archivos en la db*/
						estado = READ_FILE_ONLY;
						break;
				}

				if ((fread(file_struct, sizeof(peli_t), CANT_ELEMENTOS_LEIDOS, pf)) != CANT_ELEMENTOS_LEIDOS)
				{
					if(ferror(pf))
					{
						fprintf(stderr, "%s:%s\n", ERROR, ERROR_LOAD);
						free_and_close(file_struct, db_struct, log, pf, db);
						return EXIT_FAILURE;
					}

					if((st = comp_and_realloc(&used_size, &alloc_size, &db_temp)) != ST_OK)
					{
						estado = NO_MEM;
						break;
					}

					if ((st = peli_cpy(&(db_temp[used_size]), db_struct) != ST_OK))
					{ /*como un strcpy pero de peli_t (no hace falta pedir memoria)*/
		      			handle_state(st, db_struct, file_struct, log, pf, db);
		      			return EXIT_FAILURE;
		   		   	}

		    		used_size++;
					estado = READ_DB_ONLY;
					break;
				}

				if ((st = peli_cpy(&(db_temp[used_size]), db_struct) != ST_OK))
				{ /*como un strcpy pero de peli_t (no hace falta pedir memoria)*/
					handle_state(st, db_struct, file_struct, log, pf, db);
					return EXIT_FAILURE;
				}

				if (db_struct ->id == file_struct ->id)
				{
					if((st = same_id(ABM, &(db_temp[used_size]), db_struct, file_struct, log, &used_size)) != ST_OK)
					{
						handle_state(st, db_struct, file_struct, log, pf, db);
						return EXIT_FAILURE;
					}
					if ((estado != READ_DB_ONLY) || (estado != READ_FILE_ONLY)) estado = READ_BOTH_FILES;
					break;
				}

				if(db_struct ->id < file_struct ->id)
				{/*guardo el de db y leo de nuevo db*/
   					if ((st = peli_cpy(&(db_temp[used_size]), db_struct) != ST_OK))
   					{
   						handle_state(st, db_struct, file_struct, log, pf, db);
   						return EXIT_FAILURE;
   					}
   					used_size++;
   					estado = READ_DB;
   					break;
				}

				else
				{
					if (ABM != COMMAND_ALTA)
					{
						fprintf(log, "%s\n", ERROR_BAJA_MOD);
						imprimir_peli(file_struct, log);
					}
					else
					{/*guardo el del archivo y leo del archivo*/
	      				if ((st = peli_cpy(&(db_temp[used_size]), file_struct) != ST_OK))
                        {
	      					handle_state(st, db_struct, file_struct, log, pf, db);
	      					return EXIT_FAILURE;
	      				}
	      				used_size++;
	      			}
	      			estado = READ_FILE;
	      			break;
				}/* FIN CASE READ_BOTH_FILES */

			case READ_DB:
				if ((fread(db_struct,sizeof(peli_t),CANT_ELEMENTOS_LEIDOS,db)) != CANT_ELEMENTOS_LEIDOS)
				{
					if(ferror(db))
					{
						fprintf(stderr, "%s:%s\n", ERROR, ERROR_LOAD);
						free_and_close(file_struct, db_struct, log, pf, db);
						return EXIT_FAILURE;
					}
					finDeListas = CPY_FILE_STRUCT;
					estado = READ_FILE_ONLY;
					break;
				}

				if((st = comp_and_realloc(&used_size, &alloc_size, &db_temp)) != ST_OK)
				{
					estado = NO_MEM;
					break;
				}

				if (db_struct ->id == file_struct ->id)
				{
					if((st = same_id(ABM, &(db_temp[used_size]), db_struct, file_struct, log, &used_size)) != ST_OK)
					{
						handle_state(st, db_struct, file_struct, log, pf, db);
						return EXIT_FAILURE;
					}
					if ((estado != READ_DB_ONLY) || (estado != READ_FILE_ONLY)) estado = READ_BOTH_FILES;
					break;
				}

				if(db_struct ->id < file_struct ->id)
				{/*guardo el de db y leo de nuevo db*/
					if ((st = peli_cpy(&(db_temp[used_size]),db_struct) != ST_OK))
					{ /*como un strcpy pero de peli_t (no hace falta pedir memoria)*/
	      				handle_state(st, db_struct, file_struct, log, pf, db);
	      				return EXIT_FAILURE;
	      			}
	      			used_size++;
	      			estado = READ_DB;
	      			break;
				}
				else
				{
					if (ABM != COMMAND_ALTA)
					{
						fprintf(log, "%s\n", ERROR_BAJA_MOD);
						imprimir_peli(file_struct, log);
					}
					else
					{/*guardo el del archivo y leo del archivo*/
	      				if ((st = peli_cpy(&(db_temp[used_size]), file_struct) != ST_OK))
	      				{/*como un strcpy pero de peli_t (no hace falta pedir memoria)*/
	      					handle_state(st, db_struct, file_struct, log, pf, db);
	      					return EXIT_FAILURE;
	      				}
	      				used_size++;
	      			}
	      			estado = READ_FILE;
	      			break;
				}


			/* FIN CASE READ_DB */

			case READ_FILE:

				if ((fread(file_struct, sizeof(peli_t), CANT_ELEMENTOS_LEIDOS, pf)) != CANT_ELEMENTOS_LEIDOS)
				{
					if(ferror(pf))
					{
						fprintf(stderr, "%s:%s\n", ERROR, ERROR_LOAD);
						free_and_close(file_struct, db_struct, log, pf, db);
						return EXIT_FAILURE;
					}

					if ((st = peli_cpy(&(db_temp[used_size]), db_struct) != ST_OK))
   					{
   						handle_state(st, db_struct, file_struct, log, pf, db);
   						return EXIT_FAILURE;
   					}
   					used_size++;
					estado = READ_DB_ONLY;
					break;
				}

				if((st = comp_and_realloc(&used_size, &alloc_size, &db_temp)) != ST_OK)
				{
					estado = NO_MEM;
					break;
				}

				if (db_struct->id == file_struct->id)
				{
					if((st = same_id(ABM, &(db_temp[used_size]), db_struct, file_struct, log, &used_size)) != ST_OK)
					{
						handle_state(st, db_struct, file_struct, log, pf, db);
						return EXIT_FAILURE;
					}
					if ((estado != READ_DB_ONLY) || (estado != READ_FILE_ONLY)) estado = READ_BOTH_FILES;
					break;
				}

				if(db_struct ->id < file_struct ->id)
				{
					if ((st = peli_cpy(&(db_temp[used_size]),db_struct) != ST_OK))
					{
		      			handle_state(st,db_struct,file_struct,log,pf,db);
		      			return EXIT_FAILURE;
		      		}
		      		used_size++;
		      		estado = READ_DB;
		      		break;
				}

				else
				{
					if (ABM != COMMAND_ALTA)
					{
						fprintf(log, "%s\n", ERROR_BAJA_MOD);
						imprimir_peli(file_struct, log);
					}
					else
					{/*guardo el del archivo y leo del archivo*/
	      				if ((st = peli_cpy(&(db_temp[used_size]), file_struct) != ST_OK))
	      				{
	      					handle_state(st, db_struct, file_struct, log, pf, db);
	      					return EXIT_FAILURE;
	      				}
	      				used_size++;
	      			}
	      			estado = READ_FILE;
	      			break;
				}
				/* FIN CASE READ_FILE */

			case READ_DB_ONLY:

				if ((fread(db_struct, sizeof(peli_t), CANT_ELEMENTOS_LEIDOS, db)) != CANT_ELEMENTOS_LEIDOS)
				{
					if(ferror(db))
					{
						fprintf(stderr, "%s:%s\n", ERROR, ERROR_LOAD);
						free_and_close(file_struct, db_struct, log, pf, db);
						return EXIT_FAILURE;
					}	/*SI no hay error significa que ya no hay más archivos en la db y en el archivo*/
					estado = NO_MORE_BYTES_TO_READ;
					break;
				}

				if((st = comp_and_realloc(&used_size, &alloc_size, &db_temp)) != ST_OK)
				{
					estado = NO_MEM;
					break;
				}
				if ((st = peli_cpy(&(db_temp[used_size]), db_struct) != ST_OK))
				{
      				handle_state(st, db_struct, file_struct, log, pf, db);
      				return EXIT_FAILURE;
      			}
	  			used_size++;
	  		estado = READ_DB_ONLY;
	  		break;/* FIN CASE READ_DB_ONLY */

			case READ_FILE_ONLY:
				if (ABM != COMMAND_ALTA)
				{
					fprintf(log, "%s\n", ERROR_BAJA_MOD);
					imprimir_peli(file_struct, log);
				}
				else
				{
					if (finDeListas == CPY_FILE_STRUCT)
					{
						if ((st = peli_cpy(&(db_temp[used_size]), file_struct) != ST_OK))
						{
	      					handle_state(st, db_struct, file_struct, log, pf, db);
	      					return EXIT_FAILURE;
	      				}
	  				used_size++;
					}
					finDeListas = CPY_FILE_STRUCT;
				}

				if ((fread(file_struct, sizeof(peli_t), CANT_ELEMENTOS_LEIDOS, pf)) != CANT_ELEMENTOS_LEIDOS)
					{
						if(ferror(pf))
						{
							fprintf(stderr, "%s:%s\n", ERROR, ERROR_LOAD);
							free_and_close(file_struct, db_struct, log, pf, db);
							return EXIT_FAILURE;
						}
						estado = NO_MORE_BYTES_TO_READ;
						break;
					}

				if((st = comp_and_realloc(&used_size, &alloc_size, &db_temp)) != ST_OK)
				{
					estado = NO_MEM;
					break;
				}

	  		estado = READ_FILE_ONLY;
	  		break;

	  		case NO_MORE_BYTES_TO_READ:/* CIERRO DB, LA ABRO EN MODO ESCRITURA Y GUARDO db_temp*/
	  			fclose(db);
	  			if ((db = fopen(argv[pos_db_cla], "wb")) == NULL)
	  			{
					fprintf(stderr, "%s:%s\n", ERROR, ERROR_OPEN_DB);
					del_films_array(&db_temp, &used_size);
					free(db_struct);
					free(file_struct);
					fclose(log);
					fclose(pf);
					return EXIT_FAILURE;
				}
				if ((fwrite(db_temp, sizeof(peli_t), used_size,db)) != used_size)
				{
					fprintf(stderr, "%s:%s\n", ERROR, ERROR_WRITE_FILE);
					del_films_array(&db_temp, &used_size);
					free_and_close(file_struct, db_struct, log, pf, db);
					return EXIT_FAILURE;
				}
				del_films_array(&db_temp, &used_size);
				free_and_close(file_struct, db_struct, log, pf, db);
				estado = SUCCESS;
				break;

			default:
					handle_state(st, db_struct, file_struct, log, pf, db);
					free_and_close(file_struct, db_struct, log, pf, db);
					return EXIT_FAILURE;
		}	/* FIN CASE READ_FILE_ONLY */
	}
	while (estado != SUCCESS);
	return EXIT_SUCCESS;
}

state_t validarArg(command_t* ptr_operacion, int argc, char* argv[], char ** db_filename,char ** op_filename,char ** log_filename){
	size_t pos_db_cla, pos_file_cla, pos_log_cla;
	
	pos_db_cla = obtener_pos_cla(COMMAND_DB, argc, argv);
	pos_file_cla = obtener_pos_cla(COMMAND_FILE, argc, argv);
	pos_log_cla = obtener_pos_cla(COMMAND_LOG, argc, argv);

	if(validarCantArg(CANT_TOTAL_PARAM_RANK,argc)!= ST_OK) {
		return handle_error(ST_ERROR_INVALID_CANT_ARG);
	}

	if( pos_db_cla == (argc -1)  || pos_file_cla == (argc-1) || pos_log_cla == (argc-1) ){
		return handle_error(ST_ERROR_PARAM_NOT_FOUND)
	}

	*db_filename = argv[pos_db_cla];
	*op_filename = argv[pos_file_cla];
	*log_filename = argv[pos_log_cla];

	if((strcmp(argv[POS_COMMAND_CLA], STR_ALTA) == 0) || (strcmp(argv[POS_COMMAND_CLA], STR_ALTA_MIN) == 0)) {
		*ptr_operacion = COMMAND_ALTA;
	}
	else if((strcmp(argv[POS_COMMAND_CLA], STR_BAJA) == 0) || (strcmp(argv[POS_COMMAND_CLA], STR_BAJA_MIN) == 0)) {
		*ptr_operacion = COMMAND_BAJA;
	}
	else if((strcmp(argv[POS_COMMAND_CLA], STR_MOD) == 0) || (strcmp(argv[POS_COMMAND_CLA], STR_MOD_MIN) == 0)) {
		*ptr_operacion = COMMAND_MOD;
	}else{
		return handle_error(ST_ERROR_COMMAND);
	}
	return ST_OK;
}





size_t obtener_pos_cla(char* pos_cla,int argc, const char *argv[]){
    int i, res;
    for (i = 0; i < argc; ++i)
    {
        if (strcmp(pos_cla, argv[i]) == 0)
        {
            res = i + 1;
        }
    }
    return res;
}


void free_and_close(peli_t *file_struct, peli_t *db_struct, FILE *log, FILE *db, FILE *pf)
{
    free(file_struct);
    free(db_struct);
    closeFileDB(pf,db)
    fclose(log);
}


void handle_state(state_t st, peli_t *db_struct, peli_t *file_struct, FILE *log, FILE *pf, FILE *db)
{
	handle_error(st);
	free_and_close(file_struct, db_struct, log, pf, db);
}

state_st comp_and_realloc(size_t *used_size, size_t *alloc_size, peli_t **db_temp_realloc)
{
    state_st st_realloc;
    peli_t *aux;
    st_realloc = ST_OK;
    if((*used_size) == (*alloc_size)) /*FUNCION*/
    {
        if ((aux = (peli_t*)realloc((*db_temp_realloc), ((*alloc_size) + CHOP_SIZE)*sizeof(peli_t))) == NULL)
        {
            del_films_array(db_temp_realloc, used_size);
            st_realloc = ST_MEMORY_ERROR;
        }
        else
        {
            alloc_size += CHOP_SIZE;
            *db_temp_realloc = aux;
            st_realloc = ST_OK;
        }
    }
    return st_realloc;
}

state_t leerValidar(size_t* n_db,peli_t* ptr_struct_read,FILE* pf_to_read,FILE* pf,FILE* log){
				if( (*n_db = fread(ptr_struct_read, sizeof(peli_t), 1, pf_to_read);) != 1){
					if(ferror(db)){
						closeFileDB(ptr_struct_read,pf),
						fclose(log);
						return handle_error(ST_UNABLE_TO_READ_FROM_FILE);
					}
				}
			return ST_OK;
			}