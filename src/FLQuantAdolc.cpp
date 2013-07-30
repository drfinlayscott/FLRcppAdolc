#include "../inst/include/FLQuantAdolc.h"

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

