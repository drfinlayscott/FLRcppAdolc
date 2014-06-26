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

// Converting timestep to year and season and vice versa
// Several options
template <typename T>
void year_season_to_timestep(const int year, const int season, const FLQuant_base<T>& flq, int& timestep);

template <typename T>
void timestep_to_year_season(const int timestep, const FLQuant_base<T>& flq, int& year, int& season);

void year_season_to_timestep(const int year, const int season, const int nseason, int& timestep);
void timestep_to_year_season(const int timestep, const int nseason, int& year, int& season);

double euclid_norm(double* x, const int size_x);

// A Newton Raphson solver for a function that has already been taped.
// Pass in the independent variables, tape no. and control parameters
int newton_raphson(std::vector<double>& indep, const int adolc_tape, const int max_iters= 50, const double max_limit = 100, const double tolerance = 1e-12);

//void project_timestep(FLFisheriesAdolc& fisheries, fwdBiolAdolc& biol, std::string srr_model_name, FLQuant params, FLQuant residuals, bool residuals_mult, FLQuantAdolc7& f, const int timestep);


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
        void project_timestep(const int timestep);

        // Various ways of calculating reproductive potential
        FLQuant_base<T> ssb() const;
        FLQuant_base<T> ssb(const int timestep, const int unit, const int area) const; // all iters in a timestep, unit and area
        T ssb(const int timestep, const int unit, const int area, const int iter) const; // single iter in a timestep, unit and area
        T ssb(const int year, const int unit, const int season, const int area, const int iter) const; // single iter in a timestep, unit and area


    private:
        FLFisheries_base<T> fisheries;
        FLQuant7_base<T> f;
        FLQuant7_base<T> f_spwn;
    protected:
        fwdBiol_base<T> biol; // Why is this protected instead of private?
};


typedef operatingModel_base<double> operatingModel;
typedef operatingModel_base<adouble> operatingModelAdolc;

