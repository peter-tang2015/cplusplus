import sys

class DictionaryTrie(object):
    """DictionaryTrie class"""

    def __init__(self):
        self.value = None
        self.children = dict()
        for idx in range(0, 26):
            self.children[ord('a') + idx] = None

    def GetChildren(self):
        return self.children
    
    def GetValue(self):
        return self.value          
    
    def AddWords(self, words = None):
        if words is None:
            return
        try:
            for word in words:
                self.AddWord(word)
        except AttributeError as e:
            print ("AttributeError: {0}".format(e))
        except:
            print ("Unexpected Error: ", sys.exc_info()[0])

    def AddWord(self, word = None):
        if word is None:
            return
        try:
            leafNode = self;
            for char in map(ord, word):
                if leafNode.children[char] is None:
                    leafNode.children[char] = DictionaryTrie()
                leafNode = leafNode.children[char]
            if leafNode.value is None:
                leafNode.value = word;
        except AttributeError as e:
            print ("AttributeError: {0}".format(e))
        except:
            print ("Unexpected error: ", sys.exc_info()[0])

    def FindWord(self, word):
        foundNode = self.FindWordAndGetNode(word)
        return foundNode is not None

    def FindWordAndGetNode(self, word):
        try:
            tempNode = self;
            for char in map(ord, word):
                if tempNode.children[char] is None:
                    return None
                tempNode = tempNode.children[char]
            if tempNode.value == word:
                return tempNode
            return None
        except AttributeError as e:
            print ("AttributeError: {0}".format(e))
        except:
            print ("Unexpected error: ", sys.exc_info()[0])

    def RemoveWord(self, word):
        try:
            wordNode = self.FindWordAndGetNode(word)
            if wordNode is not None:
                wordNode.value = None
        except AttributeError as e:
            print ("AttributeError: {0}".format(e))
        except:
            print ("Unexpected error: ", sys.exc_info()[0])

    def __Traverse(self, root, result):
        try:
            for char in range(0, 26):
                tmpNode = root.children[ord('a') + char]
                if  tmpNode is not None:
                    if tmpNode.value is not None:
                        result.append(tmpNode.value)
                    self.__Traverse(tmpNode, result)
        except AttributeError as e:
            print ("AttributeError: {0}".format(e))
        except:
            print ("Unexpected error: ", sys.exc_info()[0])        
        
    def Traverse(self):
        result = []
        self.__Traverse(self, result)
        if len(result) == 0:
            return None
        return result

    def __FindPrefix(self, prefix):
        try:
            tempNode = self;
            for char in map(ord, prefix):
                if tempNode.children[char] is None:
                    return None
                tempNode = tempNode.children[char]
            return tempNode
        except AttributeError as e:
            print ("AttributeError: {0}".format(e))
        except:
            print ("Unexpected error: ", sys.exc_info()[0])    

    def QueryPrefix(self, prefix):
        tempNode = self.__FindPrefix(prefix)
        
        if tempNode is not None:
            result = []
            self.__Traverse(tempNode, result)
            if len(result) > 0:
                return result
        return None
