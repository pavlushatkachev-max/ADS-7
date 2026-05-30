// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) return;
    Car* cur = first;
    Car* nxt;
    do {
        nxt = cur->next;
        delete cur;
        cur = nxt;
    } while (cur != first);
}

void Train::addCar(bool light) {
    Car* wagon = new Car;
    wagon->light = light;
    wagon->next = nullptr;
    wagon->prev = nullptr;

    if (!first) {
        first = wagon;
        wagon->next = wagon;
        wagon->prev = wagon;
        return;
    }

    Car* back = first->prev;
    wagon->next = first;
    wagon->prev = back;
    back->next = wagon;
    first->prev = wagon;
}

void Train::goNext(Car*& pos) {
    pos = pos->next;
    ++countOp;
}

void Train::goPrev(Car*& pos) {
    pos = pos->prev;
    ++countOp;
}

int Train::getLength() {
    if (!first) return 0;
    resetCounter();
    Car* here = first;
    if (!here->light) here->light = true;
    int dist = 0;
    bool solved = false;

    while (!solved) {
        dist = 0;
        do {
            goNext(here);
            ++dist;
        } while (!here->light);
        here->light = false;
      
        for (int i = 0; i < dist; ++i)
            goPrev(here);
        if (!here->light)
            solved = true;
    }
    return dist;
}

int Train::getOpCount() const {
    return countOp;
}
