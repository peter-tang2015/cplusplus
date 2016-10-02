#include "StdAfx.h"
#include "TextInputFile.h"

using namespace std;

namespace Linguamatics {
namespace TextHighlight{
TextInputFile::TextInputFile(const string &fileName)
	:TextFile(fileName), m_IFileStream(fileName)
{
}


TextInputFile::~TextInputFile(void)
{
	if (m_IFileStream.is_open()) {
		m_IFileStream.close();
	}
}

void TextInputFile::GetTextString(string &text)
{
	if (m_IFileStream.good()) {
		text.clear();
		text = string ((istreambuf_iterator<char>(m_IFileStream)), istreambuf_iterator<char>());
	}
	else {
		throw std::runtime_error("TextInputFile:: Invalid file");
	}
}

}
}
