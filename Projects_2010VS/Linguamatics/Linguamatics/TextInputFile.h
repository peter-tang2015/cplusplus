#pragma once

#ifndef TEXT_INPUT_FILE_H
#define TEXT_INPUT_FILE_H

#include "TextFile.h"

namespace Linguamatics {
namespace TextHighlight {
class TextInputFile :
	public TextFile
{
public:
	TextInputFile(const std::string &fileName);
	~TextInputFile(void);

	void GetTextString(std::string &text);

private:
	std::ifstream m_IFileStream;
};

}
}

#endif