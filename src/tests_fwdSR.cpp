/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../../inst/include/fwdSR.h"

/*-------------------------------------------------------*/
// Templated class tests


// [[Rcpp::export]]
void test_fwdSR_empty_constructor(){
	fwdSR flsr;
	return;
}

//// [[Rcpp::export]]
//void test_fwdSR_sexp_constructor(SEXP flsr_sexp){
//	fwdSR flsr(flsr_sexp);
//	return;
//}

// [[Rcpp::export]]
void test_fwdSR_constructor(std::string model_name, const FLQuant params, const FLQuant residuals, const bool residuals_mult){

    fwdSR fwdsr(model_name, params, residuals, residuals_mult);
    return;
}


// [[Rcpp::export]]
fwdSR test_fwdSR_constructor_wrap(std::string model_name, const FLQuant params, const FLQuant residuals, const bool residuals_mult){

    fwdSR fwdsr(model_name, params, residuals, residuals_mult);
    return fwdsr;
}

// [[Rcpp::export]]
double test_fwdSR_constructor_value(std::string model_name, const FLQuant params, const FLQuant residuals, const bool residuals_mult){

    fwdSR fwdsr(model_name, params, residuals, residuals_mult);
    double out = fwdsr.eval_model(288540,1,1,1,1,1);
    return out;

}

// [[Rcpp::export]]
int test_fwdSR_get_nparams(std::string model_name, const FLQuant params, const FLQuant residuals, const bool residuals_mult){
    fwdSR fwdsr(model_name, params, residuals, residuals_mult);
    return fwdsr.get_nparams();

}

//// [[Rcpp::export]]
//double test_fwdSR_eval_model(SEXP flsr_sexp){
//	fwdSR flsr(flsr_sexp);
//    double out = flsr.eval_model(288540);
//    //double out = 10.0;
//	return out;
//}




//// [[Rcpp::export]]
//fwdBiolAdolc test_fwdBiolAdolc_sexp_constructor(SEXP flb_sexp){
//	fwdBiolAdolc fwdb(flb_sexp);
//	return fwdb;
//}
//
//// [[Rcpp::export]]
//fwdBiol test_fwdBiol_as_wrap(fwdBiol fwdb){
//	return fwdb;
//}
//
//// [[Rcpp::export]]
//fwdBiolAdolc test_fwdBiolAdolc_as_wrap(fwdBiolAdolc fwdb){
//	return fwdb;
//}
//
//// [[Rcpp::export]]
//fwdBiol test_fwdBiol_copy_constructor(fwdBiol fwdb1){
//	fwdBiol fwdb2(fwdb1); // uses copy constructor
//    return fwdb2;
//}
//
//// [[Rcpp::export]]
//fwdBiolAdolc test_fwdBiolAdolc_copy_constructor(fwdBiolAdolc fwdb1){
//	fwdBiolAdolc fwdb2(fwdb1); // uses copy constructor
//    return fwdb2;
//}
//
//// [[Rcpp::export]]
//Rcpp::List test_fwdBiol_copy_constructor2(fwdBiol fwdb1, int quant, int year, int unit, int season, int area, int iter, double value){
//	fwdBiol fwdb2(fwdb1); // uses copy constructor
//	fwdb2.n()(quant,year,unit,season,area,iter) = value;
//	return Rcpp::List::create(Rcpp::Named("fwdb1", fwdb1),
//				Rcpp::Named("fwdb2",fwdb2));
//}
//
//// [[Rcpp::export]]
//Rcpp::List test_fwdBiolAdolc_copy_constructor2(fwdBiolAdolc fwdb1, int quant, int year, int unit, int season, int area, int iter, double value){
//    adouble value_ad = value;
//	fwdBiolAdolc fwdb2(fwdb1); // uses copy constructor
//	fwdb2.n()(quant,year,unit,season,area,iter) = value_ad;
//	return Rcpp::List::create(Rcpp::Named("fwdb1", fwdb1),
//				Rcpp::Named("fwdb2",fwdb2));
//}
//
//// [[Rcpp::export]]
//fwdBiol test_fwdBiol_assignment_operator(fwdBiol fwdb1){
//	fwdBiol fwdb2 = fwdb1; 
//    return fwdb2;
//}
//
//// [[Rcpp::export]]
//fwdBiolAdolc test_fwdBiolAdolc_assignment_operator(fwdBiolAdolc fwdb1){
//	fwdBiolAdolc fwdb2 = fwdb1; 
//    return fwdb2;
//}
//
//// [[Rcpp::export]]
//Rcpp::List test_fwdBiol_assignment_operator2(fwdBiol fwdb1, int quant, int year, int unit, int season, int area, int iter, double value){
//	fwdBiol fwdb2 = fwdb1; 
//	fwdb2.n()(quant,year,unit,season,area,iter) = value;
//	return Rcpp::List::create(Rcpp::Named("fwdb1", fwdb1),
//				Rcpp::Named("fwdb2",fwdb2));
//}
//
//// [[Rcpp::export]]
//Rcpp::List test_fwdBiolAdolc_assignment_operator2(fwdBiolAdolc fwdb1, int quant, int year, int unit, int season, int area, int iter, double value){
//    adouble value_ad = value;
//	fwdBiolAdolc fwdb2 = fwdb1; 
//	fwdb2.n()(quant,year,unit,season,area,iter) = value_ad;
//	return Rcpp::List::create(Rcpp::Named("fwdb1", fwdb1),
//				Rcpp::Named("fwdb2",fwdb2));
//}
//
