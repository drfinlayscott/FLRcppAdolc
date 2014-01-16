/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../inst/include/FLCatch.h"

/*-------------------------------------------------*/
// Templated class

// Default constructor
// Just an empty object
template <typename T>
FLCatch_base<T>::FLCatch_base(){
    name = std::string();
    desc = std::string(); 
    range = Rcpp::NumericVector();
    landings_n_flq = FLQuant_base<T>();
    discards_n_flq = FLQuant_base<T>();
    landings_wt_flq = FLQuant();
    discards_wt_flq = FLQuant();
    catch_sel_flq = FLQuant();
    price_flq = FLQuant();
    //catch_q_flq = FLQuant();
}

// Constructor from a SEXP S4 FLBiol
// But this does not set the SRR!
// Need another constructor for that
// Used as intrusive 'as'
template <typename T>
FLCatch_base<T>::FLCatch_base(SEXP flc_sexp){
    Rcpp::S4 flc_s4 = Rcpp::as<Rcpp::S4>(flc_sexp);
    name = Rcpp::as<std::string>(flc_s4.slot("name"));
    desc = Rcpp::as<std::string>(flc_s4.slot("desc"));
    range = flc_s4.slot("range");
    landings_n_flq = flc_s4.slot("landings.n");
    discards_n_flq = flc_s4.slot("discards.n");
    landings_wt_flq = flc_s4.slot("landings.wt");
    discards_wt_flq = flc_s4.slot("discards.wt");
    catch_sel_flq = flc_s4.slot("catch.sel");
    price_flq = flc_s4.slot("price");
    //catch_q_flq = flc_s4.slot("catch.q");
}

// Copy constructor - else members can be pointed at by multiple instances
template <typename T>
FLCatch_base<T>::FLCatch_base(const FLCatch_base<T>& FLCatch_source){
    name = FLCatch_source.name;
    desc = FLCatch_source.desc;
    range = Rcpp::clone<Rcpp::NumericVector>(FLCatch_source.range);
    landings_n_flq = FLCatch_source.landings_n_flq;
    discards_n_flq = FLCatch_source.discards_n_flq;
    landings_wt_flq = FLCatch_source.landings_wt_flq;
    discards_wt_flq = FLCatch_source.discards_wt_flq;
    catch_sel_flq = FLCatch_source.catch_sel_flq;
    price_flq = FLCatch_source.price_flq;
    //catch_q_flq = FLCatch_source.catch_q_flq;
}

// Assignment operator to ensure deep copy - else 'data' can be pointed at by multiple instances
template <typename T>
FLCatch_base<T>& FLCatch_base<T>::operator = (const FLCatch_base<T>& FLCatch_source){
	if (this != &FLCatch_source){
        name = FLCatch_source.name;
        desc = FLCatch_source.desc;
        range = Rcpp::clone<Rcpp::NumericVector>(FLCatch_source.range);
        landings_n_flq = FLCatch_source.landings_n_flq;
        discards_n_flq = FLCatch_source.discards_n_flq;
        landings_wt_flq = FLCatch_source.landings_wt_flq;
        discards_wt_flq = FLCatch_source.discards_wt_flq;
        catch_sel_flq = FLCatch_source.catch_sel_flq;
        price_flq = FLCatch_source.price_flq;
        //catch_q_flq = FLCatch_source.catch_q_flq;
	}
	return *this;
}

/* Intrusive 'wrap' */
// Returns an FLBiol and ignores the SRR
template <typename T>
FLCatch_base<T>::operator SEXP() const{
    //Rprintf("Wrapping FLCatch_base<T>.\n");
    Rcpp::S4 flc_s4("FLCatch");
    flc_s4.slot("name") = name;
    flc_s4.slot("desc") = desc;
    flc_s4.slot("range") = range;
    flc_s4.slot("landings.n") = landings_n_flq;
    flc_s4.slot("discards.n") = discards_n_flq;
    flc_s4.slot("landings.wt") = landings_wt_flq;
    flc_s4.slot("discards.wt") = discards_wt_flq;
    flc_s4.slot("catch.sel") = catch_sel_flq;
    flc_s4.slot("price") = price_flq;
    //flc_s4.slot("catch.q") = catch_q_flq;
    return Rcpp::wrap(flc_s4);
}

// Accessors
// Get only
template <typename T>
FLQuant_base<T> FLCatch_base<T>::landings_n() const {
    return landings_n_flq;
}

template <typename T>
FLQuant_base<T> FLCatch_base<T>::discards_n() const {
    return discards_n_flq;
}

template <typename T>
FLQuant FLCatch_base<T>::landings_wt() const {
    return landings_wt_flq;
}

template <typename T>
FLQuant FLCatch_base<T>::discards_wt() const {
    return discards_wt_flq;
}

template <typename T>
FLQuant FLCatch_base<T>::catch_sel() const {
    return catch_sel_flq;
}

template <typename T>
FLQuant FLCatch_base<T>::price() const {
    return price_flq;
}

// Get and Set
template <typename T>
FLQuant_base<T>& FLCatch_base<T>::landings_n() {
    return landings_n_flq;
}

template <typename T>
FLQuant_base<T>& FLCatch_base<T>::discards_n() {
    return discards_n_flq;
}

template <typename T>
FLQuant& FLCatch_base<T>::landings_wt() {
    return landings_wt_flq;
}

template <typename T>
FLQuant& FLCatch_base<T>::discards_wt() {
    return discards_wt_flq;
}

template <typename T>
FLQuant& FLCatch_base<T>::catch_sel() {
    return catch_sel_flq;
}

template <typename T>
FLQuant& FLCatch_base<T>::price() {
    return price_flq;
}
/*
template <typename T>
FLQuant& FLCatch_base<T>::catch_q() {
    return catch_q_flq;
}
*/

// methods

/*
template <typename T>
FLQuant_base<T> FLCatch_base<T>::landings() {
    return landings_n_flq;
}
*/



// Explicit instantiation of class
template class FLCatch_base<double>;
template class FLCatch_base<adouble>;

