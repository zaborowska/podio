// datamodel specific includes
#include "GenVertex.h"
#include "GenVertexConst.h"
#include "GenVertexObj.h"
#include "GenVertexData.h"
#include "GenVertexCollection.h"
#include <iostream>

ConstGenVertex::ConstGenVertex() : m_obj(new GenVertexObj()){
 m_obj->acquire();
};

ConstGenVertex::ConstGenVertex(LorentzVectorPosition Position) : m_obj(new GenVertexObj()){
 m_obj->acquire();
   m_obj->data.Position = Position;
};


ConstGenVertex::ConstGenVertex(const ConstGenVertex& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstGenVertex& ConstGenVertex::operator=(const ConstGenVertex& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstGenVertex::ConstGenVertex(GenVertexObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstGenVertex ConstGenVertex::clone() const {
  return {new GenVertexObj(*m_obj)};
}

ConstGenVertex::~ConstGenVertex(){
  if ( m_obj != nullptr) m_obj->release();
}


std::vector<ConstMCParticle>::const_iterator ConstGenVertex::Daughters_begin() const {
  auto ret_value = m_obj->m_Daughters->begin();
  std::advance(ret_value, m_obj->data.Daughters_begin);
  return ret_value;
}

std::vector<ConstMCParticle>::const_iterator ConstGenVertex::Daughters_end() const {
  auto ret_value = m_obj->m_Daughters->begin();
  std::advance(ret_value, m_obj->data.Daughters_end-1);
  return ++ret_value;
}

unsigned int ConstGenVertex::Daughters_size() const {
  return (m_obj->data.Daughters_end-m_obj->data.Daughters_begin);
}

ConstMCParticle ConstGenVertex::Daughters(unsigned int index) const {
  if (Daughters_size() > index) {
    return m_obj->m_Daughters->at(m_obj->data.Daughters_begin+index);
}
  else throw std::out_of_range ("index out of bounds for existing references");
}
std::vector<ConstMCParticle>::const_iterator ConstGenVertex::Parents_begin() const {
  auto ret_value = m_obj->m_Parents->begin();
  std::advance(ret_value, m_obj->data.Parents_begin);
  return ret_value;
}

std::vector<ConstMCParticle>::const_iterator ConstGenVertex::Parents_end() const {
  auto ret_value = m_obj->m_Parents->begin();
  std::advance(ret_value, m_obj->data.Parents_end-1);
  return ++ret_value;
}

unsigned int ConstGenVertex::Parents_size() const {
  return (m_obj->data.Parents_end-m_obj->data.Parents_begin);
}

ConstMCParticle ConstGenVertex::Parents(unsigned int index) const {
  if (Parents_size() > index) {
    return m_obj->m_Parents->at(m_obj->data.Parents_begin+index);
}
  else throw std::out_of_range ("index out of bounds for existing references");
}

bool  ConstGenVertex::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstGenVertex::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstGenVertex::operator==(const GenVertex& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const GenVertex& p1, const GenVertex& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}
