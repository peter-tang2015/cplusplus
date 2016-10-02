#ifndef TEXT_HIGHLIGHTER_H
#define TEXT_HIGHLIGHTER_H

#include <string>

namespace Linguamatics {
namespace TextHighlight {


class TextHighlighter {
public:
	// highlight the file based on two input files
	virtual std::string writeContext(const std::string &textSrcFileName, 
									 const std::string &positionSrcFileName) = 0;							
};

} // end of TextHighlight
} // end of Linguamatics

#endif