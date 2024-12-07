#include <iostream>
#include <vector>
#include <functional>
#include <string>

#include "Data.hh"

// generic function comparing two values of some type T used later for int and
// double
template <class T>
bool testEqual(const std::string& name, T expected, T real) {
  if (expected != real) {
    std::cout << "(" << name << ": <" << expected << ">"
              << ", " << real << ") ";
    return false;
  }
  return true;
}

bool testReadingSize() {
  std::cout << "testReadingSize...";
  Data datA("testA");
  return testEqual<int>("size", 1, datA.size());
}

bool testReadingMeasurement() {
  std::cout << "testReadingMeasurement...";
  Data datA("testA");
  return testEqual("measurement", 10., datA.measurement(0));
}

bool testReadingBinEdges() {
  std::cout << "testReadingBinEdges...";
  Data datA("testA");
  return testEqual("bin low", 0., datA.binLow(0)) &&
         testEqual("bin high", 1., datA.binHigh(0));
}

bool testReadingErrors() {
  std::cout << "testReadingErrors...";
  Data datA("testA");
  return testEqual("error", 2., datA.error(0));
}

bool testCopyConstructor() {
  std::cout << "testCopyConstructor...";
  Data a("testA");
  Data b(a);
  Data c = a;  // equivalent to Data c(a)
  return testEqual("measurement", 10., b.measurement(0)) &&
         testEqual("measurement", 10., c.measurement(0));
}

void runTests() {
  std::cout << "running tests...\n";
  std::vector<std::function<bool()> > tests(
      {testReadingSize, testReadingMeasurement, testReadingBinEdges,
       testReadingErrors, testCopyConstructor});
  for (auto test : tests)
    std::cout << (test() ? " ok" : " FAILED!") << std::endl;
}

int main() {
  using namespace std;

  cout << "******************************************************" << endl;
  runTests();
  cout << "******************************************************" << endl;
  // create objects which hold data of experiments A, B, C, and D
  Data datA("exp_A");
  Data datB("exp_B");
  Data datC("exp_C");
  Data datD("exp_D");

  // here is the data from experiment A
  cout << "bin 27: from " << datA.binLow(27) << " to " << datA.binHigh(27)
       << endl;
  cout << "measurement of experiment A in bin 27: " << datA.measurement(27)
       << endl;
  cout << "******************************************************" << endl;
  // here is the data from experiment B
  cout << "bin 27: from " << datB.binLow(27) << " to " << datB.binHigh(27)
       << endl;
  cout << "measurement of experiment B in bin 27: " << datB.measurement(27)
       << endl;
  cout << "******************************************************" << endl;
  // here is the data from experiment C
  cout << "bin 27: from " << datC.binLow(27) << " to " << datC.binHigh(27)
       << endl;
  cout << "measurement of experiment C in bin 27: " << datC.measurement(27)
       << endl;
  cout << "******************************************************" << endl;
  // here is the data from experiment D
  cout << "bin 27: from " << datD.binLow(27) << " to " << datD.binHigh(27)
       << endl;
  cout << "measurement of experiment D in bin 27: " << datD.measurement(27)
       << endl;
  cout << "******************************************************" << endl;

  // Check compatibility for experiment A and B in bin 27
  cout << "check_compatibility_single(A,B,27,1): " << datA.check_compatibility_single(datB, 27, 1) << endl;
  cout << "******************************************************" << endl;
  
  // Check compatibility for experiment A and B for 1 to 5 standard deviations
  cout << "checkCompatibility(A, B, 1) = " << datA.checkCompatibility(datB, 1) << endl;
  cout << "checkCompatibility(A, B, 2) = " << datA.checkCompatibility(datB, 2) << endl;
  cout << "checkCompatibility(A, B, 3) = " << datA.checkCompatibility(datB, 3) << endl;
  cout << "checkCompatibility(A, B, 4) = " << datA.checkCompatibility(datB, 4) << endl;
  cout << "checkCompatibility(A, B, 5) = " << datA.checkCompatibility(datB, 5) << endl;
  cout << "******************************************************" << endl;

  // Average datasets 
  cout << "******************************************************" << endl;

  return 0;
}
