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

// [[Rcpp::export]]
FLQuant test_FLCatch_catch_wt(const FLCatch flc){
    return flc.catch_wt();
}

// [[Rcpp::export]]
FLQuantAdolc test_FLCatchAdolc_catch_wt(const FLCatchAdolc flc){
    return flc.catch_wt();
}

// [[Rcpp::export]]
FLQuant test_FLCatch_catches(const FLCatch flc){
    return flc.catches();
}

// [[Rcpp::export]]
FLQuantAdolc test_FLCatchAdolc_catches(const FLCatchAdolc flc){
    return flc.catches();
}

// [[Rcpp::export]]
FLQuant test_FLCatch_discards_ratio(const FLCatch flc){
    return flc.discards_ratio();
}

// [[Rcpp::export]]
FLQuantAdolc test_FLCatchAdolc_discards_ratio(const FLCatchAdolc flc){
    return flc.discards_ratio();
}

// [[Rcpp::export]]
FLQuant test_FLCatch_landings_sel(const FLCatch flc){
    return flc.landings_sel();
}

// [[Rcpp::export]]
FLQuantAdolc test_FLCatchAdolc_landings_sel(const FLCatchAdolc flc){
    return flc.landings_sel();
}

// [[Rcpp::export]]
FLQuant test_FLCatch_discards_sel(const FLCatch flc){
    return flc.discards_sel();
}

// [[Rcpp::export]]
FLQuantAdolc test_FLCatchAdolc_discards_sel(const FLCatchAdolc flc){
    return flc.discards_sel();
}

/*------------------------------------------------------------------------*/
// FLCatches - double

// [[Rcpp::export]]
FLCatches test_FLCatches_as_wrap(FLCatches flcs){
    return flcs;
}

// [[Rcpp::export]]
FLCatches test_FLCatches_empty_wrap(){
	FLCatches flcs;
	return flcs;
}

// [[Rcpp::export]]
FLCatches test_FLCatches_sexp_constructor(SEXP flcs_sexp1){
	FLCatches flcs(flcs_sexp1);
	return flcs;
}

// [[Rcpp::export]]
FLCatches test_FLCatches_FLCatch_constructor(FLCatch flc){
	FLCatches flcs(flc);
	return flcs;
}

// [[Rcpp::export]]
FLCatches test_FLCatches_copy_constructor(FLCatches flcs){
    FLCatches out(flcs);
    return out;
}

// Checking that a deep copy has been made
// [[Rcpp::export]]
Rcpp::List test_FLCatches_copy_constructor2(FLCatches flcs1, int catches, int quant, int year, int unit, int season, int area, int iter, double value){
	FLCatches flcs2(flcs1); 
	flcs2(catches).landings_n()(quant,year,unit,season,area,iter) = value;
	return Rcpp::List::create(Rcpp::Named("flcs1", flcs1),
                            Rcpp::Named("flcs2",flcs2));
}

// [[Rcpp::export]]
FLCatches test_FLCatches_assignment_operator(FLCatches flcs){
    FLCatches out;
    out = flcs;
    return out;
}

// Checking that a deep copy has been made
// [[Rcpp::export]]
Rcpp::List test_FLCatches_assignment_operator2(FLCatches flcs1, int catches, int quant, int year, int unit, int season, int area, int iter, double value){
	FLCatches flcs2;
    flcs2 = flcs1; 
	flcs2(catches).landings_n()(quant,year,unit,season,area,iter) = value;
	return Rcpp::List::create(Rcpp::Named("flcs1", flcs1),
				Rcpp::Named("flcs2",flcs2));
}

// Testing adding another FLQ into FLQ7 - also tests wrap
// [[Rcpp::export]]
FLCatches test_FLCatches_function_operator(FLCatches flcs, FLCatch flc){
    flcs(flc);
	return flcs;
}

// [[Rcpp::export]]
int test_FLCatches_get_ncatches(SEXP flc_sexp1){
	FLCatches flcs(flc_sexp1);
    int length = flcs.get_ncatches();
	return length;
}

// [[Rcpp::export]]
FLCatch test_FLCatches_const_get_single_index_accessor(const FLCatches flcs, const int element){
    FLCatch flc = flcs(element);
    return flc;
}

// [[Rcpp::export]]
FLCatch test_FLCatches_get_single_index_accessor(FLCatches flcs, const int element){
    FLCatch flc = flcs(element);
    return flc;
}
 
// [[Rcpp::export]]
double test_FLCatches_const_get_value_accessor(const FLCatches flcs, const int catches, int quant, int year, int unit, int season, int area, int iter){
    double value_out = flcs(catches).landings_n()(quant,year,unit,season,area,iter);
    return value_out;
}

// [[Rcpp::export]]
double test_FLCatches_get_value_accessor(FLCatches flcs, const int catches, int quant, int year, int unit, int season, int area, int iter){
    double value_out = flcs(catches).landings_n()(quant,year,unit,season,area,iter);
    return value_out;
}

// [[Rcpp::export]]
FLCatches test_FLCatches_set_single_index_accessor(FLCatches flcs, const int element, const FLCatch flc){
    flcs(element) = flc;
    return flcs;
}

// [[Rcpp::export]]
FLCatches test_FLCatches_set_value_accessor(FLCatches flcs, const int element, int quant, int year, int unit, int season, int area, int iter, double value){
    flcs(element).landings_n()(quant,year,unit,season,area,iter) = value;
    return flcs;
}

// [[Rcpp::export]]
FLCatch test_FLCatches_const_get_single_index_default_accessor(const FLCatches flcs){
    FLCatch flc = flcs();
    return flc;
}

// [[Rcpp::export]]
FLCatch test_FLCatches_get_single_index_default_accessor(FLCatches flcs){
    FLCatch flc = flcs();
    return flc;
}
 
// [[Rcpp::export]]
FLCatches test_FLCatches_set_single_index_default_accessor(FLCatches flcs, const FLCatch flc){
    flcs() = flc;
    return flcs;
}

/*------------------------------------------------------------------------*/
// FLCatches - adouble

// [[Rcpp::export]]
FLCatchesAdolc test_FLCatchesAdolc_as_wrap(FLCatchesAdolc flcs){
    return flcs;
}

// [[Rcpp::export]]
FLCatchesAdolc test_FLCatchesAdolc_empty_wrap(){
	FLCatchesAdolc flcs;
	return flcs;
}

// [[Rcpp::export]]
FLCatchesAdolc test_FLCatchesAdolc_sexp_constructor(SEXP flcs_sexp1){
	FLCatchesAdolc flcs(flcs_sexp1);
	return flcs;
}

// [[Rcpp::export]]
FLCatchesAdolc test_FLCatchesAdolc_FLCatchAdolc_constructor(FLCatchAdolc flc){
	FLCatchesAdolc flcs(flc);
	return flcs;
}

// [[Rcpp::export]]
FLCatchesAdolc test_FLCatchesAdolc_copy_constructor(FLCatchesAdolc flcs){
    FLCatchesAdolc out(flcs);
    return out;
}

// Checking that a deep copy has been made
// [[Rcpp::export]]
Rcpp::List test_FLCatchesAdolc_copy_constructor2(FLCatchesAdolc flcs1, int catches, int quant, int year, int unit, int season, int area, int iter, double value){
    adouble ad_value = value;
	FLCatchesAdolc flcs2(flcs1); 
	flcs2(catches).landings_n()(quant,year,unit,season,area,iter) = ad_value;
	return Rcpp::List::create(Rcpp::Named("flcs1", flcs1),
                            Rcpp::Named("flcs2",flcs2));
}

// [[Rcpp::export]]
FLCatchesAdolc test_FLCatchesAdolc_assignment_operator(FLCatchesAdolc flcs){
    FLCatchesAdolc out;
    out = flcs;
    return out;
}

// Checking that a deep copy has been made
// [[Rcpp::export]]
Rcpp::List test_FLCatchesAdolc_assignment_operator2(FLCatchesAdolc flcs1, int catches, int quant, int year, int unit, int season, int area, int iter, double value){
    adouble ad_value = value;
	FLCatchesAdolc flcs2;
    flcs2 = flcs1; 
	flcs2(catches).landings_n()(quant,year,unit,season,area,iter) = ad_value;
	return Rcpp::List::create(Rcpp::Named("flcs1", flcs1),
				Rcpp::Named("flcs2",flcs2));
}

// Testing adding another FLQ into FLQ7 - also tests wrap
// [[Rcpp::export]]
FLCatchesAdolc test_FLCatchesAdolc_function_operator(FLCatchesAdolc flcs, FLCatchAdolc flc){
    flcs(flc);
	return flcs;
}

// [[Rcpp::export]]
int test_FLCatchesAdolc_get_ncatches(SEXP flc_sexp1){
	FLCatchesAdolc flcs(flc_sexp1);
    int length = flcs.get_ncatches();
	return length;
}

// [[Rcpp::export]]
FLCatchAdolc test_FLCatchesAdolc_const_get_single_index_accessor(const FLCatchesAdolc flcs, const int element){
    FLCatchAdolc flc = flcs(element);
    return flc;
}

// [[Rcpp::export]]
FLCatchAdolc test_FLCatchesAdolc_get_single_index_accessor(FLCatchesAdolc flcs, const int element){
    FLCatchAdolc flc = flcs(element);
    return flc;
}
 
// [[Rcpp::export]]
double test_FLCatchesAdolc_const_get_value_accessor(const FLCatchesAdolc flcs, const int catches, int quant, int year, int unit, int season, int area, int iter){
    adouble ad_value_out = flcs(catches).landings_n()(quant,year,unit,season,area,iter);
    return ad_value_out.value();
}

// [[Rcpp::export]]
double test_FLCatchesAdolc_get_value_accessor(FLCatchesAdolc flcs, const int catches, int quant, int year, int unit, int season, int area, int iter){
    adouble ad_value_out = flcs(catches).landings_n()(quant,year,unit,season,area,iter);
    return ad_value_out.value();
}

// [[Rcpp::export]]
FLCatchesAdolc test_FLCatchesAdolc_set_single_index_accessor(FLCatchesAdolc flcs, const int element, const FLCatchAdolc flc){
    flcs(element) = flc;
    return flcs;
}

// [[Rcpp::export]]
FLCatchesAdolc test_FLCatchesAdolc_set_value_accessor(FLCatchesAdolc flcs, const int element, int quant, int year, int unit, int season, int area, int iter, double value){
    adouble ad_value = value;
    flcs(element).landings_n()(quant,year,unit,season,area,iter) = ad_value;
    return flcs;
}

// [[Rcpp::export]]
FLCatchAdolc test_FLCatchesAdolc_const_get_single_index_default_accessor(const FLCatchesAdolc flcs){
    FLCatchAdolc flc = flcs();
    return flc;
}

// [[Rcpp::export]]
FLCatchAdolc test_FLCatchesAdolc_get_single_index_default_accessor(FLCatchesAdolc flcs){
    FLCatchAdolc flc = flcs();
    return flc;
}
 
// [[Rcpp::export]]
FLCatchesAdolc test_FLCatchesAdolc_set_single_index_default_accessor(FLCatchesAdolc flcs, const FLCatchAdolc flc){
    flcs() = flc;
    return flcs;
}

