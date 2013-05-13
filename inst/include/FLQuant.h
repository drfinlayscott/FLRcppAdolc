#include <RcppCommon.h>
#include <Rcpp.h>

/*
 * FLQuant class
 * constructors
 * make a NumericVector and set the dim attributes
	return flq.attr("dim");	
 * do I need to make a destructor?
 * make data protected but write public accessor
 *
 * data is a NumericVector which has attributes - dim and dimnames
 */

class FLQuant {
	public:
		FLQuant();
		FLQuant(SEXP flq_sexp);
		FLQuant(const FLQuant& FLQuant_source); // copy constructor to ensure that copy of NumericVector is a deep copy

		/* Get accessors 
		 * Note the use of 'const' because the get methods should promise not to modify the members (we are returning them)
		 */
		std::string get_units() const;
		void set_units(std::string new_units);
		Rcpp::NumericVector get_data() const;
		double operator () (const int quant, const int year, const int unit, const int season, const int area, const int iter) const;
		FLQuant& operator = (const FLQuant& FLQuant_source);
		int get_nquant() const;
		int get_nyear() const;
		int get_nunit() const;
		int get_nseason() const;
		int get_narea() const;
		int get_niter() const;
		int get_data_element(const int quant, const int year, const int unit, const int season, const int area, const int iter) const;

		/* Set accessors */
		double& operator () (const int quant, const int year, const int unit, const int season, const int area, const int iter);

	private: 
		Rcpp::NumericVector data;
		std::string units;	
};

// Custom as-wrap methods
namespace Rcpp {
    template <> FLQuant as(SEXP flq_sexp);
    template <> SEXP wrap(const FLQuant &flq);
}

