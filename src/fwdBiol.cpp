/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../inst/include/fwdBiol.h"

/*-------------------------------------------------*/
// Templated class

// Default constructor
// Just an empty object
template <typename T>
fwdBiol_base<T>::fwdBiol_base(){
    name = std::string();
    desc = std::string(); 
    range = Rcpp::NumericVector();
    n_flq = FLQuant_base<T>();
    wt_flq = FLQuant();
    m_flq = FLQuant();
    spwn_flq = FLQuant();
    fec_flq = FLQuant();
    // SRR
}

// Constructor from a SEXP S4 FLBiol
// But this does not set the SRR!
// Need another constructor for that
// Used as intrusive 'as'
template <typename T>
fwdBiol_base<T>::fwdBiol_base(SEXP flb_sexp){
    Rcpp::S4 fwdb_s4 = Rcpp::as<Rcpp::S4>(flb_sexp);
    name = Rcpp::as<std::string>(fwdb_s4.slot("name"));
    desc = Rcpp::as<std::string>(fwdb_s4.slot("desc"));
    range = fwdb_s4.slot("range");
    n_flq = fwdb_s4.slot("n");
    wt_flq = fwdb_s4.slot("wt");
    m_flq = fwdb_s4.slot("m");
    spwn_flq = fwdb_s4.slot("spwn");
    fec_flq = fwdb_s4.slot("fec");
    // SRR
}

// Copy constructor - else members can be pointed at by multiple instances
template <typename T>
fwdBiol_base<T>::fwdBiol_base(const fwdBiol_base<T>& fwdBiol_source){
    name = fwdBiol_source.name;
    desc = fwdBiol_source.desc;
    range = Rcpp::clone<Rcpp::NumericVector>(fwdBiol_source.range);
    n_flq = fwdBiol_source.n_flq;
    wt_flq = fwdBiol_source.wt_flq;
    m_flq = fwdBiol_source.m_flq;
    spwn_flq = fwdBiol_source.spwn_flq;
    fec_flq = fwdBiol_source.fec_flq;
    // SRR
}

// Assignment operator to ensure deep copy - else 'data' can be pointed at by multiple instances
template <typename T>
fwdBiol_base<T>& fwdBiol_base<T>::operator = (const fwdBiol_base<T>& fwdBiol_source){
	if (this != &fwdBiol_source){
        name = fwdBiol_source.name;
        desc = fwdBiol_source.desc;
        range = Rcpp::clone<Rcpp::NumericVector>(fwdBiol_source.range);
        n_flq = fwdBiol_source.n_flq;
        wt_flq = fwdBiol_source.wt_flq;
        m_flq = fwdBiol_source.m_flq;
        spwn_flq = fwdBiol_source.spwn_flq;
        fec_flq = fwdBiol_source.fec_flq;
        // SRR
	}
	return *this;
}

/* Intrusive 'wrap' */
// Returns an FLBiol and ignores the SRR
template <typename T>
fwdBiol_base<T>::operator SEXP() const{
    //Rprintf("Wrapping fwdBiol_base<T>.\n");
    Rcpp::S4 flb_s4("FLBiol");
    flb_s4.slot("name") = name;
    flb_s4.slot("desc") = desc;
    flb_s4.slot("range") = range;
    flb_s4.slot("n") = n_flq;
    flb_s4.slot("wt") = wt_flq;
    flb_s4.slot("m") = m_flq;
    flb_s4.slot("spwn") = spwn_flq;
    flb_s4.slot("fec") = fec_flq;
    return Rcpp::wrap(flb_s4);
}

// Get const accessors
template <typename T>
FLQuant_base<T> fwdBiol_base<T>::n() const {
    return n_flq;
}

template <typename T>
FLQuant fwdBiol_base<T>::wt() const {
    return wt_flq;
}

template <typename T>
FLQuant fwdBiol_base<T>::m() const {
    return m_flq;
}
template <typename T>
FLQuant fwdBiol_base<T>::spwn() const {
    return spwn_flq;
}
template <typename T>
FLQuant fwdBiol_base<T>::fec() const {
    return fec_flq;
}

// Get and set accessors
template <typename T>
FLQuant_base<T>& fwdBiol_base<T>::n() {
    return n_flq;
}

template <typename T>
FLQuant& fwdBiol_base<T>::wt() {
    return wt_flq;
}

template <typename T>
FLQuant& fwdBiol_base<T>::m() {
    return m_flq;
}
template <typename T>
FLQuant& fwdBiol_base<T>::spwn() {
    return spwn_flq;
}
template <typename T>
FLQuant& fwdBiol_base<T>::fec() {
    return fec_flq;
}




// Explicit instantiation of class
template class fwdBiol_base<double>;
template class fwdBiol_base<adouble>;

/*------------------------------------------------------------*/
// Operating model class

/*
// Empty constructor
operating_model::operating_model(){
    // Empties
    biol = fwdBiol_Adolc();
    // The other members
    // fishery
}

// Make these
// operator SEXP() const; // Used as intrusive 'wrap'
// operating_model(const operating_model& operating_model_source); // copy constructor to ensure that copy is a deep copy - used when passing object into functions
// operating_model& operator = (const operating_model& operating_model_source); // Assignment operator for a deep copy

operating_model::operating_model(fwdBiol_Adolc biol_source){
    biol = biol_source;
}


// Accessors (for testing)
fwdBiol_Adolc operating_model::get_biol(){
    return biol;
}

// Indexing start at 1
void operating_model::timestep_to_year_season(const int timestep, int& year, int& season){
    year =  (timestep-1) / biol.n.get_nseason() + 1;
    season = (timestep-1) % biol.n.get_nseason() + 1;
}

void operating_model::calc_N(const int timestep){
    const int year = 0; 
    const int season = 0;

    //timestep_to_year_season(timestep, const FLQuant_base<T>& flq, year, season);

}
*/
/*-------------------------------------------------*/
// Original, non-templated version
// Default constructor
// Just an empty object
/*
fwdBiol::fwdBiol(){
    name = std::string();
    desc = std::string(); 
    range = Rcpp::NumericVector();
    n = FLQuant();
    wt = FLQuant();
    m = FLQuant();
    spwn = FLQuant();
    fec = FLQuant();
    // SRR
}

// Constructor from a SEXP S4 FLBiol
// But this does not set the SRR!
// Need another constructor for that
// Used as intrusive 'as'
fwdBiol::fwdBiol(SEXP flb_sexp){
    Rcpp::S4 fwdb_s4 = Rcpp::as<Rcpp::S4>(flb_sexp);
    name = Rcpp::as<std::string>(fwdb_s4.slot("name"));
    desc = Rcpp::as<std::string>(fwdb_s4.slot("desc"));
    range = fwdb_s4.slot("range");
    n = fwdb_s4.slot("n");
    wt = fwdb_s4.slot("wt");
    m = fwdb_s4.slot("m");
    spwn = fwdb_s4.slot("spwn");
    fec = fwdb_s4.slot("fec");
    // SRR
}

// Copy constructor - else members can be pointed at by multiple instances
fwdBiol::fwdBiol(const fwdBiol& fwdBiol_source){
    name = fwdBiol_source.name;
    desc = fwdBiol_source.desc;
    range = Rcpp::clone<Rcpp::NumericVector>(fwdBiol_source.range);
    n = fwdBiol_source.n;
    wt = fwdBiol_source.wt;
    m = fwdBiol_source.m;
    spwn = fwdBiol_source.spwn;
    fec = fwdBiol_source.fec;
    // SRR
}

// Assignment operator to ensure deep copy - else 'data' can be pointed at by multiple instances
fwdBiol& fwdBiol::operator = (const fwdBiol& fwdBiol_source){
	if (this != &fwdBiol_source){
        name = fwdBiol_source.name;
        desc = fwdBiol_source.desc;
        range = Rcpp::clone<Rcpp::NumericVector>(fwdBiol_source.range);
        n = fwdBiol_source.n;
        wt = fwdBiol_source.wt;
        m = fwdBiol_source.m;
        spwn = fwdBiol_source.spwn;
        fec = fwdBiol_source.fec;
    // SRR
	}
	return *this;
}

// Intrusive 'wrap' 
// Returns an FLBiol and ignores the SRR
fwdBiol::operator SEXP() const{
    Rprintf("Wrapping fwdBiol.\n");
    Rcpp::S4 flb_s4("FLBiol");
    flb_s4.slot("name") = name;
    flb_s4.slot("desc") = desc;
    flb_s4.slot("range") = range;
    flb_s4.slot("n") = n;
    flb_s4.slot("wt") = wt;
    flb_s4.slot("m") = m;
    flb_s4.slot("spwn") = spwn;
    flb_s4.slot("fec") = fec;
    return Rcpp::wrap(flb_s4);
}
*/
