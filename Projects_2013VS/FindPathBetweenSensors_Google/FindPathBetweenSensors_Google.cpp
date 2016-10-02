// FindPathBetweenSensors_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <array>
#include <limits>
#include <set>
#include <vector>

#include <cassert>
#include <cmath>

struct Location
{
    Location()
        : x(-1.0)
        , y(-1.0)
    {}
    Location(double x_, double y_)
        : x(x_)
        , y(y_)
    {}
    double x;
    double y;

    static double GetDistance(const Location &l1, const Location &l2) {
        const double deltaX = l1.x - l2.x;
        const double deltaY = l1.y - l2.y;
        return sqrt(deltaX*deltaX + deltaY*deltaY);
    }

    bool operator==(const Location &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};

struct EdgeCross
{
    EdgeCross()
    {}

    EdgeCross(double lb, double ub)
        : lowerBound(lb)
        , upperBound(ub)
    {}

    inline void SetBounds(double lb, double ub)
    {
        lowerBound = lb;
        upperBound = ub;
    }

    inline void SetLowerBound(double lb)
    {
        lowerBound = lb;
    }

    inline void SetUpperBound(double ub)
    {
        upperBound = ub;
    }
    bool IsValid() const {
        return lowerBound != std::numeric_limits<double>::max() &&
               upperBound != std::numeric_limits<double>::min();
    }

    double lowerBound = std::numeric_limits<double>::max();
    double upperBound = std::numeric_limits<double>::min();

    void MergeBounds(const EdgeCross &rhs)
    {
        SetBounds(std::min(lowerBound, rhs.lowerBound),
                  std::max(upperBound, rhs.upperBound));
    }
    enum EDGE
    {
        LEFT = 0UL,
        TOP,
        RIGHT,
        BOTTOM,
        MAX
    };

    using EdgeCrosses = std::array<EdgeCross, EDGE::MAX>;
};

struct EdgeCrossCmpLess
{
    bool operator() (const EdgeCross *lhs, const EdgeCross *rhs) const {
        return lhs->upperBound < rhs->lowerBound;
    }
};

struct Sensor
{
    Sensor()
    {}

    Sensor(const Location &cnter, double rds)
        : center(cnter)
        , radius(rds)
    {
        assert(radius >= 0.0);
    }
    Location center;
    double radius = 0.0;

    bool Crossed(const Sensor &rhs) const {
        double dist = Location::GetDistance(this->center, rhs.center);
        return dist <= fabs(this->radius + rhs.radius);
    }

    bool CrossedWithHLine(const double Y, EdgeCross& ec) const {
        if (Y >= (center.y - radius) && Y <= (center.y + radius)) {
            const double deltaY = center.y - Y;
            const double deltaX = sqrt(radius*radius - deltaY*deltaY);
            ec.SetBounds(center.x - deltaX, center.x + deltaX);
            return true;
        }

        return false;
    }

    bool CrossedWithVLine(const double X, EdgeCross& ec) const {
        if (X >= (center.x - radius) && X <= (center.x + radius)) {
            const double deltaX = center.x - X;
            const double deltaY = sqrt(radius*radius - deltaX*deltaX);
            ec.SetBounds(center.y - deltaY, center.y + deltaY);
            return true;
        }

        return false;
    }
};

struct SensorRange
{
    SensorRange()
    {}

    EdgeCross::EdgeCrosses edgeCrosses;
    std::vector<const Sensor *> sensors;

    void MergeEdgeCross(const EdgeCross::EdgeCrosses &ecs) {
        for (size_t idx = 0; idx < ecs.size(); ++idx) {
            edgeCrosses[idx].MergeBounds(ecs[idx]);
        }
    }
    void Merge(const SensorRange &sr) {
        MergeEdgeCross(sr.edgeCrosses);
        sensors.insert(sensors.end(), sr.sensors.begin(), sr.sensors.end());
    }
};

struct Rectangle {
    Rectangle()
    {}

    Rectangle(const double l, const double r, const double t, const double b)
    {
        assert(l < r);
        assert(b < t);
        edges[EdgeCross::LEFT] = l;
        edges[EdgeCross::RIGHT] = r;
        edges[EdgeCross::TOP] = t;
        edges[EdgeCross::BOTTOM] = b;
    }

    std::array<double, EdgeCross::MAX> edges;
};

void FindCrossBetweenSensorAndRect(const Sensor &sensor,
                                   const Rectangle &rect,
                                   EdgeCross::EdgeCrosses &edgeCrosses)
{
    for (size_t edge = EdgeCross::LEFT; edge < EdgeCross::MAX; ++edge) {
        if (edge & 1UL) {
            sensor.CrossedWithHLine(rect.edges[edge], edgeCrosses[edge]);
        }
        else {
            sensor.CrossedWithVLine(rect.edges[edge], edgeCrosses[edge]);
        }
    }
}

bool GenerateSenorRangeMap(const std::vector<Sensor> &sensors,
                           const Rectangle &rect,
                           const bool breakIfNoPath,
                           const bool vPath,
                           std::vector<SensorRange> &sensorRanges)
{
    auto itEnd = sensors.cend();
    std::vector<size_t> toMerge;
    for (auto it = sensors.cbegin(); it != itEnd; ++it) {
		const size_t CUR_SIZE = sensorRanges.size();
        toMerge.clear();
        toMerge.reserve(CUR_SIZE);
        for (size_t idx = 0; idx < CUR_SIZE; ++idx) {
            auto&& sRange = sensorRanges[idx];
            auto itSenEnd = sRange.sensors.cend();
            for (auto itSen = sRange.sensors.cbegin(); itSen != itSenEnd; ++itSen) {
                if ((*itSen)->Crossed(*it)) {
                    toMerge.push_back(idx);
                    break;
                }
            }
        }

        const SensorRange *workingSR = NULL;
        if (toMerge.empty()) {
            // create a new sensor range
            SensorRange sr;
            sr.sensors.emplace_back(&(*it));
            FindCrossBetweenSensorAndRect(*it, rect, sr.edgeCrosses);
            sensorRanges.push_back(sr);
            workingSR = &sensorRanges.back();
        }
        else {
            // merge all existing sensor range
            // 1. merge the rest into the first senror range
            // 2. erase the sensor ranges except the very first
            auto itMergeREnd = toMerge.crend() - 1;
            for (auto itMergeR = toMerge.crbegin(); itMergeR != itMergeREnd; ++itMergeR) {
                auto&& sRangeToKeep = sensorRanges[*toMerge.begin()];
                auto&& sRangeToMerge = sensorRanges[*itMergeR];
                sRangeToKeep.Merge(sRangeToMerge);
                sensorRanges.erase(sensorRanges.begin() + *itMergeR);
            }
            // merege with the sensor
            EdgeCross::EdgeCrosses edgeCrosses;
            FindCrossBetweenSensorAndRect(*it, rect, edgeCrosses);
            auto&& sRangeToKeep = sensorRanges[*toMerge.begin()];
            sRangeToKeep.MergeEdgeCross(edgeCrosses);
            sRangeToKeep.sensors.push_back(&(*it));
            workingSR = &sRangeToKeep;
        }
        if (workingSR && breakIfNoPath) {
            if ((vPath &&
                 workingSR->edgeCrosses[EdgeCross::LEFT].IsValid() &&
                 workingSR->edgeCrosses[EdgeCross::RIGHT].IsValid()) ||
                (!vPath &&
                 workingSR->edgeCrosses[EdgeCross::TOP].IsValid() &&
                 workingSR->edgeCrosses[EdgeCross::BOTTOM].IsValid())) {
                    return false;
            }
        }
    }
    return true;
}

bool ProcessCornerCase(const bool vPath,
                       const EdgeCross::EdgeCrosses &edgeCrosses,
                       const Rectangle &rect,
                       EdgeCross &edge)
{
    if (edge.IsValid()) {
        if (vPath) {
            // left corner
            if (edgeCrosses[EdgeCross::LEFT].IsValid()) {
                edge.SetLowerBound(rect.edges[EdgeCross::LEFT]);
            }
            // right corner
            if (edgeCrosses[EdgeCross::RIGHT].IsValid()) {
                edge.SetUpperBound(rect.edges[EdgeCross::RIGHT]);
            }
        }
        else {
            // top corner
            if (edgeCrosses[EdgeCross::TOP].IsValid()) {
                edge.SetUpperBound(rect.edges[EdgeCross::TOP]);
            }
            // bottom corner
            if (edgeCrosses[EdgeCross::BOTTOM].IsValid()) {
                edge.SetLowerBound(rect.edges[EdgeCross::BOTTOM]);
            }
        }
        return true;
    }

    return false;
}

using Path = std::array<Location, 2>;
using EdgeCrossSet = std::set<const EdgeCross*, EdgeCrossCmpLess>;

bool GetMidPointOfFirstGap(const EdgeCrossSet &ecs,
                           const Rectangle &rect,
                           const bool vPath,
                           double &val)
{
    const double lowerBound = vPath ?
        rect.edges[EdgeCross::LEFT] : rect.edges[EdgeCross::BOTTOM];
    const double upperBound = vPath ?
        rect.edges[EdgeCross::RIGHT] : rect.edges[EdgeCross::TOP];
    if (ecs.empty()) {
        val = (lowerBound + upperBound) / 2;
        return true;
    }
    auto itFirst = ecs.cbegin();
    if ((*itFirst)->lowerBound > lowerBound) {
        val = (lowerBound + (*itFirst)->lowerBound) / 2;
        return true;
    }
    auto itSecond = ++ecs.cbegin();
    if (itSecond == ecs.cend()) {
        if ((*itFirst)->upperBound < upperBound) {
            val = ((*itFirst)->upperBound + upperBound) / 2;
            return true;
        }
        return false;
    }

    if ((*itFirst)->upperBound < (*itSecond)->lowerBound) {
        val = ((*itFirst)->upperBound + (*itSecond)->lowerBound) / 2;
        return true;
    }
    return false;
}

bool FindPath(const std::vector<Sensor> &sensors,
              const Rectangle &rect,
              const bool vPath,
              Path &path)
{
    std::vector<SensorRange> sensorRanges;
    if (!sensors.empty()) {
        if (!GenerateSenorRangeMap(sensors, rect, true, vPath, sensorRanges)) {
            return false;
        }
    }

    if (sensorRanges.empty()) {
        if (vPath) {
            path[0] = Location{ rect.edges[EdgeCross::LEFT], rect.edges[EdgeCross::TOP] };
            path[1] = Location{ rect.edges[EdgeCross::LEFT], rect.edges[EdgeCross::BOTTOM] };
        }
        else {
            path[0] = Location{ rect.edges[EdgeCross::LEFT], rect.edges[EdgeCross::TOP] };
            path[1] = Location{ rect.edges[EdgeCross::RIGHT], rect.edges[EdgeCross::TOP] };
        }
        return true;
    }

    EdgeCrossSet ecsFrom;
    EdgeCrossSet ecsTo;
    auto itEnd = sensorRanges.end();
    for (auto it = sensorRanges.begin(); it != itEnd; ++it) {
        if (vPath && ProcessCornerCase(vPath,
                                       it->edgeCrosses,
                                       rect, 
                                       it->edgeCrosses[EdgeCross::TOP])) {
            ecsFrom.insert(&(it->edgeCrosses[EdgeCross::TOP]));
        }
        if (vPath && ProcessCornerCase(vPath,
                                       it->edgeCrosses,
                                       rect,
                                       it->edgeCrosses[EdgeCross::BOTTOM])) {
            ecsTo.insert(&(it->edgeCrosses[EdgeCross::BOTTOM]));
        }
        if (!vPath && ProcessCornerCase(vPath,
                                        it->edgeCrosses,
                                        rect,
                                        it->edgeCrosses[EdgeCross::LEFT])) {
            ecsFrom.insert(&(it->edgeCrosses[EdgeCross::LEFT]));
        }
        if (!vPath && ProcessCornerCase(vPath,
                                        it->edgeCrosses,
                                        rect,
                                        it->edgeCrosses[EdgeCross::RIGHT])) {
            ecsTo.insert(&(it->edgeCrosses[EdgeCross::RIGHT]));
        }
    }

    double valFrom, valTo;
    if (GetMidPointOfFirstGap(ecsFrom, rect, vPath, valFrom) &&
        GetMidPointOfFirstGap(ecsTo, rect, vPath, valTo)) {
        path[0] = vPath ? Location(valFrom, rect.edges[EdgeCross::TOP]) :
                          Location(rect.edges[EdgeCross::LEFT], valFrom);
        path[1] = vPath ? Location(valTo, rect.edges[EdgeCross::BOTTOM]) :
                          Location(rect.edges[EdgeCross::RIGHT], valTo);

        return true;
    }

    return false;
}

void TestFindPathBetweenSensors()
{
    Path path;
    const Rectangle rect = { 1.0, 9.0, 8.0, 1.0 };
    {
        const std::vector<Sensor> sensors{ { { 2.0, 3.0 }, 1.0 },
                                           { { 4.0, 3.0 }, 1.0 },
                                           { { 6.0, 3.0 }, 1.0 },
                                           { { 8.0, 3.0 }, 1.0 }
                                         };
        assert(FindPath(sensors, rect, true, path) == false);
        assert(FindPath(sensors, rect, false, path) == true);
        assert(path.at(0) == Location(1.0, 2.0) && path.at(1) == Location(9.0, 2.0));
    }

    {
        const std::vector<Sensor> sensors{ { { 2.0, 3.0 }, 1.0 },
                                           { { 4.0, 3.0 }, 1.0 },
                                           { { 6.0, 3.0 }, 1.0 },
                                           { { 8.0, 3.0 }, 1.0 },
                                           { { 8.0, 8.0 }, 1.0 },
                                           { { 7.0, 7.0 }, 1.0 }
                                         };
        assert(FindPath(sensors, rect, true, path) == false);
        assert(FindPath(sensors, rect, false, path) == true);
        assert(path.at(0) == Location(1.0, 2.0) && path.at(1) == Location(9.0, 2.0));
    }

    {
        const std::vector<Sensor> sensors{ { { 2.0, 7.2 }, 1.0 },
                                           { { 3.0, 6.0 }, 1.0 },
                                           { { 4.0, 4.5 }, 1.0 },
                                           { { 8.0, 7.2 }, 1.0 },
                                           { { 7.0, 6.2 }, 1.0 },
                                           { { 2.0, 3.0 }, 1.0 },
                                           { { 3.0, 4.0 }, 1.0 },
                                           { { 9.0, 1.0 }, 1.0 }
                                         };
        assert(FindPath(sensors, rect, true, path) == true);
        assert(path.at(0) == Location(5.0, 8.0) && path.at(1) == Location(4.5, 1.0));
        assert(FindPath(sensors, rect, false, path) == true);
        assert(path.at(0) == Location(1.0, 2.0) && path.at(1) == Location(9.0, 4.6));
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestFindPathBetweenSensors();
    return 0;
}
