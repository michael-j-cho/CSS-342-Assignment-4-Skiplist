
//

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

ostream &operator<<(ostream &out, const SkipList &skip) {
  for (int d = skip.maxLevel - 1; d >= 0; d--) {
    out << d << ": ";
    SNode *curr = skip.head->next;
    if (curr != skip.tail) {
      out << curr->value;
      curr = curr->next;
    }
    while (curr != nullptr && curr != skip.tail) {
      out << "-->" << curr->value;
      curr = curr->next;
    }
    out << endl;
  }
  return out;
}

SNode::SNode(int value) : value{value}{}

// how many next/prev pointers it has
int SNode::height() const { return 0; }

// increase the number of next/prev pointers it has
void SNode::increaseHeight() {}

SkipList::SkipList(int maxLevel, int probability)
    : maxLevel{maxLevel}, probability{probability} {
  assert(maxLevel > 0 && probability >= 0 && probability < 100);
  head = new SNode(INT_MIN);
  tail = new SNode(INT_MAX);
  head->next = tail;
  head->prev = nullptr;
  tail->next = nullptr;
  tail->prev = head;
}

bool SkipList::shouldInsertAtHigher() const {
  return rand() % 100 < probability;
}

bool SkipList::add(const vector<int> &values) { return true; }

bool SkipList::add(int value) { 
  if(contains(value)) {
    return false;
  }

  SNode *newNodePtr = new SNode(value);
  SNode *curr = head;
  SNode *prev = head;
  
  while(curr->value < value) {
    curr = curr->next;
  }
  if(curr->value > value && curr->prev->value < value) {
    prev = curr->prev;
    prev->next = newNodePtr;
    newNodePtr->prev = prev;
    newNodePtr->next = curr;
    curr->prev = newNodePtr;
    return true;
  }
  return false;
}

SkipList::~SkipList() {
  // need to delete individual nodes
}

bool SkipList::remove(int data) { 
  if(!contains(data)) {
    return false;
  }
  SNode *curr = head;
  while(curr != nullptr) {
    if(curr->value == data){
      curr->prev->next = curr->next;
      // delete??
    }
    curr = curr->next;
  }
return true; 
}

// get the node that would be before this data
// at level-0
vector<SNode *> SkipList::getBeforeNodes(int data) const {
  vector<SNode *> v(maxLevel);
  return v;
}

SNode *SkipList::containsSNode(int data) const { return nullptr; }

bool SkipList::contains(int data) const { 
  SNode *curr = head;
  while(curr != nullptr) {
    if(curr->value == data) {
      return true;
    }
    curr = curr->next;
  }
return false; 
}

void SkipList::connect2AtLevel(SNode *a, SNode *b, int level) {}

void SkipList::connect3AtLevel(SNode *a, SNode *b, SNode *c, int level) {}