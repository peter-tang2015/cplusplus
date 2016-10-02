from EdgeCross import EdgeCross
from EdgeCross import EdgeCrosses
from Sensor import Sensor

class SensorRange(object):
    """SensorRange class"""

    def __init__(self, *args, **kwargs):
        self.edgeCrosses = EdgeCrosses()
        self.sensors = list()

    def MergeEdgeCross(self, ecs):
        for idx in range(0, EdgeCross.MAX()):
            self.edgeCrosses.ecs[idx].MergeBounds(ecs.ecs[idx])

    def Merge(self, sr):
        self.MergeEdgeCross(sr.edgeCrosses)
        self.sensors.extend(sr.sensors)

                        


