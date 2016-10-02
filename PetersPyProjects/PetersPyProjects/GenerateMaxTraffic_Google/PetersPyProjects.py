from exceptions import AttributeError
import sys

# dict() to take neighbour id as key and MaxTraffic as value
class gNode (object):
    def __init__(self, id, traffic):
        self.id = id
        self.traffic = traffic
        self.neighbours = dict()
        self.maxTraffic = 0
        self.sumOfNeighboursTraffic = 0

    def AppendNeighbour(self, neighbour):
        if neighbour is None:
            return
        self.neighbours[neighbour] = 0

    def AppendNeighbours(self, neighbours = None):
        if neighbours is None:
            return
        for neighbour in neighbours:
            self.AppendNeighbour(neighbour)

    def __hash__(self):
        return hash(self.id)

    def __eq__(self, other):
        return self.id == other.id


class gNodeHelper (object):
    def __init__(self):
        pass

    @staticmethod
    def __CalculateNeighboursTraffic(root, parent):
        if root is None:
            return 0
        if len(root.neighbours) == 1 and parent is not None:
            return root.traffic

        traffic = 0
        for key in root.neighbours.keys():
            if parent is None or key.id != parent.id:
                root.neighbours[key] = gNodeHelper.__CalculateNeighboursTraffic(key, root)
                traffic += root.neighbours[key]
        return traffic + root.traffic

    @staticmethod
    def __CalculateParentTraffic(root, parent):
        if root is None:
            return
        if parent is not None:
            root.neighbours[parent] = parent.sumOfNeighboursTraffic + parent.traffic - parent.neighbours[root]
        
        for val in root.neighbours.values():
            root.sumOfNeighboursTraffic += val
        
        for key in root.neighbours.keys():
            if parent is None or key.id != parent.id:
                gNodeHelper.__CalculateParentTraffic(key, root)

    @staticmethod
    def __PopulateMaxTraffic(root, parent):
        if root is None:
            return
        for val in root.neighbours.values():
            if root.maxTraffic < val:
                root.maxTraffic = val
        
        for key in root.neighbours.keys():
            if parent is None or key != parent:
                gNodeHelper.__PopulateMaxTraffic(key, root)

    @staticmethod
    def GenerateMaxTraffic(root):
        try:
            gNodeHelper.__CalculateNeighboursTraffic(root, None)
            gNodeHelper.__CalculateParentTraffic(root, None)
            gNodeHelper.__PopulateMaxTraffic(root, None)
        except AttributeError() as e:
            print ("AttributeError: {0}".format(e))
        except:
            print ("Unexpected error: ", sys.exc_info()[0])

def TestCase1():
    node1 = gNode(1, 1)
    node2 = gNode(2, 2)
    node3 = gNode(3, 3)
    node4 = gNode(4, 4)
    node5 = gNode(5, 5)

    node1.AppendNeighbour(node5)
    node5.AppendNeighbours((node1, node2, node3, node4))
    node2.AppendNeighbour(node5)
    node3.AppendNeighbour(node5)
    node4.AppendNeighbour(node5)

    gNodeHelper.GenerateMaxTraffic(node1)

def TestCase1_1():
    node1 = gNode(1, 1)
    node2 = gNode(2, 2)
    node3 = gNode(3, 3)
    node4 = gNode(4, 4)
    node5 = gNode(5, 5)

    node1.AppendNeighbour(node5)
    node5.AppendNeighbours((node1, node2, node3, node4))
    node2.AppendNeighbour(node5)
    node3.AppendNeighbour(node5)
    node4.AppendNeighbour(node5)

    gNodeHelper.GenerateMaxTraffic(node5)


def TestCase2():
    node1 = gNode(1, 1)
    node2 = gNode(2, 2)
    node3 = gNode(3, 3)
    node4 = gNode(4, 4)
    node5 = gNode(5, 5)
    node7 = gNode(7, 7)
    node8 = gNode(8, 8)
    node15 = gNode(15, 15)
    node38 = gNode(38, 38)

    node1.AppendNeighbour(node5)
    node5.AppendNeighbours((node1, node2, node3, node4))
    node2.AppendNeighbours((node5, node7, node15))
    node3.AppendNeighbour(node5)
    node4.AppendNeighbour(node5)
    node7.AppendNeighbours((node2, node8))
    node8.AppendNeighbours((node7, node38))
    node15.AppendNeighbour(node2)
    node38.AppendNeighbour(node8)

    gNodeHelper.GenerateMaxTraffic(node1)

def TestCase2_1():
    node1 = gNode(1, 1)
    node2 = gNode(2, 2)
    node3 = gNode(3, 3)
    node4 = gNode(4, 4)
    node5 = gNode(5, 5)
    node7 = gNode(7, 7)
    node8 = gNode(8, 8)
    node15 = gNode(15, 15)
    node38 = gNode(38, 38)

    node1.AppendNeighbour(node5)
    node5.AppendNeighbours((node1, node2, node3, node4))
    node2.AppendNeighbours((node5, node7, node15))
    node3.AppendNeighbour(node5)
    node4.AppendNeighbour(node5)
    node7.AppendNeighbours((node2, node8))
    node8.AppendNeighbours((node7, node38))
    node15.AppendNeighbour(node2)
    node38.AppendNeighbour(node8)

    gNodeHelper.GenerateMaxTraffic(node5)

def Main():
    TestCase1()
    TestCase1_1()
    TestCase2()
    TestCase2_1()
    
if __name__ == '__main__':
    Main()
