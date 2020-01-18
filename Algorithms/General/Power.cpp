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

// can also be viewed as if expo varies from 0 to 1001

const int tope=1001;
long long int expo[tope];
expo[0] = 1;
for (int i = 1; i < tope; i += 1) {
    expo[i] = (A * expo[i-1]) % modulo;
}
