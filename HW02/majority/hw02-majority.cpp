#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

/**
 * The following recursive function returns the majority element in a vector of integers
 * @param a input vector consisting of positive integers
 * @return the majority element or -1 if none is found
 */

int majority (vector<int> a)
{
    int vectorSize = a.size();
    int counter = 0;
    if (vectorSize == 1)
        return a[0];

    bool odd = (vectorSize % 2 == 1);
    vector<int> b;

    if (a.size() == 3) {
        if (a[0] == a[1])
            return a[0];
        if (a[1] == a[2])
            return a[1];
        if (a[0] == a[2])
            return a[2];
        return -1;
    }
    else
        for (int pos = 0; pos < vectorSize; pos+=2) {
            if ((pos == vectorSize - 1 && odd && counter > 0) || a[pos] == a[pos+1])
                {
                counter++;
                b.push_back(a[pos]);
                }

    }
    if (b.size() == 0)
        return -1;
    /* write your code here, based on the detailed explanation of exercise 2.26 */
    // Using clog for debugging output
    clog << "Input vector is: ";
    for (auto& x : a)
        clog << x << " ";
    clog << endl;
    return majority(b);
}

int main(int argc, char* argv[]) {
    //Use clog for your debugging output
    clog << "This program runs from " << argv[0] << endl;
    if (argc < 2) {
        cerr << "Missing filename argument" << endl;
        exit (0);
    }

    /* The first command line argument is the input filename */
    ifstream inputfile {argv[1]};   /* input file stream */
    if (inputfile.good()) {
        int num_test, num_items_per_test;
        vector<int> testVector;

        inputfile >> num_test;  // read the number of test cases

        //Use clog for your debugging
        clog << "Number of test cases: " << num_test << endl;
        for (int k = 0; k < num_test; k++) {
            inputfile >> num_items_per_test;
            clog << "Test " << k << " has " << num_test << " data items" << endl;
            testVector.clear();
            for (int m = 0; m < num_items_per_test; m++) {
                int val;
                inputfile >> val;
                testVector.push_back(val);
            }
            // Use cout for the ACTUAL output
            cout << "Majority: " << majority(testVector) << endl;
        }
    } else {
        cerr << "Can't open data file " << argv[1] << endl;
    }
    return 0;
}
