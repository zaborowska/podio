#ifndef ConstGenVertex_H
#define ConstGenVertex_H
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


#include "GenVertexObj.h"

class ConstGenVertex {

  friend GenVertex;
  friend GenVertexCollection;
  friend GenVertexCollectionIterator;

public:

  /// default constructor
  ConstGenVertex();
  ConstGenVertex(LorentzVectorPosition Position);

  /// constructor from existing GenVertexObj
  ConstGenVertex(GenVertexObj* obj);
  /// copy constructor
  ConstGenVertex(const ConstGenVertex& other);
  /// copy-assignment operator
  ConstGenVertex& operator=(const ConstGenVertex& other);
  /// support cloning (deep-copy)
  ConstGenVertex clone() const;
  /// destructor
  ~ConstGenVertex();


public:

  const LorentzVectorPosition& Position() const { return m_obj->data.Position; };

  unsigned int Daughters_size() const;
  ConstMCParticle Daughters(unsigned int) const;
  std::vector<ConstMCParticle>::const_iterator Daughters_begin() const;
  std::vector<ConstMCParticle>::const_iterator Daughters_end() const;
  unsigned int Parents_size() const;
  ConstMCParticle Parents(unsigned int) const;
  std::vector<ConstMCParticle>::const_iterator Parents_begin() const;
  std::vector<ConstMCParticle>::const_iterator Parents_end() const;

  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from GenVertexObj instance
  void unlink(){m_obj = nullptr;};

  bool operator==(const ConstGenVertex& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const GenVertex& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const GenVertex& p1,
//       const GenVertex& p2 );

  const podio::ObjectID getObjectID() const;

private:
  GenVertexObj* m_obj;

};

#endif
