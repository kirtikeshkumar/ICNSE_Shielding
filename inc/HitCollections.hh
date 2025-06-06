/*
**	Filename : HitCollections.hh
**	2025-06-03
**	username : rsehgal
*/
#ifndef HitCollections_hh
#define HitCollections_hh

#include "G4THitsCollection.hh"
#include "shielding_Hit.hh"
using NaIHitCollection = G4THitsCollection<shielding_Hit>;
using GeHitCollection = G4THitsCollection<shielding_Hit>;

#endif
