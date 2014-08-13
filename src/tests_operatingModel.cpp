
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
    const int biol_no = 1;
    return om.ssb(biol_no);
}

// [[Rcpp::export]]
FLQuantAdolc test_operatingModel_SSB_iters(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const int timestep, const int unit, const int area, const fwdControl ctrl){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    const int biol_no = 1;
    FLQuantAdolc out = om.ssb(timestep, unit, area, biol_no);
    return out;
}

// [[Rcpp::export]]
double test_operatingModel_SSB_single_iter(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const int timestep, const int unit, const int area, const int iter, const fwdControl ctrl){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    const int biol_no = 1;
    adouble out = om.ssb(timestep, unit, area, iter, biol_no);
    return out.value();
}

// [[Rcpp::export]]
double test_operatingModel_SSB_single_iter_year_season(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const int year, const int unit, const int season, const int area, const int iter, const fwdControl ctrl){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    const int biol_no = 1;
    adouble out = om.ssb(year, unit, season, area, iter, biol_no);
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
Rcpp::IntegerVector test_operating_model_get_target_age_range_indices(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const fwdControl ctrl, const int target_no){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    const int biol_no = 1;
    Rcpp::IntegerVector age_range_indices = om.get_target_age_range_indices(target_no, biol_no);
    return age_range_indices;
}




// [[Rcpp::export]]
Rcpp::List test_operating_model_targets(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const fwdControl ctrl, const int fishery_no, const int catch_no, const int target_no){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    const int biol_no = 1;
    Rcpp::IntegerVector age_range_indices = om.get_target_age_range_indices(target_no, biol_no);
    FLQuantAdolc fbar_catch = om.fbar(age_range_indices, fishery_no, catch_no, biol_no);
    FLQuantAdolc fbar = om.fbar(age_range_indices, biol_no);
    FLQuantAdolc catches_catch_out = om.catches(fishery_no, catch_no, 1);
    FLQuantAdolc catches_out = om.catches(1);
    FLQuantAdolc ssb_out = om.ssb(biol_no);
    FLQuantAdolc biomass_out = om.biomass(biol_no);

	return Rcpp::List::create(Rcpp::Named("fbar_catch", fbar_catch),
                            Rcpp::Named("fbar",fbar),
                            Rcpp::Named("catches_catch",catches_catch_out),
                            Rcpp::Named("catches",catches_out),
                            Rcpp::Named("biomass",biomass_out),
                            Rcpp::Named("ssb",ssb_out));
}


// [[Rcpp::export]]
int test_operatingModel_get_target_fmult_timestep(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const fwdControl ctrl, const int target_no){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    return om.get_target_fmult_timestep(target_no);
}

// Evaluate by target no
// [[Rcpp::export]]
std::vector<double> test_operatingModel_eval_target(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const fwdControl ctrl, const int target_no, const int min_iter, const int max_iter){
    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    std::vector<adouble> out_ad = om.eval_target(target_no, min_iter, max_iter);
    std::vector<double> out(out_ad.size(), 0.0);
    for (int i=0; i<out.size(); ++i){
        out[i] = out_ad[i].value();
    }
    return out;
}


// Evaluate by target type
// [[Rcpp::export]]
std::vector<double> test_operatingModel_eval_target2(FLFisheriesAdolc flfs, SEXP flb_sexp, const std::string model_name, const FLQuant params, const int timelag, const FLQuant residuals, const bool residuals_mult, const FLQuant7Adolc f, const FLQuant7 f_spwn, const fwdControl ctrl, const int target_no){

    fwdBiolAdolc biol(flb_sexp, model_name, params, timelag, residuals, residuals_mult);
    operatingModel om(flfs, biol, f, f_spwn, ctrl);
    const int year = ctrl.get_target_year(target_no); 
    const int season = ctrl.get_target_season(target_no);
    const int unit = 1;
    const int area = 1;
    const int biol_no = 1;
    std::vector<adouble> out_ad = om.eval_target(target_no, year, unit, season, area);
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
