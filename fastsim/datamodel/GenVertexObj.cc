#include "GenVertexObj.h"


GenVertexObj::GenVertexObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_Daughters(new std::vector<ConstMCParticle>()),m_Parents(new std::vector<ConstMCParticle>())
    { }

GenVertexObj::GenVertexObj(const podio::ObjectID id, GenVertexData data) :
    ObjBase{id,0},
    data(data)
    { }

GenVertexObj::GenVertexObj(const GenVertexObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    ,m_Daughters(new std::vector<ConstMCParticle>(*(other.m_Daughters))),m_Parents(new std::vector<ConstMCParticle>(*(other.m_Parents)))
    { }

GenVertexObj::~GenVertexObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_Daughters;
delete m_Parents;

  }
}
