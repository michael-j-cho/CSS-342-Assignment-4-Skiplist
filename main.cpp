#include <cassert>
#include <iostream>

#include "skiplist.h"

using namespace std;

void test1() {
  // setting seed for easy testing
  srand(10000);
  SkipList skp(5, 80);
  cout << boolalpha;
  skp.add(3);
  cout << skp << endl;
  skp.add(10);
  cout << skp << endl;
  skp.add(5);
  cout << skp << endl;
  skp.add(7);
  skp.add(11);
  skp.add(12);
  skp.add(13);
  skp.add(14);
  skp.add(15);
  skp.add(16);
  skp.add(17);
  skp.add(18);
  skp.add(19);
  skp.add(20);
  cout << skp << endl;
  skp.remove(9);
  // skp.add(vector<int>{1, 7, 9});
  // // cannot add existing
  // assert(!skp.add(vector<int>{1, 7}));
  cout << skp << endl;
  cout << "7 ? " << skp.contains(7) << endl;
  cout << "3 ? " << skp.contains(3) << endl;
  cout << "-100 ? " << skp.contains(-100) << endl;
  cout << "100 ? " << skp.contains(100) << endl;
  bool result = skp.remove(5);
  assert(result);
  result = skp.remove(5);
  assert(!result);
  cout << skp << endl;
}

int main() {
//test
  test1();

  cout << "Done." << endl;
  return 0;
}