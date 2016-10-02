#include "StdAfx.h"
#include "TextOutputFile.h"

using namespace std;

namespace Linguamatics {
namespace TextHighlight{
TextOutputFile::TextOutputFile(const string &fileName)
	: TextFile(fileName), m_OFileStream(fileName)
{
}


TextOutputFile::~TextOutputFile(void)
{
	if (m_OFileStream.is_open()){
		m_OFileStream.close();
	}
}

void TextOutputFile::WriteText(const string &text)
{
	if (m_OFileStream.good()){
		m_OFileStream << text;
	}
	else {
		throw std::runtime_error("TextOutputFile:: invalid file");
	}
}

}
}