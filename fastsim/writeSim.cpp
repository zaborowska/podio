// Data model
#include "EventInfoCollection.h"
#include "MCParticleCollection.h"
#include "GenVertexCollection.h"
#include "ParticleCollection.h"

// STL
#include <iostream>
#include <vector>

// podio specific includes
#include "podio/EventStore.h"
#include "podio/ROOTWriter.h"

int main()
{
  std::cout<<"start processing"<<std::endl;

  auto store = podio::EventStore();
  auto writer = podio::ROOTWriter("fastsim.root", &store);

  auto& info     = store.create<EventInfoCollection>("info");
  auto& mcparticles     = store.create<MCParticleCollection>("mcparticles");
  auto& vertices = store.create<GenVertexCollection>("genvertices");
  auto& particles     = store.create<ParticleCollection>("particles");
  writer.registerForWrite<EventInfoCollection>("info");
  writer.registerForWrite<MCParticleCollection>("mcparticles");
  writer.registerForWrite<GenVertexCollection>("genvertices");
  writer.registerForWrite<ParticleCollection>("particles");

  unsigned nevents=1;

  for(unsigned i=0; i<nevents; ++i)
  {
    if(i % 100 == 0)
      std::cout << "processing event " << i << std::endl;

    auto inf = EventInfo();
    inf.Number(i);
    info.push_back(inf);


    auto mcpart = MCParticle();
    auto mccore = BareParticle();
    mccore.Type = 1;
    mccore.Charge = 1;
    mccore.Status = 1;
    mccore.P4.px = 11.5;
    mccore.P4.py = 7.5;
    mccore.P4.pz = 8.5;
    mccore.P4.e = 85;
    mcpart.Core(mccore);
    mcparticles.push_back(mcpart);

    auto part = Particle();
    auto core = BareParticle();
    core.Type = 1;
    core.Charge = 1;
    core.Status = 1;
    core.P4.px = 11.5;
    core.P4.py = 7.5;
    core.P4.pz = 8.5;
    core.P4.e = 85;
    part.Core(core);
    particles.push_back(part);

    // creating a relation between Particle and MCParticle
    mcpart.RecParticle(part);
    // part.SimParticle(mcpart);

    writer.writeEvent();
    store.clearCollections();
  }

  writer.finish();
}
