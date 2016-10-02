#pragma once

#ifndef POSITION_LINK_LIST_H
#define POSITION_LINK_LIST_H

#include "TextHighlighterApi.h"

namespace Linguamatics {
namespace TextHighlight {

struct TextPosition {
	size_t position;
	size_t wordCounts;
	TextPosition *next;

	TextPosition(size_t pos, size_t count) {
		position = pos;
		wordCounts = count;
		next = NULL;
	}

	~TextPosition(){
	
	}
};

struct PositionLinkListGuard{
	PositionLinkListGuard();
	~PositionLinkListGuard();
	TextPosition *posLinkList;
};

class PositionLinkList
{	
public:
	static void ConstructLinkList(const std::string &text, TextPosition* posLinkList);
	static void ConstructOneElement(const std::string &oneLineString, size_t &pos, size_t &count);
	static void AppendOneElement(TextPosition* posLinkList, TextPosition* element);
	static void Delete(TextPosition* posLinkList);
private:
	PositionLinkList(void);
	~PositionLinkList(void);

};

}
}
#endif
