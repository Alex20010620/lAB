#include "_map.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(test, insertion_tests) {
    _map<int, int> map1;    // <value, key>
    map1.insert(2, 1);
    map1.insert(1, 2);
    map1.insert(4, 3);
    map1.insert(3, 4);
    map1.insert(6, 5);
    map1.insert(5, 6);
    map1.insert(7, 7);

    //checks for numbers (BFS)
    _array<int> arr_values = map1.get_values();
    _array<int> arr_test;
    arr_test.insert(1);
    arr_test.insert(2);
    arr_test.insert(3);
    arr_test.insert(4);
    arr_test.insert(5);
    arr_test.insert(6);
    arr_test.insert(7);

    ASSERT_TRUE(arr_values == arr_test);

    ASSERT_EQ(map1.find(7)->color, RED);
    ASSERT_EQ(map1.find(6)->color, BLACK);
    ASSERT_EQ(map1.find(5)->color, RED);
    ASSERT_EQ(map1.find(1)->color, BLACK);
    ASSERT_EQ(map1.find(3)->color, BLACK);

    _map<int, int> map2;
    map2.insert(3, 1000);
    map2.insert(1, 100);
    map2.insert(2, 10);
    map2.insert(4, 0);

    _array<int> arr_values2 = map2.get_values();
    _array<int> arr_test2;
    arr_test2.insert(1);
    arr_test2.insert(2);
    arr_test2.insert(3);
    arr_test2.insert(4);
    ASSERT_TRUE(arr_values2 == arr_test2);

    ASSERT_EQ(map2.find(0)->color, RED);
    ASSERT_EQ(map2.find(1000)->color, BLACK);

    _map<int, char> map3;   // key is char
    map3.insert(2, 'a');
    map3.insert(1, 'b');
    map3.insert(4, 'x');
    map3.insert(3, 'y');
    map3.insert(5, 'z');

    _array<char> vec_keys3 = map3.get_keys();
    _array<char> vec_test3;
    vec_test3.insert('b');
    vec_test3.insert('a');
    vec_test3.insert('y');
    vec_test3.insert('x');
    vec_test3.insert('z');

    ASSERT_TRUE(vec_keys3 == vec_test3);

    ASSERT_EQ(map3.find('z')->color, RED);
    ASSERT_EQ(map3.find('x')->color, RED);
    ASSERT_EQ(map3.find('a')->color, BLACK);
    ASSERT_EQ(map3.find('b')->color, BLACK);
    ASSERT_EQ(map3.find('y')->color, BLACK);
}

TEST(test, erase_tests) {
    _map<int, int> map1;    // <value, key>
    map1.insert(2, 1);
    map1.insert(1, 2);
    map1.insert(4, 3);
    map1.insert(3, 4);
    map1.insert(6, 5);
    map1.insert(5, 6);
    map1.insert(7, 7);
    map1.remove(3);

    _array<int> arr_values = map1.get_keys();
    _array<int> arr_test;
    arr_test.insert(2);
    arr_test.insert(1);
    arr_test.insert(6);
    arr_test.insert(4);
    arr_test.insert(7);
    arr_test.insert(5);
    ASSERT_TRUE(arr_values == arr_test);

    ASSERT_EQ(map1.find(4)->color, BLACK);


    _map<int, int> map2;
    map2.insert(3, 1000);
    map2.insert(1, 100);
    map2.insert(2, 10);
    map2.insert(4, 0);
    map2.remove(1000);
    map2.remove(100);

    _array<int> arr_keys2 = map2.get_keys();
    _array<int> vec_test2;
    vec_test2.insert(10);
    vec_test2.insert(0);

    ASSERT_TRUE(arr_keys2 == vec_test2);

    ASSERT_EQ(map2.find(10)->color, BLACK);
    ASSERT_EQ(map2.find(0)->color, RED);

    _map<int, int> map3;
    map3.insert(1, 500);
    map3.insert(3, 300);
    map3.insert(2, 200);
    map3.insert(4, 2000);
    map3.insert(5, 20000);
    map3.insert(6, 0);
    map3.remove(2000);


    _array<int> arr_keys3 = map3.get_keys();
    _array<int> vec_test23;
    vec_test23.insert(300);
    vec_test23.insert(200);
    vec_test23.insert(20000);
    vec_test23.insert(0);
    vec_test23.insert(500);

    ASSERT_TRUE(arr_keys3 == vec_test23);

    ASSERT_EQ(map3.find(500)->color, RED);
    ASSERT_EQ(map3.find(0)->color, RED);
}

TEST(test, other_tests) {
    _map<double, float> empty_map;
    empty_map.insert(1.0, 1.0f);
    empty_map.insert(2.0, 1.25f);
    empty_map.insert(3.0, 1.5f);
    empty_map.clear();

    ASSERT_ANY_THROW(empty_map.get_values());
    ASSERT_ANY_THROW(empty_map.get_keys());
    ASSERT_ANY_THROW(empty_map.find(2.0));
    ASSERT_ANY_THROW(empty_map.remove(2.0));
}
