/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../inst/include/FLQuant_multidim.h"

// Default constructor
// No dimnames set as the array is null
template <typename T>
FLQuant7_base<T>::FLQuant7_base(){
    //Rprintf("In FLQuant7_base<T> basic constructor\n");
    // Make NULL std::vector<T>?
}

// Used as intrusive 'as' - takes a list
template <typename T> 
FLQuant7_base<T>::FLQuant7_base(SEXP lst_sexp){
    //Rprintf("In FLQuant7_base<T> SEXP constructor\n");
    Rcpp::List lst(lst_sexp);
    Rcpp::List::iterator lst_iterator;
    for (lst_iterator = lst.begin(); lst_iterator != lst.end(); ++ lst_iterator){
        data.push_back(*lst_iterator);
    }
}

// Takes an FLQuant or FLQuantAdolc and adds it on the end
template <typename T> 
FLQuant7_base<T>::FLQuant7_base(FLQuant_base<T> flq){
    //Rprintf("In FLQuant7_base<T> FLQuant constructor\n");
    data.push_back(flq);
}

// Intrusive wrap
// List is unamed
template<typename T>
FLQuant7_base<T>::operator SEXP() const{
    //Rprintf("Wrapping FLQuant7_base<T>.\n");
    Rcpp::List list_out;
    for (int i = 0; i < get_ndim7(); i++){
        list_out.push_back(data[i]);
    }
    // Or, using iterators.
    // Would like to use an iterator member but cannot change its value in a const method so cannot set value to data.begin()
    //typename vector<FLQuant_base<T> >::const_iterator data_iterator; 
    //for (data_iterator = data.begin(); data_iterator != data.end(); ++data_iterator){ // iterator must be const because the method is const
    //    list_out.push_back(*data_iterator);
    //}
    return list_out;
}


// Copy constructor - else 'data' can be pointed at by multiple instances
template<typename T>
FLQuant7_base<T>::FLQuant7_base(const FLQuant7_base<T>& FLQuant7_source){
    //Rprintf("In FLQuant7_base<T> copy constructor\n");
	data  = FLQuant7_source.data; // std::vector always does deep copy
}

// Assignment operator to ensure deep copy - else 'data' can be pointed at by multiple instances
template<typename T>
FLQuant7_base<T>& FLQuant7_base<T>::operator = (const FLQuant7_base<T>& FLQuant7_source){
    //Rprintf("In FLQuant7_base<T> assignment operator\n");
	if (this != &FLQuant7_source){
        data  = FLQuant7_source.data; // std::vector always does deep copy
	}
	return *this;
}

/*--------------- Accessors -------------------*/

template <typename T>
int FLQuant7_base<T>::get_ndim7() const {
    int length = data.size();
    return length;
}


// Add another FLQuant_base<T> to the data
template <typename T>
void FLQuant7_base<T>::operator() (const FLQuant_base<T> flq){
    data.push_back(flq);
}

// Get only data accessor - single element
template <typename T>
FLQuant_base<T> FLQuant7_base<T>::operator () (const unsigned int element) const{
    //Rprintf("In const single element accessor\n");
    if (element > get_ndim7()){
        Rcpp::stop("FLQuant7_base: Trying to access element larger than data size.");
    }
    return data[element-1];
}

// Data accessor - single element
template <typename T>
FLQuant_base<T>& FLQuant7_base<T>::operator () (const unsigned int element){
    //Rprintf("In single element accessor\n");
    if (element > get_ndim7()){
        Rcpp::stop("FLQuant7_base: Trying to access element larger than data size.");
    }
	return data[element-1];
}

// Get only data accessor - all dims
template <typename T>
T FLQuant7_base<T>::operator () (const unsigned int dim7, const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter) const{
    //Rprintf("In const multiple element accessor\n");
    if (dim7 > get_ndim7()){
        Rcpp::stop("FLQuant7_base: Trying to access element larger than data size.");
    }
	return data[dim7-1](quant, year, unit, season, area, iter);
}

// Get and set data accessor - all dims
template <typename T>
T& FLQuant7_base<T>::operator () (const unsigned int dim7, const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter){
    //Rprintf("In multiple element accessor\n");
    if (dim7 > get_ndim7()){
        Rcpp::stop("FLQuant7_base: Trying to access element larger than data size.");
    }
	return data[dim7-1](quant, year, unit, season, area, iter);
}

// Explicit instantiation of class
template class FLQuant7_base<double>;
template class FLQuant7_base<adouble>;

/*-------------------------------------------------*/
/*
dummy_as::dummy_as(){
    Rprintf("In default constructor\n");
}

dummy_as::dummy_as(SEXP sexp){
    Rprintf("In intrinsic as\n");
}

template <typename T>
dummy_as_template<T>::dummy_as_template(){
    Rprintf("In default template constructor\n");
}

template <typename T>
dummy_as_template<T>::dummy_as_template(SEXP sexp){
    Rprintf("In intrinsic template as\n");
}

template class dummy_as_template<double>;
template class dummy_as_template<adouble>;
*/

/*----------------------------------------*/
/*


class dummy {
    public:
        std::vector<double> data;
        // Declare iterators as members
        std::vector<double>::iterator iterator1;
        std::vector<double>::const_iterator const_iterator1;

        void test1(){
            iterator1 = data.begin();
        }

        void test2() const {
            // const_iterator1 = data.begin(); // Fails because we cannot change the value of const_iterator1 as it is a member in a const method.
            std::vector<double>::const_iterator const_iterator2 = data.begin(); // Compiles
        }
};
*/
