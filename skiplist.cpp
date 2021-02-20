/** Michael Cho 2/19/21
 * CSS342
 *
 * This is the skiplist implementation file. It contains the methods
 * to construct a skiplist, as well as display, navigate, add, remove,
 * and connect nodes in the list. There are also a few various helper
 * methods.
 * */

#include "skiplist.h"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

using namespace std;

/** Overloaded << operator prints out the SkipList at every level.
Precondition: SkipList must be instantiated.
Postcondition: Prints SkipList to the console.*/
ostream &operator<<(ostream &out, const SkipList &skip) {
  for (int i = skip.maxLevel - 1; i >= 0; i--) {
    out << "Level: " + to_string(i) + " -- ";
    SNode *curr = skip.frontGuard[i];
    while (curr != nullptr) {
      out << to_string(curr->value) + ", ";
      curr = curr->next;
    }
    out << "\n";
  }
  return out;
}

/** Constructor: Creates an SNode object with a specified value.
All pointers are set to nullptr.
Precondition: None.
Postcondition: Creates SNode obj with value.*/
SNode::SNode(int value)
    : value{value}, next{nullptr}, prev{nullptr}, up{nullptr}, down{nullptr} {}

/** Constructor: Creates a SkipList object and creates array containers
for the pointers. Sets the front and rear of each level array to
INT_MIN and INT_MAX and connects each pointer horizontally and vertically.
Precondition: None.
Postcondition: Creates specified level of arrays and connects "guards".*/
SkipList::SkipList(int maxLevel, int probability)
    : maxLevel{maxLevel}, probability{probability} {
  assert(maxLevel > 0 && probability >= 0 && probability <= 100);

  // Creates an array of front and rear guards depending on the
  // specified depth level.
  frontGuard = new SNode *[maxLevel];
  rearGuard = new SNode *[maxLevel];

  // Initializes each front and rear guard at each level with
  // INT_MAX and INT_MIN respectively. Then, connects the front
  // and rear.
  for (int i = 0; i < maxLevel; i++) {
    frontGuard[i] = new SNode(INT_MIN);
    rearGuard[i] = new SNode(INT_MAX);
    frontGuard[i]->next = rearGuard[i];
    rearGuard[i]->prev = frontGuard[i];
  }

  // Connects each level vertically.
  for (int i = 0; i < maxLevel - 1; i++) {
    frontGuard[i]->up = frontGuard[i + 1];
    frontGuard[i + 1]->down = frontGuard[i];
    rearGuard[i]->up = rearGuard[i + 1];
    rearGuard[i + 1]->down = rearGuard[i];
  }
}

/** Destructor: Calls the clear method.
Precondition: SkipList object must exist.
Postcondition: Deletes the SkipList object with the clear method.*/
SkipList::~SkipList() { clear(); }

/** Clear: Deletes each dynamically created SNode in the SkipList
object and sets each one to nullptr. Then, deletes the dynamically
created frontGuard and rearGuard arrays.
Precondition: SkipList object must exist.
Postcondition: Deletes all SNodes, frontGuard, and rearGuard.*/
void SkipList::clear() {
  SNode *curr;
  for (int i = maxLevel - 1; i >= 0; i--) {
    curr = frontGuard[i];
    while (curr->next != nullptr) {
      curr = curr->next;
      delete curr->prev;
      curr->prev = nullptr;
    }
    delete curr;
    curr = nullptr;
  }
  delete[] frontGuard;
  delete[] rearGuard;
}

/** Boolean to determine if value should be inserted at a higher level.
Precondition: SkipList object must exist.
Postcondition: Returns true if random number is less than probability.*/
bool SkipList::shouldInsertAtHigher() const {
  return rand() % 100 < probability;
}

/** Boolean that calls the methods to check for duplicates and adds value
at level 0 if value does not already exist.
Precondition: SkipList object must exist.
Postcondition: Returns true add is successful.*/
bool SkipList::add(int value) {
  if (contains(value)) {
    return false;
  }
  int level = 0;
  addAtLevel(value, level);
  return true;
}

/** Method that creates a new SNode with specified value and adds that SNode
at a specified level. This method recursively calls itself to add at higher
levels if necessary.
Precondition: SkipList object must exist.
Postcondition: Adds a new node at the specified level.*/
void SkipList::addAtLevel(int value, int level) {
  SNode *newNode = new SNode(value);
  SNode *curr = frontGuard[level];

  // Traversing through the nodes at current level.
  while (curr->value < value && curr->next != nullptr) {
    curr = curr->next;
  }

  // When the correct position in the list is found, calls addBefore
  // method to link nodes together.
  addBefore(curr, newNode);
  assert(newNode->next == curr && curr->prev == newNode);
  assert(newNode->prev != nullptr && newNode->prev->value < newNode->value);
  level++;

  // Check whether to increase depth of skiplist.
  if (shouldInsertAtHigher() && level < maxLevel) {
    addAtLevel(value, level);
    connectLevels(newNode, level);
  }
}

/** Method that links nodes in correct order horizontally when adding a new
value. 
Precondition: SkipList object must exist. 
Postcondition: Inserts a node before the current node.*/
void SkipList::addBefore(SNode *curr, SNode *newNode) {
  assert(newNode != nullptr && newNode->value < curr->value);
  newNode->prev = curr->prev;
  curr->prev->next = newNode;
  newNode->next = curr;
  curr->prev = newNode;
}

/** Method that connects levels vertically. Creates a node below the current
level that finds the same value and connects the two levels.
Precondition: SkipList object must exist. Value must exit on both levels.
Postcondition: Connects node below with node above.*/
void SkipList::connectLevels(SNode *node, int level) {
  SNode *nodeBelow = frontGuard[level - 1];
  while (nodeBelow != nullptr) {
    if (nodeBelow->value == node->value) {
      nodeBelow->up = node;
      node->down = nodeBelow;
      break;
    }
    nodeBelow = nodeBelow->next;
  }
}

/** Method that removes a single value throughout the skiplist. Uses the
contains method to check whether the value exists in the list. Then, goes
through each level and deletes the node with the specified value data. Also,
deletes the pointer and sets to nullptr. 
Precondition: SkipList object must        exist. 
Postcondition: Returns true removed successfully.*/
bool SkipList::remove(int data) {
  if (!contains(data)) {
    return false;
  }
  SNode *curr;
  for (int i = 0; i < maxLevel; i++) {
    curr = frontGuard[i];
    while (curr->next != nullptr) {
      curr = curr->next;
      if (curr->value == data) {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        break;
      }
    }
  }
  curr = nullptr;
  return true;
}

/** Boolean method that checks whether a particular value exists within the
list. Method searches throughout the list with the order of logN by going from
highest level of the list down. 
Precondition: SkipList object must exist.
Postcondition: Returns true the value is found.*/
bool SkipList::contains(int data) const {
  SNode *curr;
  for (int i = maxLevel - 1; i >= 0; i--) {
    curr = frontGuard[i];
    while (curr != nullptr && curr->value < data) {
      curr = curr->next;
      if (curr->value == data) {
        return true;
      }
    }
  }
  return false;
}
