from EdgeCross import EdgeCross
from EdgeCross import EdgeCrosses
from Location import Location

import math

class Sensor(object):
    """Sensor class"""
    
    def __init__(self):
        self.center = Location()
        self.radius = 0.0
    
    def __init__(self, center, radius):
        self.center = center
        self.radius = radius
        assert(radius > 0)

    def Crossed(self, rhs):
        distance = Location.GetDistance(self.center, rhs.center)
        return distance <= math.fabs(self.radius + rhs.radius)

    def CrossedWithHLine(self, Y, ec):
        if Y >= (self.center.y - self.radius) and Y <= (self.center.y + self.radius):
            deltaY = self.center.y - Y;
            deltaX = math.sqrt(self.radius*self.radius - deltaY*deltaY)
            ec.SetBounds(self.center.x - deltaX, self.center.x + deltaX)
            return True
        return False

    def CrossedWithVLine(self, X, ec):
        if X >= (self.center.x - self.radius) and X <= (self.center.x + self.radius):
            deltaX = self.center.x - X;
            deltaY = math.sqrt(self.radius*self.radius - deltaX*deltaX)
            ec.SetBounds(self.center.y - deltaY, self.center.y + deltaY)
            return True
        return False


    

