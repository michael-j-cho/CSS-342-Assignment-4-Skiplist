/** Michael Cho 2/19/21
 * CSS342
 *
 * This is the main driver file that is running the tests.
 * */

#include "skiplist.h"
#include <cassert>
#include <iostream>

using namespace std;

/** Test. Creates a SkipList object skp with 5 levels
and 80 percent probability. Adds various values into
the skiplist and checks the contains and remove methods. */
void test1() {
  srand(10000);
  SkipList skp(5, 80);
  cout << boolalpha;
  skp.add(3);
  skp.add(5);
  skp.add(9);
  skp.add(17);
  skp.add(13);
  skp.add(33);
  skp.add(2);
  cout << skp << endl;
  assert(skp.contains(2));
  assert(!skp.contains(300));
  cout << "7 ? " << skp.contains(7) << endl;
  cout << "3 ? " << skp.contains(3) << endl;
  cout << "-100 ? " << skp.contains(-100) << endl;
  cout << "100 ? " << skp.contains(100) << endl << endl;
  bool result = skp.remove(5);
  assert(result);
  result = skp.remove(5);
  assert(!result);
  cout << skp << endl;
}

/** Test. Creates a SkipList object s with 4 levels
and 50 percent probability. Uses a for loop for randomly
generate 40 numbers to enter into the skiplist. Displays
the skiplist after each added value. */
void test2() {
  SkipList s(4);
  for (int i = 0; i < 20; ++i) {
    int number = rand() % 100;
    s.add(number);
    cout << "After adding " << number << endl;
    cout << s << endl;
  }
}

/** Test. Creates a SkipList object s with 5 levels
and 100 percent probability. Uses a for loop for randomly
generate 20 numbers to enter into the skiplist. Displays
he skiplist after each added value. This skiplist should
add the same value at every depth level because of 100%
probability.*/
void test3() {
  SkipList s(5, 100);
  for (int i = 0; i < 20; ++i) {
    int number = rand() % 100;
    s.add(number);
  }
  cout << s << endl;
}

/** Test. Creates a SkipList object s with the default depth
level and probability (1, 50). 20 numbers are randomly
generated. All values will be on a single level.*/
void test4() {
  SkipList s;
  for (int i = 0; i < 20; ++i) {
    int number = rand() % 100;
    s.add(number);
  }
  cout << s << endl;
}

int main() {
  test1();
  test2();
  test3();
  test4();
  cout << "Done." << endl;
  return 0;
}