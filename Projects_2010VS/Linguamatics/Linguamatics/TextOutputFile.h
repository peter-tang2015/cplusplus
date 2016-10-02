#pragma once

#ifndef TEXT_OUTPUT_FILE_H
#define TEXT_OUTPUT_FILE_H

#include "TextFile.h"
#include <string>

namespace Linguamatics {
namespace TextHighlight {
class TextOutputFile :	public TextFile
{
public:
	TextOutputFile(const std::string &fileName);
	~TextOutputFile(void);

	void WriteText(const std::string &text);

private:
	std::ofstream m_OFileStream;

};

}
}

#endif

