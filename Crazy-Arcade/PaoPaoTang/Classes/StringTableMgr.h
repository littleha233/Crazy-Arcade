#ifndef _STRING_TABLE_MGR_H_
#define _STRING_TABLE_MGR_H_
#include "tinyxml.h"
#include <map>
#include <assert.h>
#include <string>
using namespace std;
class CStringTableMgr
{
private:
	CStringTableMgr(){}
	static void init(map<string,string>& rStringTable)
	{
		TiXmlDocument doc;
		bool bLoaded = doc.LoadFile("Config/StringTable.xml");
		assert(bLoaded == true);
		TiXmlElement* element = doc.RootElement()->FirstChildElement();
		while(element!=NULL)
		{
			const char* pKey = element->Attribute("key");
			const char* pText = element->Attribute("text");
			rStringTable.insert(make_pair(pKey,pText));
			element = element->NextSiblingElement();
		}
	}
public:
	static const char* getString(const char* key)
	{
		static map<string,string> stringTable;
		if(stringTable.size()==0)
			init(stringTable);
		map<string,string>::iterator it = stringTable.find(key);
		if(it != stringTable.end())
			return it->second.c_str();
		else
			return "";
	}
};
#endif