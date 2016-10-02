import unittest
from PetersPyProjects import gNode
from PetersPyProjects import gNodeHelper


class Test_Test_GenerateMaxTraffic(unittest.TestCase):
    def test_A(self):
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

        self.assertEqual(node1.maxTraffic, 14)
        self.assertEqual(node2.maxTraffic, 13)
        self.assertEqual(node3.maxTraffic, 12)
        self.assertEqual(node4.maxTraffic, 11)
        self.assertEqual(node5.maxTraffic, 4)

    def test_B(self):
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

        self.assertEqual(node1.maxTraffic, 14)
        self.assertEqual(node2.maxTraffic, 13)
        self.assertEqual(node3.maxTraffic, 12)
        self.assertEqual(node4.maxTraffic, 11)
        self.assertEqual(node5.maxTraffic, 4)

    def test_C(self):
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

        self.assertEqual(node1.maxTraffic, 82)
        self.assertEqual(node2.maxTraffic, 53)
        self.assertEqual(node3.maxTraffic, 80)
        self.assertEqual(node4.maxTraffic, 79)
        self.assertEqual(node5.maxTraffic, 70)
        self.assertEqual(node7.maxTraffic, 46)
        self.assertEqual(node8.maxTraffic, 38)
        self.assertEqual(node15.maxTraffic, 68)
        self.assertEqual(node38.maxTraffic, 45)

    def test_D(self):
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

        self.assertEqual(node1.maxTraffic, 82)
        self.assertEqual(node2.maxTraffic, 53)
        self.assertEqual(node3.maxTraffic, 80)
        self.assertEqual(node4.maxTraffic, 79)
        self.assertEqual(node5.maxTraffic, 70)
        self.assertEqual(node7.maxTraffic, 46)
        self.assertEqual(node8.maxTraffic, 38)
        self.assertEqual(node15.maxTraffic, 68)
        self.assertEqual(node38.maxTraffic, 45)

if __name__ == '__main__':
    unittest.main()
