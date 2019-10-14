//hw02-maxvalue.cpp
//By Andy Hudson
// NOTE: Using any of the 4 methods with an array of size 1 will pair the element provided with a copy of itself!

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

/**
 * This function returns the maximum a[j]+a[i] of a pair elements (as described in Ex 2.28a)
 * @param values positive input values
 * @return the maximum result
 */
int maxPlus(vector<int> values) {
    if (values.size() == 0)
        return -1;

    int largest = 0;

    for (int i = 0; i < values.size(); ++i)
        if (values[i] > largest)
            largest = values[i];

    return largest + largest;
}

/**
 * This function returns the maximum a[j]-a[i] of a pair elements (as described in Ex 2.28b)
 * @param values positive input values
 * @return the maximum result
 */
int maxMinus(vector<int> values) {
    if (values.size() == 0)
        return -1;

    int largest = 0;
    int largestIndex = 0;
    int smallest = 0;

    //find largest
    for (int i = 0; i < values.size(); ++i) {
        if (values[i] > largest) {
            largest = values[i];
            largestIndex = i;
        }
    }
    //use largest as bound to find smallest (as opposed to using infinity as an upper bound for smallest)
    smallest = largest;
    for (int i = 0; i <= largestIndex; ++i) {
        if (values[i] < smallest)
            smallest = values[i];
    }

    if (values.size() == 1)
        return 0;
    else
        return largest - smallest;
}

/**
 * This function returns the maximum a[j]*a[i] of a pair elements (as described in Ex 2.28c)
 * @param values positive input values
 * @return the maximum result
 */
int maxProduct(vector<int> values) {
    if (values.size() == 0)
        return -1;

    int largest = 0;
    //int nextLargest = 1;

    for (int i = 0; i < values.size(); ++i)
        if (values[i] > largest)
            largest = values[i];
    /*
    for (int i = 0; i < values.size(); ++i) {
        if (values[i] > largest) {
            nextLargest = largest;
            largest = values[i];
        }
        else if (values[i] >= nextLargest)
            nextLargest = values[i];
    }
    */
    //if (values.size() == 1)
        return largest * largest;
    //else
        //return largest * nextLargest;
}

/**
 * This function returns the maximum a[j]/a[i] of a pair elements (as described in Ex 2.28c)
 * @param values positive input values
 * @return the maximum result
 */
int maxDivide(vector<int> values) {
    if (values.size() == 0)
        return -1;

    int largest = 0;
    int smallest = 1;
    int largestIndex = 0;

    //find largest
    for (int i = 0; i < values.size(); ++i) {
        if (values[i] > largest){
            largest = values[i];
            largestIndex = i;
        }
    }
    //use largest as bound to find smallest (as opposed to using infinity as an upper bound for smallest)
    smallest = largest;
    for (int i = 0; i <= largestIndex; ++i) {
        if (values[i] < smallest)
            smallest = values[i];
    }

    if (values.size() == 1)
        return 1;
    else
        return largest / smallest;
}

int main(int argc, char* argv[]) {
    //Use clog for your debugging output
    clog << "This program runs from " << argv[0] << endl;
    if (argc < 2) {
        //Use cerr for error messages
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
            cout << "Sum : " << maxPlus(testVector) << endl;
            cout << "Diff: " << maxMinus(testVector) << endl;
            cout << "Prod: " << maxProduct(testVector) << endl;
            cout << "Div : " << maxDivide(testVector) << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }
    } else {
        cerr << "Can't open data file " << argv[1] << endl;
    }
    return 0;
}
