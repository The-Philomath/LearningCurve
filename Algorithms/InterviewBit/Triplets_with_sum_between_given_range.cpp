// Problem : https://www.interviewbit.com/problems/triplets-with-sum-between-given-range/
// Author  : The Philomath
// Date    : 09-01-2020

/**********************************************************************************
*    Given an array of real numbers greater than zero in form of strings.
*    Find if there exists a triplet (a,b,c) such that 1 < a+b+c < 2 .
*    Return 1 for true or 0 for false.
*
*    Example:
*    Given [0.6, 0.7, 0.8, 1.2, 0.4] ,
*    You should return 1
*    as
*    0.6+0.7+0.4=1.7
*    1<1.7<2
*
*    Hence, the output is 1.
*
*    O(n) solution is expected.
*
**********************************************************************************/
int Solution::solve(vector<string> &A) {

        vector<double> AL(3,INT_MIN);
        vector<double> AS(2,INT_MAX);
        vector<double> BS(2,INT_MAX) ;
        double c = INT_MAX;
        double range = double(2)/double(3);
        for(int i = 0; i< A.size(); i++)
        {
            double d = stod(A[i]);
            if(d > 0 && d < range)
            {
                if(d>AL[0])
                {
                    AL[2] = AL[1];
                    AL[1] = AL[0];
                    AL[0] = d;
                }
                else if(d>AL[1])
                {
                    AL[2] = AL[1];
                    AL[1] = d;
                }
                else if(d>AL[2])
                {
                    AL[2] = d;
                }
                if(d<AS[0])
                {
                    AS[1] = AS[0];
                    AS[0] = d;
                }
                else if(d<AS[1])
                {
                    AS[1] = d;
                }
            }
            else if(d >= range && d <= 1)
            {
                if(d<BS[0])
                {
                    BS[1] = BS[0];
                    BS[0] = d;
                }
                else if(d<BS[1])
                {
                    BS[1] = d;
                }
            }
            else if(d > 1 && d < 2)
            {
                if(d < c) c = d;
            }
        }
        
        if(((AL[0] + AL[1] + AL[2]) > 1) ||
            ((AL[0] + AL[1] + BS[0]) > 1 && (AL[0] + AL[1] + BS[0]) < 2) ||
            ((AS[0] + AS[1] + c) > 1 && (AS[0] + AS[1] + c) < 2) ||
            ((AS[0] + BS[0] + BS[1]) > 1 && (AS[0] + BS[0] + BS[1]) < 2) ||
            ((AS[0] + BS[0] + c) > 1 && (AS[0] + BS[0] + c) < 2)
        )
        {
            return 1;
        }
        return 0;
  }
