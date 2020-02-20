KMP(Knuth, Morris, Pratt) is an important algorithm used for pattern searching.
Suppose there is an String s and we need to find all the occurrences of `s` in a String `t`.

KMP algorithm also used in DNA matching, information security, document matching etc.

In a naïve approach we will loop over both the strings and for each element of `s` compare with `t`.
But it will take the O(lengths*lengtht) time.

lets take some examples and try to minimize the complexity:-
1. if no character of `s` matches the first few characters of `t`.
   s = Mad
   t = Philomath

    If we look at above example `s` do not matches the first 3 characters of `t`.
    So in second iteration instead of checking from index 1 of `t` we can start to check from index 3.
    Because we know that all elements are distinct and they are not going to match anyway.

2. if few characters of `s` matches the few characters of `t`
    s = abcdabc
    t = abcdabefgh....

   In this example we got a mismatch at index 6.

   Also we can see that first 3 characters of s(prefix) matches the last 3 characters of s(suffixes).
   So our next comparison should start form the beginning of the suffix i.e. index 4
   And in that comparison we can skip the characters which we have already compared i.e

   s =      abcdabc
   t = abcd abefghif...

   so we can start comparing the 'c' and 'e' as have already compared the first two characters as part of suffix.
   That exactly what KMP will do.

   How will we know how many elements we have to skip in comparison.
   For that we need to preprocess the `s` string and create an auxiliary array which will tell us the number of
   elements which we should skip.

```cpp
vector<int> createAuxArray(string &s)
{
  vector<int> aux(s.size(), 0);

  int i = 1;
  int m = 0;
  while(i < s.size())
  {
    if(s[i] == s[m])
    {
      m += 1;
      aux[i] = m;
      i++;
    }
    else if(m != 0) //s[i] != s[m] mismatch and m != 0 means there was a prefix which was equal to the suffix
    {
      m = aux[m-1]; // it means there can be few characters which will still match with next i. A possible prefix.
                    // in below example we got a mismatch at index 7 'C' so at that point we reset m to 2
    }
    else
    {
      aux[i] = 0; // can avoid as whole array initially set to 0
      i++;
    }
  }
  return aux;
}
```
s:-         A C A B A C A C D
Aux array:- 0 0 1 0 1 2 3 2 0

Now we can find the start indices of all the patterns using this auxiliary array.
```cpp
vector<int> searchPatterns(string s, string t)
{
  auto aux = createAuxArray(s);
  int i = 0;
  int j = 0;
  vector<int> ret;
  while(i < t.size())
  {
    if(s[i] != t[j])
    {
      if(j == 0)
        i++;
      else
        j = aux[j-1];
    }
    else
    {
      i++;
      j++;

      if(j == s.size()) // whole string found in t, reset j
      {
        ret.emplace_back(i - j);
        j = aux[j-1];
      }
    }
  }
  return ret;
}

```

#### References
[Medium.com](https://medium.com/@giri_sh/string-matching-kmp-algorithm-27c182efa387)

### Authors

* **The Philomath**
