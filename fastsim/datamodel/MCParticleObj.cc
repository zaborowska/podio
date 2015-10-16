#include "MCParticleObj.h"
#include "GenVertexConst.h"
#include "GenVertexConst.h"
#include "ParticleConst.h"


MCParticleObj::MCParticleObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_StartVertex(new ConstGenVertex())
,m_EndVertex(new ConstGenVertex())
,m_RecParticle(new ConstParticle())

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
delete m_StartVertex;
delete m_EndVertex;
delete m_RecParticle;

  }
}
