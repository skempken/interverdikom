#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <string>
#include <vector>
#include <sstream>

using namespace std;

namespace ivk
{

class StringUtils
{

public:

    static int splitString(const string& input, 
        const string& delimiter, vector<string>& results, 
        bool includeEmpties = true);
    
    static string formatTime(int seconds);

};

}

#endif /*STRINGUTILS_H_*/
