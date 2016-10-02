#include "StdAfx.h"
#include "TextHighlighterImp.h"

#include <vector>
#include "TextInputFile.h"
#include "PositionLinkList.h"

using namespace std;

namespace Linguamatics {
namespace TextHighlight {
TextHighlighterImp::TextHighlighterImp(void)
{

}

TextHighlighterImp::~TextHighlighterImp(void)
{
}

string TextHighlighterImp::writeContext(const std::string &textSrcFileName, const std::string &positionSrcFileName)
{
	// populate the content
	string content;
	PopulateText(textSrcFileName, content);

	// construct the position link list
	PositionLinkListGuard posLLGuard;
	PopulatePositionLinkList(positionSrcFileName, posLLGuard.posLinkList);
	
	return writeContext(content, posLLGuard.posLinkList);
}
	
string TextHighlighterImp::writeContext(const std::string &text, TextPosition *posLinkList)
{
	TextPosition *curPos = posLinkList;
	size_t wordPosition = 0, index = 0;
	size_t insertStartPos, insertEndPos;
	vector<size_t> posToInsertTag;
	while (curPos) {
		wordPosition = GetInsertPosition(text, index, wordPosition, curPos->position,
			curPos->wordCounts, insertStartPos, insertEndPos);
		posToInsertTag.push_back(insertStartPos);
		posToInsertTag.push_back(insertEndPos);
		//
		// next position
		curPos = curPos->next;
	}

	return InsertTags(const string& text, posToIntertTag);
}

size_t TextHighlighterImp::InsertTags(const string& text, posToIntertTag)
{
	string text
}

size_t TextHighlighterImp::GetInsertPosition(const string& text, size_t& index, size_t curWordCount,
											 size_t desiredWordCount, size_t desiredWordSize, 
											 size_t &insertStartPos, size_t &insertEndPos){
{
	bool isSpaceDetected = true;
	bool isNotSpaceDetected = false;
	bool isEndOfSentenceDetected = false;
	size_t cur_word_pos;
	while (index < text.size()) {
		if(isspace(text.at(index))){
			// space detected
			if (!isSpaceDetected) {
				isSpaceDetected = true;
			}
			isNotSpaceDetected = isEndOfSentenceDetected = false;
		}
		else {
			if (isSpaceDetected) {
				// word detected
				isNotSpaceDetected = true;
				cur_word_pos = index;	
			}
			if (text.at(index) == '.') {
				isEndOfSentenceDetected = true;
			}
		}


		// increment index
		++ index;

		if (isSpaceDetected && isNotSpaceDetected){
			++curWordCount;
			isSpaceDetected = isNotSpaceDetected = false;
		}

		if (curWordCount == desiredWordCount){
			insertStartPos = cur_word_pos;
			if (isEndOfSentenceDetected){
				--insertStartPos;
			}
		}
		if (curWordCount == (desiredWordCount + desiredWordSize)) {
			insertEndPos = cur_word_pos;
			if (isEndOfSentenceDetected){
				--insertStartPos;
			}

			break;
		}

		isEndOfSentenceDetected = false;
	}

	return curWordCount;
}

void TextHighlighterImp::PopulatePositionLinkList(const std::string &posSrcFileName, TextPosition *posLinkList)
{
	TextInputFile posFile(posSrcFileName);

	// read out file
	string posText;
	posFile.GetTextString(posText);

	// parse into link list
	PositionLinkList::ConstructLinkList(posText, posLinkList);
}

void TextHighlighterImp::PopulateText(const std::string &textSrcFileName, std::string &content)
{
	TextInputFile contentFile(textSrcFileName);
	contentFile.GetTextString(content);
}

}
}