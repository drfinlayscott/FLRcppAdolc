
/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../../inst/include/projection.h"

// [[Rcpp::export]]
void test_operatingModel_empty_constructor(){
    operatingModel om;
    return;
}

// [[Rcpp::export]]
void test_operatingModelAdolc_empty_constructor(){
    operatingModelAdolc om;
    return;
}

// [[Rcpp::export]]
operatingModelAdolc test_operatingModel_full_constructor(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const FLQuant residuals, const bool residuals_mult, const FLQuantAdolc7 f, const FLQuantAdolc7 f_spwn){
    fwdBiolAdolc biol(flb_sexp, model_name, params, residuals, residuals_mult);
    operatingModelAdolc om(flfs, biol, f, f_spwn);
    return om;
}

