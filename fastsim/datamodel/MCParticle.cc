// datamodel specific includes
#include "MCParticle.h"
#include "MCParticleConst.h"
#include "MCParticleObj.h"
#include "MCParticleData.h"
#include "MCParticleCollection.h"
#include <iostream>
#include "GenVertex.h"
#include "GenVertex.h"
#include "Particle.h"

MCParticle::MCParticle() : m_obj(new MCParticleObj()){
 m_obj->acquire();
};

MCParticle::MCParticle(BareParticle Core) : m_obj(new MCParticleObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
};

MCParticle::MCParticle(const MCParticle& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

MCParticle& MCParticle::operator=(const MCParticle& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

MCParticle::MCParticle(MCParticleObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

MCParticle MCParticle::clone() const {
  return {new MCParticleObj(*m_obj)};
}

MCParticle::~MCParticle(){
  if ( m_obj != nullptr) m_obj->release();
}

MCParticle::operator ConstMCParticle() const {return ConstMCParticle(m_obj);};

  const ConstGenVertex MCParticle::StartVertex() { return ConstGenVertex(*(m_obj->m_StartVertex));};
  const ConstGenVertex MCParticle::EndVertex() { return ConstGenVertex(*(m_obj->m_EndVertex));};
  const ConstParticle MCParticle::RecParticle() { return ConstParticle(*(m_obj->m_RecParticle));};

void MCParticle::Core(class BareParticle value){ m_obj->data.Core = value;}
void MCParticle::StartVertex(ConstGenVertex value) { if (m_obj->m_StartVertex != nullptr) delete m_obj->m_StartVertex; m_obj->m_StartVertex = new ConstGenVertex(value); };
void MCParticle::EndVertex(ConstGenVertex value) { if (m_obj->m_EndVertex != nullptr) delete m_obj->m_EndVertex; m_obj->m_EndVertex = new ConstGenVertex(value); };
void MCParticle::RecParticle(ConstParticle value) { if (m_obj->m_RecParticle != nullptr) delete m_obj->m_RecParticle; m_obj->m_RecParticle = new ConstParticle(value); };


bool  MCParticle::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID MCParticle::getObjectID() const {
  return m_obj->id;
}

bool MCParticle::operator==(const ConstMCParticle& other) const {
     return (m_obj==other.m_obj);
}


//bool operator< (const MCParticle& p1, const MCParticle& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}
