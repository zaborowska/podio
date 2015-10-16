// datamodel specific includes
#include "GenVertex.h"
#include "GenVertexConst.h"
#include "GenVertexObj.h"
#include "GenVertexData.h"
#include "GenVertexCollection.h"
#include <iostream>

GenVertex::GenVertex() : m_obj(new GenVertexObj()){
 m_obj->acquire();
};

GenVertex::GenVertex(LorentzVectorPosition Position) : m_obj(new GenVertexObj()){
 m_obj->acquire();
   m_obj->data.Position = Position;
};

GenVertex::GenVertex(const GenVertex& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

GenVertex& GenVertex::operator=(const GenVertex& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

GenVertex::GenVertex(GenVertexObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

GenVertex GenVertex::clone() const {
  return {new GenVertexObj(*m_obj)};
}

GenVertex::~GenVertex(){
  if ( m_obj != nullptr) m_obj->release();
}

GenVertex::operator ConstGenVertex() const {return ConstGenVertex(m_obj);};


void GenVertex::Position(class LorentzVectorPosition value){ m_obj->data.Position = value;}

std::vector<ConstMCParticle>::const_iterator GenVertex::Daughters_begin() const {
  auto ret_value = m_obj->m_Daughters->begin();
  std::advance(ret_value, m_obj->data.Daughters_begin);
  return ret_value;
}

std::vector<ConstMCParticle>::const_iterator GenVertex::Daughters_end() const {
  auto ret_value = m_obj->m_Daughters->begin();
  std::advance(ret_value, m_obj->data.Daughters_end-1);
  return ++ret_value;
}

void GenVertex::addDaughters(ConstMCParticle component) {
  m_obj->m_Daughters->push_back(component);
  m_obj->data.Daughters_end++;
}

unsigned int GenVertex::Daughters_size() const {
  return (m_obj->data.Daughters_end-m_obj->data.Daughters_begin);
}

ConstMCParticle GenVertex::Daughters(unsigned int index) const {
  if (Daughters_size() > index) {
    return m_obj->m_Daughters->at(m_obj->data.Daughters_begin+index);
}
  else throw std::out_of_range ("index out of bounds for existing references");
}
std::vector<ConstMCParticle>::const_iterator GenVertex::Parents_begin() const {
  auto ret_value = m_obj->m_Parents->begin();
  std::advance(ret_value, m_obj->data.Parents_begin);
  return ret_value;
}

std::vector<ConstMCParticle>::const_iterator GenVertex::Parents_end() const {
  auto ret_value = m_obj->m_Parents->begin();
  std::advance(ret_value, m_obj->data.Parents_end-1);
  return ++ret_value;
}

void GenVertex::addParents(ConstMCParticle component) {
  m_obj->m_Parents->push_back(component);
  m_obj->data.Parents_end++;
}

unsigned int GenVertex::Parents_size() const {
  return (m_obj->data.Parents_end-m_obj->data.Parents_begin);
}

ConstMCParticle GenVertex::Parents(unsigned int index) const {
  if (Parents_size() > index) {
    return m_obj->m_Parents->at(m_obj->data.Parents_begin+index);
}
  else throw std::out_of_range ("index out of bounds for existing references");
}

bool  GenVertex::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID GenVertex::getObjectID() const {
  return m_obj->id;
}

bool GenVertex::operator==(const ConstGenVertex& other) const {
     return (m_obj==other.m_obj);
}


//bool operator< (const GenVertex& p1, const GenVertex& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}
