#pragma once

#include "DictionaryTrie.h"

#include <exception>
#include <string>
#include <unordered_map>
#include <vector>

struct ExoticChar
{
    ExoticChar(const std::string &ec, const int v)
        : eChar(ec), val(v)
    {}

    ExoticChar& operator=(const ExoticChar &rhs) {
        this->eChar = rhs.eChar;
        this->val = rhs.val;
        return *this;
    }

    std::string eChar;
    int val;
};

class EscException : public std::exception
{
public:
    EscException(const std::string &msg) 
        : m_Msg(msg)
    {}

    const char* what() const {
        return m_Msg.c_str();
    }

private:
    const std::string m_Msg;
};

class ExoticStringComparator
{
public:
    ExoticStringComparator(const std::vector<ExoticChar> &staticTable);
    ~ExoticStringComparator();

    int CompareExoticString(const std::string &lhs, const std::string &rhs) const;
private:
    DictionaryTrie* m_StaticMapRoot;
    std::unordered_map<DictionaryTrie*, int> m_KeyValMap;
};

