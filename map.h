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
         BST<pair<K,V> > bst;

      public:
         //constructors and destructor
         map(){}
         map(const map <K, V> & rhs) throw (const char *){}
         ~map(){bst.clear();};

         //standard container interfaces
         map<K, V> & operator = (const map<K, V> & rhs)throw (const char *);
         int size()     {return bst.size();}
         bool empty()   {return bst.empty();}
         void clear()   {bst.clear();}

         //view and modify tree
         void insert(const K & k, const V & v);
         void insert(const typename pair<K, V>::pair & rhs);
         V & operator [] (const K & k);

         //iterator functions
         class iterator;
         //iterator find(const K & k)       { return iterator(bst.find(k));}
         //iterator begin()                 { return iterator(bst.begin());}
         //iterator end()                   { return iterator(bst.end());}
         //iterator rbegin()                { return iterator(bst.rbegin());}
         //iterator rend()                  { return iterator(bst.rend());}

         //constant iterator functions
         class cosntIterator;
         //cosntIterator cfind(K & k) const { return iterator(bst.cfind(k));}
         //cosntIterator cbegin() const     { return iterator(bst.cbegin());}
         //cosntIterator cend() const       { return iterator(bst.cend());}
         //cosntIterator crbegin() const    { return iterator(bst.crbegin());}
         //cosntIterator crend() const      { return iterator(bst.crend());}

         //reverse iterator functions
         class reverse_iterator;

   };

   template <class K, class V>
   class map<K, V>::iterator
   {
      private:
         typename BST<pair<K, V>>::iterator bstIterator;
         
      public:
         //Constructors
         iterator() : bstIterator(NULL) {}
         iterator(typename BST<pair<K, V>>::iterator rhs) : 
            bstIterator(rhs) {}
         iterator(const iterator & rhs) : bstIterator(rhs) {}

         //Assignment Operator
         iterator & operator = (const iterator & it)
         {
            this->bstIterator = it.bstIterator;
            return *this;
         }

         //Equality Operator
         bool operator == (const iterator & it)
         {
            return (it.bstIterator == bstIterator);
         }

         //Inequality Operator
         bool operator != (const iterator & it)
         {
            return false;//return !(it.bstIterator == bstIterator);
         }

         //Increment Operator (Postfix)
         iterator & operator ++ ()
         {
            //Test this!
            ++bstIterator;
            return *this;
         }

         //Increment Operator (Postfix)
         iterator & operator ++ (int postfix)
         {
            //Test this!
            iterator returnValue(this);
            ++bstIterator;
            return returnValue;
         }

         //Decrement Operator (Prefix)
         iterator & operator -- ()
         {
            //Test this!
            --bstIterator;
            return *this;
         }

         //Decrement Operator (Postfix)
         iterator & operator -- (int postfix)
         {
            //Test this!
            iterator returnValue(this);
            --bstIterator;
            return returnValue;
         }

         //Dereference Operator
         V operator * () throw (const char *)
         {
            auto i = *bstIterator;
            return i.second;
         }
   };


   template <class K, class V>
   map<K, V>  & map<K,V> :: operator = (const map<K, V> & rhs)throw (const char *)
   {
      bst = rhs.bst;

      return *this;
   }

   template <class K, class V>
   V & map<K,V> :: operator [] (const K & k)
   {
      pair<K,V> newPair;
      newPair.first = k;
      iterator foundIt = bst.find(newPair);
      if(foundIt)
         return (*foundIt).second;
      else
         bst.insert(newPair);

      return (*bst.find(newPair)).second;
   }
}

#endif // MAP_H_INCLUDED
