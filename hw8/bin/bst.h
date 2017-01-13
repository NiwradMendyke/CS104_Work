/**
 * Darwin Mendyke
 * CS104
 * 4/30/16
 * 
 * bst.h
 * Implements a(n unbalanced) BST storing Key,Value pairs
 */



#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>


/* -----------------------------------------------------
 * Regular Binary Tree Nodes
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class Node {
  public:
    Node (const KeyType & k, const ValueType & v, Node<KeyType, ValueType> *p)
      : _item(k, v)
     // the default is to create new nodes as leaves
      { _parent = p; _left = _right = NULL; }
    
    virtual ~Node()
    { }
    
    std::pair<const KeyType, ValueType> const & getItem () const
    { return _item; }
    
    std::pair<const KeyType, ValueType> & getItem ()
    { return _item; }
    
    const KeyType & getKey () const
    { return _item.first; }
    
    const ValueType & getValue () const
    { return _item.second; }
    
    /* the next three functions are virtual because for AVL-Trees,
       we'll want to use AVL nodes, and for those, the
       getParent, getLeft, and getRight functions should return 
       AVL nodes, not just ordinary nodes.
       That's an advantage of using getters/setters rather than a struct. */
    
    virtual Node<KeyType, ValueType> *getParent () const
      { return _parent; }
    
    virtual Node<KeyType, ValueType> *getLeft () const
      { return _left; }
    
    virtual Node<KeyType, ValueType> *getRight () const
      { return _right; }
    
    
    void setParent (Node<KeyType, ValueType> *p)
    { _parent = p; }
    
    void setLeft (Node<KeyType, ValueType> *l)
    { _left = l; }
    
    void setRight (Node<KeyType, ValueType> *r)
    { _right = r; }
    
    void setValue (const ValueType &v)
    { _item.second = v; }
  
    int printParent ()
    {
      if (_parent == NULL)
        return -100;
      else
        return _parent->getKey();
    }

  protected:
    std::pair<const KeyType, ValueType> _item;
    Node <KeyType, ValueType> *_left, *_right, *_parent;
};



/* -----------------------------------------------------
 * Regular Binary Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class BinarySearchTree {
  protected:
    // Main data member of the class
    Node<KeyType, ValueType> *root;

  public:
    /**
     * Constructor
     */
    BinarySearchTree () { root = NULL; }

    /**
     * Destructor
     */
    ~BinarySearchTree () { deleteAll (root); }

    /**
     * Prints the entire tree structure in a nice format 
     *  
     * It will denote subtrees in [] brackets.
     *  This could be helpful if you want to debug your functions. 
     */  
    void print () const
    { 
      printRoot (root);
      std::cout << "\n";
    }

    /**
     * returns the value of the node with the given key
     */
    const ValueType findValue(const KeyType &to_find)
    {
      return internalFind(to_find)->getValue();
    }

    /**
     * An In-Order iterator
     *  !!! You must implement this !!!
     */
    class iterator {
      public:
        /**
         * Initialize the internal members of the iterator
         */
        iterator(Node<KeyType, ValueType>* ptr)
        {
          curr = ptr;
        }
        
        std::pair<const KeyType, ValueType>& operator*()
        { return curr->getItem();  }
        
        std::pair<const KeyType, ValueType>* operator->() 
        { return &(curr->getItem()); }
        
        /**
         * Checks if 'this' iterator's internals have the same value
         *  as 'rhs'
         */
        bool operator==(const iterator& rhs) const
        {
          if (rhs.curr == NULL) {
            if (curr == NULL) {
              return true;
            }
            return false;
          }

          if (curr->getKey() == rhs.curr->getKey() && curr->getValue() == rhs.curr->getValue())
            return true;
          return false;
        }
        
        /**
         * Checks if 'this' iterator's internals have a different value
         *  as 'rhs'
         */
        bool operator!=(const iterator& rhs) const
        {
          if (rhs.curr == NULL) {
            if (curr == NULL) {
              return false;
            }
            return true;
          }

          if (curr->getKey() != rhs.curr->getKey() || curr->getValue() != rhs.curr->getValue())
            return true;
          return false;
        }
        
        /**
         * Advances the iterator's location using an in-order sequencing
         */
        iterator& operator++() 
        {
          //std::cerr << "++ operator called" << std::endl;

          curr = successor(curr);
          return *this;
        }
    
      protected:
        Node<KeyType, ValueType>* curr;
        //you are welcome to add any necessary variables and helper functions here.

        /**
         * Returns the next largest value in the BST
         *
         * filled with lots of debug statements
         */
        Node<KeyType, ValueType> *successor(Node<KeyType, ValueType>* curr) 
        {
          //std::cerr << "successor called" << std::endl;
          if (curr == NULL) {
            return NULL;
          }
          else if (curr->getLeft() != NULL || curr->getRight() != NULL) { // if at a parent node
            //std::cerr << "successor is a parent node" << std::endl;
            if (curr->getRight() == NULL) { // if no right child
              //std::cerr << "left child " << curr->getKey() << " is " << curr->getLeft()->getKey() << std::endl;
              //std::cerr << "parent of " << curr->getLeft()->getKey() << " is " << curr->getLeft()->getParent()->getKey() << std::endl;
              if (curr->getParent() != NULL && curr->getKey() < curr->getParent()->getKey()) {
                return curr->getParent();
              }
              else {
                Node<KeyType, ValueType>* temp = curr;
                while (curr != NULL && temp->getKey() >= curr->getKey()) {
                  curr = curr->getParent(); // travels up until reaches parent greater than node
                }

                return curr;
              }
            }
            if (curr->getRight() != NULL) { // if right child exists
              //std::cerr << "right child " << curr->getKey() << " is " << curr->getRight()->getKey() << std::endl;
              //std::cerr << "parent of " << curr->getRight()->getKey() << " is " << curr->getRight()->getParent()->getKey() << std::endl;
              curr = curr->getRight();

              while (curr->getLeft() != NULL) { // travels down until reaches bottom-most left node
                curr = curr->getLeft();
              }

              return curr;
            }
          }
          else { // if at a child node
            if (curr->getParent() == NULL) {
              return NULL;
            }
            if (curr->getKey() < curr->getParent()->getKey()) { // if node is less than parent
              //std::cerr << "successor is a left child node" << std::endl;
              return curr->getParent();
            }
            if (curr->getKey() > curr->getParent()->getKey()) { // if node is greater than parent
              //std::cerr << "successor is a right child node" << std::endl;
              Node<KeyType, ValueType>* temp = curr;
              while (curr != NULL && temp->getKey() >= curr->getKey()) {
                curr = curr->getParent(); // travels up until reaches parent greater than node
              }

              return curr;
            }
          }
        
          return NULL;
        }

    };

  
    /**
     * Returns an iterator to the "smallest" item in the tree
     */
    iterator begin() 
    {
      Node<KeyType, ValueType>* curr = root;

      while (curr->getLeft() != NULL) {
        curr = curr->getLeft();
      }

      iterator it(curr);
      return it;
    }

    /**
     * Returns an iterator whose value means INVALID
     */
    iterator end() 
    {
      iterator it(NULL);
      return it;
    }
  
  protected:
    /**
     * Helper function to find a node with given key, k and 
     * return a pointer to it or NULL if no item with that key
     * exists
     */
    Node<KeyType, ValueType>* internalFind(const KeyType& k) const 
    {
      Node<KeyType, ValueType> *curr = root;
      while (curr) {
        if (curr->getKey() == k) {
          return curr;
        } 
        else if (k < curr->getKey()) {
          curr = curr->getLeft();
        } 
        else {
          curr = curr->getRight();
        }
      }
      return NULL;
    }
    
    /**
     * Helper function to print the tree's contents
     */
    void printRoot (Node<KeyType, ValueType> *r) const
    {
      if (r != NULL) {
      	std::cout << "[";
      	printRoot (r->getLeft());
      	std::cout << " (" << r->getKey() << ", " << r->getValue();// << ") ";
        if (r->getParent() != NULL) {
          std::cout << ", " << r->getParent()->getKey() << ")";
        }
        else {
          std::cout << ")";
        }
      	printRoot (r->getRight());
      	std::cout << "]";
      }
      else {
        std::cout << "NULL";
      }
    }
    
    /**
     * Helper function to delete all the items
     */
    void deleteAll (Node<KeyType, ValueType> *r)
    {
      if (r != NULL) {
      	deleteAll (r->getLeft());
      	deleteAll (r->getRight());
      	delete r;
      }
    }
};

/* Feel free to add member function definitions here if you need */

#endif
