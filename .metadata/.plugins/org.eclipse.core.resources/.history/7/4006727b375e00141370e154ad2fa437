//
//  CS263-Trees
//

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "hw411_binarytree.hpp"

class TreeTest {
public:
    TreeTest() {
        for (auto x = refData.begin(); x != refData.end(); ++x)
            items.insert(*x);
    }

    vector<string> refData {
        "ram",
        "memory",
        "keyboard",
        "cpu",
        "gpu",
        "mouse",
        "monitor",
        "usb",
        "wireless",
        "ssd",
        "DVD",
        "LCD",
        "VGA",
        "bluetooth",
        "HDMI",
        "speakers",
        "videocam",
        "microphone",
        "power",
        "firewire"};
    gvsu::BinaryTree<string> items;
};


TEST_CASE_METHOD (TreeTest, "contains")
{
    CHECK_NOTHROW(items.contains("power"));
    for (auto p = refData.begin(); p != refData.end(); ++p)
        CHECK (items.contains(*p));
    CHECK_FALSE (items.contains("POWER"));
}

TEST_CASE_METHOD (TreeTest, "insert should not accept duplicate")
{
    for (auto p = refData.begin(); p != refData.end(); ++p)
        CHECK_FALSE(items.insert(*p));
}

TEST_CASE_METHOD (TreeTest, "remove")
{
    cout << items << endl;
    for (auto p = refData.begin(); p != refData.end(); ++p)
    {
        items.remove(*p);
        CHECK_FALSE (items.contains(*p));
    }
}

TEST_CASE_METHOD(TreeTest, "Tree counters ")
{
    /* Tester function for Question 4.13 a-c */
    gvsu::BinaryTree<string> ctest;

    CHECK (ctest.numberOfNodes() == 0);
    CHECK (ctest.numberOfLeaves() == 0);
    CHECK (ctest.numberOfFullNodes() == 0);
    int k = 0;
    for (auto x = refData.begin(); x != refData.end(); ++x)
    {
        k++;
        ctest.insert (*x);
        int F = ctest.numberOfFullNodes();
        int L = ctest.numberOfLeaves();
        CHECK (ctest.numberOfNodes() == k);
        CHECK (L == F + 1);
    }
}

TEST_CASE_METHOD(TreeTest, "level order")
{
    /* Tester function for Question 4.40 */
    vector<string> level = items.levelOrder();
    CHECK (level.size() > 0);
    vector<string> expected {"ram", "memory", "usb", "keyboard", "mouse",
        "ssd", "wireless", "cpu", "monitor", "power", "speakers",
        "videocam", "DVD", "gpu", "microphone", "LCD", "firewire",
        "HDMI", "VGA", "bluetooth"};
    CHECK (level == expected);
}
