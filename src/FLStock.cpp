#include "../inst/include/FLStock.h"

// Default constructor
// Just an empty object
FLStock::FLStock(){
    name = std::string();
    desc = std::string(); 
    range = Rcpp::NumericVector(); // Could force it to be 7 elements with dimnames?
    catches = FLQuant();
    catch_n = FLQuant();  
    catch_wt = FLQuant(); 
    discards = FLQuant();
    discards_n = FLQuant();
    discards_wt = FLQuant();
    landings = FLQuant();
    landings_n = FLQuant();
    landings_wt = FLQuant();
    stock = FLQuant();
    stock_n = FLQuant();
    stock_wt = FLQuant();
    m = FLQuant();
    mat = FLQuant();
    harvest = FLQuant();
    harvest_spwn = FLQuant();
    m_spwn = FLQuant();
}

// Constructor from a SEXP S4 FLStock
FLStock::FLStock(SEXP fls_sexp){
    Rcpp::S4 fls_s4 = Rcpp::as<Rcpp::S4>(fls_sexp);
    name = Rcpp::as<std::string>(fls_s4.slot("name"));
    desc = Rcpp::as<std::string>(fls_s4.slot("desc"));
    range = fls_s4.slot("range");
    catches = fls_s4.slot("catch");
    catch_n = fls_s4.slot("catch.n");
    catch_wt = fls_s4.slot("catch.wt");
    discards = fls_s4.slot("discards");
    discards_n = fls_s4.slot("discards.n"); 
    discards_wt = fls_s4.slot("discards.wt"); 
    landings = fls_s4.slot("landings"); 
    landings_n = fls_s4.slot("landings.n"); 
    landings_wt = fls_s4.slot("landings.wt");
    stock = fls_s4.slot("stock");
    stock_n = fls_s4.slot("stock.n"); 
    stock_wt = fls_s4.slot("stock.wt"); 
    m = fls_s4.slot("m"); 
    mat = fls_s4.slot("mat"); 
    harvest = fls_s4.slot("harvest"); 
    harvest_spwn = fls_s4.slot("harvest.spwn"); 
    m_spwn = fls_s4.slot("m.spwn"); 
}

/* Define template specialisations for as and wrap */
namespace Rcpp {
    template <> FLStock as(SEXP fls_sexp) {
        FLStock fls(fls_sexp);
        return fls;
    }

    template <> SEXP wrap(const FLStock &fls) {
        Rcpp::S4 fls_s4("FLStock");
        fls_s4.slot("name") = fls.name;
        fls_s4.slot("desc") = fls.desc;
        fls_s4.slot("range") = fls.range;
        fls_s4.slot("catch") = fls.catches;
        fls_s4.slot("catch.n") = fls.catch_n;
        fls_s4.slot("catch.wt") = fls.catch_wt;
        fls_s4.slot("discards") = fls.discards;
        fls_s4.slot("discards.n") = fls.discards_n;
        fls_s4.slot("discards.wt") = fls.discards_wt;
        fls_s4.slot("landings") = fls.landings;
        fls_s4.slot("landings.n") = fls.landings_n;
        fls_s4.slot("landings.wt") = fls.landings_wt;
        fls_s4.slot("stock") = fls.stock;
        fls_s4.slot("stock.n") = fls.stock_n;
        fls_s4.slot("stock.wt") = fls.stock_wt;
        fls_s4.slot("m") = fls.m;
        fls_s4.slot("mat") = fls.mat;
        fls_s4.slot("harvest") = fls.harvest;
        fls_s4.slot("harvest.spwn") = fls.harvest_spwn;
        fls_s4.slot("m.spwn") = fls.m_spwn;
        return Rcpp::wrap(fls_s4);
    }
}

