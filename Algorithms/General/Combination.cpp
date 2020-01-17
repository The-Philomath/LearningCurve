// Problem : Combination function
// Author  : The Philomath
// Date    : 17-01-2019

/**********************************************************************************
*
*    Calculate nCr
*
**********************************************************************************/
long long int combination(int n,int r){
    int C[r+1];
    memset(C, 0, sizeof(C));

    C[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = min(i, r); j > 0; j--)
            C[j] = C[j] + C[j-1];
    }
    return C[r];
}
