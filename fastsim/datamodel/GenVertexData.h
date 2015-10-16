#ifndef GenVertexDATA_H
#define GenVertexDATA_H

//  vertex position (x,y,z,ct) [cm]
// author: A. Zaborowska

#include "LorentzVectorPosition.h"


class GenVertexData {
public:
  LorentzVectorPosition Position; /// vertex position (x,y,z,ct) [cm] 
  unsigned int Daughters_begin; 
  unsigned int Daughters_end; 
  unsigned int Parents_begin; 
  unsigned int Parents_end; 

};

#endif
