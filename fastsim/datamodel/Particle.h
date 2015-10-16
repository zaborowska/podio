#ifndef Particle_H
#define Particle_H
#include "ParticleData.h"
#include "BareParticle.h"

#include <vector>
#include "podio/ObjectID.h"

//  general particle information
// author: A. Zaborowska

//forward declarations
class ParticleCollection;
class ParticleCollectionIterator;
class ConstParticle;


#include "ParticleConst.h"
#include "ParticleObj.h"

class Particle {

  friend ParticleCollection;
  friend ParticleCollectionIterator;
  friend ConstParticle;

public:

  /// default constructor
  Particle();
    Particle(BareParticle Core);

  /// constructor from existing ParticleObj
  Particle(ParticleObj* obj);
  /// copy constructor
  Particle(const Particle& other);
  /// copy-assignment operator
  Particle& operator=(const Particle& other);
  /// support cloning (deep-copy)
  Particle clone() const;
  /// destructor
  ~Particle();

  /// conversion to const object
  operator ConstParticle () const;

public:

  const BareParticle& Core() const { return m_obj->data.Core; };

  BareParticle& Core() { return m_obj->data.Core; };
  void Core(class BareParticle value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleObj instance
  void unlink(){m_obj = nullptr;};

  bool operator==(const Particle& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstParticle& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Particle& p1,
//       const Particle& p2 );

  const podio::ObjectID getObjectID() const;

private:
  ParticleObj* m_obj;

};

#endif
