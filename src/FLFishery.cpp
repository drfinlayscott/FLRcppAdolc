/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../inst/include/FLFishery.h"

/*-------------------------------------------------*/
// Templated class

// Default constructor
// Just an empty object
template <typename T>
FLFishery_base<T>::FLFishery_base(){
    //Rprintf("In FLFishery empty constructor\n");
    name = std::string();
    effort_flq = FLQuant();
    vcost_flq = FLQuant();
    fcost_flq = FLQuant();
}

// Constructor from a SEXP S4 FLFishery
// Used as intrusive 'as'
template <typename T>
FLFishery_base<T>::FLFishery_base(SEXP flf_sexp) : FLCatches_base<T>(flf_sexp){ // Force the FLCatches SEXP constructor to be called first
    //Rprintf("In FLFishery SEXP constructor\n");
    Rcpp::S4 flf_s4 = Rcpp::as<Rcpp::S4>(flf_sexp);
    name = Rcpp::as<std::string>(flf_s4.slot("name"));
    effort_flq = flf_s4.slot("effort");
    vcost_flq = flf_s4.slot("vcost");
    fcost_flq = flf_s4.slot("fcost");
    range = flf_s4.slot("range");
}

/* Intrusive 'wrap' */
// Note that we have to use this manky FLCatches_base<T>::member_of_FLCatches syntax with templated inheritance
// Returns an FLFishery
template <typename T>
FLFishery_base<T>::operator SEXP() const{
    //Rprintf("Wrapping FLFishery_base<T>.\n");
    Rcpp::S4 flf_s4("FLFishery");
    flf_s4.slot("name") = name;
    flf_s4.slot("effort") = effort_flq;
    flf_s4.slot("vcost") = vcost_flq;
    flf_s4.slot("fcost") = fcost_flq;
    flf_s4.slot("range") = range;
    // FLCatches bits - can't call wrap on these bits
    Rcpp::List list_out;
    for (unsigned int i = 0; i < FLCatches_base<T>::get_ncatches(); i++){
        list_out.push_back(FLCatches_base<T>::catches[i]);
    }
    flf_s4.slot(".Data") = list_out;
    flf_s4.slot("desc") = FLCatches_base<T>::desc;
    flf_s4.slot("names") = FLCatches_base<T>::names;
    return Rcpp::wrap(flf_s4);
}

// Copy constructor - else members can be pointed at by multiple instances
template <typename T>
FLFishery_base<T>::FLFishery_base(const FLFishery_base<T>& FLFishery_source) : FLCatches_base<T>(FLFishery_source){
    //Rprintf("In FLFishery_base copy constructor\n");
    name = FLFishery_source.name;
    effort_flq = FLFishery_source.effort_flq;
    vcost_flq = FLFishery_source.vcost_flq;
    fcost_flq = FLFishery_source.fcost_flq;
    range = Rcpp::clone<Rcpp::NumericVector>(FLFishery_source.range);
}

// Assignment operator to ensure deep copy - else 'data' can be pointed at by multiple instances
template <typename T>
FLFishery_base<T>& FLFishery_base<T>::operator = (const FLFishery_base<T>& FLFishery_source){
    //Rprintf("In FLFishery_base assignment operator\n");
	if (this != &FLFishery_source){
        // Need to add all the bits from a FLCatches too
        FLCatches_base<T>::operator=(FLFishery_source);
        name = FLFishery_source.name;
        effort_flq = FLFishery_source.effort_flq;
        vcost_flq = FLFishery_source.vcost_flq;
        fcost_flq = FLFishery_source.fcost_flq;
        range = Rcpp::clone<Rcpp::NumericVector>(FLFishery_source.range);
	}
	return *this;
}

// Accessors of economic slots
template <typename T>
FLQuant FLFishery_base<T>::effort() const {
    return effort_flq;
}

template <typename T>
FLQuant FLFishery_base<T>::vcost() const {
    return vcost_flq;
}

template <typename T>
FLQuant FLFishery_base<T>::fcost() const {
    return fcost_flq;
}

template <typename T>
FLQuant& FLFishery_base<T>::effort() {
    return effort_flq;
}

template <typename T>
FLQuant& FLFishery_base<T>::vcost() {
    return vcost_flq;
}

template <typename T>
FLQuant& FLFishery_base<T>::fcost() {
    return fcost_flq;
}

// Explicit instantiation of classes
template class FLFishery_base<double>;
template class FLFishery_base<adouble>;

