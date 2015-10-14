#ifndef ALBERS_PYTHONEVENTSTORE_H
#define ALBERS_PYTHONEVENTSTORE_H


#include "podio/EventStore.h"
#include "podio/ROOTReader.h"

class PythonEventStore {
public:
  /// constructor from filename
  PythonEventStore(const char* filename);

  /// access a collection.
  podio::CollectionBase* get(const char* name);

  /// signify end of event
  void endOfEvent();

  /// go to a given event
  void goToEvent(unsigned ievent);

  /// get number of entries in the tree
  unsigned getEntries() const;

 private:
  podio::ROOTReader m_reader;
  podio::EventStore m_store;
};

#endif