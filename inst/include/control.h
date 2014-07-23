// Change the name of the object?
/* 
 * Copyright 2013 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include <RcppCommon.h>
#include <Rcpp.h>

// fwdControl class
// no need for adoubles
// two main components:
// data.frame describing controls per timestep
// array for the iterations in a timestep

// This class won't be modified - it is a read-only class
// All methods will b consts I guess

// The target_iters is a 3D array with fixed size of second dimension (3)


class fwdControl {
	public:
		fwdControl();
		fwdControl(SEXP fwd_control_sexp); // Used as intrusive 'as'
        operator SEXP() const; // Used as intrusive 'wrap'
		fwdControl(const fwdControl& fwdControl_source); // copy constructor to ensure that copies (i.e. when passing to functions) are deep
		fwdControl& operator = (const fwdControl& fwdControl_source); // Assignment operator for a deep copy
        Rcpp::DataFrame get_target() const;
    private:
        Rcpp::DataFrame target;
        Rcpp::NumericVector target_iters; 
};


