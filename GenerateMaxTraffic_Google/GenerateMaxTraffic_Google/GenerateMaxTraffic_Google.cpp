// GenerateMaxTraffic_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <limits>
#include <memory>
#include <unordered_map>

#include <cassert>

struct gNode
{
    using NeighbourNodes = std::unordered_map<gNode*, size_t>;
    gNode(size_t i, size_t t)
        : id(i)
        , traffic(t)
    {}
	
    void AppendNeighbour(gNode* neighbour)
    {
        neighbours.insert(std::make_pair(neighbour, 0));
    }

    void AppendNeighbours(const std::vector < gNode* > ns)
    {
	    auto itEnd = ns.cend();
	    for (auto it = ns.cbegin(); it != itEnd; ++it) {
		    AppendNeighbour(*it);
	    }
    }

    size_t id;
    size_t traffic;
    NeighbourNodes neighbours;
    size_t maxTraffic = 0;
    size_t sumOfNeighboursTraffic = 0;
};

size_t CalculateNeighboursTraffic(gNode* root, const gNode* parent)
{
    if (!root) {
        return 0;
    }

    if (root->neighbours.size() == 1 && parent) {
	    return root->traffic;
    }

    auto itEnd = root->neighbours.end();
    size_t traffic = 0;
    for (auto it = root->neighbours.begin(); it != itEnd; ++it) {
        if (!parent || it->first->id != parent->id) {
	        it->second = CalculateNeighboursTraffic(it->first, root);
	        traffic += it->second;
        }
    }
return traffic + root->traffic;
}

void CalculateParentTraffic(gNode *root, const gNode *parent)
{
    if (!root) {
        return;
    }
    if (parent) {
        const auto itFound = parent->neighbours.find(root);
        assert(itFound != parent->neighbours.end());
        auto rootItFound = root->neighbours.find(const_cast<gNode*>(parent));
        assert(rootItFound != root->neighbours.end());
        rootItFound->second = parent->sumOfNeighboursTraffic + parent->traffic - itFound->second;
    }

    auto itEnd = root->neighbours.cend();
    for (auto it = root->neighbours.cbegin(); it != itEnd; ++it) {
	    root->sumOfNeighboursTraffic += it->second;
    }
	
    for (auto it = root->neighbours.begin(); it != itEnd; ++it) {
        if (!parent || it->first != parent) {
	        CalculateParentTraffic(it->first, root);
        }
    }
}

void PopulateMaxTraffic(gNode *root, const gNode *parent)
{
	if (!root) {
		return;
	}

	const auto itEnd = root->neighbours.cend();
	for (auto it = root->neighbours.cbegin(); it != itEnd; ++it) {
		if (root->maxTraffic < it->second) {
			root->maxTraffic = it->second;
		}
	}

	for (auto it = root->neighbours.begin(); it != itEnd; ++it) {
		if (!parent || it->first != parent) {
			PopulateMaxTraffic(it->first, root);
		}
	}
}

void GenerateMaxTraffic(gNode* node)
{	
	CalculateNeighboursTraffic(node, 0);

	CalculateParentTraffic(node, 0);

	PopulateMaxTraffic(node, 0);
}

void Test_GenerateMaxTraffic()
{
    {
        gNode node1(1, 1);
        gNode node2(2, 2);
        gNode node3(3, 3);
        gNode node4(4, 4);
        gNode node5(5, 5);

        node1.AppendNeighbour(&node5);
        node2.AppendNeighbour(&node5);
        node3.AppendNeighbour(&node5);
        node4.AppendNeighbour(&node5);
        node5.AppendNeighbours({&node1, &node2, &node3, &node4});

        GenerateMaxTraffic(&node1);
		
        assert(node1.maxTraffic == 14);
        assert(node2.maxTraffic == 13);
        assert(node3.maxTraffic == 12);
        assert(node4.maxTraffic == 11);
        assert(node5.maxTraffic == 4);
    }

    {
        gNode node1(1, 1);
        gNode node2(2, 2);
        gNode node3(3, 3);
        gNode node4(4, 4);
        gNode node5(5, 5);
        gNode node7(7, 7);
        gNode node8(8, 8);
        gNode node15(15, 15);
        gNode node38(38, 38);
		
        node1.AppendNeighbour(&node5);
        node2.AppendNeighbours({ &node5, &node7, &node15 });
        node3.AppendNeighbour(&node5);
        node4.AppendNeighbour(&node5);
        node5.AppendNeighbours({ &node1, &node2, &node3, &node4 });
        node7.AppendNeighbours({ &node2, &node8 });
        node8.AppendNeighbours({ &node7, &node38 });
        node15.AppendNeighbour(&node2);
        node38.AppendNeighbour(&node8);

        GenerateMaxTraffic(&node1);

        assert(node1.maxTraffic == 82);
        assert(node2.maxTraffic == 53);
        assert(node3.maxTraffic == 80);
        assert(node4.maxTraffic == 79);
        assert(node5.maxTraffic == 70);
        assert(node7.maxTraffic == 46);
        assert(node8.maxTraffic == 38);
        assert(node15.maxTraffic == 68);
        assert(node38.maxTraffic == 45);
    }

    {
        gNode node1(1, 1);
        gNode node2(2, 2);
        gNode node3(3, 3);
        gNode node4(4, 4);
        gNode node5(5, 5);
        gNode node7(7, 7);
        gNode node8(8, 8);
        gNode node15(15, 15);
        gNode node38(38, 38);

        node1.AppendNeighbour(&node5);
        node2.AppendNeighbours({ &node5, &node7, &node15 });
        node3.AppendNeighbour(&node5);
        node4.AppendNeighbour(&node5);
        node5.AppendNeighbours({ &node1, &node2, &node3, &node4 });
        node7.AppendNeighbours({ &node2, &node8 });
        node8.AppendNeighbours({ &node7, &node38 });
        node15.AppendNeighbour(&node2);
        node38.AppendNeighbour(&node8);

        GenerateMaxTraffic(&node5);

        assert(node1.maxTraffic == 82);
        assert(node2.maxTraffic == 53);
        assert(node3.maxTraffic == 80);
        assert(node4.maxTraffic == 79);
        assert(node5.maxTraffic == 70);
        assert(node7.maxTraffic == 46);
        assert(node8.maxTraffic == 38);
        assert(node15.maxTraffic == 68);
        assert(node38.maxTraffic == 45);
    }
}

int main()
{
	Test_GenerateMaxTraffic();

	return 0;
}

