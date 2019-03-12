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
         iterator find(const K & k)       {iterator(bst.find(k));}
         iterator begin()                 {iterator(bst.begin());}
         iterator end()                   {iterator(bst.end());}
         iterator rbegin()                {iterator(bst.rbegin());}
         iterator rend()                  {iterator(bst.rend());}

         //constant iterator functions
         class cosntIterator;
         cosntIterator cfind(K & k) const {iterator(bst.cfind(k));}
         cosntIterator cbegin() const     {iterator(bst.cbegin());}
         cosntIterator cend() const       {iterator(bst.cend());}
         cosntIterator crbegin() const    {iterator(bst.crbegin());}
         cosntIterator crend() const      {iterator(bst.crend());}

         //reverse iterator functions
         class reverse_iterator;

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
