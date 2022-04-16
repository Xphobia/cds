
#include <stdio.h>
#include "array.h"

int main(void)
{
    Array a = array_create(10);
    printf("size = %d\n", array_size(&a));

    *array_at(&a, 0) = 10;
    printf("a[0] = %d\n", *array_at(&a, 0));

    int number = 0;
    int cnt = 0;
    while (number != -1) {
        scanf("%d", &number);
        if (number != -1) {
            array_set(&a, cnt, number);
            cnt++;
        }
    }

    int idx = 0;
    for (idx = 0; idx < a.size; idx++) {
        printf("%d\t", array_get(&a, idx));
    }
    printf("\n");

    array_free(&a);

    return 0;
}