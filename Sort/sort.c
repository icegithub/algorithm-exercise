#include <stdio.h>
/* -------------- */
/*  +-------------------+      +----------------------+ */
/*  |                   |      |                      | */
/*  |                   ------+-                     | */
/*  +-------------------+      +----------------------+ */
//用插入排序对给定数组排序
int InsertSort(int a[], int a_length)
{
     if(!a && a_length <=0)
          return -1;
     int i = 0, j = 0;
     int v;
     for(i = 1; i < a_length; i++) {
          v = a[i];      //用于存储开始比较第一个数
          j = i - 1;     //得到i前面一个数字
          while(j>=0 && a[j] > v) {//比较的实质是让i前面的有序，然后i向后退
               a[j+1] = a[j]; //j后面的数被当前j替换
               j = j - 1;     //j向前移动一位
          }
          a[j+1] = v;
     }
}

//对于给定数组进行快速排序
/* int quicksort(int a[], int start, int end) */
/* { */
/*      if(a_length > 1) { */
/*        int s; */
/*        s = partition(a, start, end); */
/*        quicksort(a, start, end); */
/*      } */
/* } */

int main(int argc, char* argv[])
{
  int a[] = {3,1,4,5,6,7,4,2,1,4,56,7};
  int a_length = 12;
  InsertSort(a, a_length);
  return 0;
}
