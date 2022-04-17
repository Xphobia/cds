
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cds_vector.h"

#define S_ERR     -1
#define S_OK       0
#define CAPACITY   4  /* Initial capacity for a fresh new vector */
#define BLOCK_SIZE 4

typedef struct _vector_t {
    elem_t data;
    uint32_t elem_size;
    uint32_t size;
    uint32_t capacity;
} _vector_t;

/* create a vector */
vector_t cds_vector_create(int elem_size) {
    _vector_t * pv = (_vector_t *)malloc(sizeof(_vector_t));
    if (pv == NULL) {
        return NULL;
    }

    pv->data = malloc(CAPACITY*sizeof(elem_size));
    if (pv->data == NULL) {
        free(pv);
        return NULL;
    }
    pv->size = 0;
    pv->elem_size = elem_size;
    pv->capacity = CAPACITY;

    return (vector_t)pv;
}

/* destroy a vector */
void cds_vector_destroy(vector_t vec) {
    _vector_t *pv = (_vector_t *)vec;
    if (pv != NULL) {
        cds_vector_free_elements(pv);
        free(pv);
        pv = NULL;
    }
}

/* free all elements of vector */
void cds_vector_free_elements(vector_t vec) {
    int32_t idx = 0;
    _vector_t *pv = (_vector_t *)vec;

    if (pv != NULL) {
        if (pv->data != NULL) {
            free(pv->data);
            pv->data = NULL;
        }
        pv->size = 0;
        pv->capacity = 0;
    }
}

/* resize vector capacity */
int32_t cds_vector_resize(vector_t vec, uint32_t capacity)
{
    _vector_t *pv = (_vector_t *)vec;
    elem_t *new_data = NULL;

    if (pv == NULL) {
        return S_ERR;
    }
    if (capacity < pv->size) {
        return S_ERR;
    }

    new_data = malloc(pv->elem_size * capacity);
    if (new_data == NULL) {
        return S_ERR;
    }
    memcpy(new_data, pv->data, pv->elem_size * pv->size);
    free(pv->data);
    pv->data = new_data;
    pv->capacity = capacity;

    return S_OK;
}

/* get vector size */
int32_t cds_vector_size(const vector_t vec)
{
    const _vector_t *pv = (const _vector_t *)vec;
    if (pv == NULL) {
        return -1;
    }

    return pv->size;
}

/* get vector capacity */
int32_t cds_vector_capacity(const vector_t vec)
{
    const _vector_t *pv = (const _vector_t *)vec;
    if (pv == NULL) {
        return -1;
    }

    return pv->capacity;
}

/* judge vector is empty or not */
int32_t cds_vector_is_empty(const vector_t vec)
{
    int32_t is_empty = 0;
    const _vector_t *pv = (const _vector_t *)vec;

    assert(pv != NULL);
    is_empty = (pv->size == 0) ? 1 : 0;

    return is_empty;
}


/* insert an element to vector */
int32_t cds_vector_append(vector_t vec, elem_t elem)
{
    int32_t ret = 0;
    _vector_t *pv = (_vector_t *)vec;

    if ((pv == NULL) || (elem == NULL)) {
        return S_ERR;
    }

    if (pv->size >= pv->capacity) {
        ret = cds_vector_resize(pv, pv->size + CAPACITY);
        if (ret == S_ERR) {
            return S_ERR;
        }
    }

    memcpy(pv->data + pv->elem_size*pv->size, elem, pv->elem_size);
    pv->size++;

    return S_OK;
}

/* remove an element from vector */
int32_t cds_vector_remove(vector_t vec, uint32_t idx)
{
    _vector_t *pv = (_vector_t *)vec;

    if (pv == NULL) {
        return S_ERR;
    }

    if ((idx > pv->size - 1) || (idx < 0)) {
        return S_ERR;
    }
    pv->data = memmove(pv->data+pv->elem_size*idx, pv->data+pv->elem_size*(idx+1), pv->elem_size*(pv->size-idx));
    pv->size--;

    return S_OK;
}

/* get an element by index */
const elem_t* cds_vector_index(const vector_t vec, uint32_t idx)
{
    const _vector_t *pv = (const _vector_t *)vec;

    if (pv == NULL) {
        return NULL;
    }

    if ((idx > pv->size) || (idx < 0)) {
        return NULL;
    } else {
        return pv->data + pv->elem_size*(idx);
    }
}

/* print elements in vector */
void cds_vector_print(const vector_t vec, void (*print)(const elem_t elem))
{
    const _vector_t *pv = (const _vector_t *)vec;

    int idx = 0;
    elem_t elem;

    printf("vector: %p, size = %d, capacity = %d\n", vec, pv->size, pv->capacity);
    printf("elements: ");
    for (idx = 0; idx < pv->size; idx++) {
        if ((idx % BLOCK_SIZE) == 0) {
            putchar('\n');
        }
        elem = pv->data + pv->elem_size * idx;
        print(elem);
        putchar('\t');
    }
    putchar('\n');
}