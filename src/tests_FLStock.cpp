#include "../../inst/include/FLStock.h"

// [[Rcpp::export]]
FLStock test_FLStock_wrap(SEXP fls_sexp){
	FLStock fls(fls_sexp);
	return fls;
}

// [[Rcpp::export]]
FLQuant test_FLStock_sexp_constructor(SEXP fls_sexp){
	FLStock fls(fls_sexp);
	return fls.stock_n;
}

// For some reason using the export causes a linking error
//// [[Rcpp::export]]
FLQuant test_FLStock_as(FLStock fls){
	return fls.stock_n;
}

