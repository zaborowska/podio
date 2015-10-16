#ifndef GenVertex_H
#define GenVertex_H
#include "GenVertexData.h"
#include "LorentzVectorPosition.h"
#include <vector>
#include "MCParticle.h"
#include "MCParticle.h"

#include <vector>
#include "podio/ObjectID.h"

//  vertex position (x,y,z,ct) [cm]
// author: A. Zaborowska

//forward declarations
class GenVertexCollection;
class GenVertexCollectionIterator;
class ConstGenVertex;


#include "GenVertexConst.h"
#include "GenVertexObj.h"

class GenVertex {

  friend GenVertexCollection;
  friend GenVertexCollectionIterator;
  friend ConstGenVertex;

public:

  /// default constructor
  GenVertex();
    GenVertex(LorentzVectorPosition Position);

  /// constructor from existing GenVertexObj
  GenVertex(GenVertexObj* obj);
  /// copy constructor
  GenVertex(const GenVertex& other);
  /// copy-assignment operator
  GenVertex& operator=(const GenVertex& other);
  /// support cloning (deep-copy)
  GenVertex clone() const;
  /// destructor
  ~GenVertex();

  /// conversion to const object
  operator ConstGenVertex () const;

public:

  const LorentzVectorPosition& Position() const { return m_obj->data.Position; };

  LorentzVectorPosition& Position() { return m_obj->data.Position; };
  void Position(class LorentzVectorPosition value);

  void addDaughters(ConstMCParticle);
  unsigned int Daughters_size() const;
  ConstMCParticle Daughters(unsigned int) const;
  std::vector<ConstMCParticle>::const_iterator Daughters_begin() const;
  std::vector<ConstMCParticle>::const_iterator Daughters_end() const;
  void addParents(ConstMCParticle);
  unsigned int Parents_size() const;
  ConstMCParticle Parents(unsigned int) const;
  std::vector<ConstMCParticle>::const_iterator Parents_begin() const;
  std::vector<ConstMCParticle>::const_iterator Parents_end() const;

  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from GenVertexObj instance
  void unlink(){m_obj = nullptr;};

  bool operator==(const GenVertex& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstGenVertex& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const GenVertex& p1,
//       const GenVertex& p2 );

  const podio::ObjectID getObjectID() const;

private:
  GenVertexObj* m_obj;

};

#endif
