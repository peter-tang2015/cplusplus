#include "stdafx.h"
#include "ExoticStringComparator.h"


ExoticStringComparator::ExoticStringComparator(const std::vector<ExoticChar> &staticTable)
    : m_StaticMapRoot(NULL)
{
    if (staticTable.empty()) {
        throw EscException("ExoticStringComparator creation - empty table");
    }

    m_StaticMapRoot = new DictionaryTrie();
    DictionaryTrie *tempPtr;
    for (auto it = staticTable.begin(); it != staticTable.end(); ++it) {
        tempPtr = AddWord(m_StaticMapRoot, it->eChar.c_str());
        if (tempPtr) {
            m_KeyValMap.insert(std::make_pair(tempPtr, it->val));
        }
    }
}


ExoticStringComparator::~ExoticStringComparator()
{
    DestoryDictionaryTrie(m_StaticMapRoot);
    m_StaticMapRoot = NULL;
}

int ExoticStringComparator::CompareExoticString(const std::string &lhs, const std::string &rhs) const
{
    auto lhsTempIt = lhs.begin();
    auto rhsTempIt = rhs.begin();

    int result = 0;
    DictionaryTrie *lhsTemp, *lhsCur;
    DictionaryTrie *rhsTemp, *rhsCur;
    //while (lhsCurIt != lhs.end() && rhsCurIt != rhs.end()) {
    while (lhsTempIt != lhs.end() && rhsTempIt != rhs.end()) {
        lhsTemp = m_StaticMapRoot;
        while (lhsTemp = FindPath(lhsTemp, *lhsTempIt)) {
            if (lhsTemp->str) {
                lhsCur = lhsTemp;
            }

            ++lhsTempIt;
            if (lhsTempIt == lhs.end()) {
                break;
            }
        }

        rhsTemp = m_StaticMapRoot;
        while (rhsTemp = FindPath(rhsTemp, *rhsTempIt)) {
            if (rhsTemp->str) {
                rhsCur = rhsTemp;
            }

            ++rhsTempIt;
            if (rhsTempIt == rhs.end()) {
                break;
            }
        }

        auto lhsValIt = m_KeyValMap.find(lhsCur);
        auto rhsValIt = m_KeyValMap.find(rhsCur);
        if (lhsValIt == m_KeyValMap.end() || rhsValIt == m_KeyValMap.end()) {
            throw EscException("CompareExoticString: invalid map");
        }
        result = lhsValIt->second - rhsValIt->second;
        if (result != 0) {
            return result;
        }
    }

    if (lhsTempIt != lhs.end()) {
        return 1;
    }
    else if (rhsTempIt != rhs.end()) {
        return -1;
    }
    return result;
}
