// Change the name of this

/* 
 * Copyright 2013 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../../inst/include/control.h"

//Rcpp::IntegerVector v =
//Rcpp::IntegerVector::create(7,8,9);
//std::vector<std::string> s(3);
//s[0] = "x";
//s[1] = "y";
//s[2] = "z";
//return Rcpp::DataFrame::create(Rcpp::Named("a")=v,
//Rcpp::Named("b")=s);


//Rcpp::NumericVector vec3 = Rcpp::NumericVector( Rcpp::Dimension(4, 5, 6));

// Empty constructor
fwdControl::fwdControl(){
    target = Rcpp::DataFrame();
    target_iters = Rcpp::NumericVector();
}

// Constructor used as intrinsic 'as'
fwdControl::fwdControl(SEXP fwd_control_sexp){
    Rprintf("In fwdControl as\n");
	Rcpp::S4 fwd_control_s4 = Rcpp::as<Rcpp::S4>(fwd_control_sexp);
    target_iters = fwd_control_s4.slot("target_iters");
    target = fwd_control_s4.slot("target");
}

// intrinsic 'wrap' 
fwdControl::operator SEXP() const{
    Rprintf("In fwdControl wrap\n");
    Rcpp::S4 fwd_control_s4("fwdControl");
    fwd_control_s4.slot("target") = target;
    fwd_control_s4.slot("target_iters") = target_iters;
    return Rcpp::wrap(fwd_control_s4);
}

// Copy constructor - else 'data' can be pointed at by multiple instances
fwdControl::fwdControl(const fwdControl& fwdControl_source){
    target = Rcpp::clone<Rcpp::DataFrame>(fwdControl_source.target); // Need to clone for a deep copy
    target_iters = Rcpp::clone<Rcpp::NumericVector>(fwdControl_source.target_iters); // Need to clone 
}

// Assignment operator to ensure deep copy - else 'data' can be pointed at by multiple instances
fwdControl& fwdControl::operator = (const fwdControl& fwdControl_source){
	if (this != &fwdControl_source){
        target = Rcpp::clone<Rcpp::DataFrame>(fwdControl_source.target); // Need to clone for a deep copy
        target_iters = Rcpp::clone<Rcpp::NumericVector>(fwdControl_source.target_iters); // Need to clone 
	}
	return *this;
}

Rcpp::DataFrame fwdControl::get_target() const{
    Rprintf("In fwdControl get_target\n");
    return target;
}

// Returns the number of targets in the control object
int fwdControl::get_ntarget() const{
     return target.nrows();
}

// Returns the number of iterations in the target_iters member object
int fwdControl::get_niter() const{
    Rcpp::IntegerVector dim = target_iters.attr("dim");
     return dim[2];
}

// Returns the year and season of the target - used to calculate the timestep in the projection loop
int fwdControl::get_target_year(const int target_no) const {
    Rcpp::IntegerVector year = target["year"];
    return year[target_no-1];
}

int fwdControl::get_target_season(const int target_no) const {
    Rcpp::IntegerVector year = target["season"];
    return year[target_no-1];
}


// It's a 3D array and we want the 2nd column of the 2nd dimension
// Indexing starts at 1
double fwdControl::get_target_value(const int target_no, const int col, const int iter) const{
    Rcpp::IntegerVector dim = target_iters.attr("dim");
    unsigned int element = (dim[1] * dim[0] * (iter - 1)) + (dim[0] * (col - 1)) + (target_no - 1); 
    return target_iters(element);
}

/*------------------------------------------------------------------*/

/* Just some tests to operate on data.frames */
// [[Rcpp::export]]
Rcpp::IntegerVector get_dataframe_year(Rcpp::DataFrame ctrl){
    Rcpp::IntegerVector year = ctrl["year"];
    return year;
}

// [[Rcpp::export]]
Rcpp::NumericVector get_dataframe_value(Rcpp::DataFrame ctrl){
    Rcpp::NumericVector value = ctrl["value"];
    return value;
}

// [[Rcpp::export]]
Rcpp::CharacterVector get_dataframe_quantity(Rcpp::DataFrame ctrl){
    Rcpp::CharacterVector quantity = ctrl["quantity"];
    return quantity;
}
