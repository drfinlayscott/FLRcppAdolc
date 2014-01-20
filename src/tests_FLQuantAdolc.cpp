/* 
 * Copyright 2013 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../../inst/include/FLQuant_base.h"

// ADOLC(QUANT) constructor

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_as_wrap(FLQuantAdolc flq){
	return flq;
}

// [[Rcpp::export]]
void test_FLQuantAdolc_basic_constructor(){
    FLQuantAdolc flq;
    return;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_sexp_constructor(SEXP flq_sexp){
	FLQuantAdolc flq(flq_sexp);
	return flq;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_dim_constructor(int nquant, int nyear, int nunit, int nseason, int narea, int niter){
    FLQuantAdolc flq(nquant, nyear, nunit, nseason, narea, niter);
    return flq;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_copy_constructor(FLQuantAdolc flq){
    FLQuantAdolc out(flq);
    return out;
}

// Checking that a deep copy has been made
// [[Rcpp::export]]
Rcpp::List test_FLQuantAdolc_copy_constructor2(FLQuantAdolc flq1, int quant, int year, int unit, int season, int area, int iter, double value){
	FLQuantAdolc flq2(flq1); 
    adouble ad_value = value;
	flq2(quant,year,unit,season,area,iter) = ad_value;
	return Rcpp::List::create(Rcpp::Named("flq1", flq1),
                            Rcpp::Named("flq2",flq2));
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_assignment_operator(FLQuantAdolc flq){
    FLQuantAdolc out;
    out = flq;
    return out;
}

// Checking that a deep copy has been made
// [[Rcpp::export]]
Rcpp::List test_FLQuantAdolc_assignment_operator2(FLQuantAdolc flq1, int quant, int year, int unit, int season, int area, int iter, double value){
	FLQuantAdolc flq2;
    flq2 = flq1; 
    adouble ad_value = value;
	flq2(quant,year,unit,season,area,iter) = ad_value;
	return Rcpp::List::create(Rcpp::Named("flq1", flq1),
				Rcpp::Named("flq2",flq2));
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_from_FLQuant_constructor(FLQuant flq){
    FLQuantAdolc flqad(flq);
    return flqad;
}

//------------------ Accessors ----------------------
/*
// [[Rcpp::export]]
std::vector<double> test_FLQuantAdolc_get_data(FLQuantAdolc flq){
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
int test_FLQuantAdolc_get_size(FLQuantAdolc flq){
	return flq.get_size();
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

//---------- () accessors -----------------

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
    adouble ad_value = value;
    flq(element) = ad_value;
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
    adouble ad_value = value;
	flq(quant,year,unit,season,area,iter) = ad_value;
	return flq;
}
//------------ Set methods -------------------------

/*
// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_set_data(FLQuantAdolc flq, std::vector<double> data_in){
	flq.set_data(data_in);
	return flq;
}
*/

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_set_dimnames(FLQuantAdolc flq, Rcpp::List new_dimnames){
    flq.set_dimnames(new_dimnames);
    return flq;

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

