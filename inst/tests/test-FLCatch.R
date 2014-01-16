context("Implementation of FLCatch - double and Adolc versions")

test_that("FLCatch as and wrap",{
    flc_in <- random_FLCatch_generator()
    expect_that(test_simple_FLCatch_sexp_constructor(flc_in), is_identical_to(as.integer(0)))
    flc_out <- test_FLCatch_as_wrap(flc_in)
    expect_that(flc_in, is_identical_to(flc_out))
    flc_out <- test_FLCatchAdolc_as_wrap(flc_in)
    expect_that(flc_in, is_identical_to(flc_out))
})

test_that("FLQuant7 constructors - double",{
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

