// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>

using namespace std;

TEST(test_stub) {
    // Add your tests here
    ASSERT_TRUE(true);
}

TEST(test_empty){
    BinarySearchTree<int> t; 
    ASSERT_TRUE(t.empty()); 
    ASSERT_TRUE(t.size() == 0); 
    ASSERT_TRUE(t.height() == 0); 
    ASSERT_TRUE(t.check_sorting_invariant()); 
    // how to test min & max here? 
  ostringstream oss_preorder;
  t.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "");

  ostringstream oss_inorder;
  t.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "");
}

TEST(test_general){
    BinarySearchTree<int> t;
    ASSERT_TRUE(t.empty()); 
    t.insert(0);

    ASSERT_TRUE(!t.empty()); 
    ASSERT_TRUE(t.size() == 1); 
    ASSERT_TRUE(t.height() == 1); 
    ASSERT_TRUE(t.check_sorting_invariant());    
    ASSERT_EQUAL(*t.min_element(), 0);
    ASSERT_EQUAL(*t.max_element(), 0);
    ASSERT_TRUE(*t.find(0) == 0);

    t.insert(1);
    t.insert(2);
    t.insert(4);
    t.insert(-2);

    // test basic cases 
    ASSERT_TRUE(!t.empty()); 
    ASSERT_TRUE(t.size() == 5); 
    ASSERT_TRUE(t.height() == 4); 
    ASSERT_TRUE(t.check_sorting_invariant());    
    ASSERT_EQUAL(*t.min_element(), -2);
    ASSERT_EQUAL(*t.max_element(), 4);
    ASSERT_TRUE(*t.find(2) == 2);

    // test min_greater_than 
    // nullptr 
    // < node 
    // = node 
    // > node 
    ASSERT_EQUAL(*t.min_greater_than(0), 1);
    ASSERT_EQUAL(*t.min_greater_than(3), 4);
    ASSERT_EQUAL(*t.min_greater_than(-1), 0);
    ASSERT_EQUAL(*t.min_greater_than(-3), -2);
    ASSERT_EQUAL(*t.min_greater_than(2), 4);
}

TEST(test_ctor){
    //ctor 1
    BinarySearchTree<double> t;   
    t.insert(0.2);
    t.insert(1.2);
    t.insert(2.1);
    t.insert(4.0);
    t.insert(-2.5);  
    ASSERT_TRUE(!t.empty()); 
    ASSERT_TRUE(t.size() == 5); 
    ASSERT_TRUE(t.height() == 4); 
    ASSERT_TRUE(t.check_sorting_invariant());    
    ASSERT_EQUAL(*t.min_element(), -2.5);
    ASSERT_EQUAL(*t.max_element(), 4.0);  
    ASSERT_TRUE(*t.find(2.1) == 2.1);
    //ctor 2, copy 
    BinarySearchTree<double> t1(t);
    ASSERT_TRUE(!t1.empty()); 
    ASSERT_TRUE(t1.size() == 5); 
    ASSERT_TRUE(t1.height() == 4); 
    ASSERT_TRUE(t1.check_sorting_invariant());    
    ASSERT_EQUAL(*t1.min_element(), -2.5);
    ASSERT_EQUAL(*t1.max_element(), 4.0); 
    ASSERT_TRUE(*t1.min_greater_than(2.1) == *t.min_greater_than(2.1));
}

TEST(test_assign_operator) {
    BinarySearchTree<int> t;
    t.insert(0);
    t.insert(1);
    t.insert(-1);
    t.insert(2);
    BinarySearchTree<int> t1;
    t1 = t;
    ASSERT_TRUE(!t1.empty()); 
    ASSERT_TRUE(!t.empty()); 
    ASSERT_TRUE(t1.size() == t.size());
    ASSERT_TRUE(t1.height() == t.height());
    ASSERT_TRUE(t.check_sorting_invariant());  
    ASSERT_TRUE(*t1.min_element()== *t.min_element());  
    ASSERT_TRUE(*t1.max_element()== *t.max_element()); 


    t1.insert(-100);
    t1 = t; 
    ASSERT_TRUE(!t1.empty()); 
    ASSERT_TRUE(!t.empty()); 
    ASSERT_TRUE(t1.size() == t.size());
    ASSERT_TRUE(t1.height() == t.height());
    ASSERT_TRUE(t.check_sorting_invariant());  
    ASSERT_TRUE(*t1.min_element()== *t.min_element());  
    ASSERT_TRUE(*t1.max_element()== *t.max_element());  

}

TEST(test_traverse_one) {
    BinarySearchTree<int> t;
    t.insert(1); 
    ASSERT_TRUE(!t.empty()); 
    ASSERT_TRUE(t.height() == 1); 
    ASSERT_TRUE(t.size() == 1); 
    ASSERT_TRUE(*t.min_element() == 1); 
    ASSERT_TRUE(*t.max_element() == 1);
    
  ostringstream oss_preorder;
  t.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "1 ");

  ostringstream oss_inorder;
  t.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "1 ");
}

TEST(test_traverse_general) {
    BinarySearchTree<double> t;
    t.insert(1);  
    t.insert(1.1);
    t.insert(0.1);
    t.insert(2.1);
    t.insert(-0.1);        
  ostringstream oss_preorder;
  t.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "1 0.1 -0.1 1.1 2.1 ");

  ostringstream oss_inorder;
  t.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "-0.1 0.1 1 1.1 2.1 ");
}

TEST(test_traverse_char) {
    BinarySearchTree<char> t;
    t.insert('a');  
    t.insert('d');
    t.insert('b');
    t.insert('c');
    t.insert('e');   

    ASSERT_TRUE(!t.empty()); 
    ASSERT_TRUE(t.size() == 5); 
    ASSERT_EQUAL(t.height(),4); 
    ASSERT_TRUE(t.check_sorting_invariant());    
    ASSERT_EQUAL(*t.min_element(),'a');
    ASSERT_EQUAL(*t.max_element(), 'e');  
    ASSERT_TRUE(*t.find('a') == 'a');

  ostringstream oss_preorder;
  t.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "a d b c e ");

  ostringstream oss_inorder;
  t.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "a b c d e ");
}

// test iterator 
TEST(test_i1_general) {
    BinarySearchTree<int> t;
    // ctor 
    BinarySearchTree<int>::Iterator i;
    BinarySearchTree<int>::Iterator i1;
    i1 = t.end(); 

    //check nullptr case 
    i = t.min_element(); 
    ASSERT_EQUAL(i,i1);
    i = t.max_element(); 
    ASSERT_EQUAL(i,i1);

    // test *, test min, max, one elemnt 
    t.insert(0);
    i = t.min_element(); 
    ASSERT_EQUAL(*i,0); 
    i = t.max_element(); 
    ASSERT_EQUAL(*i,0); 
    //begin, end(null)
    i = t.begin();
    ASSERT_TRUE(*i == 0);

    t.insert(2);
    // begin, ++ 
    i = t.begin();
    ASSERT_TRUE(*i == 0);
    ++i; 
    ASSERT_TRUE(*i == 2);

    //general case, more elements 
    t.insert(4);
    t.insert(6);
    t.insert(8);

    // max, min 
    i = t.min_element(); 
    ASSERT_EQUAL(*i,0); 
    i = t.max_element(); 
    ASSERT_EQUAL(*i,8); 

    i = t.insert(10);
    ASSERT_EQUAL(*i,10);   

    // ++*  , == 
    ++(*i); 
    ASSERT_EQUAL(*i,11);  
    ASSERT_TRUE(*i == 11); 

    // !=
    ASSERT_TRUE(*i != 10); 
    //? -> 
    
    // nullptr find, min_greatest 
    BinarySearchTree<int>::Iterator i3 = t.min_greater_than(1000);
    BinarySearchTree<int>::Iterator i4 = t.find(-1000);
    ASSERT_EQUAL(i3,i1);
    ASSERT_EQUAL(i4,i1);
}

TEST(test_i2_find) {
    BinarySearchTree <int> t;
    t.insert(0);
    BinarySearchTree<int>::Iterator i0 = t.find(0);
    ASSERT_EQUAL(*i0, 0);
    t.insert(1);
    t.insert(2);
    t.insert(-1);

    BinarySearchTree<int>::Iterator i1 = t.find(0);
    BinarySearchTree<int>::Iterator i2 = t.find(1);
    BinarySearchTree<int>::Iterator i3 = t.find(2);
    BinarySearchTree<int>::Iterator i4 = t.find(-1);
    ASSERT_EQUAL(*i1, 0);
    ASSERT_EQUAL(*i2, 1);   
    ASSERT_EQUAL(*i3, 2);
    ASSERT_EQUAL(*i4, -1);
}

TEST(test_i3_min) {
    BinarySearchTree<int> t;
    t.insert(0);
    BinarySearchTree<int>::Iterator i1 = t.min_greater_than(-1);
    ASSERT_TRUE(*i1 == 0);
    ASSERT_TRUE(*i1 == *t.max_element());
    t.insert(2);
    t.insert(6);
    BinarySearchTree<int>::Iterator i2 = t.min_greater_than(5);
    ASSERT_TRUE(*i2 == 6);
    t.insert(-2);
    t.insert(-6);
    BinarySearchTree<int>::Iterator i3 = t.min_greater_than(-2);
    ASSERT_TRUE(*i3 == 0);
    BinarySearchTree<int>::Iterator i4 = t.min_greater_than(-1000);
    ASSERT_TRUE(*i4 == -6);
    ASSERT_TRUE(*i4 == *t.min_element());
}

TEST(test_sort_cases){
    BinarySearchTree <int> t;
    t.insert(0);
    t.insert(1);
    t.insert(-5);

    ASSERT_TRUE(t.check_sorting_invariant());

    BinarySearchTree <int>::Iterator i1 = t.find(0);
    *i1 = -1; 
    ASSERT_TRUE(t.check_sorting_invariant());
    *i1 = -6; 
    ASSERT_TRUE(!t.check_sorting_invariant());   
    *i1 = -5; 
    ASSERT_TRUE(!t.check_sorting_invariant());     
}

TEST_MAIN()