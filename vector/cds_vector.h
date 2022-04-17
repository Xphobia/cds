
#ifndef _CDS_VECTOR_H
#define _CDS_VECTOR_H

typedef int int32_t;
typedef unsigned int uint32_t;
typedef void *vector_t;
typedef void *elem_t;

/* create a vector */
vector_t cds_vector_create(int32_t elem_size);

/* destroy a vector */
void cds_vector_destroy(vector_t vec);

/* free all elements of vector */
void cds_vector_free_elements(vector_t vec);

/* resize vector capacity */
int32_t cds_vector_resize(vector_t vec, uint32_t capacity);

/* get vector size */
int32_t cds_vector_size(const vector_t vec);

/* get vector capacity */
int32_t cds_vector_capacity(const vector_t vec);

/* judge vector is empty or not */
int32_t cds_vector_is_empty(const vector_t vec);

/* insert an element to vector */
int32_t cds_vector_append(vector_t vec, elem_t elme);

/* remove an element from vector */
int32_t cds_vector_remove(vector_t vec, uint32_t idx);

/* get an element by index */
const elem_t* cds_vector_index(const vector_t vec, uint32_t idx);

/* print elements in vector */
void cds_vector_print(const vector_t vec, void (*print)(const elem_t elem));

#endif /* _CDS_VECOR_H */