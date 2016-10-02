import math

class Location(object):
    """Location"""
    def __init__(self):
        self.x = -1.0
        self.y = -1.0

    def __init__(self, x, y):
        self.x = x
        self.y = y

    @staticmethod
    def GetDistance(l1, l2):
        deltaX = l1.x - l2.x
        deltaY = l1.y - l2.y
        return math.sqrt(deltaX*deltaX + deltaY*deltaY)

    def __str__(self):
        return str(self.__dict__)

    def __eq__(self, rhs):
        return self.__dict__ == rhs.__dict__

    def __cmp__(self, rhs):
        return self.__dict__ == rhs.__dict__

