// standard includes
#include <stdexcept>
#include "MCParticleCollection.h" 
#include "MCParticleCollection.h" 


#include "GenVertexCollection.h"

GenVertexCollection::GenVertexCollection() : m_collectionID(0), m_entries() ,m_rel_Daughters(new std::vector<ConstMCParticle>()),m_rel_Parents(new std::vector<ConstMCParticle>()),m_refCollections(nullptr), m_data(new GenVertexDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

}

const GenVertex GenVertexCollection::operator[](unsigned int index) const {
  return GenVertex(m_entries[index]);
}

const GenVertex GenVertexCollection::at(unsigned int index) const {
  return GenVertex(m_entries.at(index));
}

int  GenVertexCollection::size() const {
  return m_entries.size();
}

GenVertex GenVertexCollection::create(){
  auto obj = new GenVertexObj();
  m_entries.emplace_back(obj);
  m_rel_Daughters_tmp.push_back(obj->m_Daughters);
  m_rel_Parents_tmp.push_back(obj->m_Parents);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return GenVertex(obj);
}

void GenVertexCollection::clear(){
  m_data->clear();
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  // clear relations to Daughters. Make sure to unlink() the reference data as they may be gone already
  for (auto& pointer : m_rel_Daughters_tmp) {for(auto& item : (*pointer)) {item.unlink();}; delete pointer;}
  m_rel_Daughters_tmp.clear();
  for (auto& item : (*m_rel_Daughters)) {item.unlink(); }
  m_rel_Daughters->clear();
  // clear relations to Parents. Make sure to unlink() the reference data as they may be gone already
  for (auto& pointer : m_rel_Parents_tmp) {for(auto& item : (*pointer)) {item.unlink();}; delete pointer;}
  m_rel_Parents_tmp.clear();
  for (auto& item : (*m_rel_Parents)) {item.unlink(); }
  m_rel_Parents->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void GenVertexCollection::prepareForWrite(){
  int index = 0;
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  if (m_refCollections != nullptr) {
    for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  }
  
  for(int i=0, size = m_data->size(); i != size; ++i){
     (*m_data)[i].Daughters_begin=index;
   (*m_data)[i].Daughters_end+=index;
   index = (*m_data)[index].Daughters_end;
   for(auto it : (*m_rel_Daughters_tmp[i])) {
     if (it.getObjectID().index == podio::ObjectID::untracked)
       throw std::runtime_error("Trying to persistify untracked object");
     (*m_refCollections)[0]->emplace_back(it.getObjectID());
     m_rel_Daughters->push_back(it);
   }
   (*m_data)[i].Parents_begin=index;
   (*m_data)[i].Parents_end+=index;
   index = (*m_data)[index].Parents_end;
   for(auto it : (*m_rel_Parents_tmp[i])) {
     if (it.getObjectID().index == podio::ObjectID::untracked)
       throw std::runtime_error("Trying to persistify untracked object");
     (*m_refCollections)[1]->emplace_back(it.getObjectID());
     m_rel_Parents->push_back(it);
   }

  }
  
}

void GenVertexCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new GenVertexObj({index,m_collectionID}, data);
        obj->m_Daughters = m_rel_Daughters;    obj->m_Parents = m_rel_Parents;
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool GenVertexCollection::setReferences(const podio::ICollectionProvider* collectionProvider){
  for(unsigned int i=0, size=(*m_refCollections)[0]->size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[0])[i];
    CollectionBase* coll = nullptr;
    collectionProvider->get(id.collectionID,coll);
    MCParticleCollection* tmp_coll = static_cast<MCParticleCollection*>(coll);
    auto tmp = (*tmp_coll)[id.index];
    m_rel_Daughters->emplace_back(tmp);
  }
  for(unsigned int i=0, size=(*m_refCollections)[1]->size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[1])[i];
    CollectionBase* coll = nullptr;
    collectionProvider->get(id.collectionID,coll);
    MCParticleCollection* tmp_coll = static_cast<MCParticleCollection*>(coll);
    auto tmp = (*tmp_coll)[id.index];
    m_rel_Parents->emplace_back(tmp);
  }


  return true; //TODO: check success
}

void GenVertexCollection::push_back(ConstGenVertex object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
          m_rel_Daughters_tmp.push_back(obj->m_Daughters);
  m_rel_Parents_tmp.push_back(obj->m_Parents);

    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void GenVertexCollection::setBuffer(void* address){
  m_data = static_cast<GenVertexDataContainer*>(address);
}


const GenVertex GenVertexCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const GenVertex* GenVertexCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const GenVertexCollectionIterator& GenVertexCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}
