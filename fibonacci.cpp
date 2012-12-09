#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

class Matrix {
public: 
    long matr[2][2];
    
    Matrix( const Matrix &rhs );
    Matrix( long a, long b, long c, long d );
    Matrix& operator = ( const Matrix & );
    friend Matrix operator*( const Matrix& lhs, const Matrix& rhs ) {
        Matrix ret( 0,0,0,0 );
        ret.matr[0][0] = lhs.matr[0][0]*rhs.matr[0][0] + lhs.matr[0][1]*rhs.matr[1][0];
        ret.matr[0][1] = lhs.matr[0][0]*rhs.matr[0][1] + lhs.matr[0][1]*rhs.matr[1][1];
        ret.matr[1][0] = lhs.matr[1][0]*rhs.matr[0][0] + lhs.matr[1][1]*rhs.matr[1][0];
        ret.matr[1][1] = lhs.matr[1][0]*rhs.matr[0][1] + lhs.matr[1][1]*rhs.matr[1][1];
        return ret;        // ret.matr[0][0] = 
    }
};


Matrix::Matrix(long a, long b, long c, long d)
{
    this->matr[0][0] = a;
    this->matr[0][1] = b;
    this->matr[1][0] = c;
    this->matr[1][1] = d;
}

Matrix::Matrix(const Matrix &rhs)
{
    this->matr[0][0] = rhs.matr[0][0];
    this->matr[0][1] = rhs.matr[0][1];
    this->matr[1][0] = rhs.matr[1][0];
    this->matr[1][1] = rhs.matr[1][1];
}
 
Matrix& Matrix::operator =(const Matrix &rhs)
{
    this->matr[0][0] = rhs.matr[0][0];
    this->matr[0][1] = rhs.matr[0][1];
    this->matr[1][0] = rhs.matr[1][0];
    this->matr[1][1] = rhs.matr[1][1];
    return *this;
}
 
Matrix power(const Matrix& m, int n)
{
    if (n == 1)
        return m;
    if (n%2 == 0)
        return power(m*m, n/2);
    else
        return power(m*m, n/2) * m;
}
 
//普通递归
long fib1(int n)
{
    if (n <= 2)
    {
        return 1;
    }
    else
    {
        return fib1(n-1) + fib1(n-2);
    }
}
/*上面的效率分析代码
  long fib1(int n, int* arr)
  {
  arr[n]++;
  if (n <= 1)
  {
  return 1;
  }
  else
  {
  return fib1(n-1, arr) + fib1(n-2, arr);
  }
  }
*/
 
long fib(int n, long a, long b, int count)
{
    if (count == n)
        return b;
    return fib(n, b, a+b, ++count);
}
//一叉递归
long fib2(int n)
{
    return fib(n, 0, 1, 1);
}
 
//非递归方法O(n)
long fib3 (int n)
{
    long x = 0, y = 1;
    for (int j = 1; j < n; j++)
    {
        y = x + y;
        x = y - x;
    }
    return y;
}
 
//矩阵乘法O(log(n))
long fib4 (int n)
{
    Matrix matrix0(1, 1, 1, 0);
    matrix0 = power(matrix0, n-1);
    return matrix0.matr[0][0];
}
 
//公式法O(1)
long fib5(int n)
{
    double z = sqrt(5.0);
    double x = (1 + z)/2;
    double y = (1 - z)/2;
    return (pow(x, n) - pow(y, n))/z + 0.5;
}
 
int main()
{
    //n = 45时候fib1()很慢
    int n = 10;
    cout << fib1(n) << endl;
    cout << fib2(n) << endl;
    cout << fib3(n) << endl;
    cout << fib4(n) << endl;
    cout << fib5(n) << endl;
    return 0;
}
