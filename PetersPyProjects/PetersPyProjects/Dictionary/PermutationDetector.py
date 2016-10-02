from DictionaryTrie import DictionaryTrie

import sys

class PermutationDetector(object):
    """Word Permutation detector"""

    def __init__(self):
        self.m_DictRoot = None

    def __init__(self, words = None):
        self.m_DictRoot = None
        self.ConstructDict(words)

    def ConstructDict(self, words = None, appendMode = False):
        try:
            if words is None:
                return
            
            if self.m_DictRoot is None or appendMode:
                self.m_DictRoot = DictionaryTrie()
        
            for word in words:
                self.m_DictRoot.AddWord(word)
        except AttributeError as e:
            print ("AttributeError: {0}".format(e))
        except:
            print ("Unexpected Error: ", sys.exc_info()[0])

    def IsPermutation(self, word = None):
        try:
            if word is None or self.m_DictRoot is None:
                return False
            if len(word) == 0:
                return False

            nextToSearch = [0]
            StrSize = len(word)
            while (len(nextToSearch) > 0):
                startSearchIndex = nextToSearch.pop(0)
                tempDict = self.m_DictRoot
                idx = 0
                for idx in range(startSearchIndex, StrSize):
                    startSearchIndex +=1
                    tempDict = tempDict.GetChildren()[ord(word[idx])]
                    if tempDict is None:
                        break
                    else :
                        if tempDict.GetValue() is not None:
                            nextToSearch.append(startSearchIndex)

                if idx == (StrSize - 1) \
                   and tempDict is not None \
                   and tempDict.GetValue() is not None:
                    return True
        except AttributeError as e:
            print ("AtrrinuteError: {0}". format(e))
        except:
            print ("Unexpected Erro: ", sys.exc_info()[0])
        return False

    def __IsPermutation_R(self, word = None, nextToSearch = None):
        try:
            if word is None:
                return False
            if nextToSearch is None or len(nextToSearch) == 0: 
                return False
            
            tempDict = self.m_DictRoot
            startSearchIndex = nextToSearch.pop(0)
            idx = 0
            searchedLen = 0
            for idx in range(startSearchIndex, len(word)) :
                searchedLen += 1
                tempDict = tempDict.GetChildren()[ord(word[idx])]
                if tempDict is None:
                    break;
                else:
                    if tempDict.GetValue() is not None:
                        nextToSearch.append(startSearchIndex + searchedLen)
                
            if idx == len(word) -1 \
               and tempDict is not None \
               and tempDict.GetValue() is not None:
                return True
            
            return self.__IsPermutation_R(word, nextToSearch)
        except AttributeError as e:
            print ("AttributeError: {0}".format(e))
        except:
            print ("Unexpected Error: ", sys.exc_info()[0])
        return False

    def IsPermutation_R(self, word = None):
        if word is None:
            return False

        nextToSearch = [0]
        return self.__IsPermutation_R(word, nextToSearch)
                            
        


