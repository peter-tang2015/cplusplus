#pragma once

#ifndef TEXT_HIGHLIGHTER_IMP_H
#define TEXT_HIGHLIGHTER_IMP_H

#include "TextHighlighterApi.h"

namespace Linguamatics {
namespace TextHighlight {
class TextHighlighterImp :
	public TextHighlighter
{
public:
	TextHighlighterImp(void);
	~TextHighlighterImp(void);

	// highlight the file based on two input files
	std::string writeContext(const std::string &textSrcFileName, const std::string &positionSrcFileName);

private:
	void writeContext(const std::string &text, TextPosition *posLinkList);
	void PopulatePositionLinkList(const std::string &posSrcFileName, TextPosition *posLinkList);
	void PopulateText(const std::string &textSrcFileName, std::string &content);
	size_t GetInsertPosition(const string& text, size_t& index, size_t curWordCount,
							 size_t desiredWordCount, size_t desiredWordSize, 
							 size_t &insertStartPos, size_t &insertEndPos);

};

}
}
#endif
