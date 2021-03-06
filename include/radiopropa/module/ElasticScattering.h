#ifndef CRPROPA_ELASTICSCATTERING_H
#define CRPROPA_ELASTICSCATTERING_H

#include "radiopropa/Module.h"
#include "radiopropa/PhotonBackground.h"

#include <vector>

namespace radiopropa {

/**
 @class ElasticScattering
 @brief Elastic scattering of background photons on cosmic ray nuclei.
 */
class ElasticScattering: public Module {
private:
    PhotonField photonField;

    std::vector<double> tabRate; // elastic scattering rate
    std::vector<std::vector<double> > tabCDF; // CDF as function of background photon frequency

    static const double lgmin; // minimum log10(Lorentz-factor)
    static const double lgmax; // maximum log10(Lorentz-factor)
    static const size_t nlg;   // number of Lorentz-factor steps
    static const double epsmin; // minimum log10(eps / J)
    static const double epsmax; // maximum log10(eps / J)
    static const size_t neps;   // number of eps steps

public:
    ElasticScattering(PhotonField photonField = CMB);
    void initRate(std::string filename);
    void initCDF(std::string filename);
    void setPhotonField(PhotonField photonField);
    void process(Candidate *candidate) const;
};

} // namespace radiopropa

#endif // CRPROPA_ELASTICSCATTERING_H
