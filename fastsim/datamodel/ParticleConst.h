#ifndef ConstParticle_H
#define ConstParticle_H
#include "ParticleData.h"
#include "BareParticle.h"

#include <vector>
#include "podio/ObjectID.h"

//  general particle information
// author: A. Zaborowska

//forward declarations
class ParticleCollection;
class ParticleCollectionIterator;


#include "ParticleObj.h"

class ConstParticle {

  friend Particle;
  friend ParticleCollection;
  friend ParticleCollectionIterator;

public:

  /// default constructor
  ConstParticle();
  ConstParticle(BareParticle Core);

  /// constructor from existing ParticleObj
  ConstParticle(ParticleObj* obj);
  /// copy constructor
  ConstParticle(const ConstParticle& other);
  /// copy-assignment operator
  ConstParticle& operator=(const ConstParticle& other);
  /// support cloning (deep-copy)
  ConstParticle clone() const;
  /// destructor
  ~ConstParticle();


public:

  const BareParticle& Core() const { return m_obj->data.Core; };


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleObj instance
  void unlink(){m_obj = nullptr;};

  bool operator==(const ConstParticle& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const Particle& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Particle& p1,
//       const Particle& p2 );

  const podio::ObjectID getObjectID() const;

private:
  ParticleObj* m_obj;

};

#endif
