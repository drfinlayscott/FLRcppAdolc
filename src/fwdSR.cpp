/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../inst/include/fwdSR.h"

/*-------------------------------------------------*/
// Templated class

template <typename T>
void fwdSR_base<T>::init_model_map(){
    Rprintf("Initialising model map\n");
    // Fill up the map
    //std::string ricker_name("ricker");
    //srr_model_ptr ricker_ptr(&ricker);
    //map_model_name_to_function.insert(make_pair(ricker_name, ricker_ptr));
    //map_model_name_to_function.insert(make_pair("ricker", &ricker)); // fails
//    pair<std::string, srr_model_ptr>("ricker", &ricker); // OK
//    map_model_name_to_function.insert(pair<std::string, srr_model_ptr>("ricker", &ricker));
    //map_model_name_to_function.insert(string_srr_model_pair("ricker", &ricker)); // works

    map_model_name_to_function["ricker"] = &ricker;
    return;

}

// Default constructor
// Just an empty object
template <typename T>
fwdSR_base<T>::fwdSR_base(){
    Rprintf("In empty fwdSR constructor\n");
}

// Main constructor method
// Assumes all dims have been checked in R before calling
template <typename T>
fwdSR_base<T>::fwdSR_base(const std::string model_name, const FLQuant params_ip, const FLQuant residuals_ip, const bool residuals_mult_ip) {
    Rprintf("In main fwdSR constructor\n");
    params = params_ip;
    residuals = residuals_ip;
    residuals_mult = residuals_mult_ip;
    init_model_map();

    // Set the model pointer
    typename model_map_type::const_iterator model_pair_found = map_model_name_to_function.find(model_name);
    if (model_pair_found != map_model_name_to_function.end()){
        model = model_pair_found->second; // pulls out value
    }
    else
        Rcpp::stop("SRR model not found\n");
} 


//// Constructor from a SEXP S4 fwdSR
//// Used as intrusive 'as'
//template <typename T>
//fwdSR_base<T>::fwdSR_base(SEXP flsr_sexp){
//    Rprintf("In single SEXP fwdSR constructor\n");
//    Rprintf("Doesn't do anything at the moment.\n");
//    Rprintf("Need to write FLPar / FLQuant method.\n");
//    Rcpp::S4 flsr_s4 = Rcpp::as<Rcpp::S4>(flsr_sexp);
//
//    // Set the function pointer
//    model = &ricker;
//    // Need to initialise params_flq from an FLPar
//    FLQuant new_params_flq(2,1,1,1,1,1);
//    params_flq = new_params_flq;
//    //params_flq(2,1,1,1,1,1);
//    params_flq(1,1,1,1,1,1) = 9.1626;
//    params_flq(2,1,1,1,1,1) = 3.5459e-6;
//
//}

/* Intrusive 'wrap' */
// Returns a List of stuff - used for tests
template <typename T>
fwdSR_base<T>::operator SEXP() const{
    Rprintf("Wrapping fwdSR_base<T>.\n");
    //Rprintf("Doesn't do anything at the moment.\n");
    return Rcpp::List::create(Rcpp::Named("params", params),
                            Rcpp::Named("residuals",residuals),
                            Rcpp::Named("residuals_mult",residuals_mult));
}


// Copy constructor - else members can be pointed at by multiple instances
template <typename T>
fwdSR_base<T>::fwdSR_base(const fwdSR_base<T>& fwdSR_source){
    model = fwdSR_source.model; // Copy the pointer - we want it point to the same place so copying should be fine.
    params = fwdSR_source.params;
    residuals = fwdSR_source.residuals;
    residuals_mult = residuals_mult;
}

// Assignment operator to ensure deep copy - else 'data' can be pointed at by multiple instances
template <typename T>
fwdSR_base<T>& fwdSR_base<T>::operator = (const fwdSR_base<T>& fwdSR_source){
	if (this != &fwdSR_source){
        model = fwdSR_source.model; // Copy the pointer - we want it point to the same place so copying should be fine.
        params = fwdSR_source.params;
        residuals = fwdSR_source.residuals;
        residuals_mult = residuals_mult;
	}
	return *this;
}


template <typename T>
T fwdSR_base<T>::eval_model(const T ssb, const int year, const int unit, const int season, const int area, const int iter){
    const int nparams = get_nparams();
    std::vector<double> model_params(nparams);
    for (int i = 1; i <= nparams; ++i){
        model_params[i-1] = params(i,year,unit,season,area,iter);
    }
    T rec = model(ssb, model_params);
    return rec;
}

//template <typename T>
//FLQuant_base<T> fwdSR_base<T>::eval_model(const FLQuant_base<T> ssb){
//
//}

// No of params in a time step - the length of the first dimension
template <typename T>
int fwdSR_base<T>::get_nparams(){
    return params.get_nquant();
}

// Explicit instantiation of class
template class fwdSR_base<double>;
template class fwdSR_base<adouble>;

//--------------------------------------------------------------------
// SRR functions
template <typename T>
T ricker(const T ssb, const std::vector<double> params){
    T rec;
    // rec = a * ssb * exp (-b * ssb)
    rec = params[0] * ssb * exp(-params[1] * ssb);
    return rec;
}


// Instantiate functions
template double ricker(const double ssb, const std::vector<double> params);
template adouble ricker(const adouble ssb, const std::vector<double> params);

