#include <stdio.h>

#define LEN 100
#define FALSE 0
#define TRUE 1
/* #define Heap Heap.content */

/* typedef struct Array{ */
/*   int length; */
/*   int (*push)(int a); */
/* }Array; */

/* typedef struct Array Array; */

void
HeapBottomUp(int Heap[], int length)
{
     int i = 0, k = 0, j = 0, v = 0;
     int n = length;
     int heap = FALSE; // 0->false
     for(i = n/2;i >= 1; i--) {
          k = i;
          v = Heap[k]; //v storage that i position number
          heap = FALSE;
          while(!heap && 2 * k <= n) {
               j = 2 * k; //子代右节点 
               if (j < n) { //there two children, find the max
                    if(Heap[j] < Heap[j+1]) j = j + 1;
               }
               if (v >= Heap[j]) {
                    heap = TRUE;
               }
               else {
                    Heap[k] = Heap[j]; 
                    k = j;
               }
          }
          Heap[k] = v;
     }
}

void 
HeapSort(int H[], int length) 
{
     int sort[LEN]={0};
     int n = length, i = 0;
     while(0 != length) {
          HeapBottomUp(H, length);
          sort[i] = H[1]; //record the top(root) number 
          H[1] = H[length-1]; //make the rightest and deepest leaf be the root
          i++, length--;//length-- delete it
     }
     printf("================After Heap Sort=================\n");
     for(i = 0; i < n-1; i++){
          printf("%3d ", sort[i]);
     }
     printf("\n");
}

int
main( int argc, char *argv[]) 
{
     int i = 0, length = 0;
     int Heap[LEN] = {0};
     /* int i = 0; */
     /* Array Heap; */
     /* Heap.length = 0; */
     /* Heap.content[LEN] = {0}; */
  
     //input
     printf("Please input the number(input any letter to end).\n");
     while(scanf("%d", &Heap[++length])!=0){}
     printf("=================Before===================\n");
     for(i = 1; i < length; i++){
          printf("%3d ", Heap[i]);
     }
     printf("\n");

     HeapBottomUp(Heap, length);

     printf("=================After====================\n");
     for(i = 1; i < length; i++){
          printf("%3d ", Heap[i]);
     }
     printf("\n");

     HeapSort(Heap, length);

     return 0;
}
