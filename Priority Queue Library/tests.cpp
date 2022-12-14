#include <gtest/gtest.h>
#include "priorityqueue.h"
using namespace std;

TEST(priorityqueue, empty) {
    priorityqueue<int> pq;
    ASSERT_EQ(pq.Size(),0);
}

TEST(priorityqueue, sizeOne) {
    priorityqueue<int> pq;
    pq.enqueue(2,1);
    ASSERT_EQ(pq.Size(), 1);
}

TEST(priorityqueue, sizeTwo) {
    priorityqueue<int> pq;
    pq.enqueue(1,1);
    pq.enqueue(2,2);
    ASSERT_EQ(pq.Size(), 2);
}

TEST(priorityqueue, stringTemplate) {
    priorityqueue<string> pq;
    pq.enqueue("Faker",1);
    pq.enqueue("Ruler", 2);
    pq.enqueue("Gamayusi", 3);
    pq.enqueue("FBI", 4);
    ASSERT_EQ(pq.toString(), "1 value: Faker\n2 value: Ruler\n3 value: Gamayusi\n4 value: FBI\n");
}

TEST(priorityqueue, stringTemplateUnordered) {
    priorityqueue<string> pq;
    pq.enqueue("Gamayusi", 3);
    pq.enqueue("Ruler", 2);
    pq.enqueue("Faker",1);
    pq.enqueue("FBI", 4);
    ASSERT_EQ(pq.toString(), "1 value: Faker\n2 value: Ruler\n3 value: Gamayusi\n4 value: FBI\n");
}

TEST(priorityqueue, sizeAfterClear) {
    priorityqueue<int> pq;
    pq.enqueue(1,1);
    pq.enqueue(2,2);
    pq.enqueue(3,3);
    pq.clear();
    ASSERT_EQ(pq.Size(), 0);
}

TEST(priorityqueue, assignmentOperatorCopyValues) {
    priorityqueue<int> pq1;
    priorityqueue<int> pq2;
    pq1.enqueue(1,1);
    pq2 = pq1;
    ASSERT_EQ(pq2.toString(), "1 value: 1\n");
}

TEST(priorityqueue, assignmentOperatorCopyTreeSize) {
    priorityqueue<double> pq1;
    priorityqueue<double> pq2;
    pq1.enqueue(1.1, 1);
    pq1.enqueue(2.2, 2);
    pq2 = pq1;
    ASSERT_EQ(pq2.Size(), 2);
}

TEST(priorityqueue, compareOperator) {
    priorityqueue<int> pq1;
    priorityqueue<int> pq2;
    pq1.enqueue(1,1);
    pq2.enqueue(1,1);
    ASSERT_EQ(pq2==pq1, true);
}

TEST(priorityqueue, sizeWithDuplicate) {
    priorityqueue<int> pq;
    pq.enqueue(1,1);
    pq.enqueue(2,1);
    pq.enqueue(3,2);
    ASSERT_EQ(pq.Size(), 3);
}

TEST(priorityqueue, outputDuplicate) {
    priorityqueue<int> pq;
    pq.enqueue(1,1);
    pq.enqueue(2,1);
    ASSERT_EQ(pq.toString(), "1 value: 1\n1 value: 2\n");
}