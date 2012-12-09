#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE 100
#define ASIIC_LENGTH 128

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
          return i - t.length + 1;
     } else {
          return -1;
     }
}

/**
 *horspool算法将主串中匹配窗口的最后一个字符跟模式串中的最后一个字符比较。如果相等，继续从后向前对主串和模式串进行比较，直到完全相等或者在某个字符处不匹配为止 。如果不匹配，则根据主串匹配窗口中的最后一个字符β在模式串中 的下一个出现位置将窗口向右移动。
 * */
const unsigned char *horspool( string s, string t )
{
     size_t scan = 0;
     size_t bad_char_skip[ UCHAR_MAX + 1 ];
     
     if( t.length <= 0 || !(s.data) || !(t.data) )
          return NULL;
     
     for( scan = 0; scan <= UCHAR_MAX; scan++ ) {
          bad_char_skip[ scan ] = t.length;
     }

     size_t last = t.length--;

     for( scan = 0; scan < last; scan++ ) {
          bad_char_skip[ t.data[ scan ] ] = last - scan;
     }

     while( s.length >= t.length ) {
          for (scan = last; s.data[ scan ] == t.data[ scan ]; scan--)
          {
               if( scan == 0 ) {
                    printf ("%s\n",s.data);
                    return s.data;
               }
          }
          
          s.length -= bad_char_skip[ s.data[last] ];
          s.data   += bad_char_skip[ s.data[last] ];
     }
     return NULL;
}

/* Returns a pointer to the first occurrence of "needle"
 * within "haystack", or NULL if not found. Works like
 * memmem( ).
 */
 
/* Note: In this example needle is a Cstring. The ending
 * 0x00 will be cut off, so you could call this example with
 * boyermoore_horspool_memmem( haystack, hlen, "abc", sizeof( "abc"))
 */
const unsigned char *
boyermoore_horspool_memmem( const unsigned char* haystack, ssize_t hlen,
                            const unsigned char* needle,   ssize_t nlen)
{
     
     size_t scan = 0;
     size_t bad_char_skip[ UCHAR_MAX + 1]; /* Officially called:
                                            * bad character shift */
 
     /* Sanity checks on the parameters */
     if ( nlen <= 0 || !haystack || !needle)
          return NULL;
 
     /* ---- Preprocess ---- */
     /* Initialize the table to default value */
     /* When a character is encountered that does not occur
      * in the needle, we can safely skip ahead for the whole
      * length of the needle.
      */
     for ( scan = 0; scan <= UCHAR_MAX; scan = scan + 1)
          bad_char_skip[ scan] = nlen;
 
     /* C arrays have the first byte at [ 0], therefore:
      * [ nlen - 1] is the last byte of the array. */
     size_t last = nlen - 1;
 
     /* Then populate it with the analysis of the needle */
     for ( scan = 0; scan < last; scan = scan + 1)
          bad_char_skip[ needle[ scan]] = last - scan;
 
     /* ---- Do the matching ---- */
 
     /* Search the haystack, while the needle can still be within it. */
     while ( hlen >= nlen)
    {
         
         /* scan from the end of the needle */
         for ( scan = last; haystack[ scan] == needle[ scan]; scan = scan - 1)
              if ( scan == 0) /* If the first byte matches, we've found it. */
                   return haystack;
 
         /* otherwise, we need to skip some bytes and start again.
           Note that here we are getting the skip value based on the last byte
           of needle, no matter where we didn't match. So if needle is: "abcd"
           then we are skipping based on 'd' and that value will be 4, and
           for "abcdd" we again skip on 'd' but the value will be only 1.
           The alternative of pretending that the mismatched character was
           the last character is slower in the normal case ( Eg. finding
           "abcd" in "...azcd..." gives 4 by using 'd' but only
           4-2==2 using 'z'. */
         hlen     -= bad_char_skip[ haystack[ last]];
         haystack += bad_char_skip[ haystack[ last]];
    }
 
     return NULL;
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
     horspool(s, t);
     /* boyermoore_horspool_memmem( s.data, strlen( s.data ), t.data, strlen( t.data )); */
     return 0;
}
