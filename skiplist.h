/** Michael Cho 2/19/21
 * CSS342
 * 
 * SkipList class header file 
 * */

#ifndef ASS4_SKIPLIST_H
#define ASS4_SKIPLIST_H

#include <iostream>
#include <vector>

using namespace std;

class SkipList;

class SNode {
  friend class SkipList;
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  /** Constructor: Creates an SNode object with a specified value.
  All pointers are set to nullptr.
  Precondition: None.
  Postcondition: Creates SNode obj with value. */
  explicit SNode(int value);

  // Value contained in the object
  int value{0};

  // Link to the next SNode
  SNode * next;

  // Link to the previous SNode
  SNode * prev;
   
  // Link to the SNode above
  SNode * up;

  // Link to the SNode below
  SNode * down;
};

class SkipList {
  /** Overloaded << operator prints out the SkipList at every level.
  Precondition: SkipList must be instantiated.
  Postcondition: Prints SkipList to the console.*/
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  // Maximum number of levels
  int maxLevel;

  // Probability of inserting at a higher level
  // as an integer between 0% and 100% (exclusive)
  int probability;

  // Array of front guards that start at INT_MIN
  // which is the beginning of each level.
  SNode **frontGuard;

  // Array of rear guards that start at INT_MAX
  // which is the end of each level.
  SNode **rearGuard;

  /** Boolean to determine if value should be inserted at a higher level.
  Precondition: SkipList object must exist.
  Postcondition: Returns true if random number is less than probability.*/
  bool shouldInsertAtHigher() const;

public:
  /** Constructor: Creates a SkipList object and creates array containers
  for the pointers. Sets the front and rear of each level array to
  INT_MIN and INT_MAX and connects each pointer horizontally and vertically.
  Default depth is 1 and default probability is 50%.
  Precondition: None.
  Postcondition: Creates specified level of arrays and connects "guards". */
  explicit SkipList(int maxLevel = 1, int probability = 50);

  /** Destructor: Calls the clear method.
  Precondition: SkipList object must exist.
  Postcondition: Deletes the SkipList object with the clear method. */
  virtual ~SkipList();

  /** Clear: Deletes each dynamically created SNode in the SkipList
  object and sets each one to nullptr. Then, deletes the dynamically
  created frontGuard and rearGuard arrays.
  Precondition: SkipList object must exist.
  Postcondition: Deletes all SNodes, frontGuard, and rearGuard. */
  void clear();

  // Copy not allowed
  SkipList(const SkipList &other) = delete;

  // Move not allowed
  SkipList(SkipList &&other) = delete;

  // Assignment not allowed
  SkipList &operator=(const SkipList &other) = delete;

  // Move assignment not allowed
  SkipList &operator=(SkipList &&other) = delete;

  /** Boolean that calls the methods to check for duplicates and adds value
  at level 0 if value does not already exist.
  Precondition: SkipList object must exist.
  Postcondition: Returns true add is successful.*/
  bool add(int value);

  /** Method that creates a new SNode with specified value and adds that SNode
  at a specified level. This method recursively calls itself to add at higher
  levels if necessary.
  Precondition: SkipList object must exist.
  Postcondition: Adds a new node at the specified level. */
  void addAtLevel(int value, int level);

  /** Method that links nodes in correct order horizontally when adding a new
  value. Precondition: SkipList object must exist. Postcondition: Inserts a node
  before the current node. */
  void addBefore(SNode *curr, SNode *newNode);

  /** Method that connects levels vertically. Creates a node below the current
  level that finds the same value and connects the two levels. Precondition:
  SkipList object must exist. Value must exit on both levels. Postcondition:
  Connects node below with node above.*/
  void connectLevels(SNode *node, int level);

  /** Method that removes a single value throughout the skiplist. Uses the
  contains method to check whether the value exists in the list. Then, goes
  through each level and deletes the node with the specified value data. Also,
  deletes the pointer and sets to nullptr. Precondition: SkipList object must
  exist. Postcondition: Returns true removed successfully.*/
  bool remove(int data);

  /** Boolean method that checks whether a particular value exists within the
  list. Method searches throughout the list with the order of logN by going from
  highest level of the list down. Precondition: SkipList object must exist.
  Postcondition: Returns true the value is found.*/
  bool contains(int data) const;
};

#endif // ASS4_SKIPLIST_HI t