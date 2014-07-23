/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../../inst/include/control.h"

// [[Rcpp::export]]
Rcpp::DataFrame test_as_fwdControl(fwdControl control){
    return control.get_target();
}

// [[Rcpp::export]]
fwdControl test_as_wrap_fwdControl(fwdControl control){
    return control;
}

// Checking that a deep copy has been made
// [[Rcpp::export]]
Rcpp::List test_fwdControl_copy_constructor2(fwdControl fc1, double value){
	fwdControl fc2(fc1); 
    // Change a value - how?
	//flq2(quant,year,unit,season,area,iter) = value;
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
Rcpp::DataFrame test_get_fwdControl_get_target(fwdControl control){
    return control.get_target();
}




