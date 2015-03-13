#include "GaudiKernel/DeclareFactoryEntries.h"
#include "EemissAlg/Eemiss.h"

DECLARE_ALGORITHM_FACTORY( Eemiss )

DECLARE_FACTORY_ENTRIES( EemissAlg ) {
  DECLARE_ALGORITHM(Eemiss);
}

