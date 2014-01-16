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
 * fwdBiol class
 * Contains biological information (incuding abundance) by age for making projections
 * It's very similar to the FLBiol class in R but also includes SRR information
 */

/*-------------------------------------------------------------------*/
/* Making a templated equivalent */
// Only n is templated and can be ADOLC
// The other slots are fixed because they are never dependent
// T is double or adouble
template <typename T>
class fwdBiol_base {
    public:
        // /* Constructors */
		fwdBiol_base();
		fwdBiol_base(SEXP fls_sexp); // Used as intrusive 'as', takes an FLBiol but with no SRR
        operator SEXP() const; // Used as intrusive 'wrap' - returns an FLBiol
		fwdBiol_base(const fwdBiol_base& fwdBiol_base_source); // copy constructor to ensure that copy is a deep copy - used when passing FLSs into functions
		fwdBiol_base& operator = (const fwdBiol_base& fwdBiol_base_source); // Assignment operator for a deep copy

        // Get accessors with const reinforced
        FLQuant_base<T> n() const;
        FLQuant wt() const;
        FLQuant m() const;
        FLQuant spwn() const;
        FLQuant fec() const;
        // Accessor methods for the slots
        FLQuant_base<T>& n();
        FLQuant& wt();
        FLQuant& m();
        FLQuant& spwn();
        FLQuant& fec();

        std::string get_name() const;
        std::string get_desc() const;
        Rcpp::NumericVector get_range() const;

        // methods
        // getRecruitment(const int timestep);
        // getN(const int timestep, const FLQuant total_f); // What class is total_f and where does it come from? Is this really a function rather than a method?

    private:
        std::string name;
        std::string desc;
        Rcpp::NumericVector range;
        FLQuant_base<T> n_flq;
        FLQuant wt_flq;
        FLQuant m_flq;
        FLQuant spwn_flq;
        FLQuant fec_flq;
        // SRR srr;
};


typedef fwdBiol_base<double> fwdBiol;
typedef fwdBiol_base<adouble> fwdBiolAdolc;

/*-----------------------------------------------------------------*/
// functions that should be methods for a class: operating_model
// is operating_model templated? Or is it just AD?
/*
class operating_model {
    public:
        // Constructors - how do they work?
        operating_model();
        operating_model(SEXP fls_sexp); // Used as intrusive 'as'.
        operator SEXP() const; // Used as intrusive 'wrap'
		operating_model(const operating_model& operating_model_source); // copy constructor to ensure that copy is a deep copy - used when passing object into functions
		operating_model& operator = (const operating_model& operating_model_source); // Assignment operator for a deep copy
        operating_model(fwdBiol_Adolc biol_source); 
        // Methods
        void calc_N(const int timestep);
        void timestep_to_year_season(const int timestep, int& year, int& season); // Indexing start at 1
        fwdBiol_Adolc get_biol(); 
    private:
        fwdBiol_Adolc biol; // Is this a double or an Adolc?
        //fishery fishery;
};

*/
/*-----------------------------------------------------------------*/
// Original, non-templated version
/*
class fwdBiol {
    public:
        //  Constructors 
		fwdBiol();
		fwdBiol(SEXP fls_sexp); // Used as intrusive 'as', uses an FLBiol but with no SRR
        operator SEXP() const; // Used as intrusive 'wrap'
		fwdBiol(const fwdBiol& fwdBiol_source); // copy constructor to ensure that copy is a deep copy - used when passing FLSs into functions
		fwdBiol& operator = (const fwdBiol& fwdBiol_source); // Assignment operator for a deep copy
        // members
        // All the slots from an FLBiol and FLStock that may be useful
        // These data members are public but the actual data in the FLQuant members is not.
        // It can only be accessed by the () operators 
        FLQuant n;
        FLQuant wt;
        FLQuant m;
        FLQuant spwn;
        FLQuant fec;
        //
        // methods
        // getRecruitment(const int timestep);
        // getN(const int timestep, const FLQuant total_f); // What class is total_f and where does it come from? Is this really a function rather than a method?

    private:
        std::string name;
        std::string desc;
        Rcpp::NumericVector range;
        // SRR srr;

};
*/
