#include "list.h"
int main(){
    list *l = list_init();
    int arr[] = {0,1,2,3,4,5,6,7,8,9,10};
    list_push_back(l, &arr[1]);
    list_push_back(l, &arr[2]);
    list_push_back(l, &arr[3]);
    
    list_destroy(l);
    return 0;
}