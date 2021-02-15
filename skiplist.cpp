
//

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

ostream &operator<<(ostream &out, const SkipList &skip) {
  for (int i = skip.maxLevel - 1; i >= 0; i--) {
    out << "Level: " + to_string(i) + " -- ";
    SNode* curr = skip.frontGuard[i];
    while(curr != nullptr) {
      if(curr->value > INT_MIN && curr->value < INT_MAX) {
        out << to_string(curr->value) + " --> ";    
      }
    curr = curr->next;
    }
    out << "\n";
  }
  return out;
}

SNode::SNode(int value) : value{value}, next{nullptr}, prev{nullptr}, 
up{nullptr}, down{nullptr} {}

// how many next/prev pointers it has
int SNode::height() const { return 0; }

// increase the number of next/prev pointers it has
void SNode::increaseHeight() {}

SkipList::SkipList(int maxLevel, int probability)
    : maxLevel{maxLevel}, probability{probability} {
  assert(maxLevel > 0 && probability >= 0 && probability < 100);
  // dynamically allocate frontGuards and rearGuards arrays
  frontGuard = new SNode *[maxLevel];
  rearGuard = new SNode *[maxLevel];

  for(int i = 0; i < maxLevel; i++) {
    frontGuard[i] = new SNode(INT_MIN);
    rearGuard[i] = new SNode(INT_MAX);
    frontGuard[i]->next = rearGuard[i];
    rearGuard[i]->prev = frontGuard[i];
  }

  for(int i = 0; i < maxLevel-1; i++) {
    frontGuard[i]->up = frontGuard[i+1];
    frontGuard[i+1]->down = frontGuard[i];
    rearGuard[i]->up = rearGuard[i+1];
    rearGuard[i+1]->down = rearGuard[i];
  }
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
  SNode *curr = frontGuard[0];
  SNode *prev = frontGuard[0];
  
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
  clear();
}

void SkipList::clear() {
  // SNode *curr = head;
  // while(curr->next != nullptr) {
  //   delete curr;
  //   cout << "Deleting " << curr->value << endl;
  //   curr = curr->next;
  // }
  // head = nullptr;
  // // nodeToDeletePtr = nullptr;
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
  
  for(int i = 0; i < maxLevel; i++) {
    SNode *curr = frontGuard[i];
    while(curr != nullptr) {
      if(curr->value == data) {
        return true;
      }
    curr = curr->next;
  }
  return false; 
  }
}

void SkipList::connect2AtLevel(SNode *a, SNode *b, int level) {}

void SkipList::connect3AtLevel(SNode *a, SNode *b, SNode *c, int level) {}