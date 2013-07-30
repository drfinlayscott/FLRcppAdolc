#include <RcppCommon.h>
#include <Rcpp.h>
#include <adolc.h>

/*
 * FLQuant_base<T> template class
 * FLQuant_base<double> is an FLQuant
 * FLQuantAdolc inherits a FLQuant_base<adouble>
 */

template <typename T>
class FLQuant_base {
	public:
        /* Constructors */
		FLQuant_base();
		FLQuant_base(SEXP flq_sexp); // Used as intrusive 'as'
        operator SEXP() const; // Used as intrusive 'wrap'
		//FLQuant_base(const FLQuant_base& FLQuant_base_source); // copy constructor to ensure that copy of NumericVector is a deep copy - used when passing FLQs into functions

        // Stupid helper function so that I can keep track of what is going on
        void what_am_i();
		/* Get accessors 
		 * Note the use of 'const' because the get methods should promise not to modify the members (we are returning them)
		 */
        /*
		std::string get_units() const;
		Rcpp::NumericVector get_data() const;
		int get_size() const;
		int get_nquant() const;
		int get_nyear() const;
		int get_nunit() const;
		int get_nseason() const;
		int get_narea() const;
		int get_niter() const;
		int get_data_element(const int quant, const int year, const int unit, const int season, const int area, const int iter) const;
        Rcpp::IntegerVector get_dim() const;
        Rcpp::List get_dimnames() const;
        */

		/* Set accessors */
        /*
		void set_units(const std::string new_units);
		void set_data(const Rcpp::NumericVector& data_in);
        void set_dim(const Rcpp::IntegerVector dim);
        void set_dimnames(const Rcpp::List dimnames);
        void set_attr(const Rcpp::IntegerVector dims, const Rcpp::List dimnames);
        */

        /* Overloaded operators */
        /*
		double& operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter); // gets and sets an element so const not reinforced
		double& operator () (const int element); // gets and sets an element so const not reinforced
		double operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter) const; // only gets an element so const reinforced - however cannot return reference due to NumericVector() operator
		double operator () (const int element) const; // only gets an element so const reinforced - - however cannot return reference due to NumericVector() operator
		FLQuant& operator = (const FLQuant& FLQuant_source); // Assignment operator for a deep copy
        */
        /* Mathematical operators */

        /* arithmetic operator, it's a friend so that we can have access to internals */
        template <typename T1, typename T2>
        friend FLQuant_base<T1>& operator *= (FLQuant_base<T1>& lhs, const FLQuant_base<T2>& rhs);
         
        /*
        FLQuant& operator *= (const FLQuant& flq_rhs);
        FLQuant operator * (const FLQuant& flq_rhs) const;
        FLQuant& operator /= (const FLQuant& flq_rhs);
        FLQuant operator / (const FLQuant& flq_rhs) const;
        FLQuant& operator += (const FLQuant& flq_rhs);
        FLQuant operator + (const FLQuant& flq_rhs) const;
        FLQuant& operator -= (const FLQuant& flq_rhs);
        FLQuant operator - (const FLQuant& flq_rhs) const;
        FLQuant& operator *= (const double& rhs);
        FLQuant operator * (const double& rhs) const;
        FLQuant& operator /= (const double& rhs);
        FLQuant operator / (const double& rhs) const;
        FLQuant& operator += (const double& rhs);
        FLQuant operator + (const double& rhs) const;
        FLQuant& operator -= (const double& rhs);
        FLQuant operator - (const double& rhs) const;
        */

        /* Other methods */
        //int match_dims(const FLQuant& flq) const;

    protected:
        std::vector<T> data;
		std::string units;	
        Rcpp::IntegerVector dim;
        Rcpp::List dimnames;
};

//// Custom as-wrap methods
//Namespace Rcpp {
//    template <> FLQuant as(SEXP flq_sexp);
//    template <> SEXP wrap(const FLQuant &flq);
//}

/* Other useful functions */
//int match_dims(const FLQuant a, const FLQuant b);
//FLQuant log(const FLQuant& flq);
//FLQuant exp(const FLQuant& flq);

typedef FLQuant_base<double> FLQuant;


