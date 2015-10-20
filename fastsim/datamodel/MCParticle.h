#ifndef MCParticle_H
#define MCParticle_H
#include "MCParticleData.h"
#include "BareParticle.h"

#include <vector>
#include "podio/ObjectID.h"

//  general particle information
// author: A. Zaborowska

//forward declarations
class MCParticleCollection;
class MCParticleCollectionIterator;
class ConstMCParticle;
class Particle;
class ConstParticle;
class GenVertex;
class ConstGenVertex;
class GenVertex;
class ConstGenVertex;


#include "MCParticleConst.h"
#include "MCParticleObj.h"

class MCParticle {

  friend MCParticleCollection;
  friend MCParticleCollectionIterator;
  friend ConstMCParticle;

public:

  /// default constructor
  MCParticle();
    MCParticle(BareParticle Core);

  /// constructor from existing MCParticleObj
  MCParticle(MCParticleObj* obj);
  /// copy constructor
  MCParticle(const MCParticle& other);
  /// copy-assignment operator
  MCParticle& operator=(const MCParticle& other);
  /// support cloning (deep-copy)
  MCParticle clone() const;
  /// destructor
  ~MCParticle();

  /// conversion to const object
  operator ConstMCParticle () const;

public:

  const BareParticle& Core() const { return m_obj->data.Core; };
  const ConstParticle RecParticle() const;
  const ConstGenVertex StartVertex() const;
  const ConstGenVertex EndVertex() const;

  BareParticle& Core() { return m_obj->data.Core; };
  void Core(class BareParticle value);
  void RecParticle(ConstParticle value);
  void StartVertex(ConstGenVertex value);
  void EndVertex(ConstGenVertex value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from MCParticleObj instance
  void unlink(){m_obj = nullptr;};

  bool operator==(const MCParticle& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstMCParticle& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const MCParticle& p1,
//       const MCParticle& p2 );

  const podio::ObjectID getObjectID() const;

private:
  MCParticleObj* m_obj;

};

#endif
