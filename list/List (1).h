#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL

template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface

public:
  //default constructor 
  List(): first(nullptr),last(nullptr), listsize(0){}

  //destructor 
  ~ List() {
    clear();
  }
  //copy constructor 
  List(const List &list): first(nullptr), last(nullptr), listsize(0){copy_all(list);}

  //overload assignment operator = 
  List operator= (const List &rhs){
      if (this == &rhs) {
        return *this; 
       }
      else {
        clear(); 
        copy_all(rhs);
        return *this;
      }
  }

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return (size()==0);
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const {
    return listsize; 
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    assert(!empty());
    return last->datum; 
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    Node *new_node = new Node; 
    new_node->datum = datum;
    new_node->next = first;
    new_node->prev = nullptr;
    first = new_node;
    if (last==nullptr) {
      last = new_node;
    } else {
     new_node->next->prev= new_node;
    }
    listsize++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    Node *new_node = new Node; 
    new_node->datum = datum;
    new_node->next = nullptr;
    new_node->prev = last;
    if (empty()) {
      first = last = new_node;
    } else {
      last = last->next = new_node;
    }
    listsize++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    assert(!empty());
    if (size()==1) {
      delete first; 
      first = last = nullptr; 
    } else {
      Node *victim = first;  // temporary keeps track of new first
      first=first->next;
      first->prev=nullptr;
      delete victim;
    }
    listsize--;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(!empty()); 
    if (size()==1) {
      delete last; 
      last = first = nullptr; 
    } else {
      Node* victim=last;
      last=last->prev;
      last->next=nullptr;
      delete victim;
    }
    listsize--;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
    if(empty()) return;
    Node *new_first = first;
    while (new_first) {
      Node *temp = new_first -> next; 
      delete new_first; 
      new_first = temp; 
    }
    first = last = nullptr; 
    listsize=0;
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    assert(empty());
    Node *temp = other.first; 
    while(temp){
      push_back(temp->datum);
      temp = temp->next;
    }

  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int listsize;
public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
  //constructors
  //default, and there is another constructor implemented in the private
  //member section.
    Iterator(): node_ptr(nullptr) {}

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    T& operator *()const{
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator& operator ++(){
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    bool operator==(Iterator rhs)const{
      return node_ptr == rhs.node_ptr;
    }

    bool operator!=(Iterator rhs)const{
      return node_ptr != rhs.node_ptr;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    //private ctor
    Iterator(Node *p):node_ptr(p){}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
    assert(i.node_ptr);
    if (size()==1) {
      pop_front();
    } 
    else if(first==i.node_ptr){
      pop_front();
    }
    else if((i.node_ptr)->next==nullptr){
      pop_back();
    }
    else{
      ((i.node_ptr)->prev)->next = (i.node_ptr)->next;
      ((i.node_ptr)->next)->prev = (i.node_ptr)->prev;
      delete i.node_ptr;
      listsize=listsize-1;
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){
    if(size()==0){
      push_front(datum);
    }
    else{
    if(first==i.node_ptr){
      push_front(datum);
    }
    else if(i.node_ptr==nullptr){
      push_back(datum);
    }
    else{
      listsize=listsize+1;
      Node *new_node = new Node;
      new_node->datum=datum;
      new_node->next=i.node_ptr;
      new_node->prev=(i.node_ptr)->prev;
      ((i.node_ptr)->prev)->next=new_node;
      (i.node_ptr)->prev=new_node;
    }
    }
  }

};//List




////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
