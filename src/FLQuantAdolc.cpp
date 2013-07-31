/* 
 * Copyright 2013 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

//#include "../inst/include/FLQuantAdolc.h"
/*
// Basic constructor
FLQuantAdolc::FLQuantAdolc() {
    Rprintf("In FLQuantAdolc basic constructor\n");
	units = std::string(); // Empty string - just ""
    dim = Rcpp::IntegerVector();
    dimnames = Rcpp::List();
    new_int = 666;
}

// Generic SEXP constructor
// Used as intrusive 'as'
// Need to add check that the SEXP is an FLQuant
FLQuantAdolc::FLQuantAdolc(SEXP flq_sexp){
    Rprintf("In FLQuant_base SEXP constructor\n");
	Rcpp::S4 flq_s4 = Rcpp::as<Rcpp::S4>(flq_sexp);
    Rcpp::NumericVector data_nv = flq_s4.slot(".Data");
    // Initialise data to the correct size?
    // Fill up data
    data.insert(data.begin(), data_nv.begin(), data_nv.end());
	units = Rcpp::as<std::string>(flq_s4.slot("units"));
	dim = data_nv.attr("dim");
	dimnames = data_nv.attr("dimnames");
    new_int = 666;
}

FLQuantAdolc::operator SEXP() const{
    Rprintf("Wrapping FLQuantAdolc\n");
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


void FLQuantAdolc::what_am_i(){
    Rprintf("I am an FLQuantAdolc\n");
    return;
}
*/

// Or.. implementing a templated AD class
/*
// Basic constructor
template<typename T>
FLQuantAD_base<T>::FLQuantAD_base() {
    Rprintf("In FLQuantAD_base basic constructor\n");
	this->units = std::string(); // Empty string - just ""
    this->dim = Rcpp::IntegerVector();
    this->dimnames = Rcpp::List();
    new_int = 666;
}

// Generic SEXP constructor
// Used as intrusive 'as'
// Need to add check that the SEXP is an FLQuant
template<typename T>
FLQuantAD_base<T>::FLQuantAD_base(SEXP flq_sexp){
    Rprintf("In FLQuant_base SEXP constructor\n");
	Rcpp::S4 flq_s4 = Rcpp::as<Rcpp::S4>(flq_sexp);
    Rcpp::NumericVector data_nv = flq_s4.slot(".Data");
    // Initialise data to the correct size?
    // Fill up data
    this->data.insert(this->data.begin(), data_nv.begin(), data_nv.end());
	this->units = Rcpp::as<std::string>(flq_s4.slot("units"));
	this->dim = data_nv.attr("dim");
	this->dimnames = data_nv.attr("dimnames");
    new_int = 666;
}

// This should be specialised for ADOLC
template<typename T>
FLQuantAD_base<T>::operator SEXP() const{
    Rprintf("Wrapping FLQuantAD_base\n");
    Rcpp::S4 flq_s4("FLQuant");
    // Make and fill the NumericVector that will be the 'data' slot 
    Rcpp::NumericVector data_nv;
    for (vector<adouble>::const_iterator data_iterator = this->data.begin(); data_iterator != this->data.end(); ++data_iterator){ // iterator must be const because the method is const
        data_nv.push_back((*data_iterator).value());
    }
    // Apply dims and dimnames
	data_nv.attr("dim") = this->dim;
	data_nv.attr("dimnames") = this->dimnames;
    // Fill the slots
    flq_s4.slot(".Data") = data_nv;
    flq_s4.slot("units") = this->units;
    return Rcpp::wrap(flq_s4);
}

template<typename T>
void FLQuantAD_base<T>::what_am_i(){
    Rprintf("I am an FLQuantAD_base<T>\n");
    return;
}

//instantiate
//template class FLQuant_base<adouble>; // Necessary so that dummy_adouble can use the dummy_base<adouble> bits
template class FLQuantAD_base<adouble>; // Necessary so that dummy_adouble can use the dummy_base<adouble> bits
*/
