/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#ifndef _FLFishery_
#define _FLFishery_
#include "FLFishery.h"
#endif 

#ifndef _fwdBiol_
#define _fwdBiol_
#include "fwdBiol.h"
#endif 

#ifndef _fwdSR_
#define _fwdSR_
#include "fwdSR.h"
#endif 

#ifndef _FLQuant_multidim_
#define _FLQuant_multidim_
#include "FLQuant_multidim.h"
#endif

template <typename T>
void year_season_to_timestep(const int year, const int season, const FLQuant_base<T>& flq, int& timestep);

template <typename T>
void timestep_to_year_season(const int timestep, const FLQuant_base<T>& flq, int& year, int& season);

double euclid_norm(double* x, const int size_x);

int newton_raphson(std::vector<double>& indep, const int adolc_tape, const int max_iters= 50, const double max_limit = 100, const double tolerance = 1e-12);

void project_timestep(FLFisheriesAdolc& fisheries, fwdBiolAdolc& biol, std::string srr_model_name, FLQuant params, FLQuant residuals, bool residuals_mult, FLQuantAdolc7& f, const int timestep);


/* Everything Louder Than Everything Else 
 * The Operating Model Class
 */

// Template it because we may want a pure double one
template <typename T>
class operatingModel_base {
    public:
        // /* Constructors */
		operatingModel_base();
		//operatingModel_base(SEXP flb_sexp); // No as because what would it take. An FLStock?
        operator SEXP() const; // Used as intrusive 'wrap' - returns a list of stuff
        operatingModel_base(const FLFisheries_base<T> fisheries_in, const fwdBiol_base<T> biol_in, const FLQuant7_base<T> f_in, const FLQuant7_base<T> f_spwn_in);

		operatingModel_base(const operatingModel_base& operatingModel_base_source); // copy constructor to ensure that copy is a deep copy - used when passing FLSs into functions
		operatingModel_base& operator = (const operatingModel_base& operatingModel_base_source); // Assignment operator for a deep copy

        void run(); // Need to specialise for AD and non-AD version
        void project_timestep();

        FLQuant_base<T> ssb() const;
        std::vector<T> ssb(const int timestep) const; // all iters
        T ssb(const int timestep, const int iter) const; 


    private:
        fwdBiol_base<T> biol;
        FLFisheries_base<T> fisheries;
        FLQuant7_base<T> f;
        FLQuant7_base<T> f_spwn;
};


typedef operatingModel_base<double> operatingModel;
typedef operatingModel_base<adouble> operatingModelAdolc;
