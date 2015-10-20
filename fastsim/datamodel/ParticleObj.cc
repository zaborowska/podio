#include "ParticleObj.h"
#include "MCParticleConst.h"


ParticleObj::ParticleObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_SimParticle(nullptr)

    { }

ParticleObj::ParticleObj(const podio::ObjectID id, ParticleData data) :
    ObjBase{id,0},
    data(data)
    { }

ParticleObj::ParticleObj(const ParticleObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

ParticleObj::~ParticleObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_SimParticle;

  }
}
