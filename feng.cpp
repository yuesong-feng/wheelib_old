#include <iostream>
#include "src/ds/dlist.h"

int main(){
    dlist *dl = dlist_init();
    dlist_destroy(dl);
    return 0;
}