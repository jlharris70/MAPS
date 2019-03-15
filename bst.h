/***********************************************************************
 * Component:
 *    Assignment 10, Binary Search Tree (BST)
 *    Brother Kirby, CS 235
 * Author:
 *    James Harris, Jerrald Nelson, Alexander Farrell
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include <iostream>
#include <typeinfo>
#include <string>        // for STRING
#include <cassert>

namespace custom
{
   /***************************************************************************
   * BST CLASS
   ***************************************************************************/
   template <class T>
   class BST
   {
      public:
            class iterator;
            class reverse_iterator;
            class cosntIterator;

            /***************************************************************************
            * BNode CLASS
            ***************************************************************************/
            class BNode
            {
               public:
                  //BNode public variables
                  T data;
                  BNode * pLeft;
                  BNode * pRight;
                  BNode * pParent;
                  bool isRed;

                  //BNode constructors
                  BNode() :pLeft(NULL), pRight(NULL), pParent(NULL), data(), isRed() {}
                  BNode(const T & t) :pLeft(NULL), pRight(NULL), pParent(NULL),
                                data(t), isRed(false) {}

                  //Data Access
                  void setData(T data) { this->data = data; }
                  T& getData() { return data; }

               private:
                  //BNode private functions
                  void verifyRB(int depth);
                  void verify(BST);
                  void balance();
            };

         //Constructors & Destructor
         BST(): root(), numElements(0) {}
         BST(BST <T> & rhs) throw (const char *) :
               root(), numElements(0) {*this = rhs;} //TODO:
         ~BST() 
         {
            
         }

         //standard container interfaces
         BST<T> & operator = (const BST<T> & rhs)throw (const char *);
         int size()  {return numElements;}
         bool empty() {return root == NULL;}
         void clear()
         {
            if (root)
            {
               deleteBTree(root);
            }
            root = NULL;
            numElements = 0;
         }

         //edit tree
         void insert(const T & t)  throw (const char *);
         void erase(iterator & it);
         BNode * getRoot() { return root; }

         //Red Black
         void redBlack(BNode* nodeToBalance)  throw (const char *);
         bool leftNode(BNode* nodeToBalance)  throw (const char *);

         //iterator functions
         iterator find(const T & t);
         iterator begin();
         iterator end();
         iterator rbegin();
         iterator rend();

         //constant iterator functions
         cosntIterator cfind(T & t) const;
         cosntIterator cbegin() const;
         cosntIterator cend() const;
         cosntIterator crbegin() const;
         cosntIterator crend() const;

      private:
         //BST private variables
         BNode * root;
         int numElements;
         bool redBlackBalance = false;

         //BST private functions
         void deleteNode(BNode dlte, bool right);
         void deleteBinaryTree(BNode dlte);
         BNode* addSingleNode(BNode* parent, BNode* node);
         //BNode * copyBinaryTree(BNode<T> * src, BNode<T> * dest){}

         /***************************************************************************
         * BNODE :: TREE SIZE
         ***************************************************************************/
         int sizeBTree(const BNode * pRoot)
         {
            int size = 1;
            if (pRoot->pLeft)
               size += sizeBTree(pRoot->pLeft);
            if(pRoot->pRight)
               size += sizeBTree(pRoot->pRight);

            return size;
         }

         /***************************************************************************
         * BNODE :: ADD LEFT
         ***************************************************************************/
         void addLeft(BNode * pNode, const T & t) throw (const char*)
         {
            try
            {
               BNode * pNew = new BNode(t);
               pNew->pParent = pNode;
               pNode->pLeft = pNew;
            }

            catch(std::bad_alloc)
            {
               std::cout << "Unable to allocate a node" << std::endl;
            }
         }

         /***************************************************************************
         * BNODE :: ADD LEFT BNode
         ***************************************************************************/
         void addLeft(BNode * pNode, BNode * pAdd)
         {
            if (pAdd)
               pAdd->pParent = pNode;
            pNode->pLeft = pAdd;
         }

         /***************************************************************************
         * BNODE :: ADD RIGHT
         ***************************************************************************/
         void addRight(BNode * pNode, BNode * pAdd)
         {
            if (pAdd)
               pAdd->pParent = pNode;
            pNode->pRight = pAdd;
         }

         /***************************************************************************
         * BNODE :: ADD RIGHT template as variable
         ***************************************************************************/
         void addRight(BNode * pNode, const T & t) throw (const char*)
         {
            try
            {
               BNode * pNew = new BNode(t);
               pNew->pParent = pNode;
               pNode->pRight = pNew;
            }
            catch (std::bad_alloc)
            {
               std::cout << "ERROR: Unable to allocate a node" << std::endl;
            }
         }

         /***************************************************************************
         * BNODE :: DELETE TREE
         ***************************************************************************/
         void deleteBTree(BNode * & pNode)
         {
            if (numElements > 0)
            {
               if (!pNode)
                  return;

               if (pNode->pLeft)
                  deleteBTree(pNode->pLeft);

               if (pNode->pRight)
                  deleteBTree(pNode->pRight);

               numElements--;
               pNode = NULL;
               delete pNode;
            }
         }

         /***************************************************************************
         * BNODE :: EXTRACTION OPERATOR OVERLOAD
         ***************************************************************************/
         std::ostream & operator << (BNode * pHead)
         {
            //If node is null, exit
            if (pHead == NULL)
               return;
            std::ostream  out;
            //call extraction operator for pHead->pLeft
            out << pHead->pLeft;
            //once a null is reached output data for the node that called pLeft
            out << pHead->data << " ";
            //now check to see if there is a pRight node
            out << pHead->pRight;

            return out;
         }

         /***************************************************************************
         * BNODE :: COPY
         ***************************************************************************/
         BNode * copyBTree(const BNode * pHead)
         {
            if(pHead == NULL)
               return NULL;

            BNode * pCopy = new BNode(pHead->data);

            pCopy->pLeft = copyBTree(pHead->pLeft);
            if (pCopy->pLeft != NULL)
               pCopy->pLeft->pParent = pCopy;

            pCopy->pRight = copyBTree(pHead->pRight);
            if (pCopy->pRight != NULL)
               pCopy->pRight->pParent = pCopy;

            return pCopy;
         }
   };

   /***************************************************************************
   * BST :: iterator
   * An iterator through the tree
   ***************************************************************************/
   template <class T>
   class BST<T> ::iterator
   {
      private:
      //typename BST<T>::BNode * p;

      public:
      BNode* p;
      //constructors
      iterator() : p(NULL) {}
      iterator(BNode * p) : p(p) {}
      iterator(const iterator & rhs) : p(rhs.p) {}

      //assignment
      iterator & operator = (const iterator & it) 
      {
         this->p = it.p;
         return *this;
      }

      //equal and not equal
      bool operator == (const iterator & it) const
      {
         return it.p == p;
      }

      bool operator != (const iterator & it) const
      {
         return it.p != p;
      }

      //postfix increment
      iterator & operator ++ (int postfix)
      {
         //if no node, exit
         if (!p)
            return *this;
         //go right
         if (p->pRight)
         {
            p = p->pRight;
            //go left all the way
            while (p->pLeft)
               p = p->pLeft;

            return *this;
         }

         BNode * pSave = p;

         //move up
         p = p->pParent;

         //if parent is NULL, exit
         if (!p)
            return *this;

         //if no more to the left, move right
         if (pSave == p->pLeft)
            return *this;

         while (p && pSave == p->pRight)
         {
            pSave = p;
            p = p->pParent;
         }

         return *this;
      }

      //postfix decrement
      iterator & operator -- (int postfix)
      {
         // do nothing if we have nothing
         if (NULL == p)
            return *this;

         // if there is a left node, take it
         if (NULL != p->pLeft)
         {
            // go left
            p = p->pLeft;

            // jig right - there might be more right-most children
            while (p->pRight)
               p = p->pRight;
            return *this;
         }

         // there are no left children, the right are done
         assert(NULL == p->pLeft);
         BNode * pSave = p;

         // go up
         p = p->pParent;

         // if the parent is the NULL, we are done!
         if (NULL == p)
            return *this;

         // if we are the right-child, got to the parent.
         if (pSave == p->pRight)
            return *this;

         // we are the left-child, go up as long as we are the left child!
         while (NULL != p && pSave == p->pLeft)
         {
            pSave = p;
            p = p->pParent;
         }

         return *this;
      }

      //prefix increment
      iterator operator ++ ()
      {
         iterator returnValue(this->p);

         //if no node, exit
         if (p == NULL)
            return returnValue;
         //go right
         if (p->pRight != NULL)
         {
            p = p->pRight;
            //go left all the way
            while (p->pLeft != NULL)
               p = p->pLeft;

            return returnValue;
         }

         BNode * pSave = p;

         //move up
         p = p->pParent;

         //if parent is NULL, exit
         if (!p)
            return returnValue;

         //if no more to the left, move right
         if (pSave == p->pLeft)
            return returnValue;

         while (p && pSave == p->pRight)
         {
            pSave = p;
            p = p->pParent;
         }

         return returnValue;
      }

      //prefix decrement
      iterator operator -- ()
      {
         iterator returnValue(this->p);

         // do nothing if we have nothing
         if (NULL == p)
            return returnValue;

         // if there is a left node, take it
         if (NULL != p->pLeft)
         {
            // go left
            p = p->pLeft;

            // jig right - there might be more right-most children
            while (p->pRight)
               p = p->pRight;
            return returnValue;
         }

         // there are no left children, the right are done
         assert(NULL == p->pLeft);
         BNode * pSave = p;

         // go up
         p = p->pParent;

         // if the parent is the NULL, we are done!
         if (NULL == p)
            return returnValue;

         // if we are the right-child, got to the parent.
         if (pSave == p->pRight)
            return returnValue;

         // we are the left-child, go up as long as we are the left child!
         while (NULL != p && pSave == p->pLeft)
         {
            pSave = p;
            p = p->pParent;
         }

         return returnValue;
      }

      //dereference
      T operator * () throw (const char *)
      {
         /*if (!p)
            return NULL;
         else
            return p->data;*/
         return p->data;
      }
   };

   /***************************************************************************
   * BST :: iterator
   * An iterator through the tree
   ***************************************************************************/
   template <class T>
   class BST<T> ::reverse_iterator
   {
      private:
      //typename BST<T>::BNode * p;

      public:
      BNode* p;
      //constructors
      reverse_iterator() : p(NULL) {}
      reverse_iterator(BNode * p) : p(p) {}
      reverse_iterator(const reverse_iterator & rhs) : p(rhs.p) {}

      //assignment
      reverse_iterator & operator = (const reverse_iterator & it)
      {
         this->p = it.p;
         return *this;
      }

      //equal and not equal
      bool operator == (const reverse_iterator & it)
      {
         return it.p == p;
      }

      bool operator != (const reverse_iterator & it)
      {
         return it.p != p;
      }

      //postfix increment
      reverse_iterator & operator -- (int postfix)
      {
         //if no node, exit
         if (!p)
            return *this;
         //go right
         if (p->pRight)
         {
            p = p->pRight;
            //go left all the way
            while (p->pLeft)
               p = p->pLeft;

            return *this;
         }

         BNode * pSave = p;

         //move up
         p = p->pParent;

         //if parent is NULL, exit
         if (!p)
            return *this;

         //if no more to the left, move right
         if (pSave == p->pLeft)
            return *this;

         while (p && pSave == p->pRight)
         {
            pSave = p;
            p = p->pParent;
         }

         return *this;
      }

      //postfix decrement
      reverse_iterator & operator ++ (int postfix)
      {
         // do nothing if we have nothing
         if (NULL == p)
            return *this;

         // if there is a left node, take it
         if (NULL != p->pLeft)
         {
            // go left
            p = p->pLeft;

            // jig right - there might be more right-most children
            while (p->pRight)
               p = p->pRight;
            return *this;
         }

         // there are no left children, the right are done
         assert(NULL == p->pLeft);
         BNode * pSave = p;

         // go up
         p = p->pParent;

         // if the parent is the NULL, we are done!
         if (NULL == p)
            return *this;

         // if we are the right-child, got to the parent.
         if (pSave == p->pRight)
            return *this;

         // we are the left-child, go up as long as we are the left child!
         while (NULL != p && pSave == p->pLeft)
         {
            pSave = p;
            p = p->pParent;
         }

         return *this;
      }

      //prefix increment
      reverse_iterator & operator ++ ()
      {
         return *this;
      }

      //prefix decrement
      reverse_iterator & operator -- ()
      {
         return *this;
      }

      //dereference
      T operator * () throw (const char *)
      {
         if (!p)
            return NULL;
         else
            return p->data;
      }
   };

   /***************************************************************************
   * BST :: CONST iterator
   * An iterator through the tree
   ***************************************************************************/
   template <class T>
   class BST<T> :: cosntIterator
   {
      private:
         //typename BST<T>::BNode * p;

      public:
         typename BST<T>::BNode * p;
         //constructors
         cosntIterator(): p(NULL){}
         cosntIterator(const BNode * p): p(p) {}
         cosntIterator(const cosntIterator & rhs): p(rhs.p){}

         //assignment
         cosntIterator & operator = (const cosntIterator & it)
         {
            //stub
         }

         //equal and not equal
         bool operator == (const cosntIterator & it) const
         {
            return *this;
         }

         bool operator != (const cosntIterator & it) const
         {
            return *this;
         }

         //postfix increment
         cosntIterator operator ++ ()
         {
            //stub
         }

         //prefix increment
//         cosntIterator <T> operator ++ ()
//         {
//            //stub
//         }

         //postfix decrement
         cosntIterator operator -- ()
         {
            //stub
         }

         //prefix decrement
//         cosntIterator <T> operator -- ()
//         {
//            //stub
//         }

         //dereference operator
         T operator * () const throw (const char *)
         {
            //stub
         }
   };

   /***************************************************************************
   * BST :: ASSIGNMENT
   * Assignment Operator
   ***************************************************************************/
   template <class T>
   BST <T> & BST <T> :: operator = (const BST <T> & rhs) throw (const char *)
   {
      clear();
      //Unless its an empty tree, we will need to copy the contents.
      if (rhs.root != NULL)
      {
         //Recursive method which builds the tree starting with the root.
         //The flow spreads out to what it needs, then puts it all
         //together on its way back!
         root = addSingleNode(NULL, rhs.root);
      }

      numElements = rhs.numElements;

      return *this;
   }

/***************************************************************************
* BST :: RedBlack
* Checks Node is left or right branch.
***************************************************************************/

   template <class T>
   bool BST <T> ::leftNode(BNode * nodeToCheck) throw(const char *)
   {
      if (nodeToCheck->pParent != NULL ) //grandparent is black
      {
         //Check Left Branch
         if (nodeToCheck->pParent->pLeft == nodeToCheck) //left Branch
         {
            return true;
         }
         else //Right Branch
         {
            return false;
         }
      }
   }


   /***************************************************************************
   * BST :: RedBlack
   * Checks Inserted node to balance the tree.
   ***************************************************************************/
   template <class T>
   void BST <T> :: redBlack(BNode * nodeToBalance) throw(const char *)
   {
      try
      {
         //Check One - No Parent - Root is black
         if (nodeToBalance->pParent == NULL)
            nodeToBalance->isRed = false;

         //Check Two - Parent is black
         nodeToBalance->isRed = true;

         //Check Three - Parent and Aunt are Red
         if ((nodeToBalance->pParent != NULL && //Parent & Grandparent isnot nothing
            nodeToBalance->pParent->pParent != NULL) &&
            (nodeToBalance->pParent->isRed == true && //Parent is red
            nodeToBalance->pParent->pParent->isRed == false)) //grandparent is black
         {
            //is node parent the left or right node of the grandparent
            if (nodeToBalance->pParent->pParent->pLeft == nodeToBalance->pParent) //Then check right for aunt
            {
               //Make sure its not NULL
               if (nodeToBalance->pParent->pParent->pRight != NULL)
               {
                  //Make sure its red
                  if (nodeToBalance->pParent->pParent->pRight->isRed == true) //Shift occurs
                  {
                     //Make Parent Black
                     nodeToBalance->pParent->isRed = false;
                     //Make aunt black
                     nodeToBalance->pParent->pParent->pRight->isRed = false;
                  }
               }
            }
            else //Check left for aunt
            {
               //Make sure its not NULL
               if (nodeToBalance->pParent->pParent->pLeft != NULL)
               {
                  //Make sure its red
                  if (nodeToBalance->pParent->pParent->pLeft->isRed == true) //Shift occurs
                  {
                     //Make Parent Black
                     nodeToBalance->pParent->isRed = false;
                     //Make aunt black
                     nodeToBalance->pParent->pParent->pLeft->isRed = false;
                  }
               }
            }
         }


         //Check Four - Parent is red, grandparent is black
         // and Aunt is black or nonexistant
         bool shift=false;
         if ((nodeToBalance->pParent != NULL && //Parent & Grandparent isnot nothing
            nodeToBalance->pParent->pParent != NULL) &&
            (nodeToBalance->pParent->isRed == true && //Parent is red
               nodeToBalance->pParent->pParent->isRed == false)) //grandparent is black
         {

            //Check Aunt to be black
            if (leftNode(nodeToBalance->pParent)==true) //Then check right for aunt
            {
               //Make sure its not NULL
               if (nodeToBalance->pParent->pParent->pRight != NULL)
               {
                  //Make sure aunt is black
                  if (nodeToBalance->pParent->pParent->pRight->isRed == false) //Shift occurs
                  {
                     shift = true;
                  }
               }
               else { shift = true; }//NIL Nodes are black
            }
            else //Check left for aunt
            {
               //Make sure its not NULL
               if (nodeToBalance->pParent->pParent->pLeft != NULL)
               {
                  //Make sure aunt is black
                  if (nodeToBalance->pParent->pParent->pLeft->isRed == false) //Shift occurs
                  {
                     shift = true;
                  }
               }
               else { shift = true; }//NIL Nodes are black
            }
         }

         //4 match -- figure out which shift
         if (shift == true)
         {

            //4A - Left Node of Left Node
            if (leftNode(nodeToBalance) == true && leftNode(nodeToBalance->pParent)==true)
            {
               BNode * nodeGParent;
               BNode * nodeGGParent;
               nodeGParent = nodeToBalance->pParent->pParent;//Grandparent
               nodeGGParent = nodeToBalance->pParent->pParent->pParent;//Great Grandparent
               nodeGParent->isRed = true; //set Grandparent Red
               nodeToBalance->pParent->isRed = false; //Set parent Black

               //Rotate grandparent to left so its right node of parent
               addRight(nodeToBalance->pParent, nodeToBalance->pParent->pParent);

               //Clear out left node
               nodeToBalance->pParent->pParent->pLeft = NULL;

               //Set Parent Nodes Parent to be great grandparent
               nodeToBalance->pParent->pParent = nodeGGParent;

               //Set Old Great GrantParent's (Now Grandparent)
               //Left node to be Parent
               nodeGGParent->pLeft = nodeToBalance->pParent;

            }

            //4B - Right Node of Right Node
            if (leftNode(nodeToBalance) == false && leftNode(nodeToBalance->pParent)==false)
            {
               BNode * nodeGParent;
               BNode * nodeGGParent;
               nodeGParent = nodeToBalance->pParent->pParent;//Grandparent
               nodeGGParent = nodeToBalance->pParent->pParent->pParent;//Great Grandparent
               nodeGParent->isRed = true; //set Grandparent Red
               nodeToBalance->pParent->isRed = false; //Set parent black

               //Rotate grandparent to left so its left node of parent
               addLeft(nodeToBalance->pParent,nodeToBalance->pParent->pParent);

               //Clear out right node
               nodeToBalance->pParent->pParent->pRight = NULL;

               //Set Parent Nodes Parent to be great grandparent
               nodeToBalance->pParent->pParent = nodeGGParent;

               //Set Old Great GrantParent's (Now Grandparent)
               //Left node to be Parent
               nodeGGParent->pRight = nodeToBalance->pParent;

            }

            //4C - Right Node of Left Node
            if (leftNode(nodeToBalance) == false && leftNode(nodeToBalance->pParent) == true)
            {
               BNode * nodeGParent;
               BNode * nodeGGParent;
               nodeGParent = nodeToBalance->pParent->pParent;//Grandparent
               nodeGGParent = nodeToBalance->pParent->pParent->pParent;//Great Grandparent
               nodeGParent->isRed = true; //set Grandparent Red
               nodeToBalance->isRed = false; //Set current node to black
               nodeGGParent->isRed = true;  //Set GGParent to red

               if (nodeGGParent == NULL)
                  nodeToBalance->pParent = NULL;
               else if (leftNode(nodeGParent) == false)
                  nodeGGParent->pRight = nodeToBalance;
               else
                  nodeGGParent->pLeft = nodeToBalance;

               //Rotate parent to right so its the right node
               addRight(nodeToBalance, nodeGParent);

               //Clean up left node
               nodeGParent->pLeft = NULL;

               //Rotate grandparent to left so its left node
               addLeft(nodeToBalance, nodeToBalance->pParent);

               // Set Parent
               nodeToBalance->pParent = nodeGGParent;

               //Clean up
               nodeToBalance->pLeft->pRight = NULL;
            }

            //4D - Left Node of Right Node
            if (leftNode(nodeToBalance) == true && leftNode(nodeToBalance->pParent) == false)
            {

               BNode * nodeGParent;
               BNode * nodeGGParent;
               nodeGParent = nodeToBalance->pParent->pParent;//Grandparent
               nodeGGParent = nodeToBalance->pParent->pParent->pParent;//Great Grandparent
               nodeGParent->isRed = true; //set Grandparent Red
               nodeToBalance->isRed = false; //Set current node to black
               nodeGGParent->isRed = true;  //Set GGParent to red

               if (nodeGGParent == NULL)
                  nodeToBalance->pParent = NULL;
               else if (leftNode(nodeGParent) == false)
                  nodeGGParent->pRight = nodeToBalance;
               else
                  nodeGGParent->pLeft = nodeToBalance;

               //Rotate grandparent to left so its left node
               addLeft(nodeToBalance, nodeGParent);

               //Clean up left node
               nodeGParent->pRight = NULL;

               //Rotate parent to right so its the right node
               addRight(nodeToBalance, nodeToBalance->pParent);

               // Set Parent
               nodeToBalance->pParent = nodeGGParent;

               //Clean up
               nodeToBalance->pRight->pLeft = NULL;

            }

         }

      }
      catch (...)
      {
         std::cout << "ERROR: Unable to red/black a node" << std::endl;
      }
   }


   /***************************************************************************
   * BST :: INSERT
   * Inserts a node from the tree in logarithmic time to size.
   ***************************************************************************/
   template <class T>
   void BST <T> :: insert(const T & t) throw (const char *)
   {
      try
      {
         //if no node, create one
         if(root == NULL)
         {
            root = new typename BST<T>::BNode(t);
         }

         BNode* nodeToCheck = root;
         bool toInsert = true;

         //Moves to where the node is in the tree
         //Each recursion checks one node and either
         //moves down to a child, or inserts at an opening.
         //If the value already exists, nothing is returned.
         while (toInsert)
         {
            if (nodeToCheck->data > t)
            {
               //If less than, move left. If nothing is left,
               //we've found the spot to add it to!
               if (nodeToCheck->pLeft != NULL)
               {
                  nodeToCheck = nodeToCheck->pLeft;
               }
               else
               {
                  //Insert the node as a new left child.
                  nodeToCheck->pLeft = new typename BST<T>::BNode(t);
                  nodeToCheck->pLeft->pParent = nodeToCheck;
                  std::string s;
                  s = typeid(nodeToCheck->data).name();
                  if (s=="i")
                     redBlack(nodeToCheck->pLeft);
                  toInsert = false;
               }
            }
            else if (nodeToCheck->data < t)
            {
               //If less than, move right. If nothing is right,
               //we've found the spot to add it to!
               if (nodeToCheck->pRight != NULL)
               {
                  nodeToCheck = nodeToCheck->pRight;
               }
               else
               {
                  //Insert the node as a new right child.
                  nodeToCheck->pRight = new typename BST<T>::BNode(t);
                  nodeToCheck->pRight->pParent = nodeToCheck;
                  std::string s;
                  s = typeid(nodeToCheck->data).name();
                  if (s == "i")
                     redBlack(nodeToCheck->pRight);
                  toInsert = false;
               }
            }
            else
            {
               //Is equals, escape the whole insert method.
               toInsert = false;
            }
         }
      }

      catch (...)
      {
         std::cout << "ERROR: Unable to allocate a node" << std::endl;
      }

      numElements++;
   }

   /***************************************************************************
   * BST :: ERASE
   * Erases a node from the tree in logarithmic time to size.
   ***************************************************************************/
   template <class T>
   void BST <T> :: erase(iterator & it)
   {
      //Four cases, handle each individually

      //First Case, no children!
      if ((it.p->pLeft == NULL) && (it.p->pRight == NULL))
      {
         //Find where the node to erase is on its parent.

         //If this node is on the right of the parent
         if ((it.p->pParent != NULL) && (it.p->pParent->pRight == it.p))
         {
            it.p->pParent->pRight = NULL;
         }

         //If this node is on the left of the parent
         if ((it.p->pParent != NULL) && (it.p->pParent->pRight == it.p))
         {
            it.p->pParent->pRight = NULL;
         }

         delete it.p;
         return;
      }

      //Second Case, one child (To the Left)!
      if ((it.p->pLeft != NULL) && (it.p->pRight == NULL))
      {
         it.p->pLeft->pParent = it.p->pParent;

         if ((it.p->pParent != NULL) && (it.p->pParent->pRight == it.p))
         {
            it.p->pParent->pRight = it.p->pLeft;
         }
         if ((it.p->pParent != NULL) && (it.p->pParent->pLeft == it.p))
         {
            it.p->pParent->pLeft = it.p->pLeft;
         }

         delete it.p;
         return;
      }

      //Third Case, one child (To the Right)!
      if ((it.p->pLeft == NULL) && (it.p->pRight != NULL))
      {
         it.p->pRight->pParent = it.p->pParent;

         if ((it.p->pParent != NULL) && (it.p->pParent->pRight == it.p))
         {
            it.p->pParent->pRight = it.p->pRight;
         }
         if ((it.p->pParent != NULL) && (it.p->pParent->pLeft == it.p))
         {
            it.p->pParent->pLeft = it.p->pRight;
         }

         delete it.p;
         return;

      }

      //Fourth Case, two children!
      if ((it.p->pLeft != NULL) && (it.p->pRight != NULL))
      {
         //Get the in order successor.
         iterator inOrderSuccessor(it);
         ++inOrderSuccessor;

         //Remember these values before we move things around!
         BNode* successorNode = inOrderSuccessor.p;
         BNode* successorOriginalParent = inOrderSuccessor.p->pParent;
         BNode* rightChild = inOrderSuccessor.p->pRight;

         //What child is it?
         bool isLeftChildOfParent = true;

         if (it.p->pParent)
         {
            isLeftChildOfParent = (it.p->pParent->pLeft == it.p);
         }
         else
         {
            root = successorNode;
         }

         //Attach Successor New Children
         successorNode->pLeft = it.p->pLeft;
         successorNode->pRight = it.p->pRight;
         successorNode->pParent = it.p->pParent;

         //Attach successor to new parent
         if (it.p->pParent)
         {
            if (isLeftChildOfParent)
            {
               successorNode->pParent->pLeft = successorNode;
            }
            else
            {
               successorNode->pParent->pRight = successorNode;
            }
         }

         //Attach successor node's children to it.
         successorNode->pLeft->pParent = successorNode;
         successorNode->pRight->pParent = successorNode;

         //Move Original Right Child (if exists)
         if (rightChild != NULL)
         {
            rightChild->pParent = successorOriginalParent;

            //Should always have an original parent,
            //but just checking!
            if (successorOriginalParent != NULL)
            {
               successorOriginalParent->pLeft = rightChild;
            }
         }
         else
         {
            //Ensures its not pointing to other nodes in the tree.
            successorOriginalParent->pLeft = NULL;
         }

         delete it.p;
      }
   }



   /***************************************************************************
   * BST :: FIND
   * Locates a value in the tree in logarithmic time to size.
   ***************************************************************************/
   template <class T>
   typename BST<T>::iterator BST<T>::find(const T& t)
   {
      if (root == NULL)
      {
         //It's obviously not in an empty tree!
         //Return iterator to null.
         return end();
      }

      BNode* nodeToCheck = root;

      while (nodeToCheck != NULL)
      {
         if (t < nodeToCheck->data)
         {
            //If less than, move left. If nothing is left,
            //it is not in the tree!
            nodeToCheck = nodeToCheck->pLeft;
         }
         else if (t > nodeToCheck->data)
         {
            //If greater than, move right. If nothing is right,
            //it is not in the tree!
            nodeToCheck = nodeToCheck->pRight;
         }
         else //If t is equal
         {
            //We've found it! Return the iterator
            return iterator(nodeToCheck);
         }
      }

      //We couldn't find it. Return iterator to null.
      return end();
   }

   /***************************************************************************
   * BST :: BEGIN
   * Returns an iterator pointing to the left most node in the tree.
   ***************************************************************************/
   template <class T>
   typename BST<T>::iterator BST<T>::begin()
   {
      BNode* node = root;

      if (node != NULL)
      {
         //Move all the way left!
         while (node->pLeft != NULL)
         {
            node = node->pLeft;
         }
      }

      return iterator(node);
   }

   /***************************************************************************
   * BST :: END
   * Returns an iterator pointing to no element.
   ***************************************************************************/
   template <class T>
   typename BST<T>::iterator BST<T>::end()
   {
      return iterator(NULL);
   }

   /***************************************************************************
   * BST :: R BEGIN
   * Returns an iterator pointing to the right most node in the tree.
   ***************************************************************************/
   template <class T>
   typename BST<T>::iterator BST<T>::rbegin()
   {
      BNode* node = root;

      if (node != NULL)
      {
         //Move all the way right!
         while (node->pRight != NULL)
         {
            node = node->pRight;
         }
      }

      return iterator(node);
   }

   /***************************************************************************
   * BST :: R END
   * Returns an iterator pointing to no element.
   ***************************************************************************/
   template <class T>
   typename BST<T>::iterator BST<T>::rend()
   {
      return iterator(NULL);
   }

   /***************************************************************************
   * BST :: ADD SINGLE NODE
   * Recursive method which copies the tree from another.
   ***************************************************************************/
   template <class T>
   typename BST<T>::BNode* BST<T>::addSingleNode(BNode* parent, BNode* node)
   {
      BNode* returnValue = new BNode(node->data);
      returnValue->pParent = parent;

      //If there's descendents on the left.
      if (node->pLeft != NULL)
      {
         //Copy descendents on the left
         returnValue->pLeft = addSingleNode(returnValue, node->pLeft);
      }

      //If there's descendents on the right.
      if (node->pRight != NULL)
      {
         //Copy descendents on the right
         returnValue->pRight = addSingleNode(returnValue, node->pRight);
      }

      return returnValue;
   }

   /***************************************************************************
   * BST INSERTION
   * Inserts the contents of the BST into an out stream.
   ***************************************************************************/
   template <class T>
   std::ostream & operator << (std::ostream & out,
      const BST<T> & bst)
   {
      for (typename BST<T>::iterator i = bst.begin(); i != bst.end(); ++i)
      {
         out << i.p->data;
         //out << " ";
      }

      return out;
   }
}



#endif // BST_H_INCLUDED
