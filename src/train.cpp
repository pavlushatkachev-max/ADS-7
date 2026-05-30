// Copyright 2021 NNTU-CS
#include "train.h"
#include <iostream>
void Train::addCar(bool light) {
  if (first == nullptr) {
    first = createCar(light);
    first->next = first;
    first->prev = first;
  } else {
    Car* item = createCar(light);
    item->prev = first->prev;
    item->next = first;
    first->prev->next = item;
    first->prev = item;
  }
}
int Train::getLength() {
    first->light = true;
    const Car* temp = first->next;
    int count = 1;
    while (temp != first) {
        if (temp->light == true) {
            countOp += (count * 2);
        }
        temp = temp->next;
        count++;
    }
    countOp += (count * 2);
    return count;
}
int Train::getOpCount() {
  return countOp;
}
