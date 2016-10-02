from EdgeCross import EdgeCross
import array

class Rectangle(object):
    """Rectangle class"""
    def __init__(self, l, r, t, b):
        self.edges = array.array('d', [0, 0, 0, 0])
        self.edges[EdgeCross.LEFT()] = l
        self.edges[EdgeCross.RIGHT()] = r
        self.edges[EdgeCross.TOP()] = t
        self.edges[EdgeCross.BOTTOM()] = b


