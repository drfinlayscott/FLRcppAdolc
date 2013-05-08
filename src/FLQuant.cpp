#include "../inst/include/FLQuant.h"

// Destructor - not needed. The members NumericVector and string are RAII and therefore look after their own resources
// set_units
// Operators:
// FLQuant + FLQuant
// FLQuant + single numeric
// FLQuant - FLQuant
// FLQuant - single numeric
// FLQuant * FLQuant
// FLQuant * single numeric
// FLQuant / FLQuant
// FLQuant / single numeric
// Check deep / shallow copy

// Default constructor
// No dimnames set as the array is null
FLQuant::FLQuant(){
	data = Rcpp::NumericVector(); // Empty NumericVector - just numeric(0)
	units = std::string(); // Empty string - just ""
}

// Constructor from an S4
// Include test that the class in the SEXP is an FLQuant?
FLQuant::FLQuant(SEXP flq_sexp){
	Rcpp::S4 flq_s4 = Rcpp::as<Rcpp::S4>(flq_sexp);
	data = flq_s4.slot(".Data");
	units = Rcpp::as<std::string>(flq_s4.slot("units"));
}

// Copy constructor - else 'data' can be pointed at by multiple instances
FLQuant::FLQuant(const FLQuant& FLQuant_source){
	data  = Rcpp::clone<Rcpp::NumericVector>(FLQuant_source.data);
	units = FLQuant_source.units; // std::string always does deep copy
}

// Assignment operator to ensure deep copy - else 'data' can be pointed at by multiple instances
FLQuant& FLQuant::operator = (const FLQuant& FLQuant_source){
	if (this != &FLQuant_source){
		data  = Rcpp::clone<Rcpp::NumericVector>(FLQuant_source.data);
		units = FLQuant_source.units; // std::string always does deep copy
	}
	return *this;
}

/* Accessor methods */
std::string FLQuant::get_units() const{
	return units;
}

Rcpp::NumericVector FLQuant::get_data() const{
	return data;
}

int FLQuant::get_nquant() const{
	Rcpp::IntegerVector dims = data.attr("dim");
	return dims(0);
}

int FLQuant::get_nyear() const{
	Rcpp::IntegerVector dims = data.attr("dim");
	return dims(1);
}

int FLQuant::get_nunit() const{
	Rcpp::IntegerVector dims = data.attr("dim");
	return dims(2);
}

int FLQuant::get_nseason() const{
	Rcpp::IntegerVector dims = data.attr("dim");
	return dims(3);
}

int FLQuant::get_narea() const{
	Rcpp::IntegerVector dims = data.attr("dim");
	return dims(4);
}

int FLQuant::get_niter() const{
	Rcpp::IntegerVector dims = data.attr("dim");
	return dims(5);
}

int FLQuant::get_data_element(const int quant, const int year, const int unit, const int season, const int area, const int iter) const{
	int element = (get_narea() * get_nseason() * get_nunit() * get_nyear() * get_nquant() * (iter - 1)) +
			(get_nseason() * get_nunit() * get_nyear() * get_nquant() * (area - 1)) +
			(get_nunit() * get_nyear() * get_nquant() * (season - 1)) +
			(get_nyear() * get_nquant() * (unit - 1)) +
			(get_nquant() * (year - 1)) +
			(quant - 1); 
	return element;
}

// Add check that arguments are >= 1 (if we keep 1 as first element)
// Also make them signed int so they are +ve always
// Get data accessor
double FLQuant::operator () (const int quant, const int year, const int unit, const int season, const int area, const int iter) const{
	int element = get_data_element(quant, year, unit, season, area, iter);
	return data(element);
}

// Set data accessor
// Add check that arguments are >= 1 (if we keep 1 as first element)
// Also make them signed int so they are +ve always
double& FLQuant::operator () (const int quant, const int year, const int unit, const int season, const int area, const int iter){
	int element = get_data_element(quant, year, unit, season, area, iter);
	return data(element);
}


/* Define template specialisations for as and wrap */
namespace Rcpp {
    template <> FLQuant as(SEXP flq_sexp) {
	FLQuant flq(flq_sexp);
        return flq;
    }

    template <> SEXP wrap(const FLQuant &flq) {
	Rcpp::S4 flq_s4("FLQuant");
	flq_s4.slot(".Data") = flq.get_data();
	flq_s4.slot("units") = flq.get_units();
        return Rcpp::wrap(flq_s4);
    }
}

/*
 * Tests 
 * To be moved somewhere else
 */

// [[Rcpp::export]]
std::string test_default_constructor_units(){
	FLQuant flq;
	return flq.get_units();
}

// [[Rcpp::export]]
Rcpp::NumericVector test_default_constructor_data(){
	FLQuant flq;
	return flq.get_data();
}

// [[Rcpp::export]]
std::string test_sexp_constructor_units(SEXP flq_sexp){
	FLQuant flq(flq_sexp);
	return flq.get_units();
}

// [[Rcpp::export]]
Rcpp::NumericVector test_sexp_constructor_data(SEXP flq_sexp){
	FLQuant flq(flq_sexp);
	return flq.get_data();
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLQuant_as(FLQuant flq){
	return flq.get_data();
}

// [[Rcpp::export]]
FLQuant test_FLQuant_as_wrap(FLQuant flq){
	return flq;
}

// [[Rcpp::export]]
double test_get_accessor(FLQuant flq, int quant, int year, int unit, int season, int area, int iter){
	double output = 0.0;
	output = flq(quant,year,unit,season,area,iter);
	return output;
}

// [[Rcpp::export]]
FLQuant test_set_accessor(FLQuant flq, int quant, int year, int unit, int season, int area, int iter, double value){
	flq(quant,year,unit,season,area,iter) = value;
	return flq;
}

// [[Rcpp::export]]
int test_get_nquant(FLQuant flq){
	return flq.get_nquant();
}

// [[Rcpp::export]]
int test_get_nyear(FLQuant flq){
	return flq.get_nyear();
}

// [[Rcpp::export]]
int test_get_nunit(FLQuant flq){
	return flq.get_nunit();
}


// [[Rcpp::export]]
int test_get_nseason(FLQuant flq){
	return flq.get_nseason();
}


// [[Rcpp::export]]
int test_get_narea(FLQuant flq){
	return flq.get_narea();
}

// [[Rcpp::export]]
int test_get_niter(FLQuant flq){
	return flq.get_niter();
}

// [[Rcpp::export]]
FLQuant test_copy_constructor(FLQuant flq1){
	FLQuant flq2(flq1); // uses copy constructor
	flq1(1,1,1,1,1,1) = 666.0;
	return flq2;
}

// [[Rcpp::export]]
FLQuant test_assignment_operator(FLQuant flq1){
	FLQuant flq2 = flq1; // uses copy constructor
	flq1(1,1,1,1,1,1) = 666.0;
	return flq2;
}




