// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}
Train::~Train() {
  if (!first) return;
  Car *cur = first;
  do {
    Car *nxt = cur->next;
    delete cur;
    cur = nxt;
  } while (cur != first);
}
void Train::addCar(bool light) {
  Car *newCar = new Car{light, nullptr, nullptr};
  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car *last = first->prev;
    newCar->next = first;
    newCar->prev = last;
    last->next = newCar;
    first->prev = newCar;
  }
}
int Train::getLength() {
  if (!first) return 0;
  if (!first->light) {
    first->light = true;
    Car *cur = first;
    int steps = 0;
    do {
      cur = cur->next;
      ++countOp;
      ++steps;
    } while (cur != first);
    for (int i = 0; i < steps; ++i) {
      cur = cur->prev;
      ++countOp;
    }
    return steps;
  } else {
    first->light = true;
    int k = 1;
    while (true) {
      Car *cur = first;
      for (int i = 0; i < k; ++i) {
        cur = cur->next;
        ++countOp;
        cur->light = false;
      }
      for (int i = 0; i < k; ++i) {
        cur = cur->prev;
        ++countOp;
      }
      if (!first->light) {
        break;
      }
      ++k;
    }
    return k;
  }
}
int Train::getOpCount() const {
  return countOp;
}
