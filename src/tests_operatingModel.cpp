
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
operatingModelAdolc test_operatingModel_full_constructor(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuantAdolc7 f, const FLQuantAdolc7 f_spwn, const fwdControl ctrl){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModelAdolc om(flfs, biol, f, f_spwn, ctrl);
    return om;
}

// [[Rcpp::export]]
FLQuant test_operatingModel_SSB_FLQ(FLFisheries flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7 f, const FLQuant7 f_spwn, const fwdControl ctrl){
    fwdBiol biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    return om.ssb();
}

// [[Rcpp::export]]
FLQuantAdolc test_operatingModelAdolc_SSB_FLQ(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuantAdolc7 f, const FLQuantAdolc7 f_spwn, const fwdControl ctrl){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModelAdolc om(flfs, biol, f, f_spwn, ctrl);
    return om.ssb();
}

// [[Rcpp::export]]
FLQuant test_operatingModel_SSB_iters(FLFisheries flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7 f, const FLQuant7 f_spwn, const int timestep, const int unit, const int area, const fwdControl ctrl){
    fwdBiol biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    FLQuant out = om.ssb(timestep, unit, area);
    return out;
}

// [[Rcpp::export]]
double test_operatingModel_SSB_single_iter(FLFisheries flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7 f, const FLQuant7 f_spwn, const int timestep, const int unit, const int area, const int iter, const fwdControl ctrl){
    fwdBiol biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    double out = om.ssb(timestep, unit, area, iter);
    return out;
}

// [[Rcpp::export]]
double test_operatingModel_SSB_single_iter_year_season(FLFisheries flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7 f, const FLQuant7 f_spwn, const int year, const int unit, const int season, const int area, const int iter, const fwdControl ctrl){
    fwdBiol biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    double out = om.ssb(year, unit, season, area, iter);
    return out;
}


// [[Rcpp::export]]
operatingModelAdolc test_operating_model_project(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuantAdolc7 f, const FLQuantAdolc7 f_spwn, const int timestep, const fwdControl ctrl){

    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModelAdolc om(flfs, biol, f, f_spwn, ctrl);
    om.project_timestep(timestep, 1, ctrl.get_niter());
    return om;
}

