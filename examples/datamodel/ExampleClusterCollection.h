//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef ExampleClusterCollection_H
#define  ExampleClusterCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// albers specific includes
#include "albers/Registry.h"
#include "albers/CollectionBase.h"

// datamodel specific includes
#include "ExampleClusterData.h"
#include "ExampleCluster.h"
#include "ExampleClusterEntry.h"

typedef std::vector<ExampleClusterData> ExampleClusterDataContainer;
typedef std::deque<ExampleClusterEntry*> ExampleClusterEntryPointerContainer;

class ExampleClusterCollectionIterator {

  public:
    ExampleClusterCollectionIterator(int index, const ExampleClusterEntryPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const ExampleClusterCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const ExampleCluster operator*() const;
    const ExampleCluster* operator->() const;
    const ExampleClusterCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable ExampleCluster m_object;
    const ExampleClusterEntryPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class ExampleClusterCollection : public albers::CollectionBase {

public:
  typedef const ExampleClusterCollectionIterator const_iterator;

  ExampleClusterCollection();
//  ExampleClusterCollection(const ExampleClusterCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  ExampleClusterCollection(ExampleClusterVector* data, int collectionID);
  ~ExampleClusterCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  ExampleCluster create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  ExampleCluster create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const ExampleCluster operator[](int index) const;

  /// Append object to the collection
  void push_back(ExampleCluster object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(albers::Registry* registry);

  albers::CollRefCollection* referenceCollections() { return m_refCollections;};

  void setID(unsigned ID){m_collectionID = ID;};

  // support for the iterator protocol
  const const_iterator begin() const {
    return const_iterator(0, &m_entries);
  }
  const	const_iterator end() const {
    return const_iterator(m_entries.size(), &m_entries);
  }

  /// returns the address of the pointer to the data buffer
  void* getBufferAddress() { return (void*)&m_data;};

  /// returns the pointer to the data buffer
  std::vector<ExampleClusterData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<double,arraysize> energy() const;


private:
  int m_collectionID;
  ExampleClusterEntryPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<ExampleHit>* m_rel_Hits; //relation buffer for r/w
  std::vector<std::vector<ExampleHit>*> m_rel_Hits_tmp;
 
  // members to handle streaming
  albers::CollRefCollection* m_refCollections;
  ExampleClusterDataContainer* m_data;
};

template<typename... Args>
ExampleCluster  ExampleClusterCollection::create(Args&&... args){
  int size = m_entries.size();
  auto entry = new ExampleClusterEntry({size,m_collectionID},{args...});
  m_entries.push_back(entry);
  return ExampleCluster(entry);
}

template<size_t arraysize>
const std::array<double,arraysize> ExampleClusterCollection::energy() const {
  std::array<double,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.energy;
 }
 return tmp;
}


#endif