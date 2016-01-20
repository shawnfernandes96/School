typedef struct {
    int maxsize;
    int size;
    int* item;
} Path;

void PathInit(Path *P, int size);
void PathDestroy(Path *P);
void PathClone(Path *O, Path *P, int lastPos);
int PathAddEntry(Path *P, int entry);
int PathRemoveEntry(Path *P);
void PathPrint(Path P);