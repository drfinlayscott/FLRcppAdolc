context("Implementation of fwdBiol - double and Adolc versions")

test_that("fwdBiol as and wrap",{
    flb_in <- random_FLBiol_generator()
    flb_out <- test_fwdBiol_as_wrap(flb_in)
    expect_that(flb_in, is_identical_to(flb_out))
    flb_out <- test_fwdBiolAdolc_as_wrap(flb_in)
    expect_that(flb_in, is_identical_to(flb_out))
})

test_that("FLQuant7 constructors - double",{
    flb_in <- random_FLBiol_generator()
    # SEXP constructors
    flb_out <- test_fwdBiol_sexp_constructor(flb_in)
    expect_that(flb_in, is_identical_to(flb_out))
    flb_out <- test_fwdBiolAdolc_sexp_constructor(flb_in)
    expect_that(flb_in, is_identical_to(flb_out))
    # Copy constructor
    flb_out <- test_fwdBiol_copy_constructor(flb_in)
    expect_that(flb_in, is_identical_to(flb_out))
    flb_out <- test_fwdBiolAdolc_copy_constructor(flb_in)
    expect_that(flb_in, is_identical_to(flb_out))
    # Copy constructor2
    indices <- round(runif(6,min=1, max = dim(n(flb_in))))
    value <- rnorm(1)
    # Makes a copy of flq_in, changes a value of flq_in, returns original and new FLQuant
    # Checks that the copy constuctor makes a 'deep' copy else changing a value in the copy FLQ will also change a value in the original FLQ
    flbs <-  test_fwdBiol_copy_constructor2(flb_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value)
    expect_that(flb_in, is_identical_to(flbs[["fwdb1"]]))
    expect_that(c(n(flbs[["fwdb2"]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
    flbs <-  test_fwdBiolAdolc_copy_constructor2(flb_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value)
    expect_that(flb_in, is_identical_to(flbs[["fwdb1"]]))
    expect_that(c(n(flbs[["fwdb2"]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
    # Assignment operator
    flb_out <- test_fwdBiol_assignment_operator(flb_in)
    expect_that(flb_in, is_identical_to(flb_out))
    flb_out <- test_fwdBiolAdolc_assignment_operator(flb_in)
    expect_that(flb_in, is_identical_to(flb_out))
    # Assignment operator2
    indices <- round(runif(6,min=1, max = dim(n(flb_in))))
    value <- rnorm(1)
    # Makes a copy of flq_in, changes a value of flq_in, returns original and new FLQuant
    # Checks that the assignment operator makes a 'deep' copy else changing a value in the copy FLQ will also change a value in the original FLQ
    flbs <-  test_fwdBiol_assignment_operator2(flb_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value)
    expect_that(flb_in, is_identical_to(flbs[["fwdb1"]]))
    expect_that(c(n(flbs[["fwdb2"]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
    flbs <-  test_fwdBiolAdolc_assignment_operator2(flb_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value)
    expect_that(flb_in, is_identical_to(flbs[["fwdb1"]]))
    expect_that(c(n(flbs[["fwdb2"]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
})

test_that("fwdBiol get and set data accessors", {
    # Get
    flb_in <- random_FLBiol_generator()
    indices <- round(runif(6,min=1, max = dim(n(flb_in))))
    values_out <- test_fwdBiol_get_accessors(flb_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6])
    values_in <- c(c(n(flb_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(m(flb_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(wt(flb_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(fec(flb_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(spwn(flb_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]))
    expect_that(values_out, is_identical_to(values_in))
    values_out <- test_fwdBiolAdolc_get_accessors(flb_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6])
    values_in <- c(c(n(flb_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(m(flb_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(wt(flb_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(fec(flb_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(spwn(flb_in)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]))
    expect_that(values_out, is_identical_to(values_in))
    # Set double
    flb_in <- random_FLBiol_generator()
    indices <- round(runif(6,min=1, max = dim(n(flb_in))))
    values_in <- rnorm(5)
    flb_out <- test_fwdBiol_set_accessors(flb_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], values_in)
    # Check inserted values are correct
    values_out <- c(c(n(flb_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(m(flb_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(wt(flb_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(fec(flb_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(spwn(flb_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]))
    expect_that(values_out, is_identical_to(values_in))
    # Check other values have been left alone
    narea <- dim(n(flb_out))[5]
    nseason <- dim(n(flb_out))[4]
    nunit<- dim(n(flb_out))[3]
    nyear <- dim(n(flb_out))[2]
    nquant <- dim(n(flb_out))[1]
    element <- (narea * nseason * nunit * nyear * nquant * (indices[6] - 1)) + (nseason * nunit * nyear * nquant * (indices[5] - 1)) + (nunit * nyear * nquant * (indices[4] - 1)) + (nyear * nquant * (indices[3] - 1)) + (nquant * (indices[2] - 1)) + (indices[1] - 1) + 1; 
    expect_that(c(n(flb_out))[-element], is_identical_to(c(n(flb_in))[-element]))
    expect_that(c(m(flb_out))[-element], is_identical_to(c(m(flb_in))[-element]))
    expect_that(c(wt(flb_out))[-element], is_identical_to(c(wt(flb_in))[-element]))
    expect_that(c(fec(flb_out))[-element], is_identical_to(c(fec(flb_in))[-element]))
    expect_that(c(spwn(flb_out))[-element], is_identical_to(c(spwn(flb_in))[-element]))
    # Set Adolc 
    flb_in <- random_FLBiol_generator()
    indices <- round(runif(6,min=1, max = dim(n(flb_in))))
    values_in <- rnorm(5)
    flb_out <- test_fwdBiolAdolc_set_accessors(flb_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], values_in)
    # Check inserted values are correct
    values_out <- c(c(n(flb_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(m(flb_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(wt(flb_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(fec(flb_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]),
                c(spwn(flb_out)[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]))
    expect_that(values_out, is_identical_to(values_in))
    # Check other values have been left alone
    narea <- dim(n(flb_out))[5]
    nseason <- dim(n(flb_out))[4]
    nunit<- dim(n(flb_out))[3]
    nyear <- dim(n(flb_out))[2]
    nquant <- dim(n(flb_out))[1]
    element <- (narea * nseason * nunit * nyear * nquant * (indices[6] - 1)) + (nseason * nunit * nyear * nquant * (indices[5] - 1)) + (nunit * nyear * nquant * (indices[4] - 1)) + (nyear * nquant * (indices[3] - 1)) + (nquant * (indices[2] - 1)) + (indices[1] - 1) + 1; 
    expect_that(c(n(flb_out))[-element], is_identical_to(c(n(flb_in))[-element]))
    expect_that(c(m(flb_out))[-element], is_identical_to(c(m(flb_in))[-element]))
    expect_that(c(wt(flb_out))[-element], is_identical_to(c(wt(flb_in))[-element]))
    expect_that(c(fec(flb_out))[-element], is_identical_to(c(fec(flb_in))[-element]))
    expect_that(c(spwn(flb_out))[-element], is_identical_to(c(spwn(flb_in))[-element]))

})
