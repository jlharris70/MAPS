#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include "bst.h"
#include "pair.h"

namespace custom
{
   template <class K, class V>
   class map
   {
      private:
         BST<K> * bst;

      public:
         //constructors and de-constructor
         map();
         map(const map <K, V> & rhs) throw (const char *);
         ~map(){};

         //standard container interfaces
         map<K, V> & operator = (const map<K, V> & rhs)throw (const char *);
         int size()  {return 0;}
         bool empty() {return 0;}
         void clear() {BST<K>::clear();}

         //view and modify tree
         void insert(const K & k, const V & v);
         void insert(const typename pair<K, V>::pair & rhs);
         V access(const K & k);

         //iterator functions
         class iterator;
         iterator find(const K & k);
         iterator begin();
         iterator end();
         iterator rbegin();
         iterator rend();

         //constant iterator functions
         class cosntIterator;
         cosntIterator cfind(K & t) const;
         cosntIterator cbegin() const;
         cosntIterator cend() const;
         cosntIterator crbegin() const;
         cosntIterator crend() const;

         //reverse iterator functions
         class reverse_iterator;

   };

   /***************************************************************************
   * BST :: iterator
   * An iterator through the tree
   ***************************************************************************/
   template <class K, class V>
   class map<K, V> :: iterator
   {
      private:
      //typename BST<T>::BNode * p;

      public:
      typename BST<K>::BNode* p;
      //constructors
      iterator() : p(NULL) {}
      iterator(typename BST<K>::BNode* p) : p(p) {}
      iterator(const iterator & rhs) : p(rhs.p) {}

      //assignment
      iterator & operator = (const iterator & it)
      {
         this->p = it.p;
         return *this;
      }

      //equal and not equal
      bool operator == (const iterator & it)
      {
         return it.p == p;
      }

      bool operator != (const iterator & it)
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

         typename BST<K>::BNode * pSave = p;

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
         typename BST<K>::BNode * pSave = p;

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

         typename BST<K>::BNode * pSave = p;

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
         typename BST<K>::BNode * pSave = p;

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
      K operator * () throw (const char *)
      {
         if (!p)
            return NULL;
         else
            return p->data;
      }

   };

   /***************************************************************************
   * BST :: REVERSE iterator
   * An iterator through the tree
   ***************************************************************************/
   template <class K, class V>
   class map<K, V> :: reverse_iterator
   {
      private:
      //typename BST<T>::BNode * p;

      public:
      typename BST<K>::BNode* p;
      //constructors
      reverse_iterator() : p(NULL) {}
      reverse_iterator(typename BST<K>::BNode * p) : p(p) {}
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

         typename BST<K>::BNode * pSave = p;

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
         typename BST<K>::BNode * pSave = p;

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
      K operator * () throw (const char *)
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
   template <class K, class V>
   class map<K,V> :: cosntIterator
   {
      private:
         //typename BST<T>::BNode * p;

      public:
         typename BST<K>::BNode * p;
         //constructors
         cosntIterator(): p(NULL){}
         cosntIterator(const typename BST<K>::BNode * p): p(p) {}
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
         K operator * () const throw (const char *)
         {
            //stub
         }

   };



}

#endif // MAP_H_INCLUDED
