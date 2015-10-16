// standard includes
#include <stdexcept>
#include "GenVertexCollection.h" 
#include "GenVertexCollection.h" 
#include "ParticleCollection.h" 


#include "MCParticleCollection.h"

MCParticleCollection::MCParticleCollection() : m_collectionID(0), m_entries() ,m_rel_StartVertex(new std::vector<ConstGenVertex>()),m_rel_EndVertex(new std::vector<ConstGenVertex>()),m_rel_RecParticle(new std::vector<ConstParticle>()),m_refCollections(nullptr), m_data(new MCParticleDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

}

const MCParticle MCParticleCollection::operator[](unsigned int index) const {
  return MCParticle(m_entries[index]);
}

const MCParticle MCParticleCollection::at(unsigned int index) const {
  return MCParticle(m_entries.at(index));
}

int  MCParticleCollection::size() const {
  return m_entries.size();
}

MCParticle MCParticleCollection::create(){
  auto obj = new MCParticleObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return MCParticle(obj);
}

void MCParticleCollection::clear(){
  m_data->clear();
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_StartVertex)) {item.unlink(); }
  m_rel_StartVertex->clear();
  for (auto& item : (*m_rel_EndVertex)) {item.unlink(); }
  m_rel_EndVertex->clear();
  for (auto& item : (*m_rel_RecParticle)) {item.unlink(); }
  m_rel_RecParticle->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void MCParticleCollection::prepareForWrite(){
  int index = 0;
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  if (m_refCollections != nullptr) {
    for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  }
  
  for(int i=0, size = m_data->size(); i != size; ++i){
  
  }
    for (auto& obj : m_entries) {(*m_refCollections)[0]->emplace_back(obj->m_StartVertex->getObjectID());};
  for (auto& obj : m_entries) {(*m_refCollections)[1]->emplace_back(obj->m_EndVertex->getObjectID());};
  for (auto& obj : m_entries) {(*m_refCollections)[2]->emplace_back(obj->m_RecParticle->getObjectID());};

}

void MCParticleCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new MCParticleObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool MCParticleCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[0])[i];
    CollectionBase* coll = nullptr;
    collectionProvider->get(id.collectionID,coll);
    GenVertexCollection* tmp_coll = static_cast<GenVertexCollection*>(coll);
    m_entries[i]->m_StartVertex = new ConstGenVertex((*tmp_coll)[id.index]);
  }
  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[1])[i];
    CollectionBase* coll = nullptr;
    collectionProvider->get(id.collectionID,coll);
    GenVertexCollection* tmp_coll = static_cast<GenVertexCollection*>(coll);
    m_entries[i]->m_EndVertex = new ConstGenVertex((*tmp_coll)[id.index]);
  }
  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[2])[i];
    CollectionBase* coll = nullptr;
    collectionProvider->get(id.collectionID,coll);
    ParticleCollection* tmp_coll = static_cast<ParticleCollection*>(coll);
    m_entries[i]->m_RecParticle = new ConstParticle((*tmp_coll)[id.index]);
  }

  return true; //TODO: check success
}

void MCParticleCollection::push_back(ConstMCParticle object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void MCParticleCollection::setBuffer(void* address){
  m_data = static_cast<MCParticleDataContainer*>(address);
}


const MCParticle MCParticleCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const MCParticle* MCParticleCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const MCParticleCollectionIterator& MCParticleCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}
