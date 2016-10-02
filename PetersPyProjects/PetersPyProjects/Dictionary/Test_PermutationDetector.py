import unittest

from PermutationDetector import PermutationDetector

class Test_PermutationDetector(unittest.TestCase):
    def test_Failure(self):
        detector = PermutationDetector(("actor", "bad", "act", "good"))
        self.assertFalse(detector.IsPermutation("badactorgoodacting"))
        self.assertFalse(detector.IsPermutation_R("badactorgoodacting"))

    def test_Success(self):
        detector = PermutationDetector(("actor", "bad", "acting", "good"))
        self.assertTrue(detector.IsPermutation("badactorgoodacting"));
        self.assertTrue(detector.IsPermutation_R("badactorgoodacting"));

if __name__ == '__main__':
    unittest.main()
