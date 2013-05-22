#include "../../inst/include/FLQuant.h"

// [[Rcpp::export]]
FLQuant test_FLQuant_as_wrap(FLQuant flq){
	return flq;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_sexp_constructor(SEXP flq_sexp){
	FLQuant flq(flq_sexp);
	return flq;
}

// [[Rcpp::export]]
Rcpp::List test_FLQuant_copy_constructor(FLQuant flq1, int quant, int year, int unit, int season, int area, int iter, double value){
	FLQuant flq2(flq1); // uses copy constructor
	flq1(quant,year,unit,season,area,iter) = value;
	return Rcpp::List::create(Rcpp::Named("flq1", flq1),
				Rcpp::Named("flq2",flq2));
}

// [[Rcpp::export]]
Rcpp::List test_FLQuant_assignment_operator(FLQuant flq1, int quant, int year, int unit, int season, int area, int iter, double value){
	FLQuant flq2 = flq1; 
	flq1(quant,year,unit,season,area,iter) = value;
	return Rcpp::List::create(Rcpp::Named("flq1", flq1),
				Rcpp::Named("flq2",flq2));
}

// [[Rcpp::export]]
std::string test_FLQuant_get_units(FLQuant flq){
	return flq.get_units();
}

// [[Rcpp::export]]
FLQuant test_FLQuant_set_units(FLQuant flq, std::string new_units){
	flq.set_units(new_units);
	return flq;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLQuant_get_data(FLQuant flq){
	return flq.get_data();
}

// [[Rcpp::export]]
FLQuant test_FLQuant_set_data(FLQuant flq, Rcpp::NumericVector data_in){
	flq.set_data(data_in);
	return flq;
}

// [[Rcpp::export]]
int test_FLQuant_get_nquant(FLQuant flq){
	return flq.get_nquant();
}

// [[Rcpp::export]]
int test_FLQuant_get_nyear(FLQuant flq){
	return flq.get_nyear();
}

// [[Rcpp::export]]
int test_FLQuant_get_nunit(FLQuant flq){
	return flq.get_nunit();
}

// [[Rcpp::export]]
int test_FLQuant_get_nseason(FLQuant flq){
	return flq.get_nseason();
}

// [[Rcpp::export]]
int test_FLQuant_get_narea(FLQuant flq){
	return flq.get_narea();
}

// [[Rcpp::export]]
int test_FLQuant_get_niter(FLQuant flq){
	return flq.get_niter();
}

// [[Rcpp::export]]
Rcpp::IntegerVector test_FLQuant_get_dim(FLQuant flq){
    return flq.get_dim();
}

// [[Rcpp::export]]
FLQuant test_FLQuant_set_dim(FLQuant flq, Rcpp::IntegerVector dim){
    flq.set_dim(dim);
    return flq;
}

// [[Rcpp::export]]
Rcpp::List test_FLQuant_get_dimnames(FLQuant flq){
    return flq.get_dimnames();
}

// [[Rcpp::export]]
double test_FLQuant_get_accessor(const FLQuant flq, int quant, int year, int unit, int season, int area, int iter){
	double output = 0.0;
	output = flq(quant,year,unit,season,area,iter);
	return output;
}

// [[Rcpp::export]]
double test_FLQuant_get_single_index_accessor(const FLQuant flq, int element){
	double output = 0.0;
	output = flq(element);
	return output;
}

// Checking that returned values cannot affect the flq
// [[Rcpp::export]]
Rcpp::List test_FLQuant_get_single_index_accessor2(const FLQuant flq, int element){
	double output = 0.0;
	output = flq(element);
    output = 666.0;
    return Rcpp::List::create(Rcpp::Named("flq_out", flq),
            Rcpp::Named("output", output));
}

// [[Rcpp::export]]
FLQuant test_FLQuant_set_accessor(FLQuant flq, int quant, int year, int unit, int season, int area, int iter, double value){
	flq(quant,year,unit,season,area,iter) = value;
	return flq;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_set_single_index_accessor(FLQuant flq, int element, double value){
	flq(element) = value;
	return flq;
}

// [[Rcpp::export]]
int test_FLQuant_match_dims(FLQuant flq1, FLQuant flq2){
    return flq1.match_dims(flq2);
}

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_multiplier_assignment_operator(FLQuant flq1, FLQuant flq2){
	flq1 *= flq2;
	return flq1;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_multiplier_operator(FLQuant flq1, FLQuant flq2){
	FLQuant flq3 = flq1 * flq2;
	return flq3;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_multiplier_assignment_operator(FLQuant flq1, double rhs){
	flq1 *= rhs;
	return flq1;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_multiplier_operator(FLQuant flq1, double rhs){
	FLQuant flq3 = flq1 * rhs;
	return flq3;
}

// [[Rcpp::export]]
Rcpp::List test_FLQuant_FLQuant_multiplier_uses_deep_copy(FLQuant flq1, FLQuant flq2){
    FLQuant flq3 = flq1 * flq2;
	return Rcpp::List::create(Rcpp::Named("flq1", flq1),
				Rcpp::Named("flq2",flq2),
				Rcpp::Named("flq3",flq3));
}

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_divide_assignment_operator(FLQuant flq1, FLQuant flq2){
	flq1 /= flq2;
	return flq1;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_divide_operator(FLQuant flq1, FLQuant flq2){
	FLQuant flq3 = flq1 / flq2;
	return flq3;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_divide_assignment_operator(FLQuant flq1, double rhs){
	flq1 /= rhs;
	return flq1;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_divide_operator(FLQuant flq1, double rhs){
	FLQuant flq3 = flq1 / rhs;
	return flq3;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_addition_assignment_operator(FLQuant flq1, FLQuant flq2){
	flq1 += flq2;
	return flq1;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_addition_operator(FLQuant flq1, FLQuant flq2){
	FLQuant flq3 = flq1 + flq2;
	return flq3;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_addition_assignment_operator(FLQuant flq1, double rhs){
	flq1 += rhs;
	return flq1;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_addition_operator(FLQuant flq1, double rhs){
	FLQuant flq3 = flq1 + rhs;
	return flq3;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_difference_assignment_operator(FLQuant flq1, FLQuant flq2){
	flq1 -= flq2;
	return flq1;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_difference_operator(FLQuant flq1, FLQuant flq2){
	FLQuant flq3 = flq1 - flq2;
	return flq3;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_difference_assignment_operator(FLQuant flq1, double rhs){
	flq1 -= rhs;
	return flq1;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_difference_operator(FLQuant flq1, double rhs){
	FLQuant flq3 = flq1 - rhs;
	return flq3;
}

