#include <stdio.h>
#include "cds_vector.h"

void print_int(const elem_t num)
{
    printf("%d\t", *((int*)num));
}

int main(void) {
    int ret = 0;
    int elem_size = sizeof(int);

    vector_t vec = cds_vector_create(elem_size);
    if (vec == NULL) {
        printf("cds_vector_create failed.\n");
        return -1;
    }
    cds_vector_print(vec, print_int);

    int val = -1;
    do {
        scanf("%d", &val);
        if (val != -1) {
            ret = cds_vector_append(vec, &val);
            if (ret != 0) {
                printf("cds_vector_append failed.\n");
                return -1;
            }
        }
    } while(val != -1);
    cds_vector_print(vec, print_int);

    cds_vector_remove(vec, 0);
    printf("\n revmoe first element\n");
    cds_vector_print(vec, print_int);

    cds_vector_destroy(vec);

    return ret;
}