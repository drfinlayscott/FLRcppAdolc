# 
# Copyright 2014 FLR Team. Distributed under the GPL 2 or later
# Maintainer: Finlay Scott, JRC
#

context("Implementation of FLCatch - double and Adolc versions")

test_that("FLCatch as and wrap",{
    flc_in <- random_FLCatch_generator()
    expect_that(test_simple_FLCatch_sexp_constructor(flc_in), is_identical_to(as.integer(0)))
    flc_out <- test_FLCatch_as_wrap(flc_in)
    expect_that(flc_in, is_identical_to(flc_out))
    flc_out <- test_FLCatchAdolc_as_wrap(flc_in)
    expect_that(flc_in, is_identical_to(flc_out))
})

test_that("FLCatch constructors",{
    flc_in <- random_FLCatch_generator()
    # SEXP constructors
    flc_out <- test_FLCatch_sexp_constructor(flc_in)
    expect_that(flc_in, is_identical_to(flc_out))
    flc_out <- test_FLCatchAdolc_sexp_constructor(flc_in)
    expect_that(flc_in, is_identical_to(flc_out))
    # Copy constructor
    flc_out <- test_FLCatch_copy_constructor(flc_in)
    expect_that(flc_in, is_identical_to(flc_out))
    flc_out <- test_FLCatchAdolc_copy_constructor(flc_in)
    expect_that(flc_in, is_identical_to(flc_out))
    # Copy constructor2
    indices <- round(runif(6,min=1, max = dim(landings.n(flc_in))))
    value <- rnorm(1)
    # Makes a copy of flq_in, changes a value of flq_in, returns original and new FLQuant
    # Checks that the copy constuctor makes a 'deep' copy else changing a value in the copy FLQ will also change a value in the original FLQ
    flcs <-  test_FLCatch_copy_constructor2(flc_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value)
    expect_that(flc_in, is_identical_to(flcs[["flc1"]]))
    expect_that(c(landings.n(flcs[["flc2"]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
    flcs <-  test_FLCatchAdolc_copy_constructor2(flc_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value)
    expect_that(flc_in, is_identical_to(flcs[["flc1"]]))
    expect_that(c(landings.n(flcs[["flc2"]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
    # Assignment operator
    flc_out <- test_FLCatch_assignment_operator(flc_in)
    expect_that(flc_in, is_identical_to(flc_out))
    flc_out <- test_FLCatchAdolc_assignment_operator(flc_in)
    expect_that(flc_in, is_identical_to(flc_out))
    # Assignment operator2
    indices <- round(runif(6,min=1, max = dim(landings.n(flc_in))))
    value <- rnorm(1)
    # Makes a copy of flq_in, changes a value of flq_in, returns original and new FLQuant
    # Checks that the assignment operator makes a 'deep' copy else changing a value in the copy FLQ will also change a value in the original FLQ
    flcs <-  test_FLCatch_assignment_operator2(flc_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value)
    expect_that(flc_in, is_identical_to(flcs[["flc1"]]))
    expect_that(c(landings.n(flcs[["flc2"]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
    flcs <-  test_FLCatchAdolc_assignment_operator2(flc_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value)
    expect_that(flc_in, is_identical_to(flcs[["flc1"]]))
    expect_that(c(landings.n(flcs[["flc2"]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
})

test_that("FLCatch get and set data accessors", {
    # Get const double
    flc_in <- random_FLCatch_generator()
    indices <- round(runif(6,min=1, max = dim(landings.n(flc_in))))
    values_out <- test_FLCatch_const_get_accessors(flc_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6])
    values_in <- c(c(landings.n(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(discards.n(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(landings.wt(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(discards.wt(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(catch.sel(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(price(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]))
                #c(catch.q(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
    expect_that(values_out, is_identical_to(values_in))
    # Get const Adolc
    flc_in <- random_FLCatch_generator()
    indices <- round(runif(6,min=1, max = dim(landings.n(flc_in))))
    values_out <- test_FLCatchAdolc_const_get_accessors(flc_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6])
    values_in <- c(c(landings.n(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(discards.n(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(landings.wt(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(discards.wt(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(catch.sel(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(price(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]))
                #c(catch.q(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
    expect_that(values_out, is_identical_to(values_in))
    # Get double
    flc_in <- random_FLCatch_generator()
    indices <- round(runif(6,min=1, max = dim(landings.n(flc_in))))
    values_out <- test_FLCatch_get_accessors(flc_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6])
    values_in <- c(c(landings.n(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(discards.n(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(landings.wt(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(discards.wt(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(catch.sel(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(price(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]))
                #c(catch.q(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
    expect_that(values_out, is_identical_to(values_in))
    # Get Adolc
    values_out <- test_FLCatchAdolc_get_accessors(flc_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6])
    values_in <- c(c(landings.n(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(discards.n(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(landings.wt(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(discards.wt(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(catch.sel(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(price(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]))
                #c(catch.q(flc_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
    expect_that(values_out, is_identical_to(values_in))
    # Set double
    flc_in <- random_FLCatch_generator()
    indices <- round(runif(6,min=1, max = dim(landings.n(flc_in))))
    values_in <- rnorm(6)
    flc_out <- test_FLCatch_set_accessors(flc_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], values_in)
    values_out <- c(c(landings.n(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(discards.n(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(landings.wt(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(discards.wt(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(catch.sel(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(price(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]))
                #c(catch.q(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
    # Check inserted values are correct
    expect_that(values_out, is_identical_to(values_in))
    # Check other values have been left alone
    narea <- dim(landings.n(flc_out))[5]
    nseason <- dim(landings.n(flc_out))[4]
    nunit<- dim(landings.n(flc_out))[3]
    nyear <- dim(landings.n(flc_out))[2]
    nquant <- dim(landings.n(flc_out))[1]
    element <- (narea * nseason * nunit * nyear * nquant * (indices[6] - 1)) + (nseason * nunit * nyear * nquant * (indices[5] - 1)) + (nunit * nyear * nquant * (indices[4] - 1)) + (nyear * nquant * (indices[3] - 1)) + (nquant * (indices[2] - 1)) + (indices[1] - 1) + 1; 
    expect_that(c(landings.n(flc_out))[-element], is_identical_to(c(landings.n(flc_in))[-element]))
    expect_that(c(discards.n(flc_out))[-element], is_identical_to(c(discards.n(flc_in))[-element]))
    expect_that(c(landings.wt(flc_out))[-element], is_identical_to(c(landings.wt(flc_in))[-element]))
    expect_that(c(discards.wt(flc_out))[-element], is_identical_to(c(discards.wt(flc_in))[-element]))
    expect_that(c(catch.sel(flc_out))[-element], is_identical_to(c(catch.sel(flc_in))[-element]))
    expect_that(c(price(flc_out))[-element], is_identical_to(c(price(flc_in))[-element]))
    #expect_that(c(catch.q(flc_out))[-element], is_identical_to(c(catch.q(flc_in))[-element]))
    # Set Adolc 
    flc_in <- random_FLCatch_generator()
    indices <- round(runif(6,min=1, max = dim(landings.n(flc_in))))
    values_in <- rnorm(6)
    flc_out <- test_FLCatchAdolc_set_accessors(flc_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], values_in)
    values_out <- c(c(landings.n(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(discards.n(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(landings.wt(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(discards.wt(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(catch.sel(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(price(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]))
                #c(catch.q(flc_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
    # Check inserted values are correct
    expect_that(values_out, is_identical_to(values_in))
    # Check other values have been left alone
    narea <- dim(landings.n(flc_out))[5]
    nseason <- dim(landings.n(flc_out))[4]
    nunit<- dim(landings.n(flc_out))[3]
    nyear <- dim(landings.n(flc_out))[2]
    nquant <- dim(landings.n(flc_out))[1]
    element <- (narea * nseason * nunit * nyear * nquant * (indices[6] - 1)) + (nseason * nunit * nyear * nquant * (indices[5] - 1)) + (nunit * nyear * nquant * (indices[4] - 1)) + (nyear * nquant * (indices[3] - 1)) + (nquant * (indices[2] - 1)) + (indices[1] - 1) + 1; 
    expect_that(c(landings.n(flc_out))[-element], is_identical_to(c(landings.n(flc_in))[-element]))
    expect_that(c(discards.n(flc_out))[-element], is_identical_to(c(discards.n(flc_in))[-element]))
    expect_that(c(landings.wt(flc_out))[-element], is_identical_to(c(landings.wt(flc_in))[-element]))
    expect_that(c(discards.wt(flc_out))[-element], is_identical_to(c(discards.wt(flc_in))[-element]))
    expect_that(c(catch.sel(flc_out))[-element], is_identical_to(c(catch.sel(flc_in))[-element]))
    expect_that(c(price(flc_out))[-element], is_identical_to(c(price(flc_in))[-element]))
    #expect_that(c(catch.q(flc_out))[-element], is_identical_to(c(catch.q(flc_in))[-element]))
})

test_that("FLCatch methods", {
    flc_in <- random_FLCatch_generator()
    # landings
    l_in <- landings(flc_in)
    l_out <- test_FLCatch_landings(flc_in)
    #expect_that(l_out, is_identical_to(l_in)) # units not dealt with correctly
    expect_that(dimnames(l_out), is_identical_to(dimnames(l_in))) # units not dealt with correctly
    expect_that(l_out@.Data, equals(l_in@.Data)) # quant sums causes numerical differences
    l_out <- test_FLCatchAdolc_landings(flc_in)
    #expect_that(l_out, is_identical_to(l_in)) # units not dealt with correctly
    expect_that(dimnames(l_out), is_identical_to(dimnames(l_in))) # units not dealt with correctly
    expect_that(l_out@.Data, equals(l_in@.Data)) # quant sums causes numerical differences

    # discards
    d_in <- discards(flc_in)
    d_out <- test_FLCatch_discards(flc_in)
    #expect_that(d_out, is_identical_to(d_in)) # units not dealt with correctly
    expect_that(dimnames(d_out), is_identical_to(dimnames(d_in))) # units not dealt with correctly
    expect_that(d_out@.Data, equals(d_in@.Data)) # quant sums causes numerical differences
    d_out <- test_FLCatchAdolc_discards(flc_in)
    #expect_that(d_out, is_identical_to(d_in)) # units not dealt with correctly
    expect_that(dimnames(d_out), is_identical_to(dimnames(d_in))) # units not dealt with correctly
    expect_that(d_out@.Data, equals(d_in@.Data)) # quant sums causes numerical differences

    # catch_n
    cn_in <- catch.n(flc_in)
    cn_out <- test_FLCatch_catch_n(flc_in)
    #expect_that(cn_out, is_identical_to(cn_in)) # units not dealt with correctly
    expect_that(dimnames(cn_out), is_identical_to(dimnames(cn_in))) # units not dealt with correctly
    expect_that(cn_out@.Data, equals(cn_in@.Data)) # quant sums causes numerical differences
    cn_out <- test_FLCatchAdolc_catch_n(flc_in)
    #expect_that(cn_out, is_identicad_to(cn_in)) # units not dealt with correctly
    expect_that(dimnames(cn_out), is_identical_to(dimnames(cn_in))) # units not dealt with correctly
    expect_that(cn_out@.Data, equals(cn_in@.Data)) # quant sums causes numerical differences

    # catches
    c_in <- catch(flc_in)
    c_out <- test_FLCatch_catches(flc_in)
    expect_that(dimnames(c_out), is_identical_to(dimnames(c_in))) # units not dealt with correctly
    expect_that(c_out@.Data, equals(c_in@.Data)) # quant sums causes numerical differences
    c_out <- test_FLCatchAdolc_catches(flc_in)
    expect_that(dimnames(c_out), is_identical_to(dimnames(c_in))) # units not dealt with correctly
    expect_that(c_out@.Data, equals(c_in@.Data)) # quant sums causes numerical differences

    # catch weight
    cw_in <- catch.wt(flc_in)
    cw_out <- test_FLCatch_catch_wt(flc_in)
    expect_that(dimnames(cw_out), is_identical_to(dimnames(cw_in))) # units not dealt with correctly
    expect_that(cw_out@.Data, equals(cw_in@.Data)) # quant sums causes numerical differences
    cw_out <- test_FLCatchAdolc_catch_wt(flc_in)
    expect_that(dimnames(cw_out), is_identical_to(dimnames(cw_in))) # units not dealt with correctly
    expect_that(cw_out@.Data, equals(cw_in@.Data)) # quant sums causes numerical differences

    # discards ratio
    dr_in <- discards.ratio(flc_in)
    dr_out <- test_FLCatch_discards_ratio(flc_in)
    expect_that(dimnames(dr_out), is_identical_to(dimnames(dr_in))) # units not dealt with correctly
    expect_that(dr_out@.Data, equals(dr_in@.Data)) # quant sums causes numerical differences
    dr_out <- test_FLCatchAdolc_discards_ratio(flc_in)
    expect_that(dimnames(dr_out), is_identical_to(dimnames(dr_in))) # units not dealt with correctly
    expect_that(dr_out@.Data, equals(dr_in@.Data)) # quant sums causes numerical differences

    # landings_sel
    ls_in <- landings.sel(flc_in)
    ls_out <- test_FLCatch_landings_sel(flc_in)
    expect_that(dimnames(ls_out), is_identical_to(dimnames(ls_in))) 
    expect_that(ls_out@.Data, is_identical_to(ls_in@.Data)) 
    ls_out <- test_FLCatchAdolc_landings_sel(flc_in)
    expect_that(dimnames(ls_out), is_identical_to(dimnames(ls_in))) 
    expect_that(ls_out@.Data, is_identical_to(ls_in@.Data)) 

    # discards_sel
    ds_in <- discards.sel(flc_in)
    ds_out <- test_FLCatch_discards_sel(flc_in)
    expect_that(dimnames(ds_out), is_identical_to(dimnames(ds_in))) 
    expect_that(ds_out@.Data, is_identical_to(ds_in@.Data)) 
    ds_out <- test_FLCatchAdolc_discards_sel(flc_in)
    expect_that(dimnames(ds_out), is_identical_to(dimnames(ds_in))) 
    expect_that(ds_out@.Data, is_identical_to(ds_in@.Data)) 
})


