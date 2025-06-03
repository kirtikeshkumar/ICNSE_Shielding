/*
**	Filename : HitCollections.h
**	2025-06-03
**	username : rsehgal
*/
#ifndef HitCollections_h
#define HitCollections_h

#include "G4THitsCollection.hh"
#include "shielding_Hit.h"
using NaIHitCollection = G4THitsCollection<shielding_Hit>;
using GeHitCollection = G4THitsCollection<shielding_Hit>;

#endif
