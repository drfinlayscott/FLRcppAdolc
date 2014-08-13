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

#include "control.h"


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

/* Everything Louder Than Everything Else 
 * The Operating Model Class
 */

// Not templated as this class for projecting with the control object - must have AD for solving

class operatingModel {
    public:
        // /* Constructors */
		operatingModel();
		//operatingModel(SEXP flb_sexp); // No as because what would it take. An FLStock?
        operator SEXP() const; // Used as intrusive 'wrap' - returns a list of stuff
        operatingModel(const FLFisheriesAdolc fisheries_in, const fwdBiolAdolc biol_in, const FLQuant7Adolc f_in, const FLQuant7 f_spwn_in, const fwdControl ctrl_in);
		operatingModel(const operatingModel& operatingModel_source); // copy constructor to ensure that copy is a deep copy - used when passing FLSs into functions
		operatingModel& operator = (const operatingModel& operatingModel_source); // Assignment operator for a deep copy

        void run(); 
        void run_all_iters(); 
        void project_timestep(const int timestep, const int min_iter=1, const int max_iter=1);


        // age range indices for the f based targets
        Rcpp::IntegerVector get_target_age_range_indices(const int target_no, const int biol_no) const; // Returns the indices of the age range, starts at 0
        // Timestep in which to use fmult to affect the target value
        int get_target_fmult_timestep(const int target_no);

        // Given the target no, evaluate the current value in the operatingModel using the year and season info in the target control
        std::vector<adouble> eval_target(const int target_no, const int min_iter, const int max_iter) const;
        //// Given the target type and the FLQuant information, return all iterations from the operatingModel
        //std::vector<adouble> eval_target_hat(const fwdControlTargetType target_type, const Rcpp::IntegerVector age_range_indices, const int year, const int unit, const int season, const int area) const;
        std::vector<adouble> eval_target(const int target_no, const int year, const int unit, const int season, const int area) const;

        // The target value we are trying to hit - either directly from the control object or a min / max / rel value calculation
        std::vector<double> calc_target_value(const int target_no) const; // gets all iters. 

        // The target value calculations
        // fbar from a catch and fishery on a stock - i.e. partial F - will need to adapt this to include multiple biols in the future
        FLQuantAdolc fbar(const Rcpp::IntegerVector age_range_indices, const int fishery_no, const int catch_no, const int biol_no = 1) const;
        // Total fbar on a biol
        FLQuantAdolc fbar(const Rcpp::IntegerVector age_range_indices, const int biol_no = 1) const;
        // catches from an FLCatch and fishery on a stock - i.e. partial F - will need to adapt this to include multiple biols in the future
        FLQuantAdolc catches(const int fishery_no, const int catch_no, const int biol_no = 1) const;
        // Total catches from a biol
        FLQuantAdolc catches(const int biol_no = 1) const;
        // Various ways of calculating reproductive potential
        FLQuantAdolc ssb(const int biol_no) const;
        FLQuantAdolc ssb(const int timestep, const int unit, const int area, const int biol_no) const; // all iters in a timestep, unit and area
        adouble ssb(const int timestep, const int unit, const int area, const int iter, const int biol_no) const; // single iter in a timestep, unit and area
        adouble ssb(const int year, const int unit, const int season, const int area, const int iter, const int biol_no) const; // single iter in a timestep, unit and area
        // Other targets
        FLQuantAdolc biomass(const int biol_no) const;

    private:
        FLFisheriesAdolc fisheries;
        FLQuant7Adolc f;
        FLQuant7 f_spwn;
        fwdControl ctrl;
    protected:
        fwdBiolAdolc biol; // This is protected because operatingModel is a friend of fwdBiol so we can access the SRR
};



