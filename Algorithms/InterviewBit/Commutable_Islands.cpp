// Problem : https://www.interviewbit.com/problems/commutable-islands/
// Author  : The Philomath
// Date    : 06-03-2020

/**********************************************************************************
*
*    There are A islands and there are M bridges connecting them. Each bridge has some cost attached to it.
*
*    We need to find bridges with minimal cost such that all islands are connected.
*
*    It is guaranteed that input data will contain at least one possible scenario
*    in which all islands are connected with each other.
*
*    Input Format:
*
*    The first argument contains an integer, A, representing the number of islands.
*    The second argument contains an 2-d integer matrix, B, of size M x 3:
*        => Island B[i][0] and B[i][1] are connected using a bridge of cost B[i][2].
*    Output Format:
*
*    Return an integer representing the minimal cost required.
*
**********************************************************************************/

int getId(vector<int>& visit, int i)
{
    while(i != visit[i])
    {
        visit[i] = visit[visit[i]];
        i = visit[i];
    }
    return i;
}

void Union(vector<int>& visit, int A, int B)
{
    int idA = getId(visit, A);
    int idB = getId(visit, B);
    visit[idA] = idB;
}

bool find(vector<int>& visit, int A, int B)
{
    return (getId(visit, A) == getId(visit, B));
}

int Solution::solve(int A, vector<vector<int> > &B) {

    if(B.size() < 1) return 0;

    std::sort(B.begin(), B.end(), [](const auto &i1, const auto &i2){
        return i1[2] < i2[2];
    });

    vector<int> visit(A+1,0);
    for(int i = 0; i<= A; i++)
    {
        visit[i] = i;
    }

    Union(visit, B[0][0], B[0][1]);
    int sum = B[0][2];

    for(int i = 1; i<B.size(); i++)
    {
        if(!find(visit, B[i][0], B[i][1]))
        {
            Union(visit, B[i][0], B[i][1]);
            sum += B[i][2];
        }
    }

    return sum;
}
