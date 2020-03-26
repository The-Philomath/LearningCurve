// Problem : String Tokenization
// Author  : The Philomath
// Date    : 26-03-2019

/**********************************************************************************
*
*    get all tokens from a string separated by a delimiters
*
**********************************************************************************/
// There are many ways we can tokenize the strings in C++. But I would prefer the STL style of tokenization.

// 1. using find and substr. it will print null strings also if token is in the beginning
void getTokens(std::vector<std::string>& vs, const std::string& s, const std::string& delim)
{
    int begin = 0;
    int end = s.find(delim);
    while(end != std::string::npos)
    {
        std::string token = s.substr(begin, end - begin);
        vs.emplace_back(token);
        begin = end + delim.length();
        end = s.find(delim, begin);
    }
    vs.emplace_back(s.substr(begin, end - begin));
}

// 2. STL style of Tokenization
void getTokens(std::vector<std::string>& vs, const std::string& str, const std::string& delimiters)
{
    // skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

    // find first "non-delimiter".
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // found a token, add it to the vector.
        vs.emplace_back(str.substr(lastPos, pos - lastPos));

        // skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);

        // find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}
