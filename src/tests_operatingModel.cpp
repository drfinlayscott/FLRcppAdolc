
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
operatingModel test_operatingModel_full_constructor(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const fwdControl ctrl){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    return om;
}

// [[Rcpp::export]]
FLQuantAdolc test_operatingModel_SSB_FLQ(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const fwdControl ctrl){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    return om.ssb();
}

// [[Rcpp::export]]
FLQuantAdolc test_operatingModel_SSB_iters(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const int timestep, const int unit, const int area, const fwdControl ctrl){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    FLQuantAdolc out = om.ssb(timestep, unit, area);
    return out;
}

// [[Rcpp::export]]
double test_operatingModel_SSB_single_iter(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const int timestep, const int unit, const int area, const int iter, const fwdControl ctrl){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    adouble out = om.ssb(timestep, unit, area, iter);
    return out.value();
}

// [[Rcpp::export]]
double test_operatingModel_SSB_single_iter_year_season(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const int year, const int unit, const int season, const int area, const int iter, const fwdControl ctrl){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    adouble out = om.ssb(year, unit, season, area, iter);
    return out.value();
}

// [[Rcpp::export]]
operatingModel test_operating_model_project(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const int timestep, const fwdControl ctrl){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    om.project_timestep(timestep, 1, ctrl.get_niter());
    return om;
}


// [[Rcpp::export]]
Rcpp::List test_operating_model_targets(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const fwdControl ctrl, const int fishery_no, const int catch_no){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);

    FLQuantAdolc fbar_catch = om.fbar(fishery_no, catch_no, 1);
    FLQuantAdolc fbar = om.fbar(1);
    FLQuantAdolc catches_catch_out = om.catches(fishery_no, catch_no, 1);
    FLQuantAdolc catches_out = om.catches(1);

	return Rcpp::List::create(Rcpp::Named("fbar_catch", fbar_catch),
                            Rcpp::Named("fbar",fbar),
                            Rcpp::Named("catches_catch",catches_catch_out),
                            Rcpp::Named("catches",catches_out));
}


// Evaluate by target no
// [[Rcpp::export]]
std::vector<double> test_operatingModel_eval_target_hat(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const fwdControl ctrl, const int target_no, const int min_iter, const int max_iter){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);

    std::vector<adouble> out_ad = om.eval_target_hat(target_no, min_iter, max_iter);
    std::vector<double> out(out_ad.size(), 0.0);
    for (int i=0; i<out.size(); ++i){
        out[i] = out_ad[i].value();
    }
    return out;
}


// Evaluate by target type
// [[Rcpp::export]]
std::vector<double> test_operatingModel_eval_target_hat2(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const fwdControl ctrl, const int target_no){

    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    const int year = ctrl.get_target_year(target_no); 
    const int season = ctrl.get_target_season(target_no);
    const int unit = 1;
    const int area = 1;
    fwdControlTargetType target_type = ctrl.get_target_type(target_no);
    std::vector<adouble> out_ad = om.eval_target_hat(target_type, year, unit, season, area);
    std::vector<double> out(out_ad.size(), 0.0);
    for (int i=0; i<out.size(); ++i){
        out[i] = out_ad[i].value();
    }
    return out;
}



// [[Rcpp::export]]
std::vector<double> test_operatingModel_calc_target_value(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const fwdControl ctrl, const int target_no){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    // Pull out values
    std::vector<double> out = om.calc_target_value(target_no);
    return out;
}
