/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../../inst/include/FLFishery.h"

/*-------------------------------------------------------*/
// double

// [[Rcpp::export]]
void test_FLFishery_empty_constructor(){
    FLFishery flf;
    return;
}

// [[Rcpp::export]]
int test_simple_FLFishery_sexp_constructor(SEXP flf_sexp){
    FLFishery flf(flf_sexp);
	return 0;
}

// [[Rcpp::export]]
FLFishery test_FLFishery_sexp_constructor(SEXP flf_sexp){
	FLFishery flf(flf_sexp);
	return flf;
}

// [[Rcpp::export]]
FLFishery test_FLFishery_as_wrap(FLFishery flf){
	return flf;
}

// [[Rcpp::export]]
FLFishery test_FLFishery_copy_constructor(FLFishery flf1){
	FLFishery flf2(flf1); // uses copy constructor
    return flf2;
}

// [[Rcpp::export]]
FLFishery test_FLFishery_assignment_operator(FLFishery flf1){
	FLFishery flf2;
    flf2 = flf1; 
    return flf2;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLFishery_const_catches_get_accessors(const FLFishery flf, int catches, int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(13);
    // members
    out[0] = flf(catches).landings_n()(quant, year, unit, season, area, iter);
    out[1] = flf(catches).discards_n()(quant, year, unit, season, area, iter);
    out[2] = flf(catches).landings_wt()(quant, year, unit, season, area, iter);
    out[3] = flf(catches).discards_wt()(quant, year, unit, season, area, iter);
    out[4] = flf(catches).catch_sel()(quant, year, unit, season, area, iter);
    out[5] = flf(catches).price()(quant, year, unit, season, area, iter);
    // derived members
    out[6] = flf(catches).catches()(1, year, unit, season, area, iter);
    out[7] = flf(catches).catch_n()(quant, year, unit, season, area, iter);
    out[8] = flf(catches).landings()(1, year, unit, season, area, iter);
    out[9] = flf(catches).discards()(1, year, unit, season, area, iter);
    out[10] = flf(catches).landings_sel()(quant, year, unit, season, area, iter);
    out[11] = flf(catches).discards_sel()(quant, year, unit, season, area, iter);
    out[12] = flf(catches).discards_ratio()(quant, year, unit, season, area, iter);
    //out[6] = flc.catch_q()(quant, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLFishery_catches_get_accessors(FLFishery flf, int catches, int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(13);
    // members
    out[0] = flf(catches).landings_n()(quant, year, unit, season, area, iter);
    out[1] = flf(catches).discards_n()(quant, year, unit, season, area, iter);
    out[2] = flf(catches).landings_wt()(quant, year, unit, season, area, iter);
    out[3] = flf(catches).discards_wt()(quant, year, unit, season, area, iter);
    out[4] = flf(catches).catch_sel()(quant, year, unit, season, area, iter);
    out[5] = flf(catches).price()(quant, year, unit, season, area, iter);
    // derived members
    out[6] = flf(catches).catches()(1, year, unit, season, area, iter);
    out[7] = flf(catches).catch_n()(quant, year, unit, season, area, iter);
    out[8] = flf(catches).landings()(1, year, unit, season, area, iter);
    out[9] = flf(catches).discards()(1, year, unit, season, area, iter);
    out[10] = flf(catches).landings_sel()(quant, year, unit, season, area, iter);
    out[11] = flf(catches).discards_sel()(quant, year, unit, season, area, iter);
    out[12] = flf(catches).discards_ratio()(quant, year, unit, season, area, iter);
    //out[6] = flc.catch_q()(quant, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLFishery_const_economics_get_accessors(const FLFishery flf, int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(3);
    out[0] = flf.effort()(1, year, unit, season, area, iter);
    out[1] = flf.vcost()(1, year, unit, season, area, iter);
    out[2] = flf.fcost()(1, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLFishery_economics_get_accessors(FLFishery flf, int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(3);
    out[0] = flf.effort()(1, year, unit, season, area, iter);
    out[1] = flf.vcost()(1, year, unit, season, area, iter);
    out[2] = flf.fcost()(1, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
FLFishery test_FLFishery_set_accessors(FLFishery flf, int catches, int quant, int year, int unit, int season, int area, int iter, double value){
    // catch members
    flf(catches).landings_n()(quant, year, unit, season, area, iter) = value;
    flf(catches).discards_n()(quant, year, unit, season, area, iter) = value;
    flf(catches).landings_wt()(quant, year, unit, season, area, iter) = value;
    flf(catches).discards_wt()(quant, year, unit, season, area, iter) = value;
    flf(catches).catch_sel()(quant, year, unit, season, area, iter) = value;
    flf(catches).price()(quant, year, unit, season, area, iter) = value;
    // economics
    flf.effort()(1, year, unit, season, area, iter) = value;
    flf.vcost()(1, year, unit, season, area, iter) = value;
    flf.fcost()(1, year, unit, season, area, iter) = value;
    return flf;
}

// [[Rcpp::export]]
Rcpp::List test_FLFishery_copy_constructor2(FLFishery flf1, int element, int quant, int year, int unit, int season, int area, int iter, double value){
	FLFishery flf2(flf1); // uses copy constructor
	flf2(element).landings_n()(quant,year,unit,season,area,iter) = value;
	return Rcpp::List::create(Rcpp::Named("flf1", flf1),
				Rcpp::Named("flf2",flf2));
}

// [[Rcpp::export]]
Rcpp::List test_FLFishery_assignment_operator2(FLFishery flf1, int element, int quant, int year, int unit, int season, int area, int iter, double value){
	FLFishery flf2;
    flf2 = flf1; // uses assignment operator;
	flf2(element).landings_n()(quant,year,unit,season,area,iter) = value;
	return Rcpp::List::create(Rcpp::Named("flf1", flf1),
				Rcpp::Named("flf2",flf2));
}

/*-------------------------------------------------------*/
// adouble

// [[Rcpp::export]]
void test_FLFisheryAdolc_empty_constructor(){
    FLFisheryAdolc flf;
    return;
}

// [[Rcpp::export]]
int test_simple_FLFisheryAdolc_sexp_constructor(SEXP flf_sexp){
    FLFisheryAdolc flf(flf_sexp);
	return 0;
}

// [[Rcpp::export]]
FLFisheryAdolc test_FLFisheryAdolc_sexp_constructor(SEXP flf_sexp){
	FLFisheryAdolc flf(flf_sexp);
	return flf;
}

// [[Rcpp::export]]
FLFisheryAdolc test_FLFisheryAdolc_as_wrap(FLFisheryAdolc flf){
	return flf;
}

// [[Rcpp::export]]
FLFisheryAdolc test_FLFisheryAdolc_copy_constructor(FLFisheryAdolc flf1){
	FLFisheryAdolc flf2(flf1); // uses copy constructor
    return flf2;
}

// [[Rcpp::export]]
FLFisheryAdolc test_FLFisheryAdolc_assignment_operator(FLFisheryAdolc flf1){
	FLFisheryAdolc flf2;
    flf2 = flf1; 
    return flf2;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLFisheryAdolc_const_catches_get_accessors(const FLFisheryAdolc flf, int catches, int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(13);
    // members
    out[0] = flf(catches).landings_n()(quant, year, unit, season, area, iter).value();
    out[1] = flf(catches).discards_n()(quant, year, unit, season, area, iter).value();
    out[2] = flf(catches).landings_wt()(quant, year, unit, season, area, iter);
    out[3] = flf(catches).discards_wt()(quant, year, unit, season, area, iter);
    out[4] = flf(catches).catch_sel()(quant, year, unit, season, area, iter);
    out[5] = flf(catches).price()(quant, year, unit, season, area, iter);
    // derived members
    out[6] = flf(catches).catches()(1, year, unit, season, area, iter).value();
    out[7] = flf(catches).catch_n()(quant, year, unit, season, area, iter).value();
    out[8] = flf(catches).landings()(1, year, unit, season, area, iter).value();
    out[9] = flf(catches).discards()(1, year, unit, season, area, iter).value();
    out[10] = flf(catches).landings_sel()(quant, year, unit, season, area, iter).value();
    out[11] = flf(catches).discards_sel()(quant, year, unit, season, area, iter).value();
    out[12] = flf(catches).discards_ratio()(quant, year, unit, season, area, iter).value();
    //out[6] = flc.catch_q()(quant, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLFisheryAdolc_catches_get_accessors(FLFisheryAdolc flf, int catches, int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(13);
    // members
    out[0] = flf(catches).landings_n()(quant, year, unit, season, area, iter).value();
    out[1] = flf(catches).discards_n()(quant, year, unit, season, area, iter).value();
    out[2] = flf(catches).landings_wt()(quant, year, unit, season, area, iter);
    out[3] = flf(catches).discards_wt()(quant, year, unit, season, area, iter);
    out[4] = flf(catches).catch_sel()(quant, year, unit, season, area, iter);
    out[5] = flf(catches).price()(quant, year, unit, season, area, iter);
    // derived members
    out[6] = flf(catches).catches()(1, year, unit, season, area, iter).value();
    out[7] = flf(catches).catch_n()(quant, year, unit, season, area, iter).value();
    out[8] = flf(catches).landings()(1, year, unit, season, area, iter).value();
    out[9] = flf(catches).discards()(1, year, unit, season, area, iter).value();
    out[10] = flf(catches).landings_sel()(quant, year, unit, season, area, iter).value();
    out[11] = flf(catches).discards_sel()(quant, year, unit, season, area, iter).value();
    out[12] = flf(catches).discards_ratio()(quant, year, unit, season, area, iter).value();
    //out[6] = flc.catch_q()(quant, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLFisheryAdolc_const_economics_get_accessors(const FLFisheryAdolc flf, int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(3);
    out[0] = flf.effort()(1, year, unit, season, area, iter);
    out[1] = flf.vcost()(1, year, unit, season, area, iter);
    out[2] = flf.fcost()(1, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
Rcpp::NumericVector test_FLFisheryAdolc_economics_get_accessors(FLFisheryAdolc flf, int quant, int year, int unit, int season, int area, int iter){
    Rcpp::NumericVector out(3);
    out[0] = flf.effort()(1, year, unit, season, area, iter);
    out[1] = flf.vcost()(1, year, unit, season, area, iter);
    out[2] = flf.fcost()(1, year, unit, season, area, iter);
    return out;
}

// [[Rcpp::export]]
FLFisheryAdolc test_FLFisheryAdolc_set_accessors(FLFisheryAdolc flf, int catches, int quant, int year, int unit, int season, int area, int iter, double value){
    adouble ad_value = value;
    // catch members
    flf(catches).landings_n()(quant, year, unit, season, area, iter) = ad_value;
    flf(catches).discards_n()(quant, year, unit, season, area, iter) = ad_value;
    flf(catches).landings_wt()(quant, year, unit, season, area, iter) = value;
    flf(catches).discards_wt()(quant, year, unit, season, area, iter) = value;
    flf(catches).catch_sel()(quant, year, unit, season, area, iter) = value;
    flf(catches).price()(quant, year, unit, season, area, iter) = value;
    // economics
    flf.effort()(1, year, unit, season, area, iter) = value;
    flf.vcost()(1, year, unit, season, area, iter) = value;
    flf.fcost()(1, year, unit, season, area, iter) = value;
    return flf;
}

// [[Rcpp::export]]
Rcpp::List test_FLFisheryAdolc_copy_constructor2(FLFisheryAdolc flf1, int element, int quant, int year, int unit, int season, int area, int iter, double value){
    adouble ad_value = value;
	FLFisheryAdolc flf2(flf1); // uses copy constructor
	flf2(element).landings_n()(quant,year,unit,season,area,iter) = ad_value;
	return Rcpp::List::create(Rcpp::Named("flf1", flf1),
				Rcpp::Named("flf2",flf2));
}

// [[Rcpp::export]]
Rcpp::List test_FLFisheryAdolc_assignment_operator2(FLFisheryAdolc flf1, int element, int quant, int year, int unit, int season, int area, int iter, double value){
    adouble ad_value = value;
	FLFisheryAdolc flf2;
    flf2 = flf1; // uses assignment operator;
	flf2(element).landings_n()(quant,year,unit,season,area,iter) = ad_value;
	return Rcpp::List::create(Rcpp::Named("flf1", flf1),
				Rcpp::Named("flf2",flf2));
}

//---------------------------------------------------------------------------------------
// FLFisheries - double

// [[Rcpp::export]]
FLFisheries test_FLFisheries_sexp_constructor(SEXP flfs_sexp1){
	FLFisheries flfs(flfs_sexp1);
	return flfs;
}

// [[Rcpp::export]]
FLFisheries test_FLFisheries_as_wrap(FLFisheries flfs){
    return flfs;
}

// [[Rcpp::export]]
int test_FLFisheries_get_nfisheries(FLFisheries flfs){
    int length = flfs.get_nfisheries();
	return length;
}


// [[Rcpp::export]]
FLFisheries test_FLFisheries_copy_constructor(FLFisheries flfs){
    FLFisheries out(flfs);
    return out;
}

// Checking that a deep copy has been made
// [[Rcpp::export]]
Rcpp::List test_FLFisheries_copy_constructor2(FLFisheries flfs1, const int fishery, const int catches, const Rcpp::IntegerVector indices, double value){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    FLFisheries flfs2(flfs1); // Copy
    flfs2(fishery)(catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]) = value;
	return Rcpp::List::create(Rcpp::Named("flfs1", flfs1),
                            Rcpp::Named("flfs2",flfs2));
}


// [[Rcpp::export]]
FLFisheries test_FLFisheries_assignment_operator(FLFisheries flfs){
    FLFisheries out;
    out = flfs;
    return out;
}

// Checking that a deep copy has been made
// [[Rcpp::export]]
Rcpp::List test_FLFisheries_assignment_operator2(FLFisheries flfs1, const int fishery, const int catches, const Rcpp::IntegerVector indices, double value){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    FLFisheries flfs2; 
    flfs2 = flfs1;
    flfs2(fishery)(catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]) = value;
	return Rcpp::List::create(Rcpp::Named("flfs1", flfs1),
                            Rcpp::Named("flfs2",flfs2));
}

// Const get everything
// [[Rcpp::export]]
Rcpp::List test_FLFisheries_const_get_single(const FLFisheries flfs, const int fishery, const int catches, const Rcpp::IntegerVector indices){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    FLFishery flf = flfs(fishery);
    FLCatch flc = flfs(fishery)(catches);
    FLQuant landings_n = flfs(fishery)(catches).landings_n();
    double value = flfs(fishery)(catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]);
    return Rcpp::List::create(Rcpp::Named("flf",flf),
            Rcpp::Named("flc", flc),
            Rcpp::Named("landings_n", landings_n),
            Rcpp::Named("value", value));
}

// get everything
// [[Rcpp::export]]
Rcpp::List test_FLFisheries_get_single(FLFisheries flfs, const int fishery, const int catches, const Rcpp::IntegerVector indices){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    FLFishery flf = flfs(fishery);
    FLCatch flc = flfs(fishery)(catches);
    FLQuant landings_n = flfs(fishery)(catches).landings_n();
    //double value = flfs(fishery)(catches).landings_n()(indices[0],indices[1],indices[2],indices[3],indices[4],indices[5]);
    double value = flfs(fishery)(catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]);
    return Rcpp::List::create(Rcpp::Named("flf",flf),
            Rcpp::Named("flc", flc),
            Rcpp::Named("landings_n", landings_n),
            Rcpp::Named("value", value));
}

// [[Rcpp::export]]
Rcpp::List test_FLFisheries_const_get_double(const FLFisheries flfs, const int fishery, const int catches, const Rcpp::IntegerVector indices){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    FLFishery flf = flfs(fishery);
    FLCatch flc = flfs(fishery, catches);
    FLQuant landings_n = flfs(fishery, catches).landings_n();
    double value = flfs(fishery, catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]);
    return Rcpp::List::create(Rcpp::Named("flf",flf),
            Rcpp::Named("flc", flc),
            Rcpp::Named("landings_n", landings_n),
            Rcpp::Named("value", value));
}

// [[Rcpp::export]]
Rcpp::List test_FLFisheries_get_double(FLFisheries flfs, const int fishery, const int catches, const Rcpp::IntegerVector indices){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    FLFishery flf = flfs(fishery);
    FLCatch flc = flfs(fishery, catches);
    FLQuant landings_n = flfs(fishery, catches).landings_n();
    double value = flfs(fishery, catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]);
    return Rcpp::List::create(Rcpp::Named("flf",flf),
            Rcpp::Named("flc", flc),
            Rcpp::Named("landings_n", landings_n),
            Rcpp::Named("value", value));
}

// [[Rcpp::export]]
FLFisheries test_FLFisheries_set_single(FLFisheries flfs, const int fishery, const int catches, const Rcpp::IntegerVector indices, double value){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    flfs(fishery)(catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]) = value;
    return flfs;
}

// [[Rcpp::export]]
FLFisheries test_FLFisheries_set_double(FLFisheries flfs, const int fishery, const int catches, const Rcpp::IntegerVector indices, double value){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    flfs(fishery, catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]) = value;
    return flfs;
}

//---------------------------------------------------------------------------
// FLFisheries - adouble

// [[Rcpp::export]]
FLFisheriesAdolc test_FLFisheriesAdolc_sexp_constructor(SEXP flfs_sexp1){
	FLFisheriesAdolc flfs(flfs_sexp1);
	return flfs;
}

// [[Rcpp::export]]
FLFisheriesAdolc test_FLFisheriesAdolc_as_wrap(FLFisheriesAdolc flfs){
    return flfs;
}

// [[Rcpp::export]]
int test_FLFisheriesAdolc_get_nfisheries(FLFisheriesAdolc flfs){
    int length = flfs.get_nfisheries();
	return length;
}


// [[Rcpp::export]]
FLFisheriesAdolc test_FLFisheriesAdolc_copy_constructor(FLFisheriesAdolc flfs){
    FLFisheriesAdolc out(flfs);
    return out;
}

// Checking that a deep copy has been made
// [[Rcpp::export]]
Rcpp::List test_FLFisheriesAdolc_copy_constructor2(FLFisheriesAdolc flfs1, const int fishery, const int catches, const Rcpp::IntegerVector indices, double value){
    adouble ad_value = value;
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    FLFisheriesAdolc flfs2(flfs1); // Copy
    flfs2(fishery)(catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]) = ad_value;
	return Rcpp::List::create(Rcpp::Named("flfs1", flfs1),
                            Rcpp::Named("flfs2",flfs2));
}


// [[Rcpp::export]]
FLFisheriesAdolc test_FLFisheriesAdolc_assignment_operator(FLFisheriesAdolc flfs){
    FLFisheriesAdolc out;
    out = flfs;
    return out;
}

// Checking that a deep copy has been made
// [[Rcpp::export]]
Rcpp::List test_FLFisheriesAdolc_assignment_operator2(FLFisheriesAdolc flfs1, const int fishery, const int catches, const Rcpp::IntegerVector indices, double value){
    adouble ad_value = value;
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    FLFisheriesAdolc flfs2; 
    flfs2 = flfs1;
    flfs2(fishery)(catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]) = ad_value;
	return Rcpp::List::create(Rcpp::Named("flfs1", flfs1),
                            Rcpp::Named("flfs2",flfs2));
}

// Const get everything
// [[Rcpp::export]]
Rcpp::List test_FLFisheriesAdolc_const_get_single(const FLFisheriesAdolc flfs, const int fishery, const int catches, const Rcpp::IntegerVector indices){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    FLFisheryAdolc flf = flfs(fishery);
    FLCatchAdolc flc = flfs(fishery)(catches);
    FLQuantAdolc landings_n = flfs(fishery)(catches).landings_n();
    double value = flfs(fishery)(catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]).value();
    return Rcpp::List::create(Rcpp::Named("flf",flf),
            Rcpp::Named("flc", flc),
            Rcpp::Named("landings_n", landings_n),
            Rcpp::Named("value", value));
}

// get everything
// [[Rcpp::export]]
Rcpp::List test_FLFisheriesAdolc_get_single(FLFisheriesAdolc flfs, const int fishery, const int catches, const Rcpp::IntegerVector indices){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    FLFisheryAdolc flf = flfs(fishery);
    FLCatchAdolc flc = flfs(fishery)(catches);
    FLQuantAdolc landings_n = flfs(fishery)(catches).landings_n();
    //double value = flfs(fishery)(catches).landings_n()(indices[0],indices[1],indices[2],indices[3],indices[4],indices[5]);
    double value = flfs(fishery)(catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]).value();
    return Rcpp::List::create(Rcpp::Named("flf",flf),
            Rcpp::Named("flc", flc),
            Rcpp::Named("landings_n", landings_n),
            Rcpp::Named("value", value));
}

// [[Rcpp::export]]
Rcpp::List test_FLFisheriesAdolc_const_get_double(const FLFisheriesAdolc flfs, const int fishery, const int catches, const Rcpp::IntegerVector indices){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    FLFisheryAdolc flf = flfs(fishery);
    FLCatchAdolc flc = flfs(fishery, catches);
    FLQuantAdolc landings_n = flfs(fishery, catches).landings_n();
    double value = flfs(fishery, catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]).value();
    return Rcpp::List::create(Rcpp::Named("flf",flf),
            Rcpp::Named("flc", flc),
            Rcpp::Named("landings_n", landings_n),
            Rcpp::Named("value", value));
}

// [[Rcpp::export]]
Rcpp::List test_FLFisheriesAdolc_get_double(FLFisheriesAdolc flfs, const int fishery, const int catches, const Rcpp::IntegerVector indices){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    FLFisheryAdolc flf = flfs(fishery);
    FLCatchAdolc flc = flfs(fishery, catches);
    FLQuantAdolc landings_n = flfs(fishery, catches).landings_n();
    double value = flfs(fishery, catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]).value();
    return Rcpp::List::create(Rcpp::Named("flf",flf),
            Rcpp::Named("flc", flc),
            Rcpp::Named("landings_n", landings_n),
            Rcpp::Named("value", value));
}

// [[Rcpp::export]]
FLFisheriesAdolc test_FLFisheriesAdolc_set_single(FLFisheriesAdolc flfs, const int fishery, const int catches, const Rcpp::IntegerVector indices, double value){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    flfs(fishery)(catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]) = value;
    return flfs;
}

// [[Rcpp::export]]
FLFisheriesAdolc test_FLFisheriesAdolc_set_double(FLFisheriesAdolc flfs, const int fishery, const int catches, const Rcpp::IntegerVector indices, double value){
    std::vector<int> std_indices = Rcpp::as<std::vector<int> > (indices);
    flfs(fishery, catches).landings_n()(std_indices[0],std_indices[1],std_indices[2],std_indices[3],std_indices[4],std_indices[5]) = value;
    return flfs;
}

