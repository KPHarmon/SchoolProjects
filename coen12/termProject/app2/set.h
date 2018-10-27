/*
 * File:        set.h
 *
 * Copyright:	2017, Darren C. Atkinson
 *
 * Description: This file contains the public function and type
 *              declarations for a set abstract data type for strings.  A
 *              set is an unordered collection of distinct elements.
 */

# ifndef SET_H
# define SET_H

typedef struct set SET;

typedef struct node NODE;

SET *createSet(int maxElts);

void destroySet(SET *sp);

void addElement(SET *sp, int *elt, int *elt2);

void removeElement(SET *sp, int *elt);

void findElement(SET *sp, int *elt);

# endif /* SET_H */
