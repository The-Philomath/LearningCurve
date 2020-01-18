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

//can be viewed as

typedef long long int lint;

const int tope=1001;

lint combi[tope][tope];
bool flag;

void precompute() {
    if(flag) return;
    flag = 1;
    for(int n = 0; n < tope; n += 1) {
        for(int k = 0; k <= n; k += 1) {
            if (k == 0 or k == n) {
                combi[n][k] = 1;
            }
            else {
                combi[n][k] = (combi[n-1][k] + combi[n-1][k-1]);
            }
        }
    }
}
