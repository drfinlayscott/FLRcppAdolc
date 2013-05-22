#include "../inst/include/FLQuant.h"

// Destructor - not needed. The members NumericVector and string are RAII and therefore look after their own resources
// set_units
// set_dim
// set_dimnames
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
		data  = Rcpp::clone<Rcpp::NumericVector>(FLQuant_source.data); // Clone for a deep copy
		units = FLQuant_source.units; // std::string always does deep copy
	}
	return *this;
}

/* Accessor methods */
std::string FLQuant::get_units() const{
	return units;
}

void FLQuant::set_units(const std::string new_units){
	units = new_units;
}

Rcpp::NumericVector FLQuant::get_data() const{
	return data;
}

void FLQuant::set_data(const Rcpp::NumericVector& data_in){
	data  = Rcpp::clone<Rcpp::NumericVector>(data_in);
}

/*  A strange method this one. You can only set different dims
  if the data member doesn't have dimnames that match the different dims.
  But the data member will already dim and dimnames attributes that match,
  so you cannot change one on it's own.
  This method is therefore only really used if the data member has no existing attributes.
  This can happen, for example, if a sugar method is used which removes all attributes */
void FLQuant::set_dim(const Rcpp::IntegerVector dim){
    // Error checks
    // Must have 6 dimensions
    const int ndim = dim.size();
    if (ndim != 6){
        Rcpp::stop("Trying to set dim attribute when ndim != 6");
    }
    // Product of dimensions must equal length of data NumericVector
    int prod_dim = 1;
    for (int i = 0; i < 6; ++i){
        prod_dim = prod_dim * dim(i);
    }
    if (prod_dim != data.size()){
        Rcpp::stop("Trying to set dim attribute which has a different total size to the data member");
    }
    data.attr("dim") = dim;
}

// This does not check that the dimnames are xxx, year, unit etc.
/*
void FLQuant::set_dimnames(const Rcpp::List dimnames){
    if (dimnames.size() != 6){
        Rcpp::stop("Dimnames must be of length 6");
    }
    data.attr("dimnames") = dimnames;
}
*/

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

Rcpp::IntegerVector FLQuant::get_dim() const{
    return data.attr("dim");
}

Rcpp::List FLQuant::get_dimnames() const{
    return data.attr("dimnames");
}

// Note that elements start at 1 NOT 0!
int FLQuant::get_data_element(const int quant, const int year, const int unit, const int season, const int area, const int iter) const{
    Rcpp::IntegerVector dims = data.attr("dim");
    if ((quant > dims(0)) || (year > dims[1]) || (unit > dims(2)) || (season > dims(3)) || (area > dims(4)) || (iter > dims(5))){
            Rcpp::stop("Trying to access element outside of dim range.");
    }
	unsigned int element = (get_narea() * get_nseason() * get_nunit() * get_nyear() * get_nquant() * (iter - 1)) +
			(get_nseason() * get_nunit() * get_nyear() * get_nquant() * (area - 1)) +
			(get_nunit() * get_nyear() * get_nquant() * (season - 1)) +
			(get_nyear() * get_nquant() * (unit - 1)) +
			(get_nquant() * (year - 1)) +
			(quant - 1); 
	return element;
}

// Data accessor - all dims
double& FLQuant::operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter){
	unsigned int element = get_data_element(quant, year, unit, season, area, iter);
	return data(element);
}

// Data accessor - single element
double& FLQuant::operator () (const int element){
    if (element > data.size()){
    Rcpp::stop("Trying to access element larger than data size.");
    }
	return data(element-1);
}

// Get only data accessor - all dims
double FLQuant::operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter) const{
	unsigned int element = get_data_element(quant, year, unit, season, area, iter);
    //double & out = data[element];
	return data[element];
    //return out;
}

// Get only data accessor - single element
double FLQuant::operator () (const int element) const{
    if (element > data.size()){
    Rcpp::stop("Trying to access element larger than data size.");
    }
    return data[element-1];
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

/* Mathematical operators */
// Was going to use Rcpp sugar to multiply the data NumericVectors together
// But this has the side effect of stripping out the dim and dimnames attributes
// We could still use it and then set_dim and set_dimnames but that seems a bit long winded
FLQuant& FLQuant::operator *= (const FLQuant& flq_rhs){
    if (match_dims(flq_rhs) != 1){
        Rcpp::stop("You cannot multiply FLQuants as your dimensions do not match.");
    }
    for (int i = 1; i <= data.size(); ++i)
        (*this)(i) = (*this)(i) * flq_rhs(i); // Use the () operator instead of accessing data member directly so indexing starts at same place
    return *this;
}

FLQuant FLQuant::operator * (const FLQuant& flq_rhs) const{
    FLQuant flq_out = *this; // Copy myself
    flq_out *= flq_rhs;
    return flq_out;
}

FLQuant& FLQuant::operator /= (const FLQuant& flq_rhs){
    if (match_dims(flq_rhs) != 1){
        Rcpp::stop("You cannot divide FLQuants as your dimensions do not match.");
    }
    for (int i = 1; i <= data.size(); ++i)
        (*this)(i) = (*this)(i) / flq_rhs(i); // Use the () operator instead of accessing data member directly so indexing starts at same place
    return *this;
}

FLQuant FLQuant::operator / (const FLQuant& flq_rhs) const{
    FLQuant flq_out = *this; // Copy myself
    flq_out /= flq_rhs;
    return flq_out;
}

FLQuant& FLQuant::operator += (const FLQuant& flq_rhs){
    if (match_dims(flq_rhs) != 1){
        Rcpp::stop("You cannot add FLQuants as your dimensions do not match.");
    }
    for (int i = 1; i <= data.size(); ++i)
        (*this)(i) = (*this)(i) + flq_rhs(i); // Use the () operator instead of accessing data member directly so indexing starts at same place
    return *this;
}

FLQuant FLQuant::operator + (const FLQuant& flq_rhs) const{
    FLQuant flq_out = *this; // Copy myself
    flq_out += flq_rhs;
    return flq_out;
}

FLQuant& FLQuant::operator -= (const FLQuant& flq_rhs){
    if (match_dims(flq_rhs) != 1){
        Rcpp::stop("You cannot subtract FLQuants as your dimensions do not match.");
    }
    for (int i = 1; i <= data.size(); ++i)
        (*this)(i) = (*this)(i) - flq_rhs(i); // Use the () operator instead of accessing data member directly so indexing starts at same place
    return *this;
}

FLQuant FLQuant::operator - (const FLQuant& flq_rhs) const{
    FLQuant flq_out = *this; // Copy myself
    flq_out -= flq_rhs;
    return flq_out;
}

/* Do the dimensions of two FLQuants match?
    If yes, return 1
    Else, return the negative of the first dimension that is wrong
*/
int FLQuant::match_dims(const FLQuant& b) const{
    Rcpp::IntegerVector dims_a =  get_dim();
    Rcpp::IntegerVector dims_b =  b.get_dim();
    for (int i=0; i<6; ++i){
        if (dims_a(i) != dims_b(i)){
            return -1 * (i+1); // Return negative of what dim does not match
        }
    }
    return 1; // Else all is good
}
