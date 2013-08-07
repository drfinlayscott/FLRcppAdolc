/* 
 * Copyright 2013 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../../inst/include/FLQuant_base.h"

/* There are 18 options per operator
 * For example, consider the '*' operator:
 * 6 operator assignment
 * FLQ   = FLQ     *= FLQ
 * FLQAD = FLQAD   *= FLQ
 * FLQAD = FLQAD   *= FLQAD
 * FLQ   = FLQ     *= double
 * FLQAD = FLQAD   *= double
 * FLQAD = FLQAD   *= adouble
 * 4 binary 'FLQ FLQ' arithmetic operator
 * FLQ   = FLQ     *  FLQ
 * FLQAD = FLQAD   *  FLQ
 * FLQAD = FLQ     *  FLQAD
 * FLQAD = FLQAD   *  FLQAD
 * 8 binary 'FLQ scalar' arithmetic operator
 * FLQ   = FLQ     *  double
 * FLQ   = double  *  FLQ
 * FLQAD = FLQAD   *  double
 * FLQAD = double  *  FLQAD
 * FLQAD = FLQ     *  adouble
 * FLQAD = adouble *  FLQ
 * FLQAD = FLQAD   *  adouble
 * FLQAD = adouble *  FLQAD
 */

//------------------ Multiplication ----------------------

/* Multiplication assignment
 * 6 of them
 */

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_multiplier_assignment_operator(FLQuant flq1, FLQuant flq2){
    flq1 *= flq2;
    return flq1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuant_multiplier_assignment_operator(FLQuantAdolc flqad1, FLQuant flq2){
    flqad1 *= flq2;
    return flqad1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuantAdolc_multiplier_assignment_operator(FLQuantAdolc flqad1, FLQuantAdolc flqad2){
    flqad1 *= flqad2;
    return flqad1;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_multiplier_assignment_operator(FLQuant flq1, double value){
    flq1 *= value;
    return flq1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_double_multiplier_assignment_operator(FLQuantAdolc flqad1, double value){
    flqad1 *= value;
    return flqad1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_adouble_multiplier_assignment_operator(FLQuantAdolc flqad1, double value){
    adouble ad_value = value;
    flqad1 *= ad_value;
    return flqad1;
}

/* Doesn't compile; which is good as it isn't supposed to. Just checking understanding of the member method.
// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuantAdolc_multiplier_assignment_operator(FLQuant flq1, FLQuantAdolc flqad2){
    flq1 *= flqad2;
    return flq1;
}
*/

/* Binary Multiplication
 * 12 of them
 */

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_multiplier_operator(FLQuant flq1, FLQuant flq2){
    FLQuant flq3 = flq1 * flq2;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuant_multiplier_operator(FLQuantAdolc flqad1, FLQuant flq2){
    FLQuantAdolc flqad3;
    flqad3 = flqad1 * flq2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuant_FLQuantAdolc_multiplier_operator(FLQuant flq1, FLQuantAdolc flqad2){
    FLQuantAdolc flqad3;
    flqad3 = flq1 * flqad2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuantAdolc_multiplier_operator(FLQuantAdolc flqad1, FLQuantAdolc flqad2){
    FLQuantAdolc flqad3;
    flqad3 = flqad1 * flqad2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_multiplier_operator(FLQuant flq1, double value){
    FLQuant flq3 = flq1 * value;
    return flq3;
}

// [[Rcpp::export]]
FLQuant test_double_FLQuant_multiplier_operator(double value, FLQuant flq1){
    FLQuant flq3 = value * flq1;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_double_FLQuantAdolc_multiplier_operator(double value, FLQuantAdolc flq1){
    FLQuantAdolc flq3 = value * flq1;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_double_multiplier_operator(FLQuantAdolc flq1, double value){
    FLQuantAdolc flq3;
    flq1 * value;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuant_adouble_multiplier_operator(FLQuant flq1, double value){
    adouble ad_value = value;
    FLQuantAdolc flq3 = flq1 * ad_value;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_adouble_FLQuant_multiplier_operator(double value, FLQuant flq1){
    adouble ad_value = value;
    FLQuantAdolc flq3 = ad_value * flq1;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_adouble_multiplier_operator(FLQuantAdolc flq1, double value){
    adouble ad_value = value;
    FLQuantAdolc flq3 = flq1 * ad_value;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_adouble_FLQuantAdolc_multiplier_operator(double value, FLQuantAdolc flq1){
    adouble ad_value = value;
    FLQuantAdolc flq3 = ad_value * flq1;
    return flq3;
}

//------------------ Division ----------------------

/* Division assignment
 * 6 of them
 */

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_division_assignment_operator(FLQuant flq1, FLQuant flq2){
    flq1 /= flq2;
    return flq1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuant_division_assignment_operator(FLQuantAdolc flqad1, FLQuant flq2){
    flqad1 /= flq2;
    return flqad1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuantAdolc_division_assignment_operator(FLQuantAdolc flqad1, FLQuantAdolc flqad2){
    flqad1 /= flqad2;
    return flqad1;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_division_assignment_operator(FLQuant flq1, double value){
    flq1 /= value;
    return flq1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_double_division_assignment_operator(FLQuantAdolc flqad1, double value){
    flqad1 /= value;
    return flqad1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_adouble_division_assignment_operator(FLQuantAdolc flqad1, double value){
    adouble ad_value = value;
    flqad1 /= ad_value;
    return flqad1;
}

/* Binary division
 * 12 of them
 */

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_division_operator(FLQuant flq1, FLQuant flq2){
    FLQuant flq3 = flq1 / flq2;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuant_division_operator(FLQuantAdolc flqad1, FLQuant flq2){
    FLQuantAdolc flqad3;
    flqad3 = flqad1 / flq2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuant_FLQuantAdolc_division_operator(FLQuant flq1, FLQuantAdolc flqad2){
    FLQuantAdolc flqad3;
    flqad3 = flq1 / flqad2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuantAdolc_division_operator(FLQuantAdolc flqad1, FLQuantAdolc flqad2){
    FLQuantAdolc flqad3;
    flqad3 = flqad1 / flqad2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_division_operator(FLQuant flq1, double value){
    FLQuant flq3 = flq1 / value;
    return flq3;
}

// [[Rcpp::export]]
FLQuant test_double_FLQuant_division_operator(double value, FLQuant flq1){
    FLQuant flq3 = value / flq1;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_double_FLQuantAdolc_division_operator(double value, FLQuantAdolc flq1){
    FLQuantAdolc flq3 = value / flq1;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_double_division_operator(FLQuantAdolc flq1, double value){
    FLQuantAdolc flq3 = flq1 / value;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuant_adouble_division_operator(FLQuant flq1, double value){
    adouble ad_value = value;
    FLQuantAdolc flq3 = flq1 / ad_value;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_adouble_FLQuant_division_operator(double value, FLQuant flq1){
    adouble ad_value = value;
    FLQuantAdolc flq3 = ad_value / flq1;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_adouble_division_operator(FLQuantAdolc flq1, double value){
    adouble ad_value = value;
    FLQuantAdolc flq3 = flq1 / ad_value;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_adouble_FLQuantAdolc_division_operator(double value, FLQuantAdolc flq1){
    adouble ad_value = value;
    FLQuantAdolc flq3 = ad_value / flq1;
    return flq3;
}

//------------------ Subtraction ----------------------

/* Subtraction assignment
 * 6 of them
 */

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_subtraction_assignment_operator(FLQuant flq1, FLQuant flq2){
    flq1 -= flq2;
    return flq1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuant_subtraction_assignment_operator(FLQuantAdolc flqad1, FLQuant flq2){
    flqad1 -= flq2;
    return flqad1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuantAdolc_subtraction_assignment_operator(FLQuantAdolc flqad1, FLQuantAdolc flqad2){
    flqad1 -= flqad2;
    return flqad1;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_subtraction_assignment_operator(FLQuant flq1, double value){
    flq1 -= value;
    return flq1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_double_subtraction_assignment_operator(FLQuantAdolc flqad1, double value){
    flqad1 -= value;
    return flqad1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_adouble_subtraction_assignment_operator(FLQuantAdolc flqad1, double value){
    adouble ad_value = value;
    flqad1 -= ad_value;
    return flqad1;
}

/* Binary subtraction
 * 12 of them
 */

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_subtraction_operator(FLQuant flq1, FLQuant flq2){
    FLQuant flq3 = flq1 - flq2;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuant_subtraction_operator(FLQuantAdolc flqad1, FLQuant flq2){
    FLQuantAdolc flqad3;
    flqad3 = flqad1 - flq2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuant_FLQuantAdolc_subtraction_operator(FLQuant flq1, FLQuantAdolc flqad2){
    FLQuantAdolc flqad3;
    flqad3 = flq1 - flqad2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuantAdolc_subtraction_operator(FLQuantAdolc flqad1, FLQuantAdolc flqad2){
    FLQuantAdolc flqad3;
    flqad3 = flqad1 - flqad2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_subtraction_operator(FLQuant flq1, double value){
    FLQuant flq3 = flq1 - value;
    return flq3;
}

// [[Rcpp::export]]
FLQuant test_double_FLQuant_subtraction_operator(double value, FLQuant flq1){
    FLQuant flq3 = value - flq1;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_double_FLQuantAdolc_subtraction_operator(double value, FLQuantAdolc flq1){
    FLQuantAdolc flq3 = value - flq1;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_double_subtraction_operator(FLQuantAdolc flq1, double value){
    FLQuantAdolc flq3 = flq1 - value;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuant_adouble_subtraction_operator(FLQuant flq1, double value){
    adouble ad_value = value;
    FLQuantAdolc flq3 = flq1 - ad_value;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_adouble_FLQuant_subtraction_operator(double value, FLQuant flq1){
    adouble ad_value = value;
    FLQuantAdolc flq3 = ad_value - flq1;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_adouble_subtraction_operator(FLQuantAdolc flq1, double value){
    adouble ad_value = value;
    FLQuantAdolc flq3 = flq1 - ad_value;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_adouble_FLQuantAdolc_subtraction_operator(double value, FLQuantAdolc flq1){
    adouble ad_value = value;
    FLQuantAdolc flq3 = ad_value - flq1;
    return flq3;
}

//------------------ Addition ----------------------

/* Addition assignment
 * 6 of them
 */

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_addition_assignment_operator(FLQuant flq1, FLQuant flq2){
    flq1 += flq2;
    return flq1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuant_addition_assignment_operator(FLQuantAdolc flqad1, FLQuant flq2){
    flqad1 += flq2;
    return flqad1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuantAdolc_addition_assignment_operator(FLQuantAdolc flqad1, FLQuantAdolc flqad2){
    flqad1 += flqad2;
    return flqad1;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_addition_assignment_operator(FLQuant flq1, double value){
    flq1 += value;
    return flq1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_double_addition_assignment_operator(FLQuantAdolc flqad1, double value){
    flqad1 += value;
    return flqad1;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_adouble_addition_assignment_operator(FLQuantAdolc flqad1, double value){
    adouble ad_value = value;
    flqad1 += ad_value;
    return flqad1;
}

/* Binary addition
 * 12 of them
 */

// [[Rcpp::export]]
FLQuant test_FLQuant_FLQuant_addition_operator(FLQuant flq1, FLQuant flq2){
    FLQuant flq3 = flq1 + flq2;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuant_addition_operator(FLQuantAdolc flqad1, FLQuant flq2){
    FLQuantAdolc flqad3;
    flqad3 = flqad1 + flq2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuant_FLQuantAdolc_addition_operator(FLQuant flq1, FLQuantAdolc flqad2){
    FLQuantAdolc flqad3;
    flqad3 = flq1 + flqad2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_FLQuantAdolc_addition_operator(FLQuantAdolc flqad1, FLQuantAdolc flqad2){
    FLQuantAdolc flqad3;
    flqad3 = flqad1 + flqad2;
    return flqad3;
}

// [[Rcpp::export]]
FLQuant test_FLQuant_double_addition_operator(FLQuant flq1, double value){
    FLQuant flq3 = flq1 + value;
    return flq3;
}

// [[Rcpp::export]]
FLQuant test_double_FLQuant_addition_operator(double value, FLQuant flq1){
    FLQuant flq3 = value + flq1;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_double_FLQuantAdolc_addition_operator(double value, FLQuantAdolc flq1){
    FLQuantAdolc flq3 = value + flq1;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_double_addition_operator(FLQuantAdolc flq1, double value){
    FLQuantAdolc flq3;
    flq1 + value;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuant_adouble_addition_operator(FLQuant flq1, double value){
    adouble ad_value = value;
    FLQuantAdolc flq3 = flq1 + ad_value;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_adouble_FLQuant_addition_operator(double value, FLQuant flq1){
    adouble ad_value = value;
    FLQuantAdolc flq3 = ad_value + flq1;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_FLQuantAdolc_adouble_addition_operator(FLQuantAdolc flq1, double value){
    adouble ad_value = value;
    FLQuantAdolc flq3 = flq1 + ad_value;
    return flq3;
}

// [[Rcpp::export]]
FLQuantAdolc test_adouble_FLQuantAdolc_addition_operator(double value, FLQuantAdolc flq1){
    adouble ad_value = value;
    FLQuantAdolc flq3 = ad_value + flq1;
    return flq3;
}



//----------- Composite tests -----------------
// Can we string all these together?

// [[Rcpp::export]]
FLQuantAdolc test_composite_arithmetic_operators(FLQuantAdolc flqad, FLQuant flq, double value){
    FLQuantAdolc flqad_out;
    flqad_out = ((((value * flq) + value) - flq) / flq) * ((value / flqad) - value);
    return flqad_out;
}
