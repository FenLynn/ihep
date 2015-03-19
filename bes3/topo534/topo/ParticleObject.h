#ifndef ParticleObject_h
#define ParticleObject_h 1

#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

class ParticleObject
{
  public:
    ParticleObject();
    ~ParticleObject();

    std::string GetParName(int ) const;
    double GetParMass(int ) const;

  private:

    std::ifstream parListFile;

    struct MyParticle
    {
      std::string col1;
      std::string col2;
      std::string ParType;
      std::string ParName;
      int ParId;
      double ParMass;
      double ParWidth;
      double ParDm;
      int Par3Charge;
      int Par2Spin;
      double ParLifeTime;
      int ParLundKC;
    };
    MyParticle aMyParticle;

    std::vector<MyParticle> Vparticle;
};
#endif

