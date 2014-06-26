// Change the name of this

/* 
 * Copyright 2013 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */


#include "../../inst/include/control.h"


// [[Rcpp::export]]
int what(){
    int x = 4;
    Rprintf("XXX\n");
    return x;
}

