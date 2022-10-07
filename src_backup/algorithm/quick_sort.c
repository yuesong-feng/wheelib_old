// #include "algorithm/algorithm.h"

// void quick_sort(int arr[], int len, int left, int right){
//     if(left >= right) return;
//     int i = left, j = right;
//     while(i < j){
//         while(j > i && arr[j] >= arr[left])
//             j--;
//         while(i < j && arr[i] <= arr[left])
//             i++;
//         swap(arr[i], arr[j]);
//     }
//     swap(arr[i], arr[left]);
//     quick_sort(arr, len, left, i - 1);
//     quick_sort(arr, len, i + 1, right);
// }
