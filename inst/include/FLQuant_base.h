/* 
 * Copyright 2013 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */


#include <RcppCommon.h>
#include <Rcpp.h>
#include <adolc.h>

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

        template <typename T2>
		FLQuant_base(const FLQuant_base<T2>& FLQuant_source); // Make an FLQuantAdolc from an FLQuant

		/* Get accessors 
		 * Note the use of 'const' because the get methods should promise not to modify the members (we are returning them)
		 */
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
		int get_data_element(const int quant, const int year, const int unit, const int season, const int area, const int iter) const;

		/* Set accessors */
		void set_data(const std::vector<T>& data_in);
        /*
		void set_units(const std::string new_units);
        void set_dim(const Rcpp::IntegerVector dim);
        void set_dimnames(const Rcpp::List dimnames);
        */

        /* Overloaded operators */
		T operator () (const unsigned int element) const; // only gets an element so const reinforced - - however cannot return reference due to NumericVector() operator
		T operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter) const; // only gets an element so const reinforced - however cannot return reference due to NumericVector() operator
		T& operator () (const unsigned int element); // gets and sets an element so const not reinforced
		T& operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter); // gets and sets an element so const not reinforced

        /* Mathematical operators */

        // Multiplication assignment
        FLQuant_base<T>& operator *= (const FLQuant_base<T>& rhs);
        FLQuant_base<T>& operator *= (const T& rhs);
        // For the special case of FLQuant_base<adouble> *= FLQuant_base<double>
        template <typename T2>
        FLQuant_base<T>& operator *= (const FLQuant_base<T2>& rhs);
        // For the special case of FLQuant_base<adouble> *= double
        template <typename T2>
        FLQuant_base<T>& operator *= (const T2& rhs);
        // Multiplication
        // Return same type as itself
        FLQuant_base<T> operator * (const FLQuant_base<T>& rhs) const;
        FLQuant_base<T> operator * (const T& rhs) const;

        // Division assignment
        FLQuant_base<T>& operator /= (const FLQuant_base<T>& rhs);
        FLQuant_base<T>& operator /= (const T& rhs);
        // For the special case of FLQuant_base<adouble> *= FLQuant_base<double>
        template <typename T2>
        FLQuant_base<T>& operator /= (const FLQuant_base<T2>& rhs);
        // For the special case of FLQuant_base<adouble> *= double
        template <typename T2>
        FLQuant_base<T>& operator /= (const T2& rhs);
        // Division
        // Return same type as itself
        FLQuant_base<T> operator / (const FLQuant_base<T>& rhs) const;
        FLQuant_base<T> operator / (const T& rhs) const;

        // Subtraction assignment
        FLQuant_base<T>& operator -= (const FLQuant_base<T>& rhs);
        FLQuant_base<T>& operator -= (const T& rhs);
        // For the special case of FLQuant_base<adouble> *= FLQuant_base<double>
        template <typename T2>
        FLQuant_base<T>& operator -= (const FLQuant_base<T2>& rhs);
        // For the special case of FLQuant_base<adouble> *= double
        template <typename T2>
        FLQuant_base<T>& operator -= (const T2& rhs);
        // Division
        // Return same type as itself
        FLQuant_base<T> operator - (const FLQuant_base<T>& rhs) const;
        FLQuant_base<T> operator - (const T& rhs) const;

        /*
        FLQuant& operator += (const FLQuant& flq_rhs);
        FLQuant operator + (const FLQuant& flq_rhs) const;

        FLQuant& operator += (const double& rhs);
        FLQuant operator + (const double& rhs) const;
        */

        /* Other methods */
        int match_dims(const FLQuant_base<T>& flq) const;
        template <typename T2>
        int match_dims(const FLQuant_base<T2>& flq) const;

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

//------------ Non-member arithmetic methods with mixed types --------------
//Canonical form: Type operator*(const Type &lhs, const Type &rhs); 
// double gets swallowed up by whatever is multiplying it
// This means that the operations involving a double need to be individually specified, else ambiguities arise
// FLQuant_base<anything>  = FLQuant_base<double> * FLQuant_base<anything>
// FLQuant = FLQuant * double
// FLQuantAdolc = FLQuantAdolc * adouble
// FLQuant_base<> = <> * FLQuant_base

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

//FLQuant log(const FLQuant& flq);
//FLQuant exp(const FLQuant& flq);





