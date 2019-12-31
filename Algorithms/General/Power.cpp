// Problem : Power function
// Author  : The Philomath
// Date    : 31-12-2019

/**********************************************************************************
*
*    Calculate pow(A, n)
*
**********************************************************************************/

long long power(int A, int expo)
{
  int res = 1;
  while(A)
  {
    if(A & 1)
    {
      res = res * A;
    }
    A = A * A;
    A = A >> 1;
  }
  return res;
}
