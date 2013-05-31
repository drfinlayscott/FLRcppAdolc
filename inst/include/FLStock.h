//#include <RcppCommon.h>
//#include <Rcpp.h>
#include "FLQuant.h"

/*
 * FLStock class
 */

class FLStock {
    public:
        /* Constructors */
		FLStock();
		FLStock(SEXP fls_sexp);
		FLStock(const FLStock& FLStock_source); // copy constructor to ensure that copy is a deep copy - used when passing FLSs into functions

        /* Don't make the data private - else writing accessor methods for all these will be a massive pain */
        // The names etc
        std::string name;
        std::string desc;
        Rcpp::NumericVector range;
        // The FLQuant slots
        FLQuant catches;  // catch is a reserved word
        FLQuant catch_n;  
        FLQuant catch_wt; 
        FLQuant discards;
        FLQuant discards_n;
        FLQuant discards_wt;
        FLQuant landings;
        FLQuant landings_n;
        FLQuant landings_wt;
        FLQuant stock;
        FLQuant stock_n;
        FLQuant stock_wt;
        FLQuant m;
        FLQuant mat;
        FLQuant harvest;
        FLQuant harvest_spwn;
        FLQuant m_spwn;
};


// Custom as-wrap methods
namespace Rcpp {
    template <> FLStock as(SEXP fls_sexp);
    template <> SEXP wrap(const FLStock &fls);
}

