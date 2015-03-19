#include "ParticleObject.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

ParticleObject::ParticleObject()
{

  parListFile.open("/ihepbatch/bes/dusx/common/particle.table", std::ios::in);
  std::string line;
  if (parListFile.is_open())
  {

    while (!parListFile.eof())
    {
      //getline (parListFile, line);
      //if (line.substr(0,3)=="add") { std::cout << line << std::endl; }      
      parListFile >> aMyParticle.col1        >> aMyParticle.col2 
                  >> aMyParticle.ParType     >> aMyParticle.ParName 
                  >> aMyParticle.ParId       >> aMyParticle.ParMass 
                  >> aMyParticle.ParWidth    >> aMyParticle.ParDm
                  >> aMyParticle.Par3Charge  >> aMyParticle.Par2Spin
                  >> aMyParticle.ParLifeTime >> aMyParticle.ParLundKC;

      Vparticle.push_back(aMyParticle);
      //std::cout << aMyParticle.ParName << std::endl;
    }

  }
  else
  {
    std::cout << "Unable to open file: particle.table" << std::endl;
    exit(1);
  }

}

ParticleObject::~ParticleObject()
{
  parListFile.close();
}

std::string ParticleObject::GetParName(int pdgid) const
{
  std::string aParName = "Unknown";

  int listLength = Vparticle.size();
  for (int i=0; i<listLength; i++)
  {
    if (Vparticle[i].ParId == pdgid)
    {
      aParName = Vparticle[i].ParName;
      break; 
    }
  }
  return aParName;
}

double ParticleObject::GetParMass(int pdgid) const
{
  double aParMass = 0.0;

  int listLength = Vparticle.size();
  for (int i=0; i<listLength; i++)
  {
    if (Vparticle[i].ParId == pdgid)
    {
      aParMass = Vparticle[i].ParMass;
      break;
    }
  }
  return aParMass;
}
