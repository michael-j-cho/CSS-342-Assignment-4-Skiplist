
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
      out << to_string(curr->value) + " --> ";    
      curr = curr->next;
    }
    out << "\n";
  }
  return out;
}

SNode::SNode(int value) : value{value}, next{nullptr}, prev{nullptr}, 
up{nullptr}, down{nullptr} {}

SkipList::SkipList(int maxLevel, int probability)
    : maxLevel{maxLevel}, probability{probability} {
  assert(maxLevel > 0 && probability >= 0 && probability < 100);
  // dynamically allocate frontGuards and rearGuards arrays
  // test comment
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

bool SkipList::add(int value) { 
  if(contains(value)) {
    return false;
  }
  int level = 0;
  addAtLevel(value, level);
  return true;
}

void SkipList::addAtLevel(int value, int level) {
  SNode *newNode = new SNode(value);
  SNode *curr = frontGuard[level];
  SNode *prev = frontGuard[level];

  while(curr->value < value && curr->next != nullptr) {
    curr = curr->next;
  }
  connectAtLevel(prev, curr, newNode);
  level++;
    if(shouldInsertAtHigher() && level < maxLevel) {
      addAtLevel(value, level);
      connectBelow(newNode, level);
    }
}

void SkipList::connectAtLevel(SNode *prev, SNode *curr, SNode *newNode) {
    prev = curr->prev; 
    prev->next = newNode;
    newNode->prev = prev;
    newNode->next = curr;
    curr->prev = newNode;   
}

void SkipList::connectBelow(SNode *node, int level) {
  SNode *currBelow = frontGuard[level - 1];
  while(currBelow != nullptr) {
    if(currBelow->value == node->value) {
      node->up = currBelow;
      currBelow->down = node;
    }
    currBelow = currBelow->next;
  }
}

SkipList::~SkipList() {
  clear();
}

void SkipList::clear() {
  SNode *curr;
  for(int i = maxLevel - 1; i >= 0; i--) {
    curr = frontGuard[i];
    while(curr->next != nullptr) {
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

bool SkipList::remove(int data) { 
  if(!contains(data)) {
    return false;
  }
  SNode *curr;
  for(int i = 0; i < maxLevel; i++) {
    curr = frontGuard[i];
    while(curr->next != nullptr) {
      curr = curr->next;
      if(curr->value == data) {
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

bool SkipList::contains(int data) const { 
  SNode *curr;
  for(int i = maxLevel - 1; i >=0; i--) {
    curr = frontGuard[i];
    while(curr != nullptr && curr->value < data) {
      curr = curr->next;
      if(curr->value == data) {
        return true;
      }
    }
  }
  return false; 
}
