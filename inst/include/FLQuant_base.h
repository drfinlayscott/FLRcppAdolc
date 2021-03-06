/* 
 * Copyright 2013 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */


#include <RcppCommon.h>
#include <Rcpp.h>
//#include <adolc.h>
#include "adolc/adolc.h"

#define _FLQuant_base_
/*
 * FLQuant_base<T> template class
 * FLQuant_base<double> is an FLQuant
 * I was originally thinking of having FLQuantAdolc as a new class that inherits FLQuant_base<adouble>.
 * This would mean we could additional member variables and methods that were appropriate for FLQuantAdolc.
 * This idea could be further expanded to a templated AD class, FLQuantAD_base<T> that could be used for AutoDiff classes as well as adouble
 * The implementation is not difficult for some methods.
 * Of course, all constructors, copy and assignement methods need to be specialised.
 * But the get_x(), set_x(), element accessor () operators could be defined in the FLQuant_base and then used by all inherited classes with different <T>
 * The problem is with a method that requires a copy to be made. If this method is 'only' declared in the base class, then slicing occurs when called by a derived class.
 * For example, the multiplication operator, *, requires a copy of the lhs to be made (it works on the lhs object, lhs.(*)).
 * If the lhs is actually FLQAdolc which as inherited FLQuant_base<adouble>, what appears in the * method is only the base FLQuant_base<adouble> object, not the full
 * FLQAdolc object. All extra methods and variables are 'sliced' off. When the copy returns, it is only a FLQuant_base<adouble> not FLQAdolc.
 * To get round this it would be possible to define lots of extra overloaded methods (e.g. FLQuantAdolc * FLQuant; FLQuantAdolc * FLQuant; FLQuant * FLQuantAdolc).
 * This doesn't sounds like too much of a hassle but the overhead becomes substantial when we have * / + - operators, as well as ones that only a double, or an adouble.
 * We can revisit this if necessary. For the time being, FLQuantAdolc is just FLQuant_base<adouble>.
 */

template <typename T>
class FLQuant_base {
	public:
        /* Constructors */
		FLQuant_base();
		FLQuant_base(SEXP flq_sexp); // Used as intrusive 'as'
        operator SEXP() const; // Used as intrusive 'wrap'
		FLQuant_base(const FLQuant_base& FLQuant_base_source); // copy constructor to ensure that copies (i.e. when passing to functions) are deep
		FLQuant_base& operator = (const FLQuant_base& FLQuant_source); // Assignment operator for a deep copy
        FLQuant_base(const int nquant, const int nyear, const int nunit, const int nseason, const int narea, const int niter); // Make an empty FLQuant

        template <typename T2>
		FLQuant_base(const FLQuant_base<T2>& FLQuant_source); // Specialised to make an FLQuantAdolc from an FLQuant

		/* Get accessors */
        std::vector<T> get_data() const;
		std::string get_units() const;
        Rcpp::IntegerVector get_dim() const;
        Rcpp::List get_dimnames() const;
		unsigned int get_size() const;
		int get_nquant() const;
		int get_nyear() const;
		int get_nunit() const;
		int get_nseason() const;
		int get_narea() const;
		int get_niter() const;
		int get_data_element(const int quant, const int year, const int unit, const int season, const int area, int iter) const;
		int get_data_element2(const int quant, const int year, const int unit, const int season, const int area, int iter) const;

		/* Set accessors */
		void set_data(const std::vector<T>& data_in);
        void set_dimnames(const Rcpp::List& dimnames_in);
        void set_units(const std::string& units_in);

        /* () get accessors */
		T operator () (const unsigned int element) const; // only gets an element so const reinforced - 
		T operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter) const; // only gets an element so const reinforced 
		T operator () (const std::vector<unsigned int> indices) const; // For all the elements - must be of length 6 
		FLQuant_base<T> operator () (const int quant_min, const int quant_max, const int year_min, const int year_max, const int unit_min, const int unit_max, const int season_min, const int season_max, const int area_min, const int area_max, const int iter_min, const int iter_max) const; // Subsetting
		FLQuant_base<T> operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area) const; // Access all iters
        /* () get and set accessors */
		T& operator () (const unsigned int element); // gets and sets an element so const not reinforced
		T& operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter); // gets and sets an element so const not reinforced
		T& operator () (const std::vector<unsigned int> indices); // For all the elements - must be of length 6 
		//FLQuant_base<T>& operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area); // Access all iters

        /* Mathematical operators */

        // Multiplication
        FLQuant_base<T>& operator *= (const FLQuant_base<T>& rhs);
        FLQuant_base<T>& operator *= (const T& rhs);
        // For the special case of FLQuant_base<adouble> *= FLQuant_base<double>
        template <typename T2>
        FLQuant_base<T>& operator *= (const FLQuant_base<T2>& rhs);
        // For the special case of FLQuant_base<adouble> *= double
        template <typename T2>
        FLQuant_base<T>& operator *= (const T2& rhs);
        // Return same type as itself
        FLQuant_base<T> operator * (const FLQuant_base<T>& rhs) const;
        FLQuant_base<T> operator * (const T& rhs) const;

        // Division
        FLQuant_base<T>& operator /= (const FLQuant_base<T>& rhs);
        FLQuant_base<T>& operator /= (const T& rhs);
        // For the special case of FLQuant_base<adouble> *= FLQuant_base<double>
        template <typename T2>
        FLQuant_base<T>& operator /= (const FLQuant_base<T2>& rhs);
        // For the special case of FLQuant_base<adouble> *= double
        template <typename T2>
        FLQuant_base<T>& operator /= (const T2& rhs);
        // Return same type as itself
        FLQuant_base<T> operator / (const FLQuant_base<T>& rhs) const;
        FLQuant_base<T> operator / (const T& rhs) const;

        // Subtraction
        FLQuant_base<T>& operator -= (const FLQuant_base<T>& rhs);
        FLQuant_base<T>& operator -= (const T& rhs);
        // For the special case of FLQuant_base<adouble> *= FLQuant_base<double>
        template <typename T2>
        FLQuant_base<T>& operator -= (const FLQuant_base<T2>& rhs);
        // For the special case of FLQuant_base<adouble> *= double
        template <typename T2>
        FLQuant_base<T>& operator -= (const T2& rhs);
        // Return same type as itself
        FLQuant_base<T> operator - (const FLQuant_base<T>& rhs) const;
        FLQuant_base<T> operator - (const T& rhs) const;

        // Addition
        FLQuant_base<T>& operator += (const FLQuant_base<T>& rhs);
        FLQuant_base<T>& operator += (const T& rhs);
        // For the special case of FLQuant_base<adouble> += FLQuant_base<double>
        template <typename T2>
        FLQuant_base<T>& operator += (const FLQuant_base<T2>& rhs);
        // For the special case of FLQuant_base<adouble> *= double
        template <typename T2>
        FLQuant_base<T>& operator += (const T2& rhs);
        // Return same type as itself
        FLQuant_base<T> operator + (const FLQuant_base<T>& rhs) const;
        FLQuant_base<T> operator + (const T& rhs) const;

        /* Other methods */
        int match_dims(const FLQuant_base<T>& flq) const;
        template <typename T2>
        int match_dims(const FLQuant_base<T2>& flq) const;
        FLQuant_base<T> propagate_iters(const int iters) const;

    protected:
        std::vector<T> data;
		std::string units;	
        Rcpp::IntegerVector dim;
        Rcpp::List dimnames;
};

typedef FLQuant_base<double> FLQuant;
typedef FLQuant_base<adouble> FLQuantAdolc;

//---------- Other useful functions ------------------------

int dim_matcher(const Rcpp::IntegerVector a, const Rcpp::IntegerVector b);
int dim5_matcher(const Rcpp::IntegerVector a, const Rcpp::IntegerVector b);


template <typename T>
string number_to_string (T number);

//------------ Non-member arithmetic methods with mixed types --------------

/* Canonical form: Type operator*(const Type &lhs, const Type &rhs); 
* double gets swallowed up by whatever is multiplying it.
* This means that the operations involving a double need to be individually specified.
* Need to be careful of ambiguities arise,
* FLQuant_base<anything>  = FLQuant_base<double> * FLQuant_base<anything>
* FLQuant = FLQuant * double
* FLQuantAdolc = FLQuantAdolc * adouble
* FLQuant_base<> = <> * FLQuant_base
*/

// The templated functions are all instantiated at the bottom of FLQuant_base.cpp

// Multiplication
template <typename T>
FLQuant_base<T> operator * (const FLQuant_base<double>& lhs, const FLQuant_base<T>& rhs);
template <typename T>
FLQuant_base<T> operator * (const FLQuant_base<T>& lhs, const FLQuant_base<double>& rhs);
// No template - resolves ambiguity arising from double * FLQ<T> and <T> * FLQ<T> (if T is double, which one is called?)
FLQuant_base<double> operator * (const double& lhs, const FLQuant_base<double>& rhs);
// For FLQuant_base<adouble> = adouble * FLQuant_base<adouble>
template <typename T>
FLQuant_base<T> operator * (const T& lhs, const FLQuant_base<T>& rhs);
// For FLQuant_base<adouble> = double * FLQuant_base<adouble>
template <typename T>
FLQuant_base<T> operator * (const double& lhs, const FLQuant_base<T>& rhs);
template <typename T>
FLQuant_base<T> operator * (const FLQuant_base<T>& lhs, const double& rhs);
// For FLQuant_base<adouble> = FLQuant_base<double> * adouble
template <typename T>
FLQuant_base<T> operator * (const FLQuant_base<double>& lhs, const T& rhs);
template <typename T>
FLQuant_base<T> operator * (const T& lhs, const FLQuant_base<double>& rhs);

// Division
template <typename T>
FLQuant_base<T> operator / (const FLQuant_base<double>& lhs, const FLQuant_base<T>& rhs);
template <typename T>
FLQuant_base<T> operator / (const FLQuant_base<T>& lhs, const FLQuant_base<double>& rhs);
// No template - resolves ambiguity
FLQuant_base<double> operator / (const double& lhs, const FLQuant_base<double>& rhs);
// For FLQuant_base<adouble> = adouble / FLQuant_base<adouble>
template <typename T>
FLQuant_base<T> operator / (const T& lhs, const FLQuant_base<T>& rhs);
// For FLQuant_base<adouble> = double / FLQuant_base<adouble>
template <typename T>
FLQuant_base<T> operator / (const double& lhs, const FLQuant_base<T>& rhs);
template <typename T>
FLQuant_base<T> operator / (const FLQuant_base<T>& lhs, const double& rhs);
// For FLQuant_base<adouble> = FLQuant_base<double> / adouble
template <typename T>
FLQuant_base<T> operator / (const FLQuant_base<double>& lhs, const T& rhs);
template <typename T>
FLQuant_base<T> operator / (const T& lhs, const FLQuant_base<double>& rhs);

// Subtraction
template <typename T>
FLQuant_base<T> operator - (const FLQuant_base<double>& lhs, const FLQuant_base<T>& rhs);
template <typename T>
FLQuant_base<T> operator - (const FLQuant_base<T>& lhs, const FLQuant_base<double>& rhs);
// No template - resolves ambiguity
FLQuant_base<double> operator - (const double& lhs, const FLQuant_base<double>& rhs);
// For FLQuant_base<adouble> = adouble - FLQuant_base<adouble>
template <typename T>
FLQuant_base<T> operator - (const T& lhs, const FLQuant_base<T>& rhs);
// For FLQuant_base<adouble> = double - FLQuant_base<adouble>
template <typename T>
FLQuant_base<T> operator - (const double& lhs, const FLQuant_base<T>& rhs);
template <typename T>
FLQuant_base<T> operator - (const FLQuant_base<T>& lhs, const double& rhs);
// For FLQuant_base<adouble> = FLQuant_base<double> - adouble
template <typename T>
FLQuant_base<T> operator - (const FLQuant_base<double>& lhs, const T& rhs);
template <typename T>
FLQuant_base<T> operator - (const T& lhs, const FLQuant_base<double>& rhs);

// Addition
template <typename T>
FLQuant_base<T> operator + (const FLQuant_base<double>& lhs, const FLQuant_base<T>& rhs);
template <typename T>
FLQuant_base<T> operator + (const FLQuant_base<T>& lhs, const FLQuant_base<double>& rhs);
// No template - resolves ambiguity arising from double + FLQ<T> and <T> + FLQ<T> (if T is double, which one is called?)
FLQuant_base<double> operator + (const double& lhs, const FLQuant_base<double>& rhs);
// For FLQuant_base<adouble> = adouble + FLQuant_base<adouble>
template <typename T>
FLQuant_base<T> operator + (const T& lhs, const FLQuant_base<T>& rhs);
// For FLQuant_base<adouble> = double + FLQuant_base<adouble>
template <typename T>
FLQuant_base<T> operator + (const double& lhs, const FLQuant_base<T>& rhs);
template <typename T>
FLQuant_base<T> operator + (const FLQuant_base<T>& lhs, const double& rhs);
// For FLQuant_base<adouble> = FLQuant_base<double> * adouble
template <typename T>
FLQuant_base<T> operator + (const FLQuant_base<double>& lhs, const T& rhs);
template <typename T>
FLQuant_base<T> operator + (const T& lhs, const FLQuant_base<double>& rhs);

// Other arithmetic operations
template <typename T>
FLQuant_base<T> log(const FLQuant_base<T>& flq);
template <typename T>
FLQuant_base<T> exp(const FLQuant_base<T>& flq);

// Shortcut methods
template <typename T>
FLQuant_base<T> year_sum(const FLQuant_base<T>& flq);

template <typename T>
FLQuant_base<T> quant_sum(const FLQuant_base<T>& flq);

// Means over various dimensions
template <typename T>
FLQuant_base<T> quant_mean(const FLQuant_base<T>& flq);  // collapse the quant dimension


template <typename T>
FLQuant_base<T> max_quant(const FLQuant_base<T>& flq);

// This only makes sense if all the values ae positive
template <typename T>
FLQuant_base<T> scale_by_max_quant(const FLQuant_base<T>& flq);

