#include <iostream>
#include <string>
using namespace std;
void function(int a) 
{
  char buffer[5];
  char *ret;
  ret = buffer + 12;
  *ret += 8;
}

int main()
{
  int x;
  x = 10;
  function(7);
  x = 1;
  cout<<x<<endl;
}
