#ifndef LAB3_TESTS_HPP
#define LAB3_TESTS_HPP

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#include "PriorityQueue.hpp"
#include "BinarySearchTree.hpp"

// Libraries needed for BinarySearchTreeTest
#include <sstream>
#include <queue>
using namespace std;

class PriorityQueueTest
{
public:
  bool test1()
  {
    PriorityQueue q(16);
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 0 );
    return true;
  }

  bool test2()
  {
    PriorityQueue q(2);
    ASSERT_TRUE( q.enqueue(10) );
    ASSERT_TRUE( !q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 1 );
    ASSERT_TRUE( q.max() == 10 );

    ASSERT_TRUE( q.dequeue() );
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 0 );
    return true;
  }

  bool test3()
  {
    PriorityQueue q(3);
    ASSERT_TRUE( q.enqueue(5) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.enqueue(3) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.enqueue(4) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.full() );

    ASSERT_TRUE( !q.enqueue(7) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.full() );
    return true;   
  }
  // enqueue 16 items, dequeue 18
  bool test4(){
    PriorityQueue q(16);
    ASSERT_TRUE(q.empty());
    for (int i = 0; i < 16; ++i)
      ASSERT_TRUE(q.enqueue(i));
    for (int i = 0; i < 16; ++i)
      ASSERT_TRUE(q.dequeue());
    for (int i = 0; i < 2; ++i)
      ASSERT_FALSE(q.dequeue());
    return 1;
  }

  // try enqueuing into a full queue
  bool test5(){
    PriorityQueue q(1);
    ASSERT_TRUE(q.empty());
    ASSERT_TRUE(q.enqueue(3));
    ASSERT_TRUE(q.size_ == 1);
    ASSERT_TRUE(q.max() == 3);
    for(int i=0; i<10; i++)
      ASSERT_FALSE(q.enqueue(8));
    ASSERT_TRUE(q.size_ == 1);
    ASSERT_TRUE(q.max() == 3);
    for(int i=0; i<10; i++)
      ASSERT_FALSE(q.enqueue(2));
    ASSERT_TRUE(q.size_ == 1);
    ASSERT_TRUE(q.max() == 3);
    return 1;
  }
  bool test6(){
    PriorityQueue q(1);
    ASSERT_TRUE(q.empty());
    ASSERT_TRUE(q.enqueue(10));
    ASSERT_TRUE(q.full());
    return 1;
  }
  // checks if enqueue works (with swapping)
  bool test7(){
    // 86,21,63,12,43,10,44,90,54,14,93,25
    // 93,90,63,54,86,25,44,12,43,14,21,10
    PriorityQueue q(12);
    ASSERT_TRUE(q.enqueue(86));
    ASSERT_TRUE(q.max() == 86);
    ASSERT_TRUE(q.enqueue(21));
    ASSERT_TRUE(q.max() == 86);
    ASSERT_TRUE(q.enqueue(63));
    ASSERT_TRUE(q.max() == 86);
    ASSERT_TRUE(q.enqueue(12));
    ASSERT_TRUE(q.max() == 86);
    // should swap here:
    ASSERT_TRUE(q.enqueue(43));
    ASSERT_TRUE(q.max() == 86);
    ASSERT_TRUE(q.enqueue(10));
    ASSERT_TRUE(q.max() == 86);
    ASSERT_TRUE(q.enqueue(44));
    ASSERT_TRUE(q.max() == 86);
    // should swap twice here:
    ASSERT_TRUE(q.enqueue(90));
    ASSERT_TRUE(q.max() == 90);
    // should swap:
    ASSERT_TRUE(q.enqueue(54));
    ASSERT_TRUE(q.max() == 90);
    ASSERT_TRUE(q.enqueue(14));
    ASSERT_TRUE(q.max() == 90);
    // swap twice
    ASSERT_TRUE(q.enqueue(93));
    ASSERT_TRUE(q.max() == 93);
    ASSERT_TRUE(q.enqueue(25));
    ASSERT_TRUE(q.max() == 93);
    // q.print();
    ASSERT_TRUE(q.heap_[1] == 93);
    ASSERT_TRUE(q.heap_[2] == 90);
    ASSERT_TRUE(q.heap_[3] == 63);
    ASSERT_TRUE(q.heap_[4] == 54);
    ASSERT_TRUE(q.heap_[5] == 86);
    ASSERT_TRUE(q.heap_[6] == 25);
    ASSERT_TRUE(q.heap_[7] == 44);
    ASSERT_TRUE(q.heap_[8] == 12);
    ASSERT_TRUE(q.heap_[9] == 43);
    ASSERT_TRUE(q.heap_[10] == 14);
    ASSERT_TRUE(q.heap_[11] == 21);
    ASSERT_TRUE(q.heap_[12] == 10);
    return 1;
  }
};

class BinarySearchTreeTest
{
private:
  // Traverse the tree in level-order so we can check if it was constructed
  // properly. Output is as follows:
  //   "val1 val2 ... valN"
  // where vali is the value of node i, using level-order traversal.
  std::string level_order(BinarySearchTree::Node* root)
  {
    // If no nodes, return an empty string.
    if (root == NULL) {
      return "";
    }
    
    std::stringstream ss;
    std::queue<BinarySearchTree::Node*> node_queue;
    node_queue.push(root);
    while (!node_queue.empty()) {
      BinarySearchTree::Node* cur_node = node_queue.front();
      node_queue.pop();
      ss << cur_node->val << " ";
      if (cur_node->left != NULL) {
        node_queue.push(cur_node->left);
      }
      if (cur_node->right != NULL) {
        node_queue.push(cur_node->right);
      }
    }
    
    std::string level_order_str = ss.str();
    // There is a trailing space at the end of the string; return everything
    // before this.
    return level_order_str.substr(0, level_order_str.size() - 1);
  }

public:
  bool test1()
  {
    // We expect an empty tree at construction.
    std::string expected_tree_level_order = "";
    
    BinarySearchTree bst;
    ASSERT_TRUE(bst.root_ == NULL);
    ASSERT_TRUE(bst.size_ == 0 && bst.size() == 0);
    
    std::string tree_level_order = level_order(bst.root_);
    // Compare the tree's representation to the expected tree.
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
    return true;
  }

  bool test2()
  {
    // We expect a single root node with value "5" after everything.
    std::string expected_tree_level_order = "5";
    
    BinarySearchTree bst;
    ASSERT_TRUE(bst.insert(5));
    ASSERT_TRUE(!bst.remove(4));
    ASSERT_TRUE(bst.exists(5));
    ASSERT_TRUE(bst.max() == bst.min() && bst.max() == 5);
    ASSERT_TRUE(bst.size() == 1);
    
    std::string tree_level_order = level_order(bst.root_);
    // Compare the tree's representation to the expected tree.
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
    return true;
  }

  bool test3()
  {
    // We expect a 2-node tree at the end of this function -- root node 10 and
    // a child node with value 6.
    std::string expected_tree_level_order = "10 6";
    
    BinarySearchTree bst;
    ASSERT_TRUE(bst.insert(10));
    ASSERT_TRUE(bst.insert(8));
    ASSERT_TRUE(bst.size() == 2);
    ASSERT_TRUE(bst.insert(6));
    ASSERT_TRUE(bst.size() == 3);

    ASSERT_TRUE(bst.remove(8));
    ASSERT_TRUE(bst.size() == 2);
    
    std::string tree_level_order = level_order(bst.root_);
    // Compare the tree's representation to the expected tree.
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
    return true;
  }
  // make sure insert/exists works
  bool test4()
  {
    BinarySearchTree bst;
    ASSERT_TRUE(bst.size_ == 0);
    ASSERT_TRUE(bst.insert(10));
    ASSERT_TRUE(bst.size_ == 1);
    ASSERT_TRUE(bst.insert(8));
    ASSERT_TRUE(bst.size_ == 2);
    ASSERT_TRUE(bst.insert(6));
    ASSERT_TRUE(bst.size_ == 3);

    ASSERT_TRUE(bst.exists(10));
    ASSERT_TRUE(bst.exists(8));
    ASSERT_TRUE(bst.exists(6));

    ASSERT_FALSE(bst.insert(6));
    ASSERT_FALSE(bst.insert(8));
    ASSERT_FALSE(bst.insert(10));

    ASSERT_FALSE(bst.exists(11));

    // bst.print();
    // cout << level_order(bst.root_) << ' ' << endl;
    return 1;
  }

  // make sure the head node works nice
  bool test5(){
    BinarySearchTree bst;
    ASSERT_TRUE(bst.root_ == NULL);
    ASSERT_TRUE(bst.insert(55));
    ASSERT_TRUE(bst.root_->val == 55);
    return 1;
  }

  // making very unbalanced tree
  bool test6(){
    // 1,2,8,3,4,5,9,7,10,6

    std::string expected_tree_level_order = "1 2 8 3 9 4 10 5 69 7 6";

    BinarySearchTree bst;
    ASSERT_TRUE(bst.insert(1));
    ASSERT_TRUE(bst.insert(2));
    ASSERT_TRUE(bst.insert(8));
    ASSERT_TRUE(bst.insert(3));
    ASSERT_TRUE(bst.insert(4));
    ASSERT_TRUE(bst.insert(5));
    ASSERT_TRUE(bst.insert(9));
    ASSERT_TRUE(bst.insert(7));
    ASSERT_TRUE(bst.insert(10));
    ASSERT_TRUE(bst.insert(6));
    ASSERT_TRUE(bst.insert(69));

    string tree_level_order = level_order(bst.root_);
    // Compare the tree's representation to the expected tree.
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)

    return 1;
  }

  // balanced w/ removes

  bool test7(){
    // 50, 17, 76, 9, 23, 54, 19, 12,67
    
    BinarySearchTree bst;
    ASSERT_TRUE(bst.insert(50));
    ASSERT_TRUE(bst.insert(17));
    ASSERT_TRUE(bst.insert(76));
    ASSERT_TRUE(bst.insert(9));
    ASSERT_TRUE(bst.insert(23));
    ASSERT_TRUE(bst.insert(54));
    ASSERT_TRUE(bst.insert(19));
    ASSERT_TRUE(bst.insert(12));
    ASSERT_TRUE(bst.insert(67));
    ASSERT_FALSE(bst.remove(1));

    std::string expected_tree_level_order = "50 17 76 9 23 54 12 19 67";
    string tree_level_order = level_order(bst.root_);
    // cout << tree_level_order << endl;
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0);

    ASSERT_TRUE(bst.remove(17));
    ASSERT_FALSE(bst.exists(17));

    std::string expected_tree_level_order1 = "50 19 76 9 23 54 12 67";
    string tree_level_order1 = level_order(bst.root_);
    // cout << tree_level_order1<< endl;
    ASSERT_TRUE(tree_level_order1.compare(expected_tree_level_order1) == 0);

    ASSERT_TRUE(bst.remove(67));

    std::string expected_tree_level_order2 = "50 19 76 9 23 54 12";
    string tree_level_order2 = level_order(bst.root_);
    ASSERT_TRUE(tree_level_order2.compare(expected_tree_level_order2) == 0);

    ASSERT_TRUE(bst.remove(76));
    std::string expected_tree_level_order3 = "50 19 54 9 23 12";
    string tree_level_order3 = level_order(bst.root_);
    ASSERT_TRUE(tree_level_order3.compare(expected_tree_level_order3) == 0);
    return 1;
  }

  bool test8(){
    // 45,53,33,28,16,97,90,91,74,75,71
    BinarySearchTree bst;
    ASSERT_TRUE(bst.insert(45));
    ASSERT_TRUE(bst.insert(52));
    ASSERT_TRUE(bst.insert(33));
    ASSERT_TRUE(bst.insert(28));
    ASSERT_TRUE(bst.insert(16));
    ASSERT_TRUE(bst.insert(97));
    ASSERT_TRUE(bst.insert(90));
    ASSERT_TRUE(bst.insert(91));
    ASSERT_TRUE(bst.insert(74));
    ASSERT_TRUE(bst.insert(75));
    ASSERT_TRUE(bst.insert(71));
    ASSERT_TRUE(bst.remove(90));
    std::string expected_tree_level_order = "45 33 52 28 97 16 91 74 71 75";
    string tree_level_order = level_order(bst.root_);
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0);

    ASSERT_TRUE(bst.depth() == 5);
    ASSERT_TRUE(bst.max() == 97);
    ASSERT_TRUE(bst.min() == 16);

    ASSERT_TRUE(bst.remove(45));
    ASSERT_TRUE(bst.depth() == 4);
    ASSERT_TRUE(bst.max() == 97);
    ASSERT_TRUE(bst.min() == 16);

    std::string expected_tree_level_order3 = "52 33 97 28 91 16 74 71 75";
    string tree_level_order3 = level_order(bst.root_);
    ASSERT_TRUE(tree_level_order3.compare(expected_tree_level_order3) == 0);

    ASSERT_TRUE(bst.remove(52));

    ASSERT_TRUE(bst.depth() == 4);
    ASSERT_TRUE(bst.max() == 97);
    ASSERT_TRUE(bst.min() == 16);
    std::string expected_tree_level_order2 = "71 33 97 28 91 16 74 75";
    string tree_level_order2 = level_order(bst.root_);
    ASSERT_TRUE(tree_level_order2.compare(expected_tree_level_order2) == 0);

    return 1;
  }

  bool test9(){
    BinarySearchTree bst[99999];
    for (int i = 0; i < 99999; ++i)
    {
      ASSERT_TRUE(bst[i].insert(45));
      ASSERT_TRUE(bst[i].insert(52));
      ASSERT_TRUE(bst[i].insert(33));
      ASSERT_TRUE(bst[i].insert(28));
      ASSERT_TRUE(bst[i].insert(16));
      ASSERT_TRUE(bst[i].insert(97));
      ASSERT_TRUE(bst[i].insert(90));
      ASSERT_TRUE(bst[i].insert(91));
      ASSERT_TRUE(bst[i].insert(74));
      ASSERT_TRUE(bst[i].insert(75));
      ASSERT_TRUE(bst[i].insert(71));
    }
    for (int i = 0; i < 99999; ++i)
    {
      ASSERT_TRUE(bst[i].remove(90));
      ASSERT_TRUE(bst[i].remove(45));
      ASSERT_TRUE(bst[i].remove(52));
    }
    return 1;
  }
};


#endif
