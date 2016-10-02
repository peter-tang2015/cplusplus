// SchedulingProblem_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>

#include <cassert>

bool SchedulingSolutionDP1(const std::vector<int> serverCenter,
                        const std::vector<int> tasks)
{
    if (tasks.empty()) {
        return true;
    }

    if (tasks.size() == 1) {
        for (size_t index = 0; index < serverCenter.size(); ++index) {
            if (tasks[0] <= serverCenter[index]) {
                return true;
            }
        }
        return false;
    }

    for (size_t index = 0; index < serverCenter.size(); ++index) {
        if (tasks[0] <= serverCenter[index]) {
            std::vector<int> newServerCenter(serverCenter);
            newServerCenter[index] -= tasks[0];
            std::vector<int>::const_iterator taskIter = tasks.begin();
            ++taskIter;
            std::vector<int> newTasks(taskIter, tasks.end());
            if (SchedulingSolutionDP1(newServerCenter, newTasks)){
                return true;
            }
        }
    }

    return false;
}

bool SchedulingSolutionDP(std::vector<int>& serverCenter,
                           const std::vector<int>& tasks, const size_t taskIndex)
{
    if (tasks.empty()) {
        return true;
    }

    if (taskIndex >= (tasks.size() - 1)) {
        for (size_t index = 0; index < serverCenter.size(); ++index) {
            if (tasks[taskIndex] <= serverCenter[index]) {
                return true;
            }
        }
        return false;
    }

    for (size_t index = 0; index < serverCenter.size(); ++index) {
        if (tasks[taskIndex] <= serverCenter[index]) {
            serverCenter[index] -= tasks[taskIndex];
            if (SchedulingSolutionDP(serverCenter, tasks, taskIndex + 1)){
                serverCenter[index] += tasks[taskIndex];
                return true;
            }
            serverCenter[index] += tasks[taskIndex];
        }
    }

    return false;
}


void TestCases()
{
    {
        std::vector<int> serverCenter = { 8, 16, 8, 32 };
        std::vector<int> tasks = { 18, 4, 8, 4, 6, 6, 8, 8 };
        assert(SchedulingSolutionDP1(serverCenter, tasks) == true);
        assert(SchedulingSolutionDP(serverCenter, tasks, 0) == true);
    }

    {
        std::vector<int> serverCenter = { 1, 3 };
        std::vector<int> tasks = { 4 };
        assert(SchedulingSolutionDP1(serverCenter, tasks) == false);
        assert(SchedulingSolutionDP(serverCenter, tasks, 0) == false);
    }

    {
        std::vector<int> serverCenter = { 7, 6 };
        std::vector<int> tasks = { 5, 3, 3, 2 };
        assert(SchedulingSolutionDP1(serverCenter, tasks) == true);
        assert(SchedulingSolutionDP(serverCenter, tasks, 0) == true);
    }

    {
        std::vector<int> serverCenter = { 1, 3, 1, 2, 3, 4 };
        std::vector<int> tasks = { 4, 3, 1, 2, 3, 1 };
        assert(SchedulingSolutionDP1(serverCenter, tasks) == true);
        assert(SchedulingSolutionDP(serverCenter, tasks, 0) == true);
    }

    {
        std::vector<int> serverCenter = { 2, 5, 10, 4, 13, 19, 23, 11, 8, 17 };
        std::vector<int> tasks = { 30, 2, 1 };
        assert(SchedulingSolutionDP1(serverCenter, tasks) == false);
        assert(SchedulingSolutionDP(serverCenter, tasks, 0) == false);
    }

    {
        std::vector<int> serverCenter = { 8, 6, 2 };
        std::vector<int> tasks = { 5, 4, 3, 2, 1 };
        assert(SchedulingSolutionDP1(serverCenter, tasks) == true);
        assert(SchedulingSolutionDP(serverCenter, tasks, 0) == true);
    }

    {
        std::vector<int> serverCenter = { 8, 6, 2 };
        std::vector<int> tasks = { 5, 4, 4, 2, 1 };
        assert(SchedulingSolutionDP1(serverCenter, tasks) == true);
        assert(SchedulingSolutionDP(serverCenter, tasks, 0) == true);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestCases();

    return 0;
}

/*
// MockOrderStore.h
#pragma
#include "OrderStore.h"

#include <gmock/gmock.h>

class MockOrderStore : public OrderStore
{
public:
    MOCK_CONST_METHOD0(getOrders, std::vector<Order>());
};

// SimpleOrderManagerTest.h
#pragma

#include <gtest/gtest.h>

class SimpleOrderManagerTest : public testing::Test
{
public:
    virtual void SetUp();
    virtual void TearDown();

};

// SimpleOrderManagerTest.cpp
#include "SimpleOrderManagerTest.h"

#include "MockOrderStore.h"
#include "Order.h"
#include "OrderWriter.h"
#include "SimpleOrderManager.h"

#include <exception>
#include <vector>

void SimpleOrderManagerTest::SetUp()
{
}

void SimpleOrderManagerTest::TearDown()
{
}

TEST_F(SimpleOrderManagerTest, GivenEmptyOrders_ExpectException)
{
    MockOrderStore mos;
    OrderWriter ow;
    SimpleOrderManager som;

    EXPECT_CALL(mos, getOrders).WillOnce(Return(sd::vector<order>()));
    try
    {
        som.WriteAllOrders(mos, ow);
    }
    catch (std::exception& e)
    {
        EXPECT_STREQ("No orders in store", e.what());
    }
}

TEST_F(SimpleOrderManagerTest, GivenNonEmptyOrders_ExpectNoException)
{
    MockOrderStore mos;
    OrderWriter ow;
    SimpleOrderManager som;

    EXPECT_CALL(mos, getOrders).WillOnce(Return(sd::vector<order>(2)));
    EXPECT_NO_THROW(som.WriteAllOrders(mos, ow));
}

// TestMain.cpp
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "Google test main() started ......" << std::endl;

    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
*/
