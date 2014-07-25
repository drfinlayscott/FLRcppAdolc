/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../../inst/include/control.h"

// [[Rcpp::export]]
fwdControl test_as_wrap_fwdControl(fwdControl control){
    return control;
}

// Checking that a deep copy has been made
// Not so important as we not actually changing any of these values
// In fact we don't have any 'write' accessors for this class
// [[Rcpp::export]]
Rcpp::List test_fwdControl_copy_constructor2(fwdControl fc1){
    // Just make a copy
	fwdControl fc2(fc1); 
	return Rcpp::List::create(Rcpp::Named("fc1", fc1),
                            Rcpp::Named("fc2",fc2));
}

// [[Rcpp::export]]
fwdControl test_fwdControl_assignment_operator(fwdControl fc){
    fwdControl out;
    out = fc;
    return out;
}

// [[Rcpp::export]]
Rcpp::DataFrame test_fwdControl_get_target(const fwdControl control){
    return control.get_target();
}

// [[Rcpp::export]]
int test_fwdControl_get_ntarget(const fwdControl control){
    return control.get_ntarget();
}

// [[Rcpp::export]]
int test_fwdControl_get_niter(const fwdControl control){
    return control.get_niter();
}

// [[Rcpp::export]]
int test_fwdControl_get_target_year(const fwdControl control, const int target_no){
    return control.get_target_year(target_no);
}

// [[Rcpp::export]]
int test_fwdControl_get_target_season(const fwdControl control, const int target_no){
    return control.get_target_season(target_no);
}

// [[Rcpp::export]]
double test_fwdControl_get_target_value(const fwdControl control, const int target_no, const int col, const int iter){
    return control.get_target_value(target_no, col, iter);
}

