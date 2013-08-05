/* 
 * Copyright 2013 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../../inst/include/FLQuant_base.h"

// [[Rcpp::export]]
void do_nothing_FLQuantAdolc(){
    return;
}

// [[Rcpp::export]]
void test_FLQuantAdolc_basic_constructor(){
    FLQuantAdolc flqad;
    return;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_sexp_constructor(SEXP flq_sexp){
	FLQuantAdolc flqad(flq_sexp);
	return flqad;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_as_wrap(FLQuantAdolc flqad){
	return flqad;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_copy_constructor(FLQuantAdolc flqad){
    FLQuantAdolc out = flqad;
    return out;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_assignment_operator(FLQuantAdolc flqad){
    FLQuantAdolc out;
    out = flqad;
    return out;
}

//------------------ Accessors ----------------------
// Cannot return vector of adoubles
/*
// [[Rcpp::export]]
std::vector<adouble> test_FLQuantAdolc_get_data(FLQuantAdolc flq){
	return flq.get_data();
}
*/

// [[Rcpp::export]]
std::string test_FLQuantAdolc_get_units(FLQuantAdolc flq){
	return flq.get_units();
}

// [[Rcpp::export]]
Rcpp::IntegerVector test_FLQuantAdolc_get_dim(FLQuantAdolc flq){
	return flq.get_dim();
}

// [[Rcpp::export]]
Rcpp::List test_FLQuantAdolc_get_dimnames(FLQuantAdolc flq){
	return flq.get_dimnames();
}

// [[Rcpp::export]]
int test_FLQuantAdolc_get_nquant(FLQuantAdolc flq){
	return flq.get_nquant();
}

// [[Rcpp::export]]
int test_FLQuantAdolc_get_nyear(FLQuantAdolc flq){
	return flq.get_nyear();
}

// [[Rcpp::export]]
int test_FLQuantAdolc_get_nunit(FLQuantAdolc flq){
	return flq.get_nunit();
}

// [[Rcpp::export]]
int test_FLQuantAdolc_get_nseason(FLQuantAdolc flq){
	return flq.get_nseason();
}

// [[Rcpp::export]]
int test_FLQuantAdolc_get_narea(FLQuantAdolc flq){
	return flq.get_narea();
}

// [[Rcpp::export]]
int test_FLQuantAdolc_get_niter(FLQuantAdolc flq){
	return flq.get_niter();
}

// [[Rcpp::export]]
int test_FLQuantAdolc_get_data_element(const FLQuantAdolc flq, int quant, int year, int unit, int season, int area, int iter){
	int out = 0;
	out = flq.get_data_element(quant,year,unit,season,area,iter);
	return out;
}

// [[Rcpp::export]]
double test_FLQuantAdolc_get_const_single_index_accessor(const FLQuantAdolc flq, const int element){
	adouble output = 0.0;
	output = flq(element);
	return output.value();
}

// [[Rcpp::export]]
double test_FLQuantAdolc_get_single_index_accessor(FLQuantAdolc flq, int element){
	adouble output = 0.0;
	output = flq(element);
	return output.value();
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_set_single_index_accessor(FLQuantAdolc flq, int element, double value){
    flq(element) = value;
    return flq;
}

// [[Rcpp::export]]
double test_FLQuantAdolc_const_get_accessor(const FLQuantAdolc flq, int quant, int year, int unit, int season, int area, int iter){
	adouble output = 0.0;
	output = flq(quant,year,unit,season,area,iter);
	return output.value();
}

// [[Rcpp::export]]
double test_FLQuantAdolc_get_accessor(FLQuantAdolc flq, int quant, int year, int unit, int season, int area, int iter){
	adouble output = 0.0;
	output = flq(quant,year,unit,season,area,iter);
	return output.value();
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_set_accessor(FLQuantAdolc flq, int quant, int year, int unit, int season, int area, int iter, double value){
	flq(quant,year,unit,season,area,iter) = value;
	return flq;
}


//------------------ Arithmetic operators ----------------------
// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuantAdolc_multiplier_assignment_operator(FLQuantAdolc flqad1, FLQuantAdolc flqad2){
    flqad1 *= flqad2;
    return flqad1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuant_multiplier_assignment_operator(FLQuantAdolc flqad1, FLQuant flq2){
    flqad1 *= flq2;
    return flqad1;
}

/* Doesn't compile; which is good as it isn't supposed to. Just checking understanding of the member method.
// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuantAdolc_multiplier_assignment_operator(FLQuant flq1, FLQuantAdolc flqad2){
    flq1 *= flqad2;
    return flq1;
}
*/

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuantAdolc_multiplier_operator(FLQuantAdolc flqad1, FLQuantAdolc flqad2){
    FLQuantAdolc flqad3 = flqad1 * flqad2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuant_multiplier_operator(FLQuantAdolc flqad1, FLQuant flq2){
    FLQuantAdolc flqad3;
    flqad3 = flqad1 * flq2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuant_FLQuantAdolc_multiplier_operator(FLQuant flq1, FLQuantAdolc flqad2){
    FLQuantAdolc flqad3 = flq1 * flqad2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuant_FLQuantAdolc_multiplier_operator(FLQuantAdolc flqad1, FLQuant flq2, FLQuantAdolc flqad3){
    FLQuantAdolc flqad4;
    flqad4 = flqad1 * flq2 * flqad3;
    return flqad4;
}

//------------------ Others --------------------------------------
// [[Rcpp::export]]
int test_FLQuantAdolc_FLQuantAdolc_match_dims(FLQuantAdolc flq1, FLQuantAdolc flq2){
    return flq1.match_dims(flq2);
}

// [[Rcpp::export]]
int test_FLQuantAdolc_FLQuant_match_dims(FLQuantAdolc flq1, FLQuant flq2){
    return flq1.match_dims(flq2);
}

// [[Rcpp::export]]
int test_FLQuant_FLQuantAdolc_match_dims(FLQuant flq1, FLQuantAdolc flq2){
    return flq1.match_dims(flq2);
}
