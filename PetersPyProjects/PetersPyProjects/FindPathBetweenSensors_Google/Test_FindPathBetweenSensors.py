from FindPathBetweenSensors_Google import FindPathBetweenSensors_Google
from Location import Location
from Rectangle import Rectangle
from Sensor import Sensor
import unittest


class Test_Test_FindPathBetweenSensors(unittest.TestCase):
    def test_A(self):
        path = []
        rect = Rectangle(1.0, 9.0, 8.0, 1.0)
        sensors = [ Sensor(Location(2.0, 3.0), 1.0), \
                    Sensor(Location(4.0, 3.0), 1.0), \
                    Sensor(Location(6.0, 3.0), 1.0), \
                    Sensor(Location(8.0, 3.0), 1.0) ]
        self.assertFalse(FindPathBetweenSensors_Google.FindPath(sensors, rect, True, path))
        self.assertTrue(FindPathBetweenSensors_Google.FindPath(sensors, rect, False, path))
        self.assertEqual(path[0], Location(1.0, 2.0))
        self.assertEqual(path[1], Location(9.0, 2.0))

    def test_B(self):
        path = []
        rect = Rectangle(1.0, 9.0, 8.0, 1.0)
        sensors = [ Sensor(Location(2.0, 3.0), 1.0), \
                    Sensor(Location(4.0, 3.0), 1.0), \
                    Sensor(Location(6.0, 3.0), 1.0), \
                    Sensor(Location(8.0, 3.0), 1.0), \
                    Sensor(Location(8.0, 8.0), 1.0), \
                    Sensor(Location(7.0, 7.0), 1.0) ]
        self.assertFalse(FindPathBetweenSensors_Google.FindPath(sensors, rect, True, path))
        self.assertTrue(FindPathBetweenSensors_Google.FindPath(sensors, rect, False, path))
        self.assertEqual(path[0], Location(1.0, 2.0))
        self.assertEqual(path[1], Location(9.0, 2.0))

    def test_C(self):
        path = []
        rect = Rectangle(1.0, 9.0, 8.0, 1.0)
        sensors = [ Sensor(Location(2.0, 7.2), 1.0), \
                    Sensor(Location(3.0, 6.0), 1.0), \
                    Sensor(Location(4.0, 4.5), 1.0), \
                    Sensor(Location(8.0, 7.2), 1.0), \
                    Sensor(Location(7.0, 6.2), 1.0), \
                    Sensor(Location(2.0, 3.0), 1.0), \
                    Sensor(Location(3.0, 4.0), 1.0), \
                    Sensor(Location(9.0, 1.0), 1.0) ]
        self.assertTrue(FindPathBetweenSensors_Google.FindPath(sensors, rect, True, path))
        self.assertEqual(path[0], Location(5.0, 8.0))
        self.assertEqual(path[1], Location(4.5, 1.0))
        path = []
        self.assertTrue(FindPathBetweenSensors_Google.FindPath(sensors, rect, False, path))
        self.assertEqual(path[0], Location(1.0, 2.0))
        self.assertEqual(path[1], Location(9.0, 4.6))

if __name__ == '__main__':
    unittest.main()
