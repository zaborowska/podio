#include "MCParticleObj.h"
#include "ParticleConst.h"
#include "GenVertexConst.h"
#include "GenVertexConst.h"


MCParticleObj::MCParticleObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_RecParticle(nullptr)
,m_StartVertex(nullptr)
,m_EndVertex(nullptr)

    { }

MCParticleObj::MCParticleObj(const podio::ObjectID id, MCParticleData data) :
    ObjBase{id,0},
    data(data)
    { }

MCParticleObj::MCParticleObj(const MCParticleObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

MCParticleObj::~MCParticleObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_RecParticle;
delete m_StartVertex;
delete m_EndVertex;

  }
}
