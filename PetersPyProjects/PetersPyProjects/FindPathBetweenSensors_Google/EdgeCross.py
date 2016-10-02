import sys

class EdgeCross(object):
    """EdgeCross class"""
    @staticmethod
    def LEFT():
        return 0
    @staticmethod
    def TOP() :
        return 1
    @staticmethod
    def RIGHT():
        return 2
    @staticmethod
    def BOTTOM():
        return 3
    @staticmethod
    def MAX():
        return 4
    
    def __init__(self, lb = sys.float_info.max, ub = sys.float_info.min):
        self.lowerBound = lb
        self.upperBound = ub

    def __hash__(self):
        return hash((self.lowerBound, self.upperBound))

    def __eq__(self, rhs):
        return self.lowerBound == rhs.lowBound and self.upperBound == rhs.upperBound

    def __lt__(self, rhs):
        return self.upperBound < rhs.lowerBound

    def SetBounds(self, lb, ub):
        self.lowerBound = lb
        self.upperBound = ub

    def SetLowerBound(self, lb):
        self.lowerBound = lb

    def SetUpperBound(self, ub):
        self.upperBound = ub

    def IsValid(self):
        return self.lowerBound != sys.float_info.max and self.upperBound != sys.float_info.min

    def MergeBounds(self, rhs):
        self.SetBounds(min(self.lowerBound, rhs.lowerBound), max(self.upperBound, rhs.upperBound))
 
class EdgeCrosses(object):
    
    def __init__(self):
        self.ecs = []
        for idx in range(0, EdgeCross.MAX()):
            self.ecs.append(EdgeCross())