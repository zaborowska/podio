#ifndef ExampleCluster_H
#define ExampleCluster_H
#include "ExampleClusterData.h"
#include <vector>
#include "ExampleHit.h"

#include <vector>
#include "podio/ObjectID.h"

//  cluster energy
// author: B. Hegner

//forward declarations


#include "ExampleClusterConst.h"
#include "ExampleClusterObj.h"



class ExampleClusterCollection;
class ExampleClusterCollectionIterator;
class ConstExampleCluster;

class ExampleCluster {

  friend ExampleClusterCollection;
  friend ExampleClusterCollectionIterator;
  friend ConstExampleCluster;

public:

  /// default constructor
  ExampleCluster();
    ExampleCluster(double energy);

  /// constructor from existing ExampleClusterObj
  ExampleCluster(ExampleClusterObj* obj);
  /// copy constructor
  ExampleCluster(const ExampleCluster& other);
  /// copy-assignment operator
  ExampleCluster& operator=(const ExampleCluster& other);
  /// support cloning (deep-copy)
  ExampleCluster clone() const;
  /// destructor
  ~ExampleCluster();

  /// conversion to const object
  operator ConstExampleCluster () const;

public:

  const double& energy() const;

  void energy(double value);

  void addHits(ConstExampleHit);
  unsigned int Hits_size() const;
  ConstExampleHit Hits(unsigned int) const;
  std::vector<ConstExampleHit>::const_iterator Hits_begin() const;
  std::vector<ConstExampleHit>::const_iterator Hits_end() const;

  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ExampleClusterObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ExampleCluster& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstExampleCluster& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ExampleCluster& p1,
//       const ExampleCluster& p2 );

  const podio::ObjectID getObjectID() const;

private:
  ExampleClusterObj* m_obj;

};



#endif
