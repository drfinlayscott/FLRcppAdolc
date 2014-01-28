/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

// Necessary check to avoid the redefinition of FLQuant_base in the RcppExports.cpp
#ifndef _FLQuant_base_
#define _FLQuant_base_

#include "FLQuant_base.h"

#endif
/*
 * fwdSR class
 * Contains data and methods for stock-recruitment relationships
 * It's very similar to the fwdSR class in R
 */

/*-------------------------------------------------------------------*/
/* Making a templated equivalent */
// Only n is templated and can be ADOLC
// The other slots are fixed because they are never dependent
// T is double or adouble
template <typename T>
class fwdSR_base {
    public:
        // /* Constructors */
		fwdSR_base();
		//fwdSR_base(SEXP fls_sexp); // Used as intrusive 'as', takes an fwdSR
		fwdSR_base(const std::string model_name, const FLQuant params, const FLQuant residuals, const bool residuals_mult = TRUE); // Main constructor method
        operator SEXP() const; // Used as intrusive 'wrap' - returns what...? Not an fwdSR. Something to be used for testing. A List to start with
		fwdSR_base(const fwdSR_base& fwdSR_base_source); // copy constructor to ensure that copy is a deep copy - used when passing FLSs into functions
		fwdSR_base& operator = (const fwdSR_base& fwdSR_base_source); // Assignment operator for a deep copy

        // Get accessors with const reinforced
        FLQuant_base<T> n() const;
        // Accessor methods for the slots
        FLQuant_base<T>& n();

        // Different ways of evaluating the model
        T eval_model(const T ssb, const int year, const int unit, const int season, const int area, const int iter);
        //FLQuant_base<T> eval_model(const FLQuant_base<T> ssb);
        //std::vector<T> eval_model(const std::vector<T> ssb);

        // methods
        // getRecruitment(const int timestep);
        // getN(const int timestep, const FLQuant total_f); // What class is total_f and where does it come from? Is this really a function rather than a method?

        // Typedef for the SRR model functions
        typedef T (*srr_model_ptr)(const T, const std::vector<double>);
        typedef std::map<std::string, srr_model_ptr> model_map_type;
        void init_model_map();

        int get_nparams(); // No of params in a time step - the length of the first dimension



    private:
        T (*model) (const T, const std::vector<double>); // Pointer to SRR function
        FLQuant_base<double> params;
        FLQuant_base<double> residuals;
        bool residuals_mult;
        // Map for the SRR models
        //std::map<std::string, srr_model_ptr> map_model_name_to_function;
        model_map_type map_model_name_to_function;
};


typedef fwdSR_base<double> fwdSR;
typedef fwdSR_base<adouble> fwdSRAdolc;

//------------------------------------------------------------------
// SRR functions

template <typename T>
T ricker(const T ssb, const std::vector<double> params);

// std::vec<T> ricker(const std::vec<T> ssb, const FLQuant params);
// FLQuant_base<T> ricker(const FLQuant<T> ssb, const FLQuant params);



