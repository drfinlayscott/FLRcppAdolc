
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

// [[Rcpp::export]]
FLQuant test_operatingModel_SSB_FLQ(FLFisheries flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const FLQuant residuals, const bool residuals_mult, const FLQuant7 f, const FLQuant7 f_spwn){
    fwdBiol biol(flb_sexp, model_name, params, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn);
    return om.ssb();
}

// [[Rcpp::export]]
FLQuantAdolc test_operatingModelAdolc_SSB_FLQ(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const FLQuant residuals, const bool residuals_mult, const FLQuantAdolc7 f, const FLQuantAdolc7 f_spwn){
    fwdBiolAdolc biol(flb_sexp, model_name, params, residuals, residuals_mult);
    operatingModelAdolc om(flfs, biol, f, f_spwn);
    return om.ssb();
}

// [[Rcpp::export]]
FLQuant test_operatingModel_SSB_iters(FLFisheries flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const FLQuant residuals, const bool residuals_mult, const FLQuant7 f, const FLQuant7 f_spwn, const int timestep, const int unit, const int area){
    fwdBiol biol(flb_sexp, model_name, params, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn);
    FLQuant out = om.ssb(timestep, unit, area);
    return out;
}

// [[Rcpp::export]]
double test_operatingModel_SSB_single_iter(FLFisheries flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const FLQuant residuals, const bool residuals_mult, const FLQuant7 f, const FLQuant7 f_spwn, const int timestep, const int unit, const int area, const int iter){
    fwdBiol biol(flb_sexp, model_name, params, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn);
    double out = om.ssb(timestep, unit, area, iter);
    return out;
}

// [[Rcpp::export]]
operatingModelAdolc test_operating_model_project(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const FLQuant residuals, const bool residuals_mult, const FLQuantAdolc7 f, const FLQuantAdolc7 f_spwn, const int timestep){

    fwdBiolAdolc biol(flb_sexp, model_name, params, residuals, residuals_mult);
    operatingModelAdolc om(flfs, biol, f, f_spwn);
    om.project_timestep(timestep);
    return om;
}

