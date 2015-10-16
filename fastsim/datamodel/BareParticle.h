#ifndef BareParticle_H
#define BareParticle_H
#include "LorentzVectorMomentum.h"


class BareParticle {
public:
  unsigned Status;
  int Type;
  short Charge;
  unsigned Bits;
  LorentzVectorMomentum P4;

};

#endif
