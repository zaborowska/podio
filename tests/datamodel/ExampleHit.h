#ifndef ExampleHit_H
#define ExampleHit_H
#include "ExampleHitData.h"

#include <vector>
#include "podio/ObjectID.h"

//  measured energy deposit
// author: B. Hegner

//forward declarations
class ExampleHitCollection;
class ExampleHitCollectionIterator;
class ConstExampleHit;


#include "ExampleHitConst.h"
#include "ExampleHitObj.h"

class ExampleHit {

  friend ExampleHitCollection;
  friend ExampleHitCollectionIterator;
  friend ConstExampleHit;

public:

  /// default constructor
  ExampleHit();
    ExampleHit(double x,double y,double z,double energy);

  /// constructor from existing ExampleHitObj
  ExampleHit(ExampleHitObj* obj);
  /// copy constructor
  ExampleHit(const ExampleHit& other);
  /// copy-assignment operator
  ExampleHit& operator=(const ExampleHit& other);
  /// support cloning (deep-copy)
  ExampleHit clone() const;
  /// destructor
  ~ExampleHit();

  /// conversion to const object
  operator ConstExampleHit () const;

public:

  const double& x() const { return m_obj->data.x; };
  const double& y() const { return m_obj->data.y; };
  const double& z() const { return m_obj->data.z; };
  const double& energy() const { return m_obj->data.energy; };

  void x(double value) { m_obj->data.x = value; };
  void y(double value) { m_obj->data.y = value; };
  void z(double value) { m_obj->data.z = value; };
  void energy(double value) { m_obj->data.energy = value; };


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ExampleHitObj instance
  void unlink(){m_obj = nullptr;};

  bool operator==(const ExampleHit& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstExampleHit& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ExampleHit& p1,
//       const ExampleHit& p2 );

  const podio::ObjectID getObjectID() const;

private:
  ExampleHitObj* m_obj;

};

#endif