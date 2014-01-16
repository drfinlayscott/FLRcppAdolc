/* 
 * Copyright 2013 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */


#include "../../inst/include/fwdBiol.h"

/*-------------------------------------------------------*/
// Templated class tests

// [[Rcpp::export]]
fwdBiol test_fwdBiol_sexp_constructor(SEXP flb_sexp){
	fwdBiol fwdb(flb_sexp);
	return fwdb;
}

// [[Rcpp::export]]
fwdBiolAdolc test_fwdBiolAdolc_sexp_constructor(SEXP flb_sexp){
	fwdBiolAdolc fwdb(flb_sexp);
	return fwdb;
}

// [[Rcpp::export]]
fwdBiol test_fwdBiol_as_wrap(fwdBiol fwdb){
	return fwdb;
}

// [[Rcpp::export]]
fwdBiolAdolc test_fwdBiolAdolc_as_wrap(fwdBiolAdolc fwdb){
	return fwdb;
}

// [[Rcpp::export]]
fwdBiol test_fwdBiol_copy_constructor(fwdBiol fwdb1){
	fwdBiol fwdb2(fwdb1); // uses copy constructor
    return fwdb2;
}

// [[Rcpp::export]]
fwdBiolAdolc test_fwdBiolAdolc_copy_constructor(fwdBiolAdolc fwdb1){
	fwdBiolAdolc fwdb2(fwdb1); // uses copy constructor
    return fwdb2;
}

// [[Rcpp::export]]
Rcpp::List test_fwdBiol_copy_constructor2(fwdBiol fwdb1, int quant, int year, int unit, int season, int area, int iter, double value){
	fwdBiol fwdb2(fwdb1); // uses copy constructor
	fwdb2.n()(quant,year,unit,season,area,iter) = value;
	return Rcpp::List::create(Rcpp::Named("fwdb1", fwdb1),
				Rcpp::Named("fwdb2",fwdb2));
}

// [[Rcpp::export]]
Rcpp::List test_fwdBiolAdolc_copy_constructor2(fwdBiolAdolc fwdb1, int quant, int year, int unit, int season, int area, int iter, double value){
    adouble value_ad = value;
	fwdBiolAdolc fwdb2(fwdb1); // uses copy constructor
	fwdb2.n()(quant,year,unit,season,area,iter) = value_ad;
	return Rcpp::List::create(Rcpp::Named("fwdb1", fwdb1),
				Rcpp::Named("fwdb2",fwdb2));
}

// [[Rcpp::export]]
fwdBiol test_fwdBiol_assignment_operator(fwdBiol fwdb1){
	fwdBiol fwdb2 = fwdb1; 
    return fwdb2;
}

// [[Rcpp::export]]
fwdBiolAdolc test_fwdBiolAdolc_assignment_operator(fwdBiolAdolc fwdb1){
	fwdBiolAdolc fwdb2 = fwdb1; 
    return fwdb2;
}

// [[Rcpp::export]]
Rcpp::List test_fwdBiol_assignment_operator2(fwdBiol fwdb1, int quant, int year, int unit, int season, int area, int iter, double value){
	fwdBiol fwdb2 = fwdb1; 
	fwdb2.n()(quant,year,unit,season,area,iter) = value;
	return Rcpp::List::create(Rcpp::Named("fwdb1", fwdb1),
				Rcpp::Named("fwdb2",fwdb2));
}

// [[Rcpp::export]]
Rcpp::List test_fwdBiolAdolc_assignment_operator2(fwdBiolAdolc fwdb1, int quant, int year, int unit, int season, int area, int iter, double value){
    adouble value_ad = value;
	fwdBiolAdolc fwdb2 = fwdb1; 
	fwdb2.n()(quant,year,unit,season,area,iter) = value_ad;
	return Rcpp::List::create(Rcpp::Named("fwdb1", fwdb1),
				Rcpp::Named("fwdb2",fwdb2));
}

// [[Rcpp::export]]
Rcpp::NumericVector test_fwdBiol_get_accessors(fwdBiol fwdb,int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(5);
    out[0] = fwdb.n()(quant, year, unit, season, area, iter);
    out[1] = fwdb.m()(quant, year, unit, season, area, iter);
    out[2] = fwdb.wt()(quant, year, unit, season, area, iter);
    out[3] = fwdb.fec()(quant, year, unit, season, area, iter);
    out[4] = fwdb.spwn()(quant, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_fwdBiolAdolc_get_accessors(fwdBiolAdolc fwdb,int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(5);
    out[0] = fwdb.n()(quant, year, unit, season, area, iter).value();
    out[1] = fwdb.m()(quant, year, unit, season, area, iter);
    out[2] = fwdb.wt()(quant, year, unit, season, area, iter);
    out[3] = fwdb.fec()(quant, year, unit, season, area, iter);
    out[4] = fwdb.spwn()(quant, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
fwdBiol test_fwdBiol_set_accessors(fwdBiol fwdb, int quant, int year, int unit, int season, int area, int iter, Rcpp::NumericVector values){
    fwdb.n()(quant, year, unit, season, area, iter) = values[0];
    fwdb.m()(quant, year, unit, season, area, iter) = values[1];
    fwdb.wt()(quant, year, unit, season, area, iter) = values[2];
    fwdb.fec()(quant, year, unit, season, area, iter) = values[3];
    fwdb.spwn()(quant, year, unit, season, area, iter) = values[4];
    return fwdb;
}

// [[Rcpp::export]]
fwdBiolAdolc test_fwdBiolAdolc_set_accessors(fwdBiolAdolc fwdb, int quant, int year, int unit, int season, int area, int iter, Rcpp::NumericVector values){
    adouble value_ad = values[0];
    fwdb.n()(quant, year, unit, season, area, iter) = value_ad;
    fwdb.m()(quant, year, unit, season, area, iter) = values[1];
    fwdb.wt()(quant, year, unit, season, area, iter) = values[2];
    fwdb.fec()(quant, year, unit, season, area, iter) = values[3];
    fwdb.spwn()(quant, year, unit, season, area, iter) = values[4];
    return fwdb;
}



/*------------------------------------------------------*/

/*
// operating_model tests

// [[Rcpp::export]]
fwdBiol_Adolc test_operating_model_constructors(fwdBiol_Adolc fwdb){
    Rprintf("Making an empty operating_model\n");
    operating_model om1;
    Rprintf("Making an operating_model with a fwdBiol\n");
    operating_model om2(fwdb);
    fwdBiol_Adolc fwdb2 = om2.get_biol();
    //fwdb2 = om2.get_biol();
    return fwdb2;
}

// [[Rcpp::export]]
Rcpp::List test_timestep_to_year_operating_model(const fwdBiol_Adolc fwdb, const int timestep){
    Rprintf("Making the om with a fwdBiol\n");
    operating_model om(fwdb);
    int year=0;
    int season=0;
    Rprintf("Getting year and season\n");
    om.timestep_to_year_season(timestep, year, season);
	return Rcpp::List::create(Rcpp::Named("year", year),
				Rcpp::Named("season", season));
}
*/
/*------------------------------------------------------*/
/*
// Multidim tests
// [[Rcpp::export]]
Rcpp::List test_7dim_FLQuant(const FLQuant flq1, const FLQuant flq2){
    vector<FLQuant> flq7(2);
    flq7[0] = flq1;
    flq7[1] = flq2;
	return Rcpp::List::create(Rcpp::Named("flq1", flq7[0]),
				Rcpp::Named("flq2", flq7[1]));
}

// [[Rcpp::export]]
Rcpp::List test_8dim_FLQuant(const FLQuant flq1, const FLQuant flq2, const FLQuant flq3, const FLQuant flq4){
    vector< vector<FLQuant> > flq8(2, vector<FLQuant>(2)); // Note space between > >
    flq8[0][0] = flq1;
    flq8[1][0] = flq2;
    flq8[0][1] = flq3;
    flq8[1][1] = flq4;
	return Rcpp::List::create(Rcpp::Named("flq1", flq8[0][0]),
				              Rcpp::Named("flq2", flq8[1][0]),
                              Rcpp::Named("flq3", flq8[0][1]),
				              Rcpp::Named("flq4", flq8[1][1]));
}

// [[Rcpp::export]]
double test_8dim_FLQuant_double(const FLQuant flq1, const FLQuant flq2, const FLQuant flq3, const FLQuant flq4){
    vector< vector<FLQuant> > flq8(2, vector<FLQuant>(2)); // Note space between > >
    flq8[0][0] = flq1;
    flq8[1][0] = flq2;
    flq8[0][1] = flq3;
    flq8[1][1] = flq4;
	return flq8[0][0](4,10,1,1,1,1);
}
*/

// This works but accessing is awkward (mix of [] and ()
// Want an accessor that goes (,,,,,,,,,)
/* () accessors */
// T operator () (const unsigned int element) const; // only gets an element so const reinforced - - however cannot return reference due to NumericVector() operator
// T operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter) const; // only gets an element so const reinforced - however cannot return reference due to NumericVector() operator
// T& operator () (const unsigned int element); // gets and sets an element so const not reinforced
// T& operator () (const unsigned int quant, const unsigned int year, const unsigned int unit, const unsigned int season, const unsigned int area, const unsigned int iter); // gets and sets an element so const not reinforced

// Accessors for FLQuant7
// (int) - returns whole FLQuant
// (int, int, int, int, int, int, int) - returns value

// Accessors for FLQuant8
// (int,int) - returns whole FLQuant
// (int, int, int, int, int, int, int, int) - returns value

//// [[Rcpp::export]]
//fwdBiol_Adolc test_fwdBiols(const fwdBiol_Adolc fwdb1, const fwdBiol_Adolc fwdb2){
//    vector<fwdBiol_Adolc> fwdbs(2); 
//    fwdbs[0] = fwdb1;
//    fwdbs[1] = fwdb2;
//    return fwdbs[1];
//}

/*------------------------------------------------------*/
// Original, non-templated version
/*

// [[Rcpp::export]]
FLQuant test_fwdBiol_sexp_constructor(SEXP flb_sexp){
	fwdBiol fwdb(flb_sexp);
	return fwdb.n;
}

// [[Rcpp::export]]
fwdBiol test_fwdBiol_wrap(SEXP flb_sexp){
	fwdBiol fwdb(flb_sexp);
	return fwdb;
}

// [[Rcpp::export]]
FLQuant test_fwdBiol_as(fwdBiol fwdb){
	return fwdb.n;
}

// [[Rcpp::export]]
fwdBiol test_fwdBiol_as_wrap(fwdBiol fwdb){
	return fwdb;
}


// [[Rcpp::export]]
Rcpp::List test_fwdBiol_copy_constructor(fwdBiol fwdb1, int quant, int year, int unit, int season, int area, int iter, double value){
	fwdBiol fwdb2(fwdb1); // uses copy constructor
	fwdb2.n(quant,year,unit,season,area,iter) = value;
	return Rcpp::List::create(Rcpp::Named("fwdb1", fwdb1),
				Rcpp::Named("fwdb2",fwdb2));
}

// [[Rcpp::export]]
Rcpp::List test_fwdBiol_assignment_operator(fwdBiol fwdb1, int quant, int year, int unit, int season, int area, int iter, double value){
	fwdBiol fwdb2;
    fwdb2 = fwdb1; 
	fwdb2.n(quant,year,unit,season,area,iter) = value;
	return Rcpp::List::create(Rcpp::Named("fwdb1", fwdb1),
				Rcpp::Named("fwdb2",fwdb2));
}

*/

