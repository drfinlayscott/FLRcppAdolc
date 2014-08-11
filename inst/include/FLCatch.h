/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

// Necessary check to avoid the redefinition of FLQuant_base in the RcppExports.cpp
#ifndef _FLQuant_base_
#define _FLQuant_base_

#include "FLQuant_base.h"

#endif
#define _FLCatch_base_
/*
 * FLCatch class
 * Contains catch information (including abundances and selectivity) for making projections
 * It's very similar to the FLCatch class in R
 */

/*-------------------------------------------------------------------*/
// Only n slots are templated and can be ADOLC
// The other slots are fixed because they are never dependent
// T is double or adouble
template <typename T>
class FLCatch_base {
    public:
        /* Constructors */
		FLCatch_base();
		FLCatch_base(SEXP flc_sexp); // Used as intrusive 'as', takes an FLCatch
        operator SEXP() const; // Used as intrusive 'wrap' - returns an FLCatch
		FLCatch_base(const FLCatch_base& FLCatch_base_source); // copy constructor to ensure that copy is a deep copy - used when passing FLSs into functions
		FLCatch_base& operator = (const FLCatch_base& FLCatch_base_source); // Assignment operator for a deep copy

        // Accessor methods for the slots
        // Get only
        FLQuant_base<T> landings_n() const;
        FLQuant_base<T> discards_n() const;
        FLQuant landings_wt() const;
        FLQuant discards_wt() const;
        FLQuant catch_sel() const;
        FLQuant price() const;
        // Get and Set
        FLQuant_base<T>& landings_n();
        FLQuant_base<T>& discards_n();
        FLQuant& landings_wt();
        FLQuant& discards_wt();
        FLQuant& catch_sel();
        FLQuant& price();
        //FLQuant& catch_q();

        // Methods
        FLQuant_base<T> landings() const;
        FLQuant_base<T> discards() const;
        FLQuant_base<T> catches() const;
        FLQuant_base<T> catch_n() const;
        FLQuant_base<T> catch_wt() const;
        FLQuant_base<T> landings_sel() const;
        FLQuant_base<T> discards_sel() const;
        FLQuant_base<T> discards_ratio() const;

        std::string get_name() const;
        std::string get_desc() const;
        Rcpp::NumericVector get_range() const;

    private:
        std::string name;
        std::string desc;
        Rcpp::NumericVector range;

        FLQuant_base<T> landings_n_flq;
        FLQuant_base<T> discards_n_flq;
        FLQuant landings_wt_flq;
        FLQuant discards_wt_flq;
        FLQuant catch_sel_flq;
        FLQuant price_flq;
        //FLQuant catch_q_flq;
};

typedef FLCatch_base<double> FLCatch;
typedef FLCatch_base<adouble> FLCatchAdolc;

/*----------------------------------------------*/
// FLCatches class - a vector of FLCatch objects

template <typename T>
class FLCatches_base {
    public:
        /* Constructors */
		FLCatches_base();
		FLCatches_base(SEXP flcs_sexp); // Used as intrusive 'as', takes a list of FLCatch objects
		FLCatches_base(FLCatch_base<T> flc); // Constructor from an FLCatches object
        operator SEXP() const; // Used as intrusive 'wrap' - returns an FLCatches objects
		FLCatches_base(const FLCatches_base& FLCatches_base_source); // copy constructor to ensure that copy is a deep copy - used when passing FLCs into functions
		FLCatches_base& operator = (const FLCatches_base& FLCatches_base_source); // Assignment operator for a deep copy

        // Accessors
		FLCatch_base<T> operator () (const unsigned int element = 1) const; // Only gets an FLCatch so const reinforced. Default is the first element
		FLCatch_base<T>& operator () (const unsigned int element = 1); // Gets and sets an FLCatch so const not reinforced

        void operator() (const FLCatch_base<T> flc); // Add another FLCatch_base<T> to the data
        unsigned int get_ncatches() const;
        //Rcpp::CharacterVector get_names() const;

    protected:
        std::vector<FLCatch_base<T> > catches;
        Rcpp::CharacterVector names; // of the catches 
        std::string desc;
};

typedef FLCatches_base<double> FLCatches;
typedef FLCatches_base<adouble> FLCatchesAdolc;


