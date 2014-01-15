/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../../inst/include/FLQuant_multidim.h"


// [[Rcpp::export]]
void test_FLQuant7_constructor(){
    FLQuant7 flq;
    return;
}

// [[Rcpp::export]]
void test_FLQuant7_sexp_constructor(SEXP flq_sexp1){
	FLQuant7 flq7(flq_sexp1);
	return;
}

// [[Rcpp::export]]
FLQuant7 test_FLQuant7_FLQuant_constructor(FLQuant flq){
	FLQuant7 flq7(flq);
	return flq7;
}

// Testing adding another FLQ into FLQ7 - also tests wrap
// [[Rcpp::export]]
FLQuant7 test_FLQuant7_function_operator(FLQuant flq1, FLQuant flq2){
	FLQuant7 flq7(flq1);
    flq7(flq2);
	return flq7;
}

// [[Rcpp::export]]
FLQuant7 test_FLQuant7_empty_wrap(){
	FLQuant7 flq7;
	return flq7;
}

// [[Rcpp::export]]
FLQuant7 test_FLQuant7_wrap(SEXP flq_sexp1){
	FLQuant7 flq7(flq_sexp1);
	return flq7;
}

// [[Rcpp::export]]
int test_FLQuant7_get_ndim7(SEXP flq_sexp1, SEXP flq_sexp2){
	FLQuant7 flq7(flq_sexp1);
    int length = flq7.get_ndim7();
	return length;
}

// [[Rcpp::export]]
FLQuant7 test_FLQuant7_as(FLQuant7 flq7){
    return flq7;
}

// Test copy and assignment constructors

// [[Rcpp::export]]
FLQuant test_FLQuant7_single_get_accessor(const FLQuant7 flq7, const int element){
    FLQuant flq = flq7(element);
    return flq;
}

// [[Rcpp::export]]
FLQuant7 test_FLQuant7_single_set_accessor(FLQuant7 flq7, const int element, const FLQuant flq){
    flq7(element) = flq;
    return flq7;
}

// [[Rcpp::export]]
double test_FLQuant7_const_get_accessor(const FLQuant7 flq7, const int dim7, const int quant, const int year, const int unit, const int season, const int area, const int iter){
	double output = 0.0;
	output = flq7(dim7, quant,year,unit,season,area,iter);
	return output;
}

// [[Rcpp::export]]
FLQuant7 test_FLQuant7_get_accessor(FLQuant7 flq7, double value, const int dim7, const int quant, const int year, const int unit, const int season, const int area, const int iter){
	flq7(dim7, quant,year,unit,season,area,iter) = value;
	return flq7;
}


/*-----------------------------------*/
/*
// as tests
// [[Rcpp::export]]
void test_dummy_SEXP(SEXP sexp){
    dummy_as test(sexp);
}

// [[Rcpp::export]]
void test_dummy_as(dummy_as d){
    d;
}

// [[Rcpp::export]]
void test_dummy_template_SEXP(SEXP sexp){
    datd test(sexp);
}

// [[Rcpp::export]]
void test_dummy_template_as(datd d){
    d;
    return;
}
*/
