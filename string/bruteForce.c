#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
     char data[ MAX_SIZE ];
     int length;
}string;


/**
 *朴素模式匹配算法又称简单匹配算法或Brute-Force算法，它是字符串模式匹配中比较简单 *的一种算法。它从主串的第一个字符开始进行模式匹配，依次比较主串和模式串中的每个字  *符，若比较全部相等（模式匹配成功），则返回模式串中第一个字符在主串中的位置，否则  *主串指针从比较失败的字符处回溯到第二个字符开始重新和模式串进行匹配，这样依此下去  *，直到和模式串匹配成功或到主串的末尾（匹配不成功）为止。
 **/
int bruteForce( string s, string t )
{
     /* printf ("%d\t%d\n",s.length, t.length); */
     int i = 0, j = 0;
     while (i < s.length && j < t.length)
     {
          if( s.data[ i ]  == t.data[ j ]) {
               i++;
               j++;
          } else {
               i = i - j + 1;
               j = 0;
          }
     } 
     
     if (j >= t.length)
     {
          return i - t.length;
     } else {
          return -1;
     }
}

/**
 *horspool算法将主串中匹配窗口的最后一个字符跟模式串中的最后一个字符比较。如果相等，继续从后向前对主串和模式串进行比较，直到完全相等或者在某个字符处不匹配为止（如下图中的α与σ失配） 。如果不匹配，则根据主串匹配窗口中的最后一个字符β在模式串中 的下一个出现位置将窗口向右移动。
 * */
int horspool( string s, string t )
{
     
}

int main(int argc, char *argv[])
{
     int i = 0, j = 0;
     string s, t;
     s.length = 0;
     t.length = 0;
     memset( s.data, 0, strlen( s.data ) );
     memset( t.data, 0, strlen( t.data ) );
     printf( "Please input s :\n" );
     scanf( "%s", s.data );
     printf ("Brute Force Algorithm\n");
     while(s.data[ s.length ] != '\0') {
          s.length++;
     }
     getchar();
     printf( "Please input t :\n" );
     scanf( "%s", t.data );
     while(t.data[ t.length ] != '\0') {
          t.length++;
     }
     j = bruteForce( s, t );
     printf( "The same letter is from: %d\nAnd the same letter is:\n", j );
     for (i=0; i < t.length; ++i)
     {
          printf ("%c", t.data[i]);
     }
     printf ("\n");
     printf ("Horspool Algorithm\n");
     return 0;
}
