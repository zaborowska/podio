#ifndef MCParticleOBJ_H
#define MCParticleOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "MCParticleData.h"



// forward declarations
class MCParticle;
class ConstMCParticle;
class ConstGenVertex;
class ConstGenVertex;
class ConstParticle;


class MCParticleObj : public podio::ObjBase {
public:
  /// constructor
  MCParticleObj();
  /// copy constructor (does a deep-copy of relation containers)
  MCParticleObj(const MCParticleObj&);
  /// constructor from ObjectID and MCParticleData
  /// does not initialize the internal relation containers
  MCParticleObj(const podio::ObjectID id, MCParticleData data);
  virtual ~MCParticleObj();

public:
  MCParticleData data;
  ConstGenVertex* m_StartVertex;
  ConstGenVertex* m_EndVertex;
  ConstParticle* m_RecParticle;


};


#endif
