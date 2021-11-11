#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    for (int i = 0; i < 100; i++) {
      il.addFront(i);
      assert(il[0] == i);
    }

    IntList myIl(il);
    myIl = il;
    // Sequential traversal
    IntList::Node * ptr = il.head;
    assert(ptr != NULL);
    IntList::Node * ptr_ = myIl.head;
    assert(ptr_ != NULL);

    int counter = 0;
    while (ptr->next != NULL) {
      assert(ptr->data == 99 - counter);
      ptr = ptr->next;
      assert(ptr_->data == 99 - counter);
      ptr_ = ptr_->next;
      counter++;
    }
    assert(counter == 99);
    assert(ptr->next == NULL);
    assert(ptr_->next == NULL);

    // Reverse traversal
    ptr = il.tail;
    ptr_ = myIl.tail;

    while (ptr->prev != NULL) {
      assert(ptr->data == 99 - counter);
      ptr = ptr->prev;
      assert(ptr_->data == 99 - counter);
      ptr_ = ptr_->prev;
      counter--;
    }
    assert(counter == 0);
  }

  void testAddBack() {
    // WRITE ME
    IntList il;
    for (int i = 0; i < 100; i++) {
      il.addBack(i);
      assert(il[i] == i);
    }
    IntList myLi(il);
    // Sequential traversal
    IntList::Node * ptr = il.head;
    assert(ptr != NULL);

    IntList::Node * ptr_ = myLi.head;
    assert(ptr_ != NULL);

    int counter = 0;
    while (ptr->next != NULL) {
      assert(ptr->data == counter);
      ptr = ptr->next;
      assert(ptr_->data == counter);
      ptr_ = ptr_->next;
      counter++;
    }
    assert(counter == 99);
    assert(ptr->next == NULL);
    assert(ptr_->next == NULL);
    // Reverse traversal
    ptr = il.tail;
    ptr_ = myLi.tail;
    counter = 0;
    while (ptr->prev != NULL) {
      assert(ptr->data == 99 - counter);
      ptr = ptr->prev;
      assert(ptr_->data == 99 - counter);
      ptr_ = ptr_->prev;
      counter++;
    }
    assert(counter == 99);
  }

  void testRemove() {
    IntList il;
    for (int i = 0; i < 5; i++) {
      il.addBack(i);
    }

    // Remove front

    for (int i = 0; i < 5; i++) {
      il.remove(i);
      if (i != 4) {
        assert(il.head->data == i + 1);
        assert(il.head->prev == NULL);
        assert(il.getSize() == 4 - i);
      }
      else {
        assert(il.head == NULL && il.tail == NULL);
        assert(il.getSize() == 0);
      }
    }

    // addition rm

    assert(il.remove(0) == false);

    // Remove back
    for (int i = 0; i < 5; i++) {
      il.addBack(i);
    }

    for (int i = 4; i >= 0; i--) {
      il.remove(i);
      assert(il.getSize() == i);
      if (i != 0) {
        assert(il.tail->data == i - 1);
        assert(il.tail->next == NULL);
      }
      else {
        assert(il.head == NULL && il.tail == NULL);
        assert(il.getSize() == 0);
      }
    }

    // Remove middle
    for (int i = 0; i < 5; i++) {
      il.addBack(i);
    }

    il.remove(3);
    // inorder
    IntList::Node * ptr = il.head;
    int myArr[] = {0, 1, 2, 4};

    int counter = 0;
    while (ptr->next != NULL) {
      assert(ptr->data == myArr[counter]);
      ptr = ptr->next;
      counter++;
    }
    assert(counter == 3);
    assert(ptr->next == NULL);
    // reverse order
    ptr = il.tail;
    while (ptr->prev != NULL) {
      assert(ptr->data == myArr[counter]);
      ptr = ptr->prev;
      counter--;
    }
    assert(counter == 0);
    assert(ptr->prev == NULL);
    assert(il.getSize() == 4);

    IntList il_;
    il_.addBack(1);
    il_.remove(1);
    assert(il_.getSize() == 0);
    assert(il_.head == NULL);
    assert(il_.tail == NULL);

    il.remove(4);
    // inorder
    ptr = il.head;
    int myArr_[] = {0, 1, 2};

    counter = 0;
    while (ptr->next != NULL) {
      assert(ptr->data == myArr_[counter]);
      ptr = ptr->next;
      counter++;
    }
    assert(counter == 2);
    assert(ptr->next == NULL);
    // reverse order
    ptr = il.tail;
    while (ptr->prev != NULL) {
      assert(ptr->data == myArr_[counter]);
      ptr = ptr->prev;
      counter--;
    }
    assert(counter == 0);
    assert(ptr->prev == NULL);
    assert(il.getSize() == 3);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
