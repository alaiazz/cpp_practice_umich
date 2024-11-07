// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here
TEST(test1_general_test) {
    // test ctor, now should be empty
    List<int> l1; 

    //check empty or not, size
    ASSERT_TRUE(l1.empty());
    ASSERT_EQUAL(l1.size(),0);

    //creat a list 2 
    List<int> l2; 
    ASSERT_TRUE(l2.empty());
    ASSERT_EQUAL(l2.size(),0);

    //insert values into list 2 (2,1), front back, size 
    l2.push_back(1);
    ASSERT_FALSE(l2.empty());
    ASSERT_EQUAL(l2.size(),1);
    ASSERT_EQUAL(l2.front(),1);
    ASSERT_EQUAL(l2.back(),1);

    l2.push_front(2);
    ASSERT_EQUAL(l2.front(),2);
    ASSERT_EQUAL(l2.back(),1);
    ASSERT_TRUE(!l2.empty());
    ASSERT_EQUAL(l2.size(),2);

    // test overload assignment = 
    l1 = l2; 

    //test empty or not, equal or not 
    ASSERT_TRUE(!l1.empty());
    ASSERT_EQUAL(l1.front(),l2.front());
    ASSERT_EQUAL(l1.back(),l2.back());
    ASSERT_EQUAL(l1.size(),l2.size());

    // add another number to l1 
    l1.push_back(0); 
    ASSERT_EQUAL(l1.back(),0);
    ASSERT_EQUAL(l1.front(),2);
    ASSERT_EQUAL(l1.size(),3);

    // pop_back, l1(2,1,0)
    l1.pop_back(); 
    ASSERT_EQUAL(l1.back(),1);
    ASSERT_EQUAL(l1.front(),2);
    ASSERT_TRUE(!l1.empty());
    ASSERT_EQUAL(l1.size(),2);
    l1.pop_back(); 
    ASSERT_EQUAL(l1.back(),2);
    ASSERT_EQUAL(l1.front(),2);
    ASSERT_TRUE(!l1.empty());
    ASSERT_EQUAL(l1.size(),1);
    l1.pop_back(); 
    ASSERT_TRUE(l1.empty());

    //pop_front, l2(2,1)
    l2.pop_front(); 
    ASSERT_EQUAL(l2.back(),1);
    ASSERT_EQUAL(l2.front(),1);
    ASSERT_TRUE(!l2.empty());
    l2.pop_front(); 
    ASSERT_TRUE(l2.empty());  
}

TEST(test2_general_test) {
    //special case (10,9,10)
    List <int> l3; 
    l3.push_back(10);
    l3.push_back(9);
    l3.push_back(10);
    ASSERT_TRUE(!l3.empty());

    //l4 (10)
    List <int> l4; 
    l4.push_front(10);
    ASSERT_TRUE(!l4.empty());

    // test ctor2, copy type 
    List <int> l5(l4);
    ASSERT_TRUE(!l5.empty());
    ASSERT_EQUAL(l4.front(),l5.front());
    ASSERT_EQUAL(l4.back(),l5.back());
    ASSERT_EQUAL(l5.size(),l4.size());
    ASSERT_EQUAL(1,l4.size());
    ASSERT_EQUAL(1,l5.size());
    ASSERT_NOT_EQUAL(&l5.back(), &l4.back());
    ASSERT_NOT_EQUAL(&l5.front(), &l4.front());

    l4 = l3; 
    ASSERT_TRUE(!l4.empty());
    ASSERT_EQUAL(l4.front(),l3.front());
    ASSERT_EQUAL(l4.back(),l3.back());
    ASSERT_EQUAL(l4.size(),l3.size());
    ASSERT_EQUAL(3,l4.size());
    ASSERT_EQUAL(3,l3.size());
    ASSERT_NOT_EQUAL(&l3.back(), &l4.back());
    ASSERT_NOT_EQUAL(&l3.front(), &l4.front());

    l3 = l5; 
    ASSERT_TRUE(!l3.empty());
    ASSERT_EQUAL(l3.front(),l5.front());
    ASSERT_EQUAL(l3.back(),l5.back());
    ASSERT_EQUAL(l3.size(),l5.size());
    ASSERT_EQUAL(1,l5.size());
    ASSERT_EQUAL(1,l3.size());  
    ASSERT_NOT_EQUAL(&l3.back(), &l5.back());
    ASSERT_NOT_EQUAL(&l3.front(), &l5.front());  

    //test clear 
    l5.clear();
    ASSERT_TRUE(l5.empty());
}

TEST(test3_general_test) {
    // test ctor, now should be empty
    List<char> l1; 

    //check empty or not, size
    ASSERT_TRUE(l1.empty());
    ASSERT_EQUAL(l1.size(),0);

    //creat a list 2 
    List<char> l2; 
    ASSERT_TRUE(l2.empty());
    ASSERT_EQUAL(l2.size(),0);

    char a = 'a';
    char b = 'b';
    char c = '1';

    //insert values into list 2 (b,a), front back, size 
    l2.push_back(a);
    ASSERT_FALSE(l2.empty());
    ASSERT_EQUAL(l2.size(),1);
    ASSERT_EQUAL(l2.front(),a);
    ASSERT_EQUAL(l2.back(),a);

    l2.push_front(b);
    ASSERT_EQUAL(l2.front(),b);
    ASSERT_EQUAL(l2.back(),a);
    ASSERT_TRUE(!l2.empty());
    ASSERT_EQUAL(l2.size(),2);

    // test overload assignment = 
    l1 = l2; 

    //test empty or not, equal or not 
    ASSERT_TRUE(!l1.empty());
    ASSERT_EQUAL(l1.front(),l2.front());
    ASSERT_EQUAL(l1.back(),l2.back());
    ASSERT_EQUAL(l1.size(),l2.size());

    // add another number to l1 (b,a,c)
    l1.push_back(c); 
    ASSERT_EQUAL(l1.back(),c);
    ASSERT_EQUAL(l1.front(),b);
    ASSERT_EQUAL(l1.size(),3);

    // pop_back, l1(b,a,c)
    l1.pop_back(); 
    ASSERT_EQUAL(l1.back(),a);
    ASSERT_EQUAL(l1.front(),b);
    ASSERT_TRUE(!l1.empty());
    ASSERT_EQUAL(l1.size(),2);
    l1.pop_back(); 
    ASSERT_EQUAL(l1.back(),b);
    ASSERT_EQUAL(l1.front(),b);
    ASSERT_TRUE(!l1.empty());
    ASSERT_EQUAL(l1.size(),1);
    l1.pop_back(); 
    ASSERT_TRUE(l1.empty());

    //pop_front, l2(b,a)
    l2.pop_front(); 
    ASSERT_EQUAL(l2.back(),a);
    ASSERT_EQUAL(l2.front(),a);
    ASSERT_TRUE(!l2.empty());
    ASSERT_EQUAL(l2.size(),1);
    l2.pop_front(); 
    ASSERT_TRUE(l2.empty());   
}

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST(test_iterator_1){ 
    List<int> l1;   
    l1.push_back(0);
    l1.push_front(1);
    l1.push_back(2);
    // l1 (102)

    //test begin 
    List<int>::Iterator i0 = l1.begin(); 
    //test assign 
    List<int>::Iterator i1 = i0; 
    //test ctor 
    List<int>::Iterator i2(i1); 
    // test ++ 
    ++i0;
    ++i0; 
    List<int>::Iterator i3 = i0;

    // check 
    ASSERT_EQUAL(*i1,1);
    ASSERT_EQUAL(*i2,1);
    ASSERT_EQUAL(*i3,2);
    ASSERT_EQUAL(i2,i1);

    //--
    --i3; 
    ASSERT_EQUAL(*i3,0);
    --i3; 
    ASSERT_EQUAL(*i3,1);
    ASSERT_EQUAL(i3,i2);

    // == 
    ASSERT_TRUE(i3 == i2); 
    ASSERT_TRUE(i3 == i1); 

    //!= 
    ++i1; 
    ASSERT_EQUAL(*i1,0);
    ASSERT_TRUE(i1 != i3);
    ++i1; 
    ++i1; 

    // begin, end 
    ASSERT_EQUAL(l1.end(), i1);
    ASSERT_EQUAL(l1.begin(), i3);

    List <int>::Iterator i4 = l1.begin(); 
    // check insert 
    l1.insert(i4,3);
    ASSERT_EQUAL(*i4,1); 
    ASSERT_EQUAL(*l1.begin(),3); 
    // 3102 
    ++i4; 
    ASSERT_EQUAL(*i4,0);
    ++i4; 
    ASSERT_EQUAL(*i4,2);    

    l1.erase(i4); 
    //310
    ASSERT_EQUAL(*l1.begin(),3);

    l1.erase(l1.begin());
    //10 
    ASSERT_EQUAL(*l1.begin(),1);

    l1.erase(++l1.begin()); 
    //1 
    ASSERT_EQUAL(*l1.begin(),1);   

    l1.erase(l1.begin());
    ASSERT_TRUE(l1.empty());
}

TEST_MAIN()
