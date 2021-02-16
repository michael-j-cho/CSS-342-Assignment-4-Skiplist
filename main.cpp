#include <cassert>
#include <iostream>

#include "skiplist.h"

using namespace std;

void test1() {
  // setting seed for easy testing
  srand(10000);
  SkipList skp(5, 50);
  cout << boolalpha;
  skp.add(3);
  skp.add(10);
  skp.add(5);
  skp.add(7);
  skp.add(9);
  skp.add(11);
  skp.add(12);
  skp.add(13);
  skp.add(14);
  skp.add(15);
  skp.add(16);
  skp.add(18);
  skp.add(19);
  skp.add(20);
  cout << skp << endl;
  skp.remove(13);
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

void test04() {
    SkipList s(5);
    for (int i = 0; i < 20; ++i) {
        int number = rand() % 100;
        s.add(number);
        cout << "After adding " << number << endl;
        cout << s << endl;
    }
}

int main() {
//test
  test1();
  test04();

  cout << "Done." << endl;
  return 0;
}