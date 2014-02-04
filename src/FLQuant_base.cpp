/* 
 * Copyright 2013 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

//// [[ Rcpp::interfaces(r, cpp) ]]

#include "../inst/include/FLQuant_base.h"

// Default constructor
// No dimnames set as the array is null
template <typename T>
FLQuant_base<T>::FLQuant_base(){
    //Rprintf("In FLQuant_base<T> basic constructor\n");
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
    //Rprintf("In FLQuant_base SEXP constructor\n");
	Rcpp::S4 flq_s4 = Rcpp::as<Rcpp::S4>(flq_sexp);
    Rcpp::NumericVector data_nv = flq_s4.slot(".Data");
    // Initialise data to the correct size?
    // Fill up data
    // Add reserve() in here first to make data the correct size?
    // data(nquant * nyear * nunit * nseason * narea * niter)?
    data.insert(data.begin(), data_nv.begin(), data_nv.end());
	units = Rcpp::as<std::string>(flq_s4.slot("units"));
	dim = data_nv.attr("dim");
	dimnames = data_nv.attr("dimnames");
}

// Make an FLQuant of a certain size filled with 0
// Note that units and dimnames have not been set
template <typename T>
FLQuant_base<T>::FLQuant_base(const int nquant, const int nyear, const int nunit, const int nseason, const int narea, const int niter){
    //Rprintf("Making a new FLQuant_base<T> with user defined dims\n");
	units = std::string(); // Empty string - just ""
    dim = Rcpp::IntegerVector::create(nquant, nyear, nunit, nseason, narea, niter);
    data = std::vector<T>(nquant * nyear * nunit * nseason * narea * niter);
    // How to fill dimnames up appropriately?
    // Just of the right size at the moment.
    // Could use ::create to pass in actual characters, but then do we want just 1:nage, 1:nyear etc?
    dimnames = Rcpp::List::create(
            Rcpp::Named("quant", Rcpp::CharacterVector(nquant)),
            Rcpp::Named("year", Rcpp::CharacterVector(nyear)),
            Rcpp::Named("unit", Rcpp::CharacterVector(nunit)),
            Rcpp::Named("season", Rcpp::CharacterVector(nseason)),
            Rcpp::Named("area", Rcpp::CharacterVector(narea)),
            Rcpp::Named("iter", Rcpp::CharacterVector(niter)));
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
    //Rprintf("Specialised wrapping FLQuant_base<double>\n");
    Rcpp::S4 flq_s4("FLQuant");
    // Make and fill the NumericVector that will be the 'data' slot 
    Rcpp::NumericVector data_nv;
    // reserve() space?
    // Rcpp::NumericVector data_nv(number of elements);nquant * nyear * nunit * nseason * narea * niter
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
    //Rprintf("Specialised wrapping FLQuant_base<adouble>\n");
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
    //Rprintf("In FLQuant_base<T> copy constructor\n");
	data  = FLQuant_source.data; // std::vector always does deep copy
	units = FLQuant_source.units; // std::string always does deep copy
    dim = Rcpp::clone<Rcpp::IntegerVector>(FLQuant_source.dim);
    dimnames = Rcpp::clone<Rcpp::List>(FLQuant_source.dimnames);
}

// Assignment operator to ensure deep copy - else 'data' can be pointed at by multiple instances
template<typename T>
FLQuant_base<T>& FLQuant_base<T>::operator = (const FLQuant_base<T>& FLQuant_source){
    //Rprintf("In FLQuant_base<T> assignment operator\n");
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
    //Rprintf("In constructor for FLQuant_base<T>(FLQuant_base<T2>)\n");
    Rcpp::stop("I have no specific instructions for these types. Please add a specialisation\n");
}

// Specialise the FLQuant_base<T>(FLQuant_base<T2>) constructor 
// Make an FLQuantAdolc from an FLQuant
template <>
template <>
FLQuant_base<adouble>::FLQuant_base(const FLQuant_base<double>& FLQuant_source){
    //Rprintf("Making an FLQuantAdolc from an FLQuant\n");
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
	return Rcpp::clone<Rcpp::IntegerVector>(dim);
}

template <typename T>
Rcpp::List FLQuant_base<T>::get_dimnames() const{
	return Rcpp::clone<Rcpp::List>(dimnames);
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
    if ((quant > dim(0)) || (year > dim(1)) || (unit > dim(2)) || (season > dim(3)) || (area > dim(4)) || (iter > dim(5))){
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
    //Rprintf("In const single element accessor\n");
    if (element > get_size()){
        Rcpp::stop("Trying to access element larger than data size.");
    }
    return data[element-1];
}

// Data accessor - single element
template <typename T>
T& FLQuant_base<T>::operator () (const unsigned int element){
    //Rprintf("In single element accessor\n");
    if (element > get_size()){
        Rcpp::stop("Trying to access element larger than data size.");
    }
	return data[element-1];
}

// Get only data accessor - all dims
template <typename T>
T FLQuant_base<T>::operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter) const{
    //Rprintf("In const multiple element accessor\n");
	unsigned int element = get_data_element(quant, year, unit, season, area, iter);
	return data[element];
}

// Data accessor - all dims
template <typename T>
T& FLQuant_base<T>::operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter){
    //Rprintf("In multiple element accessor\n");
	unsigned int element = get_data_element(quant, year, unit, season, area, iter);
	return data[element];
}

// Get data accessor - all dims with an integer vector
template <typename T>
T FLQuant_base<T>::operator () (const std::vector<unsigned int> indices) const {
    if (indices.size() > 6){
        Rcpp::stop("FLQuant indices accessor - indices longer than 6.");
    }
    if (indices.size() < 6){
        Rcpp::stop("FLQuant indices accessor - indices shorter than 6.");
    }
	unsigned int element = get_data_element(indices[0],indices[1],indices[2],indices[3],indices[4],indices[5]);
	return data[element];
}

// Data accessor - all dims with an integer vector
template <typename T>
T& FLQuant_base<T>::operator () (const std::vector<unsigned int> indices) {
    if (indices.size() > 6){
        Rcpp::stop("FLQuant indices accessor - indices longer than 6.");
    }
    if (indices.size() < 6){
        Rcpp::stop("FLQuant indices accessor - indices shorter than 6.");
    }
	unsigned int element = get_data_element(indices[0],indices[1],indices[2],indices[3],indices[4],indices[5]);
	return data[element];
}

// Subset
template <typename T>
FLQuant_base<T> FLQuant_base<T>::operator () (const int quant_min, const int quant_max, const int year_min, const int year_max, const int unit_min, const int unit_max, const int season_min, const int season_max, const int area_min, const int area_max, const int iter_min, const int iter_max) const {
    // Check ranges
    if ((quant_min < 1) || (year_min < 1)|| (unit_min < 1)|| (season_min < 1)|| (area_min < 1)|| (iter_min < 1) || (quant_max > get_nquant()) || (year_max > get_nyear()) || (unit_max > get_nunit()) || (season_max > get_nseason()) || (area_max > get_narea()) || (iter_max > get_niter())){
        Rcpp::stop("In FLQuant subsetter: requested subset dimensions are outside of FLQuant bounds.\n");
    }
    // Check max >= min
    if ((quant_max < quant_min) || (year_max < year_min) || (unit_max < unit_min) || (season_max < season_min) || (area_max < area_min) || (iter_max < iter_min)){
        Rcpp::stop("In FLQuant subsetter: min dim > max\n");
    }

    const int new_quant_dim = quant_max - quant_min + 1;
    const int new_year_dim = year_max - year_min + 1;
    const int new_unit_dim = unit_max - unit_min + 1;
    const int new_season_dim = season_max - season_min + 1;
    const int new_area_dim = area_max - area_min + 1;
    const int new_iter_dim = iter_max - iter_min + 1;
    FLQuant_base<T> out(new_quant_dim, new_year_dim, new_unit_dim, new_season_dim, new_area_dim, new_iter_dim);
    for (int quant_count = 1; quant_count <= new_quant_dim; ++quant_count){
        for (int year_count = 1; year_count <= new_year_dim; ++year_count){
            for (int unit_count = 1; unit_count <= new_unit_dim; ++unit_count){
                for (int season_count = 1; season_count <= new_season_dim; ++season_count){
                    for (int area_count = 1; area_count <= new_area_dim; ++area_count){
                        for (int iter_count = 1; iter_count <= new_iter_dim; ++iter_count){
                            unsigned int element = get_data_element(quant_count + quant_min - 1, year_count + year_min - 1, unit_count + unit_min - 1, season_count + season_min - 1, area_count + area_min - 1, iter_count + iter_min - 1);
                            out(quant_count, year_count, unit_count, season_count, area_count, iter_count) = data[element];
    }}}}}}

    // Fix dimnames too - this is horrible
    Rcpp::List old_dimnames = get_dimnames();
    Rcpp::List new_dimnames = get_dimnames();
    Rcpp::CharacterVector old_quant_dimname = Rcpp::as<Rcpp::CharacterVector>(old_dimnames[0]);
    Rcpp::CharacterVector new_quant_dimname(new_quant_dim);
    for (int quant_count = 0; quant_count < new_quant_dim; ++quant_count){
        new_quant_dimname[quant_count] = old_quant_dimname[quant_count + quant_min - 1];
    }
    new_dimnames[0] = new_quant_dimname;

    Rcpp::CharacterVector old_year_dimname = Rcpp::as<Rcpp::CharacterVector>(old_dimnames[1]);
    Rcpp::CharacterVector new_year_dimname(new_year_dim);
    for (int year_count = 0; year_count < new_year_dim; ++year_count){
        new_year_dimname[year_count] = old_year_dimname[year_count + year_min - 1];
    }
    new_dimnames[1] = new_year_dimname;

    Rcpp::CharacterVector old_unit_dimname = Rcpp::as<Rcpp::CharacterVector>(old_dimnames[2]);
    Rcpp::CharacterVector new_unit_dimname(new_unit_dim);
    for (int unit_count = 0; unit_count < new_unit_dim; ++unit_count){
        new_unit_dimname[unit_count] = old_unit_dimname[unit_count + unit_min - 1];
    }
    new_dimnames[2] = new_unit_dimname;

    Rcpp::CharacterVector old_season_dimname = Rcpp::as<Rcpp::CharacterVector>(old_dimnames[3]);
    Rcpp::CharacterVector new_season_dimname(new_season_dim);
    for (int season_count = 0; season_count < new_season_dim; ++season_count){
        new_season_dimname[season_count] = old_season_dimname[season_count + season_min - 1];
    }
    new_dimnames[3] = new_season_dimname;

    Rcpp::CharacterVector old_area_dimname = Rcpp::as<Rcpp::CharacterVector>(old_dimnames[4]);
    Rcpp::CharacterVector new_area_dimname(new_area_dim);
    for (int area_count = 0; area_count < new_area_dim; ++area_count){
        new_area_dimname[area_count] = old_area_dimname[area_count + area_min - 1];
    }
    new_dimnames[4] = new_area_dimname;

    Rcpp::CharacterVector old_iter_dimname = Rcpp::as<Rcpp::CharacterVector>(old_dimnames[5]);
    Rcpp::CharacterVector new_iter_dimname(new_iter_dim);
    for (int iter_count = 0; iter_count < new_iter_dim; ++iter_count){
        new_iter_dimname[iter_count] = old_iter_dimname[iter_count + iter_min - 1];
    }
    new_dimnames[5] = new_iter_dimname;

    out.set_dimnames(new_dimnames);



    return out;

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

// Checks if dimnames dimensions fit current dim
template <typename T>
void FLQuant_base<T>::set_dimnames(const Rcpp::List& dimnames_in){
    Rcpp::CharacterVector name;
    int dim_length = 0;
    for (int i = 0; i <= 5; ++i){
        name = dimnames_in[i];
        dim_length = name.size();
        if (dim_length != dim[i]){
            Rcpp::stop("Cannot set dimnames as new dimnames are different size to current dimensions\n");
        }
    }
    dimnames = dimnames_in;
}

template <typename T>
void FLQuant_base<T>::set_units(const std::string& units_in){
    units = units_in;
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
    //Rprintf("In self multiplication assignment\n");
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
    //Rprintf("In T1*=T2 multiplication assignment\n");
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
    //Rprintf("In scalar T=*T multiplication assignment\n");
    std::transform((*this).data.begin(), (*this).data.end(), (*this).data.begin(), std::bind1st(std::multiplies<T>(),rhs)); 
    return *this;
}

// Special case of multiplication assignment 
// Used for FLQuantAdolc *= double
// Needs to be instanitated due to extra template class, T2
template <typename T>
template <typename T2>
FLQuant_base<T>& FLQuant_base<T>::operator *= (const T2& rhs){
    //Rprintf("In scalar T=*T2 multiplication assignment\n");
    std::transform((*this).data.begin(), (*this).data.end(), (*this).data.begin(), std::bind1st(std::multiplies<T>(),rhs)); 
    return *this;
}

// General multiplication
// FLQuant_base<T> * FLQuant_base<T>
template <typename T>
FLQuant_base<T> FLQuant_base<T>::operator * (const FLQuant_base<T>& rhs) const{
    //Rprintf("In self multiplication\n");
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
    //Rprintf("FLQuant_base<double> * FLQuant_base<T>\n");
    if (lhs.match_dims(rhs) != 1){
        Rcpp::stop("You cannot multiply FLQuants as your dimensions do not match.");
    }
    FLQuant_base<T> out = rhs;
    out *= lhs;
    return out;

}

template <typename T>
FLQuant_base<T> operator * (const FLQuant_base<T>& lhs, const FLQuant_base<double>& rhs){
    //Rprintf("FLQuant_base<T> * FLQuant_base<double>\n");
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

/* Other methods */
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
//FLQuant_base<T> log(const FLQuant_base<T>& flq);
//FLQuant_base<T> exp(const FLQuant_base<T>& flq);

template <typename T>
FLQuant_base<T> log(const FLQuant_base<T>& flq){
    FLQuant_base<T> flq_out = flq;
    std::vector<T> data = flq_out.get_data();
    for (typename std::vector<T>::iterator data_iterator = data.begin(); data_iterator != data.end(); ++data_iterator){
        (*data_iterator) = log(*data_iterator);
    }
    flq_out.set_data(data);
    return flq_out;
}

template <typename T>
FLQuant_base<T> exp(const FLQuant_base<T>& flq){
    FLQuant_base<T> flq_out = flq;
    std::vector<T> data = flq_out.get_data();
    for (typename std::vector<T>::iterator data_iterator = data.begin(); data_iterator != data.end(); ++data_iterator){
        (*data_iterator) = exp(*data_iterator);
    }
    flq_out.set_data(data);
    return flq_out;
}

int dim_matcher(const Rcpp::IntegerVector dims_a, const Rcpp::IntegerVector dims_b){
    for (int i=0; i<6; ++i){
        if (dims_a(i) != dims_b(i)){
            return -1 * (i+1); // Return negative of what dim does not match
        }
    }
    return 1; // Else all is good
}

/*------------- Shortcut methods ----------------*/
template <typename T>
FLQuant_base<T> year_sum(const FLQuant_base<T>& flq){
    Rprintf("In year_sum\n");
    Rcpp::IntegerVector dim = flq.get_dim();
    // Need to make an empty FLQ with the right dim
    // New constructor?
    FLQuant_base<T> sum_flq(dim[0], 1, dim[2], dim[3], dim[4], dim[5]);

    Rcpp::List dimnames = flq.get_dimnames();
    dimnames["year"] = Rcpp::CharacterVector::create("1");
    // Set dimnames
    sum_flq.set_dimnames(dimnames);
    return sum_flq;
}

template <typename T>
FLQuant_base<T> quant_sum(const FLQuant_base<T>& flq){
    Rcpp::IntegerVector dim = flq.get_dim();
    // Make an empty FLQ with the right dim
    FLQuant_base<T> sum_flq(1, dim[1], dim[2], dim[3], dim[4], dim[5]);
    //// Set dimnames and units
    Rcpp::List dimnames = flq.get_dimnames();
    dimnames[0] = Rcpp::CharacterVector::create("all");
    sum_flq.set_dimnames(dimnames);
    sum_flq.set_units(flq.get_units());
    // Old school summing - looks ugly
    // Cannot use accumulate() as not defined for adouble
    T sum = 0;
    for (int iters=1; iters <= flq.get_niter(); ++iters){
        for (int areas=1; areas <= flq.get_narea(); ++areas){
            for (int seasons=1; seasons <= flq.get_nseason(); ++seasons){
                for (int units=1; units <= flq.get_nunit(); ++units){
                    for (int years=1; years <= flq.get_nyear(); ++years){
                        sum = 0;
                        for (int quants=1; quants <= flq.get_nquant(); ++quants){
                            sum += flq(quants, years, units, seasons, areas, iters);
                        }
                        sum_flq(1, years, units, seasons, areas, iters) = sum;
    }}}}}
    // This also works - not so nested but maybe harder to decipher
    //int nquant = flq.get_nquant();
    //for (int chunk_counter=1; chunk_counter <= (flq.get_size()) / nquant; ++chunk_counter){
    //    T sum = 0;
    //    for (int quant_counter = (chunk_counter * nquant - nquant + 1); quant_counter <= (chunk_counter * nquant); ++quant_counter){
    //        sum = sum + flq(quant_counter);
    //    }
    //    sum_flq(chunk_counter) = sum;
    //}
    return sum_flq;
}

// max_quant - returns an FLQuant with size 1 in first dimension containing the maximum value of the quant dimension
// Would like to be able to use template functions max and max_element
// But we have to be careful when using conditionals and Adolc adouble
// So we do it using the fmax() function from Adolc
// Might be possible to use template functions if we moved to CppAD
template <typename T>
FLQuant_base<T> max_quant(const FLQuant_base<T>& flq){
    Rcpp::IntegerVector dim = flq.get_dim();
    // Make an empty FLQ with the right dim
    FLQuant_base<T> max_flq(1, dim[1], dim[2], dim[3], dim[4], dim[5]);
    // Set dimnames and units
    Rcpp::List dimnames = flq.get_dimnames();
    dimnames[0] = Rcpp::CharacterVector::create("all");
    max_flq.set_dimnames(dimnames);
    max_flq.set_units(flq.get_units());
    // Old school summing - looks ugly
    T max = 0;
    for (int iters=1; iters <= flq.get_niter(); ++iters){
        for (int areas=1; areas <= flq.get_narea(); ++areas){
            for (int seasons=1; seasons <= flq.get_nseason(); ++seasons){
                for (int units=1; units <= flq.get_nunit(); ++units){
                    for (int years=1; years <= flq.get_nyear(); ++years){
                        max = flq(1, years, units, seasons, areas, iters);
                        for (int quants=1; quants <= flq.get_nquant(); ++quants){
                            max = fmax(max, flq(quants, years, units, seasons, areas, iters));
                        }
                        max_flq(1, years, units, seasons, areas, iters) = max;
    }}}}}
    return max_flq;
}


// This only makes sense if all the values ae positive
template <typename T>
FLQuant_base<T> scale_by_max_quant(const FLQuant_base<T>& flq){
    FLQuant_base<T> max_quant_flq = max_quant(flq);
    // Copy the original FLQ to get the right dim
    FLQuant_base<T> scaled_flq = flq;
    // max_flq.set_units(flq.get_units()); // units should be set to ""
    for (int iters=1; iters <= flq.get_niter(); ++iters){
        for (int areas=1; areas <= flq.get_narea(); ++areas){
            for (int seasons=1; seasons <= flq.get_nseason(); ++seasons){
                for (int units=1; units <= flq.get_nunit(); ++units){
                    for (int years=1; years <= flq.get_nyear(); ++years){
                        for (int quants=1; quants <= flq.get_nquant(); ++quants){
                            scaled_flq(quants, years, units, seasons, areas, iters)  = flq(quants, years, units, seasons, areas, iters) / max_quant_flq(1, years, units, seasons, areas, iters);
                            //scaled_flq(quants, years, units, seasons, areas, iters)  = flq(quants, years, units, seasons, areas, iters); 
                        }
    }}}}}
    return scaled_flq;
}

/*----------------------------------------------------*/
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

// Explicit instantiation of extra templated artithmetic functions
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

// Explicit instantiation of other functions
template FLQuant_base<double> log(const FLQuant_base<double>& flq);
template FLQuant_base<adouble> log(const FLQuant_base<adouble>& flq);
template FLQuant_base<double> exp(const FLQuant_base<double>& flq);
template FLQuant_base<adouble> exp(const FLQuant_base<adouble>& flq);
template FLQuant_base<double> year_sum(const FLQuant_base<double>& flq);
template FLQuant_base<adouble> year_sum(const FLQuant_base<adouble>& flq);

template FLQuant_base<double> quant_sum(const FLQuant_base<double>& flq);
template FLQuant_base<adouble> quant_sum(const FLQuant_base<adouble>& flq);

template FLQuant_base<double> max_quant(const FLQuant_base<double>& flq);
template FLQuant_base<adouble> max_quant(const FLQuant_base<adouble>& flq);

template FLQuant_base<double> scale_by_max_quant(const FLQuant_base<double>& flq);
template FLQuant_base<adouble> scale_by_max_quant(const FLQuant_base<adouble>& flq);

