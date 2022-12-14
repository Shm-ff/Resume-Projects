
#include <gtest/gtest.h>
#include "mymap.h"
#include "myrandom.h"
#include <vector>

TEST(mymap, none) {
    mymap<int, int> temp;
    ASSERT_EQ(temp.Size(), 0);
}
TEST(mymap, typechar) {
    mymap<char, int> temp;
    ASSERT_EQ(temp.Size(), 0);
}
TEST(mymap, typefloat) {
    mymap<float, int> temp;
    ASSERT_EQ(temp.Size(), 0);
}
TEST(mymap, typelong) {
    mymap<long, int> temp;
    ASSERT_EQ(temp.Size(), 0);
}
TEST(mymap, typestring) {
    mymap<string, int> temp;
    ASSERT_EQ(temp.Size(), 0);
}
TEST(mymap, typedouble) {
    mymap<double, int> temp;
    ASSERT_EQ(temp.Size(), 0);
}
TEST(mymap, typeMixed) {
    mymap<char, string> temp;
    ASSERT_EQ(temp.Size(), 0);
}
TEST(mymap, typeMixedII) {
    mymap<char, double> temp;
    ASSERT_EQ(temp.Size(), 0);
}
TEST(mymap, multiple) {
    mymap<int, int> map;
    int n = 10;
    int arr[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};

    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    ASSERT_EQ(map.Size(), 10);
}
TEST(mymap, mixedMultiple) {
    mymap<char, int> map;
    int arr[] = {2, 1, 3};

    map.put('T', arr[0]);
    map.put('A', arr[1]);
    map.put('G', arr[2]);
    string sol = "key: A value: 1\nkey: G value: 3\nkey: T value: 2\n";
    ASSERT_EQ(map.toString(), sol);
}
TEST(mymap, mixedMultipleII) {
    mymap<string, int> map;
    int arr[] = {2, 1, 3};
    map.put("T", arr[0]);
    map.put("A", arr[1]);
    map.put("G", arr[2]);
    string sol = "key: A value: 1\nkey: G value: 3\nkey: T value: 2\n";
    ASSERT_EQ(map.toString(), sol);
}
TEST(mymap, doesContains) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    ASSERT_EQ(map.contains(3), true);
}
TEST(mymap, doesntContains) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    ASSERT_EQ(map.contains(4), false);
}
TEST(mymap, get) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(map.get(arr[i]), arr[i]);
        EXPECT_EQ(map.Size(), 3);
    }
    ASSERT_EQ(map.Size(), 3);
}
TEST(mymap, toString) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map.Size(), 3);
    string sol = "key: 1 value: 1\nkey: 2 value: 2\nkey: 3 value: 3\n";
    EXPECT_EQ(map.toString(), sol);
}
TEST(mymap, brackets) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(map[arr[i]], arr[i]);
        EXPECT_EQ(map.Size(), 3);
    }
}
TEST(mymap, begin) {
    mymap<int, int> mp1;
    int arr[] = {2, 1, 3};
    int order[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        mp1.put(arr[i], arr[i]);
    }
    int i =0;
    for (auto key : mp1) {
        EXPECT_EQ(order[i++], key);
    }
}
TEST(mymap, clear) {
    mymap<int, int> map;
    int n = 10;
    int arr[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};
    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    map.clear();
    ASSERT_EQ(map.Size(), 0);
}
TEST(mymap, copy) {
    mymap<int, int> map;
    mymap<int, int> map2;
    int n = 10;
    int arr[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};
    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    map2 = map;
    map.clear();
    ASSERT_EQ(map2.Size(), n);
}

// Copy and Clear Stress Test
TEST(mymap, CopyPeerTest) {

    // Create two mymaps m1 and m2
    mymap<int, int> m1;
    mymap<int, int> m2;
    int n = 10000;

    for(int  i = 0; i < n; i++) {

        // Generate two random numbers
        int key = randomInteger(0, 100000);
        int val = randomInteger(0, 100000);

        // Insert them in map1
        m1.put(key, val);

        // Insert different elements in map2
        if(i % 2) {
            m2.put(val, key);
        }
    }

    // At this point they must be unequal
    ASSERT_NE(m1.Size(), m2.Size());

    // Set map2 equals to map1
    m2 = m1;

    // Both should be the same size and contain the same elements
    ASSERT_EQ(m1.Size(), m2.Size());
    ASSERT_EQ(m1.toString(), m2.toString());

    // Clear map1
    m1.clear();

    // Now they are unequal again
    ASSERT_NE(m1.Size(), m2.Size());
    // Map1 must be empty
    ASSERT_EQ(m1.Size(), 0);
}
//Test for operator[] on already balanced tree.

TEST(mymap, operatorBrackets){
    mymap<int, string> test;
    map<int, string> omap;
    int n= 10;
    int arr[] = {40, 25, 60, 18, 35, 80, 30, 38, 50, 70};

    for (int i = 0; i < n; i++) {
        string value = "MAX: " + to_string(randomInteger(0, 40));
        test.put(arr[i], value);
        omap.emplace(arr[i], value);
    }
    for(int i=0; i<n;i++){
        ASSERT_EQ(test[arr[i]], omap[arr[i]]);
    }

    //Value not in map
    for(int i=0; i<n;i++){
        ASSERT_EQ(test[i*1000], "");
        ASSERT_EQ(test.Size(), n+i+1);
    }

    //Duplicate values
    for (int i = 0; i < n; i++) {
        string value = "MAX: " + to_string(randomInteger(0, 40));
        test.put(arr[i], value);
        omap[arr[i]] = value;
    }
    for(int i=0; i<n;i++){
        ASSERT_EQ(test[arr[i]], omap[arr[i]]);
    }

}

//Copy Constructor
TEST(copyConstructor, IIConCopy) {
    mymap<int, int> m;
    map<int, int> correct;
    vector<int> keys;
    int key;
    int val;
    int arrSize = 15;
    int high = 500, low = 0;
    int modOp = (high - (low + 1)) + low;


    //Populate
    for (int i = 0; i < arrSize; i++) {
        key = rand() % modOp;
        val = rand() % modOp;

        keys.push_back(key);

        m.put(key, val);
        correct[key] = val;
    }

    EXPECT_EQ(m.Size(), correct.size()) << "mymap != map\n";

    mymap<int, int> m2 = m;
    EXPECT_EQ(m.toString(), m2.toString()) << "Copy operator formating off\n";
    EXPECT_EQ(m2.Size(), correct.size()) << "M2's size does not match correct's\n";

    //Both have the same return value on keys
    int compA;
    int compB;
    for (auto& k : keys) {
        compA = m2[k];
        compB = correct[k];
        EXPECT_EQ(compA, compB) << compA << " != " << compB << "\t Incorrect Copy Constructor\n";
    }
}

//Copy Operator test <int, int>
TEST(Operator, IICopyP) {
    mymap<int, int> m;
    mymap<int, int> m2;

    //Populate 1 and 2
    int key, value, high, low, modOp;
    int arrSize = rand() % 100;

    string mOriginal, m2Original;

    //Populate m
    high = 500;
    low = 1;
    modOp = (high - (low + 1)) + low;
    for (int i = 0; i < arrSize; i++) {
        key = rand() % modOp;
        value = rand() % modOp;
        m.put(key, value);
    }

    //Populate m2
    high = 1000;
    low = 500;
    modOp = (high - (low + 1)) + low;
    for (int i = 0; i < arrSize; i++) {
        key = rand() % modOp;
        value = rand() % modOp;
        m2.put(key, value);
    }

    m = m2;

    EXPECT_EQ(m.Size(), m2.Size()) << "IIEquals; size difference\n";
    EXPECT_NE(mOriginal, m.toString()) << "m should not still equal original\n";
    EXPECT_EQ(m2.toString(), m.toString()) << "toString() !=\n" << "M:\n" << m.toString() << "\nM2:\n" << m2.toString() << endl;;
}

// default constructor Test and size Test
TEST(mymap, defaultConstructor) {

    // create a mymap
    mymap<int, int> m;

    // check if the size is 0
    EXPECT_EQ(m.Size(), 0);

}

// put Test and size Test
TEST(mymap, put) {

    // create a mymap
    mymap<int, int> m;

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.Size(), 3);

}

// get Test
TEST(mymap, getII) {

    // create a mymap
    mymap<int, int> m;

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.get(1), 1);
    EXPECT_EQ(m.get(2), 2);
    EXPECT_EQ(m.get(3), 3);
    EXPECT_EQ(m.get(4), 0);

}

// contains Test
TEST(mymap, containsKey) {

    // create a mymap
    mymap<int, int> m;

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.contains(1), true);
    EXPECT_EQ(m.contains(2), true);
    EXPECT_EQ(m.contains(3), true);
    EXPECT_EQ(m.contains(4), false);

}

// toString Test
TEST(mymap, tostr) {

    // create a mymap
    mymap<int, int> m;

    int arr[] = {3, 2, 1};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    string sol = "key: 1 value: 1\nkey: 2 value: 2\nkey: 3 value: 3\n";
    EXPECT_EQ(sol, m.toString());

}

// operator[] Test
TEST(mymap, operator) {

    // create a mymap
    mymap<int, int> m;

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m[1], 1);
    EXPECT_EQ(m[2], 2);
    EXPECT_EQ(m[3], 3);
    EXPECT_EQ(m[4], 0);

}

// stress test combining all the tests above
TEST(mymap, stressTest) {

    // create a mymap
    mymap<int, int> m;

    vector< int > arr;

    for (int i = 0; i < 10000; i++) {
        int num = randomInteger(0, 10000);
        // append num to arr
        arr.push_back(num);
        m.put(i, num);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m[i], arr[i]);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m.contains(i), true);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m.get(i), arr[i]);
    }

    EXPECT_EQ(m.Size(), 10000);

}

// Testing Put with random int key (Testing Size and toString)
TEST(Put, randomIntInt){

    map<int, int> m;
    mymap <int, int> mymap;
    stringstream s;

    int randomKey = 0;
    int randomValue = 0;
    int randomSize = 0;
    string test;

    for (int i = 0; i < 35; i++){

        test = "";
        s.str("");

        randomSize = randomInteger(1, 50);

        for (int p = 0; p < randomSize; p++){

            randomKey = randomInteger(0, 100);
            randomValue = randomInteger(0, 100);

            m[randomKey] = randomValue;
            mymap.put(randomKey, randomValue);

        }

        for (auto const& x : m){
            s << "key: " << x.first << " value: " << x.second << "\n";
        }

        test = mymap.toString();

        ASSERT_EQ(mymap.Size(), m.size());
        ASSERT_EQ(test, s.str());

        mymap.clear();
        m.clear();

    }

}

// Testing put with random char key (Testing Size and toString)
TEST(Put, randomCharInt){

    map<char, int> m;
    mymap <char, int> mymap;
    stringstream s;

    char randomKey = 0;
    int randomValue = 0;
    int randomSize = 0;
    string test;


    for (int i = 0; i < 35; i++){

        test = "";
        s.str("");

        randomSize = randomInteger(1, 50);

        for (int p = 0; p < randomSize; p++){

            randomKey = randomInteger(65, 90); // get uppercase characthers
            randomValue = randomInteger(0, 100);

            m[randomKey] = randomValue;
            mymap.put(randomKey, randomValue);

        }

        for (auto const& x : m){
            s << "key: " << x.first << " value: " << x.second << "\n";
        }

        test = mymap.toString();

        ASSERT_EQ(mymap.Size(), m.size());
        ASSERT_EQ(test, s.str());

        mymap.clear();
        m.clear();

    }

}

TEST(final, comprehensizeTEST1)
{
    map<char, int> mapTest;
    mymap<char, int> map1;
    vector<char> charArr;
    vector<int> intArr;
    vector<char> testVec;
    stringstream ss;
    int n = 100000;
    for (int i = 0; i < n; i++)
    {
        charArr.clear();
        intArr.clear();
        mapTest.clear();
        for (int i = 0; i < 30; i++)
        {
            charArr.push_back(randomInteger(97, 122));
            intArr.push_back(randomInteger(1, 40));
        }
        for (int i = 0; i < 30; i++)
        {
            map1.put(charArr[i], intArr[i]);
            EXPECT_TRUE(map1.contains(charArr[i]));
            EXPECT_EQ(map1.get(charArr[i]), intArr[i]);
            EXPECT_EQ(map1[charArr[i]], intArr[i]);
            mapTest[charArr[i]] = intArr[i];
        }
        EXPECT_FALSE(map1.contains('T'));
        EXPECT_EQ(map1.get('T'), {});
        EXPECT_FALSE(map1.contains('T'));
        EXPECT_EQ(map1.Size(), mapTest.size());
        ss.str("");
        testVec.clear();
        for (auto e : mapTest)
        {
            testVec.push_back(e.first);
            ss << "key: " << e.first << " value: " << e.second << endl;
        }
        int j = 0;
        for (auto b : map1)
        {
            EXPECT_EQ(testVec.at(j++), b);
        }
        EXPECT_EQ(ss.str(), map1.toString());
        mymap<char, int> mapCopy = map1;
        j = 0;
        for (auto b : mapCopy)
        {
            EXPECT_EQ(testVec.at(j++), b);
        }
        EXPECT_EQ(mapCopy.toString(), map1.toString());
        EXPECT_EQ(mapCopy.toString(), ss.str());
        EXPECT_EQ(mapCopy.Size(), map1.Size());
        mymap<char, int> mapCopy2;
        mapCopy2 = map1;
        j = 0;
        for (auto b : mapCopy2)
        {
            EXPECT_EQ(testVec.at(j++), b);
        }
        EXPECT_EQ(mapCopy2.Size(), mapCopy.Size());
        EXPECT_EQ(mapCopy2.toString(), mapCopy.toString());
        EXPECT_EQ(mapCopy2.toString(), map1.toString());
        EXPECT_EQ(mapCopy2.toString(), ss.str());
        map1.clear();
        EXPECT_EQ(map1.Size(), 0);
    }
}