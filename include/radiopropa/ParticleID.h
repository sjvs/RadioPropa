#ifndef CRPROPA_PARTICLE_ID_H
#define CRPROPA_PARTICLE_ID_H

#include <cstddef>
#include <vector>
#include <string>

namespace radiopropa {

/** This implements the 2012 Monte Carlo nuclear code scheme.
 * Ion numbers are +/- 10LZZZAAAI.
 * AAA is A - total baryon number
 * ZZZ is Z - total charge
 * L is the total number of strange quarks.
 * I is the isomer number, with I=0 corresponding to the ground state.
 */
int nucleusId(int a, int z);
int chargeNumber(int id);
int massNumber(int id);

bool isNucleus(int id);

/* Additional modules */
std::string convertIdToName(int id); 

/* CRPropa2.0 code scheme */
int convertFromCRPropa2NucleusId(int id);
int convertToCRPropa2NucleusId(int id);

} // namespace radiopropa

#endif // CRPROPA_PARTICLE_ID_H