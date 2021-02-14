
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
    auto *curr = skip.head->forward;
    if (curr != skip.tail) {
      out << curr->value;
      curr = curr->forward;
    }
    while (curr != nullptr && curr != skip.tail) {
      out << "-->" << curr->value;
      curr = curr->forward;
    }
    out << endl;
  }
  return out;
}

SNode::SNode(int value) : value{value} {
  // if(head->forward == nullptr) {
  //   head->forward = this;
  //   this->backward = headptr;
  //   this->forward = nullptr;
  // }
}

// how many forward/backward pointers it has
int SNode::height() const { return 0; }

// increase the number of forward/backward pointers it has
void SNode::increaseHeight() {}

SkipList::SkipList(int maxLevel, int probability)
    : maxLevel{maxLevel}, probability{probability} {
  assert(maxLevel > 0 && probability >= 0 && probability < 100);
}

bool SkipList::shouldInsertAtHigher() const {
  return rand() % 100 < probability;
}

bool SkipList::add(const vector<int> &values) { return true; }

bool SkipList::add(int value) { 
  if(head == nullptr) {
    SNode *newNodePtr = new SNode(value);
    head = newNodePtr;
    newNodePtr->forward = nullptr;
    cout << "Successful add " << value << endl;
    return true;
  }

  SNode *curr = head->forward;
  SNode *prev = head;
  SNode *newNodePtr = new SNode(value);
  while(prev != nullptr) {
    if(prev->value < value && (curr == nullptr || curr->value > value)) {
      newNodePtr->backward = prev;
      newNodePtr->forward = curr;
      cout << "Successful add " << value << endl;
      return true;
    } else if (prev->value > value) {
      head = newNodePtr;
      newNodePtr->forward = prev;
      return true;
    }
    prev = curr;
    curr = curr->forward;
  }  
  return false; 
}

SkipList::~SkipList() {
  // need to delete individual nodes
}

bool SkipList::remove(int data) { return true; }

// get the node that would be before this data
// at level-0
vector<SNode *> SkipList::getBeforeNodes(int data) const {
  vector<SNode *> v(maxLevel);
  return v;
}

SNode *SkipList::containsSNode(int data) const { return nullptr; }

bool SkipList::contains(int data) const { return true; }

void SkipList::connect2AtLevel(SNode *a, SNode *b, int level) {}

void SkipList::connect3AtLevel(SNode *a, SNode *b, SNode *c, int level) {}