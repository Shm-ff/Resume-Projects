#include <iostream>
#include "bar.h"
using namespace std;


bool testBarDefaultConstructor() {
	Bar b;
    if (b.getName() != "") {
    	cout << "testBarDefaultConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 0) {
    	cout << "testBarDefaultConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "") {
    	cout << "testBarDefaultConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarParamConstructor() {
	Bar b("Chicago", 9234324, "US");
    if (b.getName() != "Chicago") {
    	cout << "testBarParamConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 9234324) {
    	cout << "testBarParamConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "US") {
    	cout << "testBarParamConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarParamConstructor: all passed!" << endl;
    return true;
}

bool milestone1test() {
	Bar b1("pistons", 42069, "NBA");
	Bar b2("Cloud9", 1993, "0-3");
	if (b1 < b2) {
		cout << "< doesn't work" << endl;
	}
	else {
		cout << "< works" << endl;
	}
	Bar b3("EG", 2003, "0-3");
	Bar b4("NRG", 2022, "0-3");
	if (b3 > b4) {
		cout << "> doesn't work" << endl;
	}
	else {
		cout << "> works" << endl;
	}
	Bar b5("SKT T1", 2022, "3-0");
	Bar b6("Gen.G", 2022, "3-0");
	if ( b5 >= b6) {
		if (b4 >= b3) {
			cout << ">= works" << endl;
		}
	}
	else {
		cout << ">= doesn't work" << endl;
	}
	if ( b5 <= b6) {
		if (b3 <= b4) {
			cout << "<= works" << endl;
		}
	}
	else {
		cout << "<= doesn't work" << endl;
	}
	return true;
}

int main() {
	testBarDefaultConstructor();
	testBarParamConstructor();
	milestone1test();
	
    return 0;
}