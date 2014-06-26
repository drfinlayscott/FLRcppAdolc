/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../../inst/include/projection.h"

// [[Rcpp::export]]
int test_year_season_to_timestep_FLQuant_double(FLQuant flq, const int year, const int season){
    int timestep = 0;
    year_season_to_timestep(year, season, flq, timestep);
    return timestep;
}

// [[Rcpp::export]]
int test_year_season_to_timestep_FLQuant_adouble(FLQuantAdolc flqad, const int year, const int season){
    int timestep = 0;
    year_season_to_timestep(year, season, flqad, timestep);
    return timestep;
}

// [[Rcpp::export]]
int test_year_season_to_timestep(FLQuant flq, const int year, const int season){
    int timestep = 0;
    year_season_to_timestep(year, season, flq.get_nseason(), timestep);
    return timestep;
}

// [[Rcpp::export]]
Rcpp::IntegerVector test_timestep_to_year_season_FLQuant_double(FLQuant flq, const int timestep){
    int year = 0;
    int season = 0;
    timestep_to_year_season(timestep, flq, year, season);
    Rcpp::IntegerVector out(2);
    out[0] = year;
    out[1] = season;
    return out;
}

// [[Rcpp::export]]
Rcpp::IntegerVector test_timestep_to_year_season_FLQuant_adouble(FLQuantAdolc flqad, const int timestep){
    int year = 0;
    int season = 0;
    timestep_to_year_season(timestep, flqad, year, season);
    Rcpp::IntegerVector out(2);
    out[0] = year;
    out[1] = season;
    return out;
}

// [[Rcpp::export]]
Rcpp::IntegerVector test_timestep_to_year_season(FLQuant flq, const int timestep){
    int year = 0;
    int season = 0;
    timestep_to_year_season(timestep, flq.get_nseason(), year, season);
    Rcpp::IntegerVector out(2);
    out[0] = year;
    out[1] = season;
    return out;
}


// [[Rcpp::export]]
double test_euclid_norm(std::vector<double> xvec){
    int size_x = xvec.size();
    double* x = new double[size_x];
    for (int i=0; i < size_x; ++i){
        x[i] = xvec[i];
    }
    double norm = euclid_norm(x, size_x);
    return norm;
}

//--------------------------------------------------------------------
// Newton-Raphson tests

// Simple 1D: 3x^2 - 4x - 4
// [[Rcpp::export]]
Rcpp::List test_NR1(const double initial_value, const int max_iters, const double max_limit, const double tolerance){

// f(x) = x^3 - 2x + 2, take 0 as starting point = infinite cycle
//
// f1(x1,x2) = x1^2 + x2^2 - 4 = 
// f2(x1,x2) = x1^2 - x2 + 1 = 0

    double final_value;
    adouble x, y;
    int tape = 1;
    trace_on(tape);
    x <<= initial_value;
    y = 3*pow(x,2) - 4*x - 4; 
    y >>= final_value;
    trace_off();
    std::vector<double> xvec(1);
    xvec[0] = initial_value;
    int out = newton_raphson(xvec, tape, max_iters, max_limit, tolerance);
	return Rcpp::List::create(Rcpp::Named("x", xvec),
                            Rcpp::Named("out",out));
}


// Simple 2D: solution: +- 0.8895, 1.7913
// [[Rcpp::export]]
Rcpp::List test_NR2(std::vector<double> initial_value, const int max_iters, const double max_limit, const double tolerance){
    // f(x) = x^3 - 2x + 2, take 0 as starting point = infinite cycle
    std::vector<double> final_value(2);
    adouble *x = new adouble[2];
    adouble *y = new adouble[2];
    int tape = 1;
    trace_on(tape);
    for (int i=0; i<2; ++i){
        x[i] <<= initial_value[i];
    }
    y[0] = pow(x[0],2) + pow(x[1],2) - 4; // A circle!
    y[1] = pow(x[0],2) - x[1] + 1;
    for (int i=0; i<2; ++i){
        y[i] >>= final_value[i];
    }
    trace_off();
    int out = newton_raphson(initial_value, tape, max_iters, max_limit, tolerance);
	return Rcpp::List::create(Rcpp::Named("x", initial_value),
                            Rcpp::Named("out",out));
}

