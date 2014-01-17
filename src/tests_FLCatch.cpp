/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../../inst/include/FLCatch.h"

/*-------------------------------------------------------*/
// Templated class tests
// [[Rcpp::export]]
int test_simple_FLCatch_sexp_constructor(SEXP flc_sexp){
    FLCatch flc(flc_sexp);
	return 0;
}

// [[Rcpp::export]]
FLCatch test_FLCatch_sexp_constructor(SEXP flc_sexp){
	FLCatch flc(flc_sexp);
	return flc;
}

// [[Rcpp::export]]
FLCatchAdolc test_FLCatchAdolc_sexp_constructor(SEXP flc_sexp){
	FLCatchAdolc flc(flc_sexp);
	return flc;
}

// [[Rcpp::export]]
FLCatch test_FLCatch_as_wrap(FLCatch flc){
	return flc;
}

// [[Rcpp::export]]
FLCatchAdolc test_FLCatchAdolc_as_wrap(FLCatchAdolc flc){
	return flc;
}

// [[Rcpp::export]]
FLCatch test_FLCatch_copy_constructor(FLCatch flc1){
	FLCatch flc2(flc1); // uses copy constructor
    return flc2;
}

// [[Rcpp::export]]
FLCatchAdolc test_FLCatchAdolc_copy_constructor(FLCatchAdolc flc1){
	FLCatchAdolc flc2(flc1); // uses copy constructor
    return flc2;
}

// [[Rcpp::export]]
Rcpp::List test_FLCatch_copy_constructor2(FLCatch flc1, int quant, int year, int unit, int season, int area, int iter, double value){
	FLCatch flc2(flc1); // uses copy constructor
	flc2.landings_n()(quant,year,unit,season,area,iter) = value;
	return Rcpp::List::create(Rcpp::Named("flc1", flc1),
				Rcpp::Named("flc2",flc2));
}

// [[Rcpp::export]]
Rcpp::List test_FLCatchAdolc_copy_constructor2(FLCatchAdolc flc1, int quant, int year, int unit, int season, int area, int iter, double value){
    adouble value_ad = value;
	FLCatchAdolc flc2(flc1); // uses copy constructor
	flc2.landings_n()(quant,year,unit,season,area,iter) = value_ad;
	return Rcpp::List::create(Rcpp::Named("flc1", flc1),
				Rcpp::Named("flc2",flc2));
}

// [[Rcpp::export]]
FLCatch test_FLCatch_assignment_operator(FLCatch flc1){
	FLCatch flc2 = flc1; 
    return flc2;
}

// [[Rcpp::export]]
FLCatchAdolc test_FLCatchAdolc_assignment_operator(FLCatchAdolc flc1){
	FLCatchAdolc flc2 = flc1; 
    return flc2;
}

// [[Rcpp::export]]
Rcpp::List test_FLCatch_assignment_operator2(FLCatch flc1, int quant, int year, int unit, int season, int area, int iter, double value){
	FLCatch flc2 = flc1; 
	flc2.landings_n()(quant,year,unit,season,area,iter) = value;
	return Rcpp::List::create(Rcpp::Named("flc1", flc1),
				Rcpp::Named("flc2",flc2));
}

// [[Rcpp::export]]
Rcpp::List test_FLCatchAdolc_assignment_operator2(FLCatchAdolc flc1, int quant, int year, int unit, int season, int area, int iter, double value){
    adouble value_ad = value;
	FLCatchAdolc flc2 = flc1; 
	flc2.landings_n()(quant,year,unit,season,area,iter) = value_ad;
	return Rcpp::List::create(Rcpp::Named("flc1", flc1),
				Rcpp::Named("flc2",flc2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLCatch_const_get_accessors(const FLCatch flc,int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(6);
    out[0] = flc.landings_n()(quant, year, unit, season, area, iter);
    out[1] = flc.discards_n()(quant, year, unit, season, area, iter);
    out[2] = flc.landings_wt()(quant, year, unit, season, area, iter);
    out[3] = flc.discards_wt()(quant, year, unit, season, area, iter);
    out[4] = flc.catch_sel()(quant, year, unit, season, area, iter);
    out[5] = flc.price()(quant, year, unit, season, area, iter);
    //out[6] = flc.catch_q()(quant, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLCatchAdolc_const_get_accessors(const FLCatchAdolc flc,int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(6);
    adouble ad_value0 = flc.landings_n()(quant, year, unit, season, area, iter);
    adouble ad_value1 = flc.discards_n()(quant, year, unit, season, area, iter);
    out[0] = ad_value0.value();
    out[1] = ad_value1.value();
    out[2] = flc.landings_wt()(quant, year, unit, season, area, iter);
    out[3] = flc.discards_wt()(quant, year, unit, season, area, iter);
    out[4] = flc.catch_sel()(quant, year, unit, season, area, iter);
    out[5] = flc.price()(quant, year, unit, season, area, iter);
    //out[6] = flc.catch_q()(quant, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLCatch_get_accessors(FLCatch flc,int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(6);
    out[0] = flc.landings_n()(quant, year, unit, season, area, iter);
    out[1] = flc.discards_n()(quant, year, unit, season, area, iter);
    out[2] = flc.landings_wt()(quant, year, unit, season, area, iter);
    out[3] = flc.discards_wt()(quant, year, unit, season, area, iter);
    out[4] = flc.catch_sel()(quant, year, unit, season, area, iter);
    out[5] = flc.price()(quant, year, unit, season, area, iter);
    //out[6] = flc.catch_q()(quant, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLCatchAdolc_get_accessors(FLCatchAdolc flc,int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(6);
    adouble ad_value0 = flc.landings_n()(quant, year, unit, season, area, iter);
    adouble ad_value1 = flc.discards_n()(quant, year, unit, season, area, iter);
    out[0] = ad_value0.value();
    out[1] = ad_value1.value();
    out[2] = flc.landings_wt()(quant, year, unit, season, area, iter);
    out[3] = flc.discards_wt()(quant, year, unit, season, area, iter);
    out[4] = flc.catch_sel()(quant, year, unit, season, area, iter);
    out[5] = flc.price()(quant, year, unit, season, area, iter);
    //out[6] = flc.catch_q()(quant, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
FLCatch test_FLCatch_set_accessors(FLCatch flc, int quant, int year, int unit, int season, int area, int iter, Rcpp::NumericVector values){
    flc.landings_n()(quant, year, unit, season, area, iter) = values[0];
    flc.discards_n()(quant, year, unit, season, area, iter) = values[1];
    flc.landings_wt()(quant, year, unit, season, area, iter) = values[2];
    flc.discards_wt()(quant, year, unit, season, area, iter) = values[3];
    flc.catch_sel()(quant, year, unit, season, area, iter) = values[4];
    flc.price()(quant, year, unit, season, area, iter) = values[5];
    //out[6] = flc.catch_q()(quant, year, unit, season, area, iter) = values[6];
    return flc;
}

// [[Rcpp::export]]
FLCatchAdolc test_FLCatchAdolc_set_accessors(FLCatchAdolc flc, int quant, int year, int unit, int season, int area, int iter, Rcpp::NumericVector values){
    adouble value_ad0 = values[0];
    adouble value_ad1 = values[1];
    flc.landings_n()(quant, year, unit, season, area, iter) = value_ad0;
    flc.discards_n()(quant, year, unit, season, area, iter) = value_ad1;
    flc.landings_wt()(quant, year, unit, season, area, iter) = values[2];
    flc.discards_wt()(quant, year, unit, season, area, iter) = values[3];
    flc.catch_sel()(quant, year, unit, season, area, iter) = values[4];
    flc.price()(quant, year, unit, season, area, iter) = values[5];
    //out[6] = flc.catch_q()(quant, year, unit, season, area, iter) = values[6];
    return flc;
}

// [[Rcpp::export]]
FLQuant test_FLCatch_landings(const FLCatch flc){
    return flc.landings();
}

// [[Rcpp::export]]
FLQuantAdolc test_FLCatchAdolc_landings(const FLCatchAdolc flc){
    return flc.landings();
}

// [[Rcpp::export]]
FLQuant test_FLCatch_discards(const FLCatch flc){
    return flc.discards();
}

// [[Rcpp::export]]
FLQuantAdolc test_FLCatchAdolc_discards(const FLCatchAdolc flc){
    return flc.discards();
}

// [[Rcpp::export]]
FLQuant test_FLCatch_catch_n(const FLCatch flc){
    return flc.catch_n();
}

// [[Rcpp::export]]
FLQuantAdolc test_FLCatchAdolc_catch_n(const FLCatchAdolc flc){
    return flc.catch_n();
}

