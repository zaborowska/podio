// datamodel specific includes
#include "Particle.h"
#include "ParticleConst.h"
#include "ParticleObj.h"
#include "ParticleData.h"
#include "ParticleCollection.h"
#include <iostream>
#include "MCParticle.h"

Particle::Particle() : m_obj(new ParticleObj()){
 m_obj->acquire();
};

Particle::Particle(BareParticle Core) : m_obj(new ParticleObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
};

Particle::Particle(const Particle& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

Particle& Particle::operator=(const Particle& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

Particle::Particle(ParticleObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

Particle Particle::clone() const {
  return {new ParticleObj(*m_obj)};
}

Particle::~Particle(){
  if ( m_obj != nullptr) m_obj->release();
}

Particle::operator ConstParticle() const {return ConstParticle(m_obj);};

  const ConstMCParticle Particle::SimParticle() { return ConstMCParticle(*(m_obj->m_SimParticle));};

void Particle::Core(class BareParticle value){ m_obj->data.Core = value;}
void Particle::SimParticle(ConstMCParticle value) { if (m_obj->m_SimParticle != nullptr) delete m_obj->m_SimParticle; m_obj->m_SimParticle = new ConstMCParticle(value); };


bool  Particle::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID Particle::getObjectID() const {
  return m_obj->id;
}

bool Particle::operator==(const ConstParticle& other) const {
     return (m_obj==other.m_obj);
}


//bool operator< (const Particle& p1, const Particle& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}
