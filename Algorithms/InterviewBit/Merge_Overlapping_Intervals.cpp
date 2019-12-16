// Problem : https://www.interviewbit.com/problems/merge-overlapping-intervals/
// Author  : The Philomath
// Date    : 16-12-2019

/**********************************************************************************
*
*    Given a collection of intervals, merge all overlapping intervals.
*
*    For example:
*
*    Given [1,3],[2,6],[8,10],[15,18],
*
*    return [1,6],[8,10],[15,18].
*
*    Make sure the returned intervals are sorted.
*
**********************************************************************************/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

// TLE because of erase function
 vector<Interval> Solution::merge(vector<Interval> &A) {
     std::sort(A.begin(), A.end(), [](Interval f, Interval s){
         if(f.start == s.start) return f.end<s.end;
         else
         return f.start<s.start;
     });

     for(int i = 1; i < A.size(); )
     {
         if((A[i].start >= A[i-1].start) && A[i].start <= A[i-1].end)
         {
             A[i-1].end = (A[i].end > A[i-1].end)? A[i].end : A[i-1].end;
             A.erase(A.begin() + i);
         }
         else
             i++;
     }
     return A;
 }

// better solution
vector<Interval> Solution::merge(vector<Interval> &A) {

    std::sort(A.begin(), A.end(), [](Interval f, Interval s){
        if(f.start == s.start) return f.end<s.end;
        else
        return f.start<s.start;
    });

    int beg = 0;
    for(int i = 1; i < A.size(); ++i)
    {
        if((A[i].start >= A[beg].start) && A[i].start <= A[beg].end)
        {
            A[beg].end = (A[i].end > A[beg].end)? A[i].end : A[beg].end;
        }
        else
        {
            beg++;
            if(beg != i) A[beg] = A[i];
        }
    }

    if(beg != A.size())
    {
        A.erase(A.begin() + beg + 1, A.end());
    }
    return A;
}
