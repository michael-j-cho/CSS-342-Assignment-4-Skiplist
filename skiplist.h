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

// only SkipList class can create SNode objects

class SkipList;

class SNode {
  friend class SkipList;
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  // constructor
  explicit SNode(int value);

  // data contained in the object
  int value{0};

  // link to Next SNode 
  SNode * next;

  // link to Prev SNode
  SNode * prev;
   
  //link to up node 
  SNode * up;

  // link to down SNode
  SNode * down;
};

class SkipList {
  // display with level
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  // maximum number of levels
  int maxLevel;

  // probability of inserting at a higher level
  // as an integer between 0% and 100% (exclusive)
  int probability;

  SNode **frontGuard;

  SNode **rearGuard;

  // return true p% of time,
  // for p = 50, each node has a 50% chance of being at higher level
  bool shouldInsertAtHigher() const;

public:
  // default SkipList has only 1 level, just one doubly-linked list
  explicit SkipList(int maxLevel = 1, int probability = 50);

  // destructor
  virtual ~SkipList();

  void clear();

  // copy not allowed
  SkipList(const SkipList &other) = delete;

  // move not allowed
  SkipList(SkipList &&other) = delete;

  // assignment not allowed
  SkipList &operator=(const SkipList &other) = delete;

  // move assignment not allowed
  SkipList &operator=(SkipList &&other) = delete;

  // return true if successfully added, no duplicates allowed
  bool add(int value);

  void addAtLevel(int value, int level);

  void addBefore(SNode *curr, SNode *newNode);

  void connectLevels(SNode *node, int level);

  // return true if successfully removed
  bool remove(int data);

  // return true if found in SkipList
  bool contains(int data) const;
};

#endif // ASS4_SKIPLIST_HI t