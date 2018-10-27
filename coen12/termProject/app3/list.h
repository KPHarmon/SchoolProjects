# ifndef LIST_H
# define LIST_H

typedef struct list LIST;

extern LIST *createList();

extern void destroyList(LIST *lp);

extern void addFirst(LIST *lp, int eltId, int eltAge);

extern void removeItem(LIST *lp, int eltId);

extern void findItem(LIST *lp, int eltId);

extern int maxAgeGap(LIST *lp);

extern void getItems(LIST *lp, int eltId);

# endif /* LIST_H */
