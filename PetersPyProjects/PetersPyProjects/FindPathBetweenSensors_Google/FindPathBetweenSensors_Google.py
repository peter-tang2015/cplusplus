from EdgeCross import EdgeCross
from EdgeCross import EdgeCrosses
from Location import Location
from Rectangle import Rectangle
from Sensor import Sensor
from SensorRange import SensorRange

import sortedcontainers
from exceptions import AttributeError
import sys

class FindPathBetweenSensors_Google(object):
    """FindPathBetweenSensors of class"""

    def __init__(self, *args, **kwargs):
        return super(FindPathBetweenSensors_Google, self).__init__(*args, **kwargs)

    @staticmethod
    def __FindCrossBetweenSensorAndRect(sensor, rect, edgeCrosses):
        for edge in range(0, EdgeCross.MAX()) :
            if edge & 1:
                sensor.CrossedWithHLine(rect.edges[edge], edgeCrosses.ecs[edge])
            else:
                sensor.CrossedWithVLine(rect.edges[edge], edgeCrosses.ecs[edge])

    @staticmethod
    def __GenerateSensorRangeMap(sensors, rect, breakIfNoPath, vPath, sensorRanges):
        for sensor in sensors:
            toMerge = []
            CUR_SIZE = len(sensorRanges)
            for idx in range(0, CUR_SIZE):
                for s in sensorRanges[idx].sensors:
                    if s.Crossed(sensor) :
                        toMerge.append(idx)
                        break
            
            workingSR = None
            if len(toMerge) == 0:
                # create a new sensor range
                sr = SensorRange()
                sr.sensors.append(sensor)
                FindPathBetweenSensors_Google.__FindCrossBetweenSensorAndRect(sensor, rect, sr.edgeCrosses)
                sensorRanges.append(sr)
                workingSR = sr
            else:
                # merge all existing sensor range
                # 1. merge the rest into the first senror range
                # 2. erase the sensor ranges except the very first
                for idx in range(len(toMerge) - 1, 0, -1):
                    sRangeToKeep = sensorRanges[toMerge[0]]
                    sRangeToMerge = sensorRanges[toMerge[idx]]
                    sRangeToKeep.Merge(sRangeToMerge)
                    del sensorRanges[toMerge[idx]]
                
                # merge with the sensor
                edgeCrosses = EdgeCrosses()
                FindPathBetweenSensors_Google.__FindCrossBetweenSensorAndRect(sensor, rect, edgeCrosses)
                sRangeToKeep= sensorRanges[toMerge[0]]
                sRangeToKeep.MergeEdgeCross(edgeCrosses)
                sRangeToKeep.sensors.append(sensor)
                workingSR = sRangeToKeep
            
            if workingSR is not None and breakIfNoPath:
                if (vPath and workingSR.edgeCrosses.ecs[EdgeCross.LEFT()].IsValid() and workingSR.edgeCrosses.ecs[EdgeCross.RIGHT()].IsValid()) or \
                   (not vPath and workingSR.edgeCrosses.ecs[EdgeCross.TOP()].IsValid() and workingSR.edgeCrosses.ecs[EdgeCross.BOTTOM()].IsValid()):
                    return False
        return True
       
    @staticmethod
    def __ProcessCornerCase(vPath, edgeCrosses, rect, edge):
        if edge.IsValid():
            if vPath:
                # left corner
                if edgeCrosses.ecs[EdgeCross.LEFT()].IsValid():
                    edge.SetLowerBound(rect.edges[EdgeCross.LEFT()])
                # right corner
                if edgeCrosses.ecs[EdgeCross.RIGHT()].IsValid():
                    edge.SetUpperBound(rect.edges[EdgeCross.RIGHT()])
            else:
                # top corner
                if edgeCrosses.ecs[EdgeCross.TOP()].IsValid():
                    edge.SetUpperBound(rect.edges[EdgeCross.TOP()])
                # bottom corner
                if edgeCrosses.ecs[EdgeCross.BOTTOM()].IsValid():
                    edge.SetLowerBound(rect.edges[EdgeCross.BOTTOM()])
            return True
        return False

    @staticmethod
    def __GetMidPointOfFirstGap(ecs, rect, vPath, val):
        lowerBound = rect.edges[EdgeCross.BOTTOM()]
        upperBound = rect.edges[EdgeCross.TOP()]
        if vPath:
            lowerBound = rect.edges[EdgeCross.LEFT()]
            upperBound = rect.edges[EdgeCross.RIGHT()]
        
        if len(ecs) == 0:
            val[0] = (lowerBound + upperBound)/2
            return True
        
        if ecs[0].lowerBound > lowerBound:
            val[0] = (ecs[0].lowerBound + lowerBound)/2
            return True

        if len(ecs) == 1:
            if ecs[0].upperBound < upperBOund:
                val[0] = (ecs[0].upperBound + upperBound)/2
                return True
            return False

        if ecs[0].upperBound < ecs[1].lowerBound:
            val[0] = (ecs[0].upperBound + ecs[1].lowerBound)/2
            return True
        
        return False

    @staticmethod
    def FindPath(sensors, rect, vPath, path):
        try:
            sensorRanges = list()
            if len(sensors) != 0:
                if not FindPathBetweenSensors_Google.__GenerateSensorRangeMap(sensors, rect, True, vPath, sensorRanges):
                    return False
            if len(sensorRanges) == 0:
                if vPath:
                    path.append(Location(rect.edges[EdgeCross.LEFT()], rect.edges[EdgeCross.TOP()]))
                    path.append(Location(rect.edges[EdgeCross.LEFT()], rect.edges[EdgeCross.BOTTOM()]))
                else:
                    path.append(Location(rect.edges[EdgeCross.LEFT()], rect.edges[EdgeCross.TOP()]))
                    path.append(Location(rect.edges[EdgeCross.RIGHT()], rect.edges[EdgeCross.TOP()]))
                return True

            ecsFrom = sortedcontainers.SortedSet([])
            ecsTo = sortedcontainers.SortedSet([])
            for sr in sensorRanges:
                if vPath and FindPathBetweenSensors_Google.__ProcessCornerCase(vPath, sr.edgeCrosses, rect, sr.edgeCrosses.ecs[EdgeCross.TOP()]):
                    ecsFrom.add(sr.edgeCrosses.ecs[EdgeCross.TOP()])
                if vPath and FindPathBetweenSensors_Google.__ProcessCornerCase(vPath, sr.edgeCrosses, rect, sr.edgeCrosses.ecs[EdgeCross.BOTTOM()]):
                    ecsTo.add(sr.edgeCrosses.ecs[EdgeCross.BOTTOM()])
                if (not vPath) and FindPathBetweenSensors_Google.__ProcessCornerCase(vPath, sr.edgeCrosses, rect, sr.edgeCrosses.ecs[EdgeCross.LEFT()]):
                    ecsFrom.add(sr.edgeCrosses.ecs[EdgeCross.LEFT()])
                if (not vPath) and FindPathBetweenSensors_Google.__ProcessCornerCase(vPath, sr.edgeCrosses, rect, sr.edgeCrosses.ecs[EdgeCross.RIGHT()]):
                    ecsTo.add(sr.edgeCrosses.ecs[EdgeCross.RIGHT()])
      
            valFrom = [0.0]
            valTo = [0.0]
            if FindPathBetweenSensors_Google.__GetMidPointOfFirstGap(ecsFrom, rect, vPath, valFrom) and \
               FindPathBetweenSensors_Google.__GetMidPointOfFirstGap(ecsTo, rect, vPath, valTo) :
                if vPath:
                    path.append(Location(valFrom[0], rect.edges[EdgeCross.TOP()]))
                    path.append(Location(valTo[0], rect.edges[EdgeCross.BOTTOM()]))
                else:
                    path.append(Location(rect.edges[EdgeCross.LEFT()], valFrom[0]))
                    path.append(Location(rect.edges[EdgeCross.RIGHT()], valTo[0]))
                return True
        except AttributeError() as e:
            print ("AttributeError: {0}".format(e))
        except:
            print ("Unexpected error: ", sys.exc_info()[0])
        return False
        

# TEST
def TestFindPathBetweenSensors():
    path = []
    rect = Rectangle(1.0, 9.0, 8.0, 1.0)
    sensors = [ Sensor(Location(2.0, 3.0), 1.0), \
                Sensor(Location(4.0, 3.0), 1.0), \
                Sensor(Location(6.0, 3.0), 1.0), \
                Sensor(Location(8.0, 3.0), 1.0) ]
    assert(FindPathBetweenSensors_Google.FindPath(sensors, rect, True, path) == False)
    assert(FindPathBetweenSensors_Google.FindPath(sensors, rect, False, path) == True)
    assert(path[0] == Location(1.0, 2.0))
    assert(path[1] == Location(9.0, 2.0))

    path = []
    sensors = [ Sensor(Location(2.0, 3.0), 1.0), \
                Sensor(Location(4.0, 3.0), 1.0), \
                Sensor(Location(6.0, 3.0), 1.0), \
                Sensor(Location(8.0, 3.0), 1.0), \
                Sensor(Location(8.0, 8.0), 1.0), \
                Sensor(Location(7.0, 7.0), 1.0) ]
    assert(FindPathBetweenSensors_Google.FindPath(sensors, rect, True, path) == False)
    assert(FindPathBetweenSensors_Google.FindPath(sensors, rect, False, path) == True)
    assert(path[0] == Location(1.0, 2.0))
    assert(path[1] == Location(9.0, 2.0))

    path = []
    sensors = [ Sensor(Location(2.0, 7.2), 1.0), \
                Sensor(Location(3.0, 6.0), 1.0), \
                Sensor(Location(4.0, 4.5), 1.0), \
                Sensor(Location(8.0, 7.2), 1.0), \
                Sensor(Location(7.0, 6.2), 1.0), \
                Sensor(Location(2.0, 3.0), 1.0), \
                Sensor(Location(3.0, 4.0), 1.0), \
                Sensor(Location(9.0, 1.0), 1.0) ]
    assert(FindPathBetweenSensors_Google.FindPath(sensors, rect, True, path) == True)
    assert(path[0] == Location(5.0, 8.0))
    assert(path[1] == Location(4.5, 1.0))
    path = []
    assert(FindPathBetweenSensors_Google.FindPath(sensors, rect, False, path) == True)
    assert(path[0] == Location(1.0, 2.0))
    assert(path[1] == Location(9.0, 4.6))

def Main():
    TestFindPathBetweenSensors()
    
if __name__ == '__main__':
    Main()
