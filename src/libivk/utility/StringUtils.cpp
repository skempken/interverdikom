#include "StringUtils.h"

namespace ivk
{

int StringUtils::splitString(const string& input, 
       const string& delimiter, vector<string>& results, 
       bool includeEmpties)
{
    int iPos = 0;
    int newPos = -1;
    int sizeS2 = (int)delimiter.size();
    int isize = (int)input.size();

    if( 
        ( isize == 0 )
        ||
        ( sizeS2 == 0 )
    )
    {
        return 0;
    }

    vector<int> positions;

    newPos = input.find (delimiter, 0);

    if( newPos < 0 )
    { 
        return 0; 
    }

    int numFound = 0;

    while( newPos >= iPos )
    {
        numFound++;
        positions.push_back(newPos);
        iPos = newPos;
        newPos = input.find (delimiter, iPos+sizeS2);
    }

    if( numFound == 0 )
    {
        return 0;
    }

    for( int i=0; i <= (int)positions.size(); ++i )
    {
        string s("");
        if( i == 0 ) 
        { 
            s = input.substr( i, positions[i] ); 
        }
        int offset = positions[i-1] + sizeS2;
        if( offset < isize )
        {
            if( i == positions.size() )
            {
                s = input.substr(offset);
            }
            else if( i > 0 )
            {
                s = input.substr( positions[i-1] + sizeS2, 
                      positions[i] - positions[i-1] - sizeS2 );
            }
        }
        if( includeEmpties || ( s.size() > 0 ) )
        {
            results.push_back(s);
        }
    }
    return numFound;
}

string StringUtils::formatTime(int seconds)
{
	const int hours = seconds / 3600;
	const int minutes = (seconds - (hours * 3600))/60; 
	seconds -= (hours*3600 + minutes*60);
	ostringstream o;
	o << hours << " h " << minutes << " min " << seconds << " s";
	return o.str();
}

}
