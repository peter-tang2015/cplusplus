import unittest

from DictionaryTrie import DictionaryTrie

class Test_DictionaryTrie(unittest.TestCase):
    def __init__(self, methodName = 'runTest'):
        super(Test_DictionaryTrie, self).__init__(methodName)
        self.m_Dict = DictionaryTrie()
        self.m_Dict.AddWord("apple")
        self.m_Dict.AddWord("orange")
        self.m_Dict.AddWord("pear")
        self.m_Dict.AddWords(("banana", "melon", "grape", "blueberry", "blue"))

    def test_Find(self):
        testDict = self.m_Dict
        self.assertTrue(testDict.FindWord("apple"))
        self.assertFalse(testDict.FindWord("sdfa"))
        
        pear = testDict.FindWordAndGetNode("pear")
        self.assertIsNotNone(pear)
        self.assertEqual(pear.GetValue(), "pear")
        for idx in range(0, 26):
            self.assertIsNone(pear.GetChildren()[ord('a')+idx])

        blue = testDict.FindWordAndGetNode("blue")
        self.assertIsNotNone(blue)
        self.assertEqual(blue.GetValue(), "blue")
        for idx in range(0, 26):
            if (ord('a') + idx) == ord('b'):
                self.assertIsNotNone(blue.GetChildren()[ord('a') + idx])
            else:
                self.assertIsNone(pear.GetChildren()[ord('a') + idx])

    def test_Remove(self):
        testDict = self.m_Dict
        testDict.RemoveWord("apple")
        self.assertFalse(testDict.FindWord("apple"))
        testDict.AddWord("apple")
        self.assertTrue(testDict.FindWord("apple"))

    def test_Traverse(self):
        testDict = self.m_Dict
        result = testDict.Traverse()
        self.assertEqual(result[0], "apple")
        self.assertEqual(result[1], "banana")
        self.assertEqual(result[2], "blue")
        self.assertEqual(result[3], "blueberry")
        self.assertEqual(result[4], "grape")
        self.assertEqual(result[5], "melon")
        self.assertEqual(result[6], "orange")
        self.assertEqual(result[7], "pear")
        self.assertEqual(len(result), 8)

    def test_QueryPrefix(self):
        testDict = self.m_Dict
        result = testDict.QueryPrefix("app")
        self.assertEqual(result[0], "apple")
        self.assertEqual(len(result), 1)
        result = testDict.QueryPrefix("adj")
        self.assertIsNone(result)
        result = testDict.QueryPrefix("blu")
        self.assertEqual(result[0], "blue")
        self.assertEqual(result[1], "blueberry")
                        
if __name__ == '__main__':
    unittest.main()
