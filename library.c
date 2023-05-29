#include "library.h"

void vector_cerinte(FILE *cerinte_file, int cerinte[])
{
    fisier_null(cerinte_file); // check fis
    int i, n=5;
    for(i=0; i<n; i++)
    {
        fscanf(cerinte_file, "%d", &cerinte[i]);
    }
}

