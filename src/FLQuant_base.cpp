/* 
 * Copyright 2013 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../inst/include/FLQuant_base.h"

// Default constructor
// No dimnames set as the array is null
template <typename T>
FLQuant_base<T>::FLQuant_base(){
    Rprintf("In FLQuant_base<T> basic constructor\n");
	units = std::string(); // Empty string - just ""
    dim = Rcpp::IntegerVector();
    dimnames = Rcpp::List();
    // Make NULL std::vector<T>?
}

// Generic SEXP constructor
// Used as intrusive 'as'
// Need to add check that the SEXP is an FLQuant
template<typename T>
FLQuant_base<T>::FLQuant_base(SEXP flq_sexp){
    Rprintf("In FLQuant_base SEXP constructor\n");
	Rcpp::S4 flq_s4 = Rcpp::as<Rcpp::S4>(flq_sexp);
    Rcpp::NumericVector data_nv = flq_s4.slot(".Data");
    // Initialise data to the correct size?
    // Fill up data
    data.insert(data.begin(), data_nv.begin(), data_nv.end());
	units = Rcpp::as<std::string>(flq_s4.slot("units"));
	dim = data_nv.attr("dim");
	dimnames = data_nv.attr("dimnames");
}

/* Used as intrusive 'wrap'
 * This needs to be specialised for T
 * i.e. wrapping a double is different to wrapping adouble
 * So this is a generic wrap that just returns a 0
 */
template<typename T>
FLQuant_base<T>::operator SEXP() const{
    Rprintf("Wrapping generic FLQuant_base. Probably not what you wanted.\n");
    int x = 0;
    return Rcpp::wrap(x);
}

// Specialise the wrap for an FLQuant_base<double>
template<>
FLQuant_base<double>::operator SEXP() const{
    Rprintf("Specialised wrapping FLQuant_base<double>\n");
    Rcpp::S4 flq_s4("FLQuant");
    // Make and fill the NumericVector that will be the 'data' slot 
    Rcpp::NumericVector data_nv;
    for (vector<double>::const_iterator data_iterator = data.begin(); data_iterator != data.end(); ++data_iterator){ // iterator must be const because the method is const
        data_nv.push_back(*data_iterator);
    }
    // Apply dims and dimnames
	data_nv.attr("dim") = dim;
	data_nv.attr("dimnames") = dimnames;
    // Fill the slots
    flq_s4.slot(".Data") = data_nv;
    flq_s4.slot("units") = units;
    return Rcpp::wrap(flq_s4);
}

// Specialise the wrap for an FLQuant_base<adouble>
// Necessary because we have to pull .value() out
template<>
FLQuant_base<adouble>::operator SEXP() const{
    Rprintf("Specialised wrapping FLQuant_base<adouble>\n");
    Rcpp::S4 flq_s4("FLQuant");
    // Make and fill the NumericVector that will be the 'data' slot 
    Rcpp::NumericVector data_nv;
    for (vector<adouble>::const_iterator data_iterator = data.begin(); data_iterator != data.end(); ++data_iterator){ // iterator must be const because the method is const
        data_nv.push_back((*data_iterator).value());
    }
    // Apply dims and dimnames
	data_nv.attr("dim") = dim;
	data_nv.attr("dimnames") = dimnames;
    // Fill the slots
    flq_s4.slot(".Data") = data_nv;
    flq_s4.slot("units") = units;
    return Rcpp::wrap(flq_s4);
}

// Copy constructor - else 'data' can be pointed at by multiple instances
template<typename T>
FLQuant_base<T>::FLQuant_base(const FLQuant_base<T>& FLQuant_source){
    Rprintf("In FLQuant_base<T> copy constructor\n");
	data  = FLQuant_source.data; // std::vector always does deep copy
	units = FLQuant_source.units; // std::string always does deep copy
    dim = Rcpp::clone<Rcpp::IntegerVector>(FLQuant_source.dim);
    dimnames = Rcpp::clone<Rcpp::List>(FLQuant_source.dimnames);
}

// Assignment operator to ensure deep copy - else 'data' can be pointed at by multiple instances
template<typename T>
FLQuant_base<T>& FLQuant_base<T>::operator = (const FLQuant_base<T>& FLQuant_source){
    Rprintf("In FLQuant_base<T> assignment operator\n");
	if (this != &FLQuant_source){
        data  = FLQuant_source.data; // std::vector always does deep copy
        units = FLQuant_source.units; // std::string always does deep copy
        dim = Rcpp::clone<Rcpp::IntegerVector>(FLQuant_source.dim);
        dimnames = Rcpp::clone<Rcpp::List>(FLQuant_source.dimnames);
	}
	return *this;
}

// Construct FLQuant_base<T> from an FLQuant_base<T2>
// Need specialisation
template <typename T>
template <typename T2>
FLQuant_base<T>::FLQuant_base(const FLQuant_base<T2>& FLQuant_source){
    Rprintf("In constructor for FLQuant_base<T>(FLQuant_base<T2>)\n");
    Rcpp::stop("I have no specific instructions for these types. Please add a specialisation\n");
}

// Specialise the FLQuant_base<T>(FLQuant_base<T2>) constructor 
// Make an FLQuantAdolc from an FLQuant
template <>
template <>
FLQuant_base<adouble>::FLQuant_base(const FLQuant_base<double>& FLQuant_source){
    Rprintf("Making an FLQuantAdolc from an FLQuant\n");
    units = FLQuant_source.get_units(); // std::string always does deep copy
    dim = FLQuant_source.get_dim();
    dimnames = FLQuant_source.get_dimnames(); 
    std::vector<double> source_data = FLQuant_source.get_data();
    data.insert(data.begin(), source_data.begin(), source_data.end());
}


//------------------ Accessors ---------------------------------

template <typename T>
std::vector<T> FLQuant_base<T>::get_data() const{
	return data;
}

template <typename T>
std::string FLQuant_base<T>::get_units() const{
	return units;
}

template <typename T>
Rcpp::IntegerVector FLQuant_base<T>::get_dim() const{
	return dim;
}

template <typename T>
Rcpp::List FLQuant_base<T>::get_dimnames() const{
	return dimnames;
}

template <typename T>
unsigned int FLQuant_base<T>::get_size() const{
	return data.size();
}

template <typename T>
int FLQuant_base<T>::get_nquant() const{
	Rcpp::IntegerVector dim = get_dim();
	return dim(0);
}

template <typename T>
int FLQuant_base<T>::get_nyear() const{
	Rcpp::IntegerVector dim = get_dim();
	return dim(1);
}

template <typename T>
int FLQuant_base<T>::get_nunit() const{
	Rcpp::IntegerVector dim = get_dim();
	return dim(2);
}

template <typename T>
int FLQuant_base<T>::get_nseason() const{
	Rcpp::IntegerVector dim = get_dim();
	return dim(3);
}

template <typename T>
int FLQuant_base<T>::get_narea() const{
	Rcpp::IntegerVector dim = get_dim();
	return dim(4);
}

template <typename T>
int FLQuant_base<T>::get_niter() const{
	Rcpp::IntegerVector dim = get_dim();
	return dim(5);
}

// Note that elements start at 1 NOT 0!
template <typename T>
int FLQuant_base<T>::get_data_element(const int quant, const int year, const int unit, const int season, const int area, const int iter) const{
    Rcpp::IntegerVector dim = get_dim();
    if ((quant > dim(0)) || (year > dim[1]) || (unit > dim(2)) || (season > dim(3)) || (area > dim(4)) || (iter > dim(5))){
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

// Get only data accessor - single element
template <typename T>
T FLQuant_base<T>::operator () (const unsigned int element) const{
    Rprintf("In const single element accessor\n");
    if (element > get_size()){
        Rcpp::stop("Trying to access element larger than data size.");
    }
    return data[element-1];
}

// Data accessor - single element
template <typename T>
T& FLQuant_base<T>::operator () (const unsigned int element){
    Rprintf("In single element accessor\n");
    if (element > get_size()){
        Rcpp::stop("Trying to access element larger than data size.");
    }
	return data[element-1];
}

// Get only data accessor - all dims
template <typename T>
T FLQuant_base<T>::operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter) const{
    Rprintf("In const multiple element accessor\n");
	unsigned int element = get_data_element(quant, year, unit, season, area, iter);
	return data[element];
}

// Data accessor - all dims
template <typename T>
T& FLQuant_base<T>::operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter){
    Rprintf("In multiple element accessor\n");
	unsigned int element = get_data_element(quant, year, unit, season, area, iter);
	return data[element];
}

//------------- Setting methods ----------------

template <typename T>
void FLQuant_base<T>::set_data(const std::vector<T>& data_in){
    Rcpp::IntegerVector dim = get_dim();
    unsigned int dim_prod = (dim[0] * dim[1] * dim[2]* dim[3]* dim[4]* dim[5]);
    if(dim_prod != data_in.size()){
        Rcpp::stop("Cannot set data. Data size does not match dims.\n");
    }
    data = data_in;
}

//------------------ Multiplication operators -------------------
/*  * Need to consider what happens with the combinations FLQuant<T1> * / + - FLQuant<T2>, i.e. what is the output type?
 *  adouble *  double = adouble
 *  adouble * adouble = adouble
 *  double  *  double = double
 *  Definition of friend function for arithmetic operation
 */

// Multiplication self assignment
template<typename T>
FLQuant_base<T>& FLQuant_base<T>::operator *= (const FLQuant_base<T>& rhs){
    Rprintf("In self multiplication assignment\n");
    if (match_dims(rhs) != 1){
        Rcpp::stop("You cannot multiply FLQuants as your dimensions do not match.");
    }
    std::transform((*this).data.begin(), (*this).data.end(), rhs.data.begin(), (*this).data.begin(), std::multiplies<T>());
    return *this;
}
// Special case of multiplication assignment 
// Instantiation below ensures that it will only compile for FLQuantAdolc *= FLQuant
// FLQuant *= FLQuantAdolc will not compile as cannot have double = double * adouble
// Needs to be instanitated due to extra template class, T2
template <typename T>
template <typename T2>
FLQuant_base<T>& FLQuant_base<T>::operator *= (const FLQuant_base<T2>& rhs){
    Rprintf("In T1*=T2 multiplication assignment\n");
    if (match_dims(rhs) != 1){
        Rcpp::stop("You cannot multiply FLQuants as your dimensions do not match.");
    }
    std::vector<T2> rhs_data = rhs.get_data();
    std::transform((*this).data.begin(), (*this).data.end(), rhs_data.begin(), (*this).data.begin(), std::multiplies<T>());
    return *this;
}

// FLQuant *= double
// FLQuantAdolc *= adouble
template <typename T>
FLQuant_base<T>& FLQuant_base<T>::operator *= (const T& rhs){
    Rprintf("In scalar T=*T multiplication assignment\n");
    std::transform((*this).data.begin(), (*this).data.end(), (*this).data.begin(), std::bind1st(std::multiplies<T>(),rhs)); 
    return *this;
}

// Special case of multiplication assignment 
// Used for FLQuantAdolc *= double
// Needs to be instanitated due to extra template class, T2
template <typename T>
template <typename T2>
FLQuant_base<T>& FLQuant_base<T>::operator *= (const T2& rhs){
    Rprintf("In scalar T=*T2 multiplication assignment\n");
    std::transform((*this).data.begin(), (*this).data.end(), (*this).data.begin(), std::bind1st(std::multiplies<T>(),rhs)); 
    return *this;
}

// General multiplication
// FLQuant_base<T> * FLQuant_base<T>
template <typename T>
FLQuant_base<T> FLQuant_base<T>::operator * (const FLQuant_base<T>& rhs) const{
    Rprintf("In self multiplication\n");
    if (match_dims(rhs) != 1){
        Rcpp::stop("You cannot multiply FLQuants as your dimensions do not match.");
    }
    FLQuant_base<T> out = *this; // Copy myself
    out *= rhs;
    return out;
}

// FLQuant_base<T> * T
template <typename T>
FLQuant_base<T> FLQuant_base<T>::operator * (const T& rhs) const{
    FLQuant_base<T> out = *this; // Copy myself
    out *= rhs;
    return out;
}

// Outside of class
template <typename T>
FLQuant_base<T> operator * (const FLQuant_base<double>& lhs, const FLQuant_base<T>& rhs){
    Rprintf("FLQuant_base<double> * FLQuant_base<T>\n");
    if (lhs.match_dims(rhs) != 1){
        Rcpp::stop("You cannot multiply FLQuants as your dimensions do not match.");
    }
    FLQuant_base<T> out = rhs;
    out *= lhs;
    return out;

}

template <typename T>
FLQuant_base<T> operator * (const FLQuant_base<T>& lhs, const FLQuant_base<double>& rhs){
    Rprintf("FLQuant_base<T> * FLQuant_base<double>\n");
    if (lhs.match_dims(rhs) != 1){
        Rcpp::stop("You cannot multiply FLQuants as your dimensions do not match.");
    }
    FLQuant_base<T> out = lhs;
    out *= rhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator * (const T& lhs, const FLQuant_base<T>& rhs){
    FLQuant_base<T> out = rhs;
    out *= lhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator * (const double& lhs, const FLQuant_base<T>& rhs){
    FLQuant_base<T> out = rhs;
    out *= lhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator * (const FLQuant_base<T>& lhs, const double& rhs){
    FLQuant_base<T> out = lhs;
    out *= rhs;
    return out;
}

FLQuant_base<double> operator * (const double& lhs, const FLQuant_base<double>& rhs){
    FLQuant_base<double> out = rhs;
    out *= lhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator * (const FLQuant_base<double>& lhs, const T& rhs){
    FLQuant_base<T> out(lhs);
    out *= rhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator * (const T& lhs, const FLQuant_base<double>& rhs){
    FLQuant_base<T> out(rhs);
    out *= lhs;
    return out;
}

//------------------ Division operators -------------------

// Division self assignment
template<typename T>
FLQuant_base<T>& FLQuant_base<T>::operator /= (const FLQuant_base<T>& rhs){
    if (match_dims(rhs) != 1){
        Rcpp::stop("You cannot divide FLQuants as your dimensions do not match.");
    }
    std::transform((*this).data.begin(), (*this).data.end(), rhs.data.begin(), (*this).data.begin(), std::divides<T>());
    return *this;
}
// Special case of division assignment 
// Instantiation below ensures that it will only compile for FLQuantAdolc /= FLQuant
template <typename T>
template <typename T2>
FLQuant_base<T>& FLQuant_base<T>::operator /= (const FLQuant_base<T2>& rhs){
    if (match_dims(rhs) != 1){
        Rcpp::stop("You cannot divide FLQuants as your dimensions do not match.");
    }
    std::vector<T2> rhs_data = rhs.get_data();
    std::transform((*this).data.begin(), (*this).data.end(), rhs_data.begin(), (*this).data.begin(), std::divides<T>());
    return *this;
}

// FLQuant /= double
// FLQuantAdolc /= adouble
template <typename T>
FLQuant_base<T>& FLQuant_base<T>::operator /= (const T& rhs){
    std::transform((*this).data.begin(), (*this).data.end(), (*this).data.begin(), std::bind2nd(std::divides<T>(),rhs)); 
    return *this;
}

// Special case of division assignment 
// Used for FLQuantAdolc /= double
// Needs to be instanitated due to extra template class, T2
template <typename T>
template <typename T2>
FLQuant_base<T>& FLQuant_base<T>::operator /= (const T2& rhs){
    std::transform((*this).data.begin(), (*this).data.end(), (*this).data.begin(), std::bind2nd(std::divides<T>(),rhs)); 
    return *this;
}

// General division 
// FLQuant_base<T> / FLQuant_base<T>
template <typename T>
FLQuant_base<T> FLQuant_base<T>::operator / (const FLQuant_base<T>& rhs) const{
    if (match_dims(rhs) != 1){
        Rcpp::stop("You cannot divide FLQuants as your dimensions do not match.");
    }
    FLQuant_base<T> out = *this; // Copy myself
    out /= rhs;
    return out;
}

// FLQuant_base<T> / T
template <typename T>
FLQuant_base<T> FLQuant_base<T>::operator / (const T& rhs) const{
    FLQuant_base<T> out = *this; // Copy myself
    out /= rhs;
    return out;
}

// Declared outside of class
template <typename T>
FLQuant_base<T> operator / (const FLQuant_base<double>& lhs, const FLQuant_base<T>& rhs){
    if (lhs.match_dims(rhs) != 1){
        Rcpp::stop("You cannot divide FLQuants as your dimensions do not match.");
    }
    FLQuant_base<T> out(lhs);
    out /= rhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator / (const FLQuant_base<T>& lhs, const FLQuant_base<double>& rhs){
    if (lhs.match_dims(rhs) != 1){
        Rcpp::stop("You cannot divide FLQuants as your dimensions do not match.");
    }
    FLQuant_base<T> out = lhs;
    out /= rhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator / (const T& lhs, const FLQuant_base<T>& rhs){
    FLQuant_base<T> out = rhs;
    std::vector<T> out_data = out.get_data();
    std::transform(out_data.begin(), out_data.end(), out_data.begin(), std::bind1st(std::divides<T>(),lhs)); 
    out.set_data(out_data);
    return out;
}

template <typename T>
FLQuant_base<T> operator / (const double& lhs, const FLQuant_base<T>& rhs){
    FLQuant_base<T> out = rhs;
    std::vector<T> out_data = out.get_data();
    std::transform(out_data.begin(), out_data.end(), out_data.begin(), std::bind1st(std::divides<T>(),lhs)); 
    out.set_data(out_data);
    return out;
}

FLQuant_base<double> operator / (const double& lhs, const FLQuant_base<double>& rhs){
    FLQuant_base<double> out = rhs;
    std::vector<double> out_data = out.get_data();
    std::transform(out_data.begin(), out_data.end(), out_data.begin(), std::bind1st(std::divides<double>(),lhs)); 
    out.set_data(out_data);
    return out;
}

template <typename T>
FLQuant_base<T> operator / (const FLQuant_base<T>& lhs, const double& rhs){
    FLQuant_base<T> out = lhs;
    out /= rhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator / (const FLQuant_base<double>& lhs, const T& rhs){
    FLQuant_base<T> out(lhs);
    out /= rhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator / (const T& lhs, const FLQuant_base<double>& rhs){
    FLQuant_base<T> out(rhs);
    std::vector<T> out_data = out.get_data();
    std::transform(out_data.begin(), out_data.end(), out_data.begin(), std::bind1st(std::divides<T>(),lhs)); 
    out.set_data(out_data);
    return out;
}

//------------------ Subtraction operators -------------------

// Subtraction self assignment
template<typename T>
FLQuant_base<T>& FLQuant_base<T>::operator -= (const FLQuant_base<T>& rhs){
    if (match_dims(rhs) != 1){
        Rcpp::stop("You cannot subtract FLQuants as your dimensions do not match.");
    }
    std::transform((*this).data.begin(), (*this).data.end(), rhs.data.begin(), (*this).data.begin(), std::minus<T>());
    return *this;
}
// Special case of subtraction assignment 
// Instantiation below ensures that it will only compile for FLQuantAdolc -= FLQuant
template <typename T>
template <typename T2>
FLQuant_base<T>& FLQuant_base<T>::operator -= (const FLQuant_base<T2>& rhs){
    if (match_dims(rhs) != 1){
        Rcpp::stop("You cannot subtract FLQuants as your dimensions do not match.");
    }
    std::vector<T2> rhs_data = rhs.get_data();
    std::transform((*this).data.begin(), (*this).data.end(), rhs_data.begin(), (*this).data.begin(), std::minus<T>());
    return *this;
}

// FLQuant -= double
// FLQuantAdolc -= adouble
template <typename T>
FLQuant_base<T>& FLQuant_base<T>::operator -= (const T& rhs){
    std::transform((*this).data.begin(), (*this).data.end(), (*this).data.begin(), std::bind2nd(std::minus<T>(),rhs)); 
    return *this;
}

// Special case of division assignment 
// Used for FLQuantAdolc -= double
// Needs to be instanitated due to extra template class, T2
template <typename T>
template <typename T2>
FLQuant_base<T>& FLQuant_base<T>::operator -= (const T2& rhs){
    std::transform((*this).data.begin(), (*this).data.end(), (*this).data.begin(), std::bind2nd(std::minus<T>(),rhs)); 
    return *this;
}

// General division 
// FLQuant_base<T> - FLQuant_base<T>
template <typename T>
FLQuant_base<T> FLQuant_base<T>::operator - (const FLQuant_base<T>& rhs) const{
    FLQuant_base<T> out = *this; // Copy myself
    out -= rhs;
    return out;
}

// FLQuant_base<T> - T
template <typename T>
FLQuant_base<T> FLQuant_base<T>::operator - (const T& rhs) const{
    FLQuant_base<T> out = *this; // Copy myself
    out -= rhs;
    return out;
}

// Declared outside of class
template <typename T>
FLQuant_base<T> operator - (const FLQuant_base<double>& lhs, const FLQuant_base<T>& rhs){
    FLQuant_base<T> out(lhs);
    out -= rhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator - (const FLQuant_base<T>& lhs, const FLQuant_base<double>& rhs){
    FLQuant_base<T> out = lhs;
    out -= rhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator - (const T& lhs, const FLQuant_base<T>& rhs){
    FLQuant_base<T> out = rhs;
    std::vector<T> out_data = out.get_data();
    std::transform(out_data.begin(), out_data.end(), out_data.begin(), std::bind1st(std::minus<T>(),lhs)); 
    out.set_data(out_data);
    return out;
}

template <typename T>
FLQuant_base<T> operator - (const double& lhs, const FLQuant_base<T>& rhs){
    FLQuant_base<T> out = rhs;
    std::vector<T> out_data = out.get_data();
    std::transform(out_data.begin(), out_data.end(), out_data.begin(), std::bind1st(std::minus<T>(),lhs)); 
    out.set_data(out_data);
    return out;
}

FLQuant_base<double> operator - (const double& lhs, const FLQuant_base<double>& rhs){
    FLQuant_base<double> out = rhs;
    std::vector<double> out_data = out.get_data();
    std::transform(out_data.begin(), out_data.end(), out_data.begin(), std::bind1st(std::minus<double>(),lhs)); 
    out.set_data(out_data);
    return out;
}

template <typename T>
FLQuant_base<T> operator - (const FLQuant_base<T>& lhs, const double& rhs){
    FLQuant_base<T> out = lhs;
    out -= rhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator - (const FLQuant_base<double>& lhs, const T& rhs){
    FLQuant_base<T> out(lhs);
    out -= rhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator - (const T& lhs, const FLQuant_base<double>& rhs){
    FLQuant_base<T> out(rhs);
    std::vector<T> out_data = out.get_data();
    std::transform(out_data.begin(), out_data.end(), out_data.begin(), std::bind1st(std::minus<T>(),lhs)); 
    out.set_data(out_data);
    return out;
}

//------------------ Addition operators -------------------

// Addition self assignment
template<typename T>
FLQuant_base<T>& FLQuant_base<T>::operator += (const FLQuant_base<T>& rhs){
    if (match_dims(rhs) != 1){
        Rcpp::stop("You cannot add FLQuants as your dimensions do not match.");
    }
    std::transform((*this).data.begin(), (*this).data.end(), rhs.data.begin(), (*this).data.begin(), std::plus<T>());
    return *this;
}
// Special case of addition assignment 
// Instantiation below ensures that it will only compile for FLQuantAdolc += FLQuant
// FLQuant += FLQuantAdolc will not compile as cannot have double = double + adouble
// Needs to be instanitated due to extra template class, T2
template <typename T>
template <typename T2>
FLQuant_base<T>& FLQuant_base<T>::operator += (const FLQuant_base<T2>& rhs){
    if (match_dims(rhs) != 1){
        Rcpp::stop("You cannot add FLQuants as your dimensions do not match.");
    }
    std::vector<T2> rhs_data = rhs.get_data();
    std::transform((*this).data.begin(), (*this).data.end(), rhs_data.begin(), (*this).data.begin(), std::plus<T>());
    return *this;
}

// FLQuant += double
// FLQuantAdolc += adouble
template <typename T>
FLQuant_base<T>& FLQuant_base<T>::operator += (const T& rhs){
    std::transform((*this).data.begin(), (*this).data.end(), (*this).data.begin(), std::bind1st(std::plus<T>(),rhs)); 
    return *this;
}

// Special case of addition assignment 
// Used for FLQuantAdolc += double
// Needs to be instanitated due to extra template class, T2
template <typename T>
template <typename T2>
FLQuant_base<T>& FLQuant_base<T>::operator += (const T2& rhs){
    std::transform((*this).data.begin(), (*this).data.end(), (*this).data.begin(), std::bind1st(std::plus<T>(),rhs)); 
    return *this;
}

// General multiplication
// FLQuant_base<T> + FLQuant_base<T>
template <typename T>
FLQuant_base<T> FLQuant_base<T>::operator + (const FLQuant_base<T>& rhs) const{
    FLQuant_base<T> out = *this; // Copy myself
    out += rhs;
    return out;
}

// FLQuant_base<T> + T
template <typename T>
FLQuant_base<T> FLQuant_base<T>::operator + (const T& rhs) const{
    FLQuant_base<T> out = *this; // Copy myself
    out += rhs;
    return out;
}

// Declared outside of class
template <typename T>
FLQuant_base<T> operator + (const FLQuant_base<double>& lhs, const FLQuant_base<T>& rhs){
    FLQuant_base<T> out = rhs;
    out += lhs;
    return out;

}

template <typename T>
FLQuant_base<T> operator + (const FLQuant_base<T>& lhs, const FLQuant_base<double>& rhs){
    FLQuant_base<T> out = lhs;
    out += rhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator + (const T& lhs, const FLQuant_base<T>& rhs){
    FLQuant_base<T> out = rhs;
    out += lhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator + (const double& lhs, const FLQuant_base<T>& rhs){
    FLQuant_base<T> out = rhs;
    out += lhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator + (const FLQuant_base<T>& lhs, const double& rhs){
    FLQuant_base<T> out = lhs;
    out += rhs;
    return out;
}

FLQuant_base<double> operator + (const double& lhs, const FLQuant_base<double>& rhs){
    FLQuant_base<double> out = rhs;
    out += lhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator + (const FLQuant_base<double>& lhs, const T& rhs){
    FLQuant_base<T> out(lhs);
    out += rhs;
    return out;
}

template <typename T>
FLQuant_base<T> operator + (const T& lhs, const FLQuant_base<double>& rhs){
    FLQuant_base<T> out(rhs);
    out += lhs;
    return out;
}

/* Accessor methods */
/*
void FLQuant::set_units(const std::string new_units){
	units = new_units;
}

*/
/*  A strange method this one. You can only set different dims
  if the data member doesn't have dimnames that match the different dims.
  But the data member will already dim and dimnames attributes that match,
  so you cannot change one on it's own.
  This method is therefore only really used if the data member has no existing attributes.
  This can happen, for example, if a sugar method is used which removes all attributes */
/*
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
*/
// This does not check that the dimnames are xxx, year, unit etc.
/*
void FLQuant::set_dimnames(const Rcpp::List dimnames){
    if (dimnames.size() != 6){
        Rcpp::stop("Dimnames must be of length 6");
    }
    data.attr("dimnames") = dimnames;
}
*/
/*
*/
/* Define template specialisations for as and wrap */
/*
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
*/
/* Mathematical operators */
// Was going to use Rcpp sugar to multiply the data NumericVectors together
// But this has the side effect of stripping out the dim and dimnames attributes
// We could still use it and then set_dim and set_dimnames but that seems a bit long winded
/*
FLQuant& FLQuant::operator *= (const FLQuant& flq_rhs){
    if (match_dims(flq_rhs) != 1){
        Rcpp::stop("You cannot multiply FLQuants as your dimensions do not match.");
    }
    for (int i = 1; i <= data.size(); ++i){
        (*this)(i) = (*this)(i) * flq_rhs(i); // Use the () operator instead of accessing data member directly so indexing starts at same place
    }
    return *this;
}

FLQuant FLQuant::operator * (const FLQuant& flq_rhs) const{
    FLQuant flq_out = *this; // Copy myself
    flq_out *= flq_rhs;
    return flq_out;
}

FLQuant& FLQuant::operator *= (const double& rhs){
    for (int i = 1; i <= data.size(); ++i){
        (*this)(i) = (*this)(i) * rhs; 
    }
    return *this;
}

FLQuant FLQuant::operator * (const double& rhs) const{
    FLQuant flq_out = *this; // Copy myself
    flq_out *= rhs;
    return flq_out;
}

FLQuant& FLQuant::operator /= (const FLQuant& flq_rhs){
    if (match_dims(flq_rhs) != 1){
        Rcpp::stop("You cannot divide FLQuants as your dimensions do not match.");
    }
    for (int i = 1; i <= data.size(); ++i){
        (*this)(i) = (*this)(i) / flq_rhs(i); // Use the () operator instead of accessing data member directly so indexing starts at same place
    }
    return *this;
}

FLQuant FLQuant::operator / (const FLQuant& flq_rhs) const{
    FLQuant flq_out = *this; // Copy myself
    flq_out /= flq_rhs;
    return flq_out;
}

FLQuant& FLQuant::operator /= (const double& rhs){
    for (int i = 1; i <= data.size(); ++i){
        (*this)(i) = (*this)(i) / rhs; 
    }
    return *this;
}

FLQuant FLQuant::operator / (const double& rhs) const{
    FLQuant flq_out = *this; // Copy myself
    flq_out /= rhs;
    return flq_out;
}

FLQuant& FLQuant::operator += (const FLQuant& flq_rhs){
    if (match_dims(flq_rhs) != 1){
        Rcpp::stop("You cannot add FLQuants as your dimensions do not match.");
    }
    for (int i = 1; i <= data.size(); ++i){
        (*this)(i) = (*this)(i) + flq_rhs(i); // Use the () operator instead of accessing data member directly so indexing starts at same place
    }
    return *this;
}

FLQuant FLQuant::operator + (const FLQuant& flq_rhs) const{
    FLQuant flq_out = *this; // Copy myself
    flq_out += flq_rhs;
    return flq_out;
}

FLQuant& FLQuant::operator += (const double& rhs){
    for (int i = 1; i <= data.size(); ++i){
        (*this)(i) = (*this)(i) + rhs; 
    }
    return *this;
}

FLQuant FLQuant::operator + (const double& rhs) const{
    FLQuant flq_out = *this; // Copy myself
    flq_out += rhs;
    return flq_out;
}

FLQuant& FLQuant::operator -= (const FLQuant& flq_rhs){
    if (match_dims(flq_rhs) != 1){
        Rcpp::stop("You cannot subtract FLQuants as your dimensions do not match.");
    }
    for (int i = 1; i <= data.size(); ++i){
        (*this)(i) = (*this)(i) - flq_rhs(i); // Use the () operator instead of accessing data member directly so indexing starts at same place
    }
    return *this;
}

FLQuant FLQuant::operator - (const FLQuant& flq_rhs) const{
    FLQuant flq_out = *this; // Copy myself
    flq_out -= flq_rhs;
    return flq_out;
}

FLQuant& FLQuant::operator -= (const double& rhs){
    for (int i = 1; i <= data.size(); ++i){
        (*this)(i) = (*this)(i) - rhs; 
    }
    return *this;
}

FLQuant FLQuant::operator - (const double& rhs) const{
    FLQuant flq_out = *this; // Copy myself
    flq_out -= rhs;
    return flq_out;
}
*/
/* Do the dimensions of two FLQuants match?
    If yes, return 1
    Else, return the negative of the first dimension that is wrong
*/

template <typename T>
int FLQuant_base<T>::match_dims(const FLQuant_base<T>& b) const{
    Rcpp::IntegerVector dims_a =  get_dim();
    Rcpp::IntegerVector dims_b =  b.get_dim();
    return dim_matcher(dims_a, dims_b);
}

template <typename T>
template <typename T2>
int FLQuant_base<T>::match_dims(const FLQuant_base<T2>& b) const{
    Rcpp::IntegerVector dims_a =  get_dim();
    Rcpp::IntegerVector dims_b =  b.get_dim();
    return dim_matcher(dims_a, dims_b);
}



/* Other functions */
/*
FLQuant log(const FLQuant& flq){
    FLQuant out = flq;
    for (int i = 1; i <= flq.get_size(); ++i){
        out(i) = log(out(i));
    }
    return out;
}

FLQuant exp(const FLQuant& flq){
    FLQuant out = flq;
    for (int i = 1; i <= flq.get_size(); ++i){
        out(i) = exp(out(i));
    }
    return out;
}
*/

/*
template <typename T1, typename T2>
std::vector<T1> operator * (const std::vector<T1>& lhs, const std::vector<T2>& rhs){
    Rprintf("T1 = T1 * T2\n");    
    std::vector<T1> out;
    return out;
}

std::vector<adouble> operator * (const std::vector<double>& lhs, const std::vector<adouble>& rhs){
    Rprintf("adouble = double * adouble\n");    
    std::vector<adouble> out;
    return out;
}
*/

int dim_matcher(const Rcpp::IntegerVector dims_a, const Rcpp::IntegerVector dims_b){
    for (int i=0; i<6; ++i){
        if (dims_a(i) != dims_b(i)){
            return -1 * (i+1); // Return negative of what dim does not match
        }
    }
    return 1; // Else all is good
}

/* Explicit instantiations - alternatively put all the definitions into the header file
 * This way we have more control over what types the functions work with
 */
// Explicit instantiation of class
template class FLQuant_base<double>;
template class FLQuant_base<adouble>;

// Instantiate arithmetic class methods with mixed types 
template FLQuant_base<adouble>& FLQuant_base<adouble>::operator *= (const FLQuant_base<double>& rhs);
template FLQuant_base<adouble>& FLQuant_base<adouble>::operator *= (const double& rhs);
template FLQuant_base<adouble>& FLQuant_base<adouble>::operator /= (const FLQuant_base<double>& rhs);
template FLQuant_base<adouble>& FLQuant_base<adouble>::operator /= (const double& rhs);
template FLQuant_base<adouble>& FLQuant_base<adouble>::operator -= (const FLQuant_base<double>& rhs);
template FLQuant_base<adouble>& FLQuant_base<adouble>::operator -= (const double& rhs);
template FLQuant_base<adouble>& FLQuant_base<adouble>::operator += (const FLQuant_base<double>& rhs);
template FLQuant_base<adouble>& FLQuant_base<adouble>::operator += (const double& rhs);
// Instantiate other class methods with mixed types 
template int FLQuant_base<adouble>::match_dims(const FLQuant_base<double>& b) const;
template int FLQuant_base<double>::match_dims(const FLQuant_base<adouble>& b) const;


// Explicit instantiation of extra artithmetic functions
// Multiplication
template FLQuant_base<adouble> operator * (const FLQuant_base<double>& lhs, const FLQuant_base<adouble>& rhs);
template FLQuant_base<adouble> operator * (const FLQuant_base<adouble>& lhs, const FLQuant_base<double>& rhs);
template FLQuant_base<adouble> operator * (const adouble& lhs, const FLQuant_base<adouble>& rhs);
template FLQuant_base<adouble> operator * (const double& lhs, const FLQuant_base<adouble>& rhs);
template FLQuant_base<adouble> operator * (const FLQuant_base<adouble>& lhs, const double& rhs);
template FLQuant_base<adouble> operator * (const FLQuant_base<double>& lhs, const adouble& rhs);
template FLQuant_base<adouble> operator * (const adouble& lhs, const FLQuant_base<double>& rhs);
// Division
template FLQuant_base<adouble> operator / (const FLQuant_base<double>& lhs, const FLQuant_base<adouble>& rhs);
template FLQuant_base<adouble> operator / (const FLQuant_base<adouble>& lhs, const FLQuant_base<double>& rhs);
template FLQuant_base<adouble> operator / (const adouble& lhs, const FLQuant_base<adouble>& rhs);
template FLQuant_base<adouble> operator / (const double& lhs, const FLQuant_base<adouble>& rhs);
template FLQuant_base<adouble> operator / (const FLQuant_base<adouble>& lhs, const double& rhs);
template FLQuant_base<adouble> operator / (const FLQuant_base<double>& lhs, const adouble& rhs);
template FLQuant_base<adouble> operator / (const adouble& lhs, const FLQuant_base<double>& rhs);
// Subtraction
template FLQuant_base<adouble> operator - (const FLQuant_base<double>& lhs, const FLQuant_base<adouble>& rhs);
template FLQuant_base<adouble> operator - (const FLQuant_base<adouble>& lhs, const FLQuant_base<double>& rhs);
template FLQuant_base<adouble> operator - (const adouble& lhs, const FLQuant_base<adouble>& rhs);
template FLQuant_base<adouble> operator - (const double& lhs, const FLQuant_base<adouble>& rhs);
template FLQuant_base<adouble> operator - (const FLQuant_base<adouble>& lhs, const double& rhs);
template FLQuant_base<adouble> operator - (const FLQuant_base<double>& lhs, const adouble& rhs);
template FLQuant_base<adouble> operator - (const adouble& lhs, const FLQuant_base<double>& rhs);
// Addition
template FLQuant_base<adouble> operator + (const FLQuant_base<double>& lhs, const FLQuant_base<adouble>& rhs);
template FLQuant_base<adouble> operator + (const FLQuant_base<adouble>& lhs, const FLQuant_base<double>& rhs);
template FLQuant_base<adouble> operator + (const adouble& lhs, const FLQuant_base<adouble>& rhs);
template FLQuant_base<adouble> operator + (const double& lhs, const FLQuant_base<adouble>& rhs);
template FLQuant_base<adouble> operator + (const FLQuant_base<adouble>& lhs, const double& rhs);
template FLQuant_base<adouble> operator + (const FLQuant_base<double>& lhs, const adouble& rhs);
template FLQuant_base<adouble> operator + (const adouble& lhs, const FLQuant_base<double>& rhs);


