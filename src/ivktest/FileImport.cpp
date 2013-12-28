#include "FileImport.h"
#include <vector>
#include <cstring>

using std::ifstream;

rvector FileImport::loadData(const char* filename)
{
	std::vector<double> inhalt;
	char tmp[20];
	char tmpstr[20]="";
	ifstream* dateiobjekt = new ifstream(filename);

	while(dateiobjekt->getline(tmp,20)){
		for(int i = 0;i<=20;i++){
			if( !isdigit(tmp[i]) ) {
				strncat(tmpstr,tmp,i);
				break;
			}
		}
		inhalt.push_back(atoi(tmpstr));

		strcpy(tmpstr,"");
	}

	dateiobjekt->close();
	delete dateiobjekt;

	rvector values(0, inhalt.size()-1);
	for(unsigned int i = 0; i<inhalt.size(); ++i)
		values[i] = inhalt[i];
	return values;
}

rvector FileImport::frame2gop(rvector data, const int gopsize)
{
	rvector ret(0, (Ub(data)-Lb(data)+1)/gopsize);
	for(int i = Lb(ret); i<=Ub(ret); ++i)
		ret[i] = 0.0;

	for(int i = Lb(data); i<=Ub(data); ++i)
	{
		ret[i/gopsize] += data[i];
	}

	return ret;
}

rvector FileImport::importGops(const char* filename, const int goplength)
{
	return frame2gop(loadData(filename), goplength);
}
