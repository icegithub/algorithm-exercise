#include <stdio.h>
#include <stdlib.h>

#define N 4

int main() 
{
	char *p = (char*)calloc(N, sizeof(char));
	/* char *p; */
	int i;
	for (i = 0; i < N; i++) {
	}
	sprintf(p+2, "%c", 'h');
	printf("%c\n", *(p+2));
	sprintf(p+2, "%c", 'e');
	printf("%s\n", p+2);
	
	char a = 'a';
	char b = 'b';
	printf("%s\n", "ab");
	return 0;
}
