//
//  main.cpp
//  P-3.11
//
//  Created by Hans Dulimarta on 9/30/14.
//  Copyright (c) 2014 Hans Dulimarta. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <string>
#include <iterator>
#include <map>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "hw311.hpp"
using namespace std;
using namespace gvsu;

/* static variables used by the allocator class */
template<typename T>
GVSU_Allocator<T>* GVSU_Allocator<T>::_instance{};
template<typename T>
GVSU_Allocator<T>* gvsu::LinkedList<T>::node_alloc = GVSU_Allocator<T>::get_instance();
template<typename T>
int GVSU_Allocator<T>::alloc_count = 0;
template<typename T>
int GVSU_Allocator<T>::dealloc_count = 0;
template<typename T>
map<T*,unsigned long> GVSU_Allocator<T>::alloc_map;

TEST_CASE("size()") {
    gvsu::LinkedList<int> empty;
    REQUIRE(empty.size() == 0);
    gvsu::LinkedList<string> empty2;
    REQUIRE(empty2.size() == 0);
}

TEST_CASE("add a new item") {
    gvsu::LinkedList<int> nums;
    vector<int> numbers(100);

    /* generate 1 to 100 and shuffle them */
    for (int k = 0; k < 100; k++)
        numbers[k] = k+1;
    random_shuffle(numbers.begin(), numbers.end());

    for (int x : numbers) {
        REQUIRE (nums.add(x) == true);
        REQUIRE (nums.add(x) == false);  /* duplicate data should be rejected */
    }
    REQUIRE (nums.size() == numbers.size());
}

TEST_CASE("Contains") {
    vector<string> elements {"Hydrogen", "Nitrogen", "Lithium", "Carbon", "Magnesium",
        "Neon", "Oxygen"};

    LinkedList<string> chem;
    for (string& s : elements) {
        REQUIRE (chem.contains(s) == false);
    }

    for (string& s : elements) {
        REQUIRE (chem.add(s) == true);
    }
    REQUIRE (chem.size() == elements.size());
    for (string& s : elements) {
        REQUIRE (chem.contains(s) == true);
        REQUIRE (chem.contains(s + "-EXTRA") == false);
    }
}

TEST_CASE("Print the list") {
    vector<string> elements {"Hydrogen", "Nitrogen", "Lithium", "Carbon", "Magnesium",
        "Neon", "Oxygen"};

    LinkedList<string> chem;

    ostringstream output;

    SECTION("Empty List") {
        output.clear();
        output << chem;
        /* When the list is empty, nothing should be printed */
        REQUIRE(output.str().length() == 0);
    }
    SECTION("Many items") {
        output.clear();
        for (string& s : elements) {
            REQUIRE (chem.add(s) == true);
        }
        REQUIRE (chem.size() == elements.size());
        output << chem;
        size_t pos = output.str().find(elements[0]);
        REQUIRE(pos != string::npos);
        for (int k = 1; k < elements.size(); k++) {
            size_t element_pos = output.str().find(elements[k]);
            REQUIRE(element_pos != string::npos);
            REQUIRE(element_pos > pos);
            pos = element_pos;
        }
    }
}

TEST_CASE("Non-destructive print") {
    vector<string> elements {"Hydrogen", "Nitrogen", "Lithium", "Carbon", "Magnesium",
        "Neon", "Oxygen"};

    LinkedList<string> chem;

    for (string& s : elements) {
        REQUIRE (chem.add(s) == true);
    }
    REQUIRE (chem.size() == elements.size());
    ostringstream output1, output2;
    output1 << chem;
    output2 << chem;
    REQUIRE(output1.str() == output1.str());
}


TEST_CASE("Remove") {
    vector<string> elements {"Hydrogen", "Nitrogen", "Lithium", "Carbon", "Magnesium",
        "Neon", "Oxygen"};

    LinkedList<string> chem;
    for (string& s : elements) {
        REQUIRE (chem.remove(s) == false);
    }

    for (string& s : elements) {
        REQUIRE (chem.add(s) == true);
    }
    REQUIRE (chem.size() == elements.size());
    int expected_size = chem.size();
    for (string& s : elements) {
        REQUIRE (chem.remove(s) == true);
        REQUIRE (chem.contains(s) == false);
        expected_size--;
        REQUIRE (chem.size() == expected_size);
        REQUIRE (chem.remove(s + "-EXTRA") == false);
        REQUIRE (chem.size() == expected_size);
    }
}


TEST_CASE("Print the list reverse") {
    vector<string> elements {"Hydrogen", "Nitrogen", "Lithium", "Carbon", "Magnesium",
        "Neon", "Oxygen"};

    LinkedList<string> chem;
    ostringstream output;
    SECTION ("Empty List") {
        output.clear();
        chem.print_reverse(output);
        REQUIRE(output.str().length() == 0);
    }

    SECTION ("One item") {
        ostringstream out1, out2;
        chem.add("Lithium");
        chem.print(out1);
        chem.print_reverse(out2);
        REQUIRE(out1.str() == out2.str());
    }
    SECTION("Multiple items") {
        output.clear();
        for (string& s : elements) {
            REQUIRE (chem.add(s) == true);
        }
        REQUIRE (chem.size() == elements.size());
        chem.print_reverse(output);
        size_t pos = output.str().find(elements[0]);

        REQUIRE(pos != string::npos);
        for (int k = 1; k < elements.size(); k++) {
            size_t element_pos = output.str().find(elements[k]);
            REQUIRE(element_pos != string::npos);
            REQUIRE(element_pos < pos);
            pos = element_pos;
        }
    }
}

TEST_CASE("Print reverse shall not reverse the list") {
    auto intAlloc = GVSU_Allocator<int>::get_instance();
    ostringstream outbefore, outafter, dump;
    LinkedList<int> nums;
    nums.add(45);
    nums.add(-1237);
    nums.add(90);
    nums.add(2345);
    int before, after;
    nums.print(outbefore);
    before = intAlloc->allocation_status().first;
    nums.print_reverse(dump);
    after = intAlloc->allocation_status().first;
    nums.print(outafter);
    if (before != after) {
        FAIL("print_reverse() allocates too much memory");
    }
    REQUIRE(outbefore.str() == outafter.str());
}

TEST_CASE("Memory Leak Check") {
    auto intAlloc = GVSU_Allocator<int>::get_instance();
    auto strAlloc = GVSU_Allocator<string>::get_instance();

    INFO("Checking for memory leaks");
    ostringstream outmsg;
    auto stat = intAlloc->allocation_status();
    if( stat.first != stat.second) {
        intAlloc->report("int");
        outmsg.clear();
        outmsg << (stat.first - stat.second)
            << " blocks of memory for integer data were not deleted";
        FAIL(outmsg.str());
    }
    stat = strAlloc->allocation_status();
    if( stat.first != stat.second) {
        strAlloc->report("string");
        outmsg.clear();
        outmsg << (stat.first - stat.second)
            << " blocks of memory for string data were not deleted";
        FAIL(outmsg.str());
    }
}
