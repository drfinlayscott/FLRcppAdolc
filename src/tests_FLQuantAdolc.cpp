#include "../../inst/include/FLQuantAdolc.h"

// [[Rcpp::export]]
void do_nothing_FLQuantAdolc(){
    return;
}

// [[Rcpp::export]]
void test_FLQuantAdolc_basic_constructor(){
    FLQuantAdolc flqad;
    flqad.what_am_i();
    return;
}

// [[Rcpp::export]]
void test_FLQuantAdolc_sexp_constructor(SEXP flq_sexp){
	FLQuantAdolc flqad(flq_sexp);
	return;
}

// [[Rcpp::export]]
FLQuant_base<adouble> test_generic_FLQuant_base_wrap(SEXP flq_sexp){
    FLQuant_base<adouble> flqad(flq_sexp);
    return flqad;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_as_wrap(FLQuantAdolc flqad){
	return flqad;
}

//------------------ Arithmetic operators ----------------------
// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuant_multiplier_assignment_operator(FLQuantAdolc flqad1, FLQuant flq2){
    flqad1.new_int = 12;
    flqad1 *= flq2;
    Rprintf("Value of new_int: %i\n", flqad1.new_int);
    return flqad1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuantAdolc_multiplier_assignment_operator(FLQuantAdolc flqad1, FLQuantAdolc flqad2){
    flqad1.new_int = 12;
    flqad2.new_int = 16;
    flqad1 *= flqad2;
    Rprintf("Value of flqad1 new_int: %i\n", flqad1.new_int);
    Rprintf("Value of flqad2 new_int: %i\n", flqad2.new_int);
    return flqad1;
}

