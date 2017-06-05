#ifndef PELICULA__H
#define PELICULA__H

typedef struct peliculas
{
	size_t id;
    char titulo[MEAN_SIZE_STR];
    char guion [MEAN_SIZE_STR];
    char director[MEAN_SIZE_STR];
    time_t fecha;
    double puntaje;
    size_t reviews;
} peli_t;

#endif
