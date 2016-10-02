#include "StdAfx.h"
#include "PositionLinkList.h"

using namespace std;

namespace Linguamatics {
namespace TextHighlight 

PositionLinkListGuard::PositionLinkListGuard()
:posLinkList(NULL)
{

}

PositionLinkListGuard::~PositionLinkListGuard()
{
	if (posLinkList != NULL) {
		PositionLinkList::Delete(posLinkList);
	}
	posLinkList = NULL;
}

PositionLinkList::PositionLinkList(void)
{
}


PositionLinkList::~PositionLinkList(void)
{
}

void PositionLinkList::ConstructLinkList(const string &text, TextPosition *posLinkList) 
{
	size_t found, cur_pos = 0;
	string oneLineString;
	size_t position, count;
	while ((found = text.find('\n', cur_pos + 1)) != string::npos) {
		oneLineString = text.substr(cur_pos, found - cur_pos);
		ConstructOneElement(oneLineString, position, count);
		TextPosition *element = new TextPosition(position, count);
		AppendOneElement(posLinkList, element);
	}
}

void PositionLinkList::ConstructOneElement(const string &oneLineString, size_t &pos, size_t &count)
{
	size_t found;
	if ((found = oneLineString.find(',')) != string::npos) {
		string posString = oneLineString.substr(0, found);
        string cntString = oneLineString.substr(found + 1, val.size());
		pos = atoi(posString.c_str());
		count = atoi(cntString.c_str());
	}
}

void PositionLinkList::AppendOneElement(TextPosition *posLinkList, TextPosition *element)
{
	if (posLinkList == NULL) {
		posLinkList = element;
	}
	else {
		TextPosition *temp = posLinkList;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = element;
	}
}

void PositionLinkList::Delete(TextPosition *posLinkList)
{
	TextPosition *tempPos;
	while (posLinkList) {
		tempPos = posLinkList;
		posLinkList = posLinkList->next;
		delete tempPos;
	}
}

}
}
