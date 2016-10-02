#pragma once

#ifndef TEXT_FILE_H
#define TEXT_FILE_H

#include <string>

namespace Linguamatics {
namespace TextHighlight {
class TextFile
{
public:
	TextFile(const std::string &fileName);
	virtual ~TextFile(void);

private:
	std::string m_FileName;
};

}
}

#endif
