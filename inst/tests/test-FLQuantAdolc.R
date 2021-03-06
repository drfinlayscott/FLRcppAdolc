context("CPP implementation of FLQuantAdolc")

test_that("FLQuantAdolc as and wrap",{
    flq_in <- random_FLQuant_generator()
    flq_out <- test_FLQuantAdolc_as_wrap(flq_in)
    expect_that(flq_in, is_identical_to(flq_out))
})

test_that("FLQuantAdolc constructors",{
    flq_in <- random_FLQuant_generator()
    # Empty constructor - doesn't do anything - but shouldn't fail
    test_FLQuantAdolc_basic_constructor()
    # SEXP constructor - used in as
    flq_out <- test_FLQuantAdolc_sexp_constructor(flq_in)
    expect_that(flq_in, is_identical_to(flq_out))
    # dim constructor
    dims <- round(runif(6, min = 1, max = 5))
    flq_out <- test_FLQuantAdolc_dim_constructor(dims[1], dims[2], dims[3], dims[4], dims[5], dims[6])
    expect_that(all(flq_out == 0), is_true())
    expect_that(dim(flq_out), equals(dims))
    # Copy constructor
    flq_out <- test_FLQuantAdolc_copy_constructor(flq_in)
    expect_that(flq_in, is_identical_to(flq_out))
    # Copy constructor2
    indices <- round(runif(6,min=1, max = dim(flq_in)))
    value <- rnorm(1)
    # Makes a copy of flq_in, changes a value of flq_in, returns original and new FLQuant
    # Checks that the copy constuctor makes a 'deep' copy else changing a value in the copy FLQ will also change a value in the original FLQ
    flqs <-  test_FLQuantAdolc_copy_constructor2(flq_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value)
    expect_that(flq_in, is_identical_to(flqs[["flq1"]]))
    expect_that(c(flqs[["flq2"]][indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
    # Assignment operator
    flq_out <- test_FLQuantAdolc_assignment_operator(flq_in)
    expect_that(flq_in, is_identical_to(flq_out))
    # Assignment operator2
    flqs <-  test_FLQuantAdolc_assignment_operator2(flq_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value)
    expect_that(flq_in, is_identical_to(flqs[["flq1"]]))
    expect_that(c(flqs[["flq2"]][indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
    # Make an FLQuantAdolc from an FLQuant
    flq_out <- test_FLQuantAdolc_from_FLQuant_constructor(flq_in)
        expect_that(flq_in, is_identical_to(flq_out))
})

test_that("FLQuantAdolc get accessors",{
    flq <- random_FLQuant_generator()
    expect_that(test_FLQuantAdolc_get_units(flq), is_identical_to(units(flq)))
    expect_that(test_FLQuantAdolc_get_dim(flq), is_identical_to(dim(flq)))
    expect_that(test_FLQuantAdolc_get_dimnames(flq), is_identical_to(dimnames(flq)))
    expect_that(test_FLQuantAdolc_get_size(flq), is_identical_to(length(c(flq@.Data))))
    expect_that(test_FLQuantAdolc_get_nquant(flq), is_identical_to(dim(flq)[1]))
    expect_that(test_FLQuantAdolc_get_nyear(flq), is_identical_to(dim(flq)[2]))
    expect_that(test_FLQuantAdolc_get_nunit(flq), is_identical_to(dim(flq)[3]))
    expect_that(test_FLQuantAdolc_get_nseason(flq), is_identical_to(dim(flq)[4]))
    expect_that(test_FLQuantAdolc_get_narea(flq), is_identical_to(dim(flq)[5]))
    expect_that(test_FLQuantAdolc_get_niter(flq), is_identical_to(dim(flq)[6]))
    indices <- round(runif(6,min=1, max = dim(flq)))
    value <- rnorm(1)
    element <- test_FLQuantAdolc_get_data_element(flq, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6])
    expect_that(c(flq[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(c(flq)[element+1]))
})

test_that("set",{
    # set_dimnames
    flq_in <- random_FLQuant_generator()
    new_dimnames <- dimnames(flq_in)
    new_dimnames[[1]][1] <- as.character(rnorm(1))
    flq_out <- test_FLQuantAdolc_set_dimnames(flq_in, new_dimnames)
    expect_that(dimnames(flq_out)[[1]][1], is_identical_to(new_dimnames[[1]][1]))
    expect_that(c(flq_out@.Data), is_identical_to(c(flq_in@.Data)))
    expect_that(dim(flq_out), is_identical_to(dim(flq_in)))
    # Check falure
    new_dimnames[[3]] <- c(new_dimnames[[3]],"extra")
    expect_that(test_FLQuantAdolc_set_dimnames(flq_in, new_dimnames), throws_error())
})

test_that("FLQuantAdolc get and set data accessors", {
    flq <- random_FLQuant_generator()
    indices <- round(runif(6,min=1, max = dim(flq)))
    index <- round(runif(1,min=1,max = prod(dim(flq))))
    value <- rnorm(1)
    # single index
    expect_that(test_FLQuantAdolc_get_const_single_index_accessor(flq, index), is_identical_to(c(flq@.Data)[index]))
    expect_that(test_FLQuantAdolc_get_single_index_accessor(flq, index), is_identical_to(c(flq@.Data)[index]))
    flq_out <- test_FLQuantAdolc_set_single_index_accessor(flq, index, value)
    expect_that(c(flq_out)[index], is_identical_to(value))
    # multiple indices
    value_out <- test_FLQuantAdolc_const_get_accessor(flq, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6])
    expect_that(c(flq[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value_out))
    value_out <- test_FLQuantAdolc_get_accessor(flq, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6])
    expect_that(c(flq[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value_out))
    flq_out <- test_FLQuantAdolc_set_accessor(flq, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value)
    expect_that(c(flq_out[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
    # Check outside bounds
    big_index <- prod(dim(flq))+1
    big_indices1 <- dim(flq) + c(1,0,0,0,0,0)
    big_indices2 <- dim(flq) + c(0,1,0,0,0,0)
    big_indices3 <- dim(flq) + c(0,0,1,0,0,0)
    big_indices4 <- dim(flq) + c(0,0,0,1,0,0)
    big_indices5 <- dim(flq) + c(0,0,0,0,1,0)
    big_indices6 <- dim(flq) + c(0,0,0,0,0,1)
    expect_that(test_FLQuantAdolc_get_const_single_index_accessor(flq, big_index), throws_error())
    expect_that(test_FLQuantAdolc_get_single_index_accessor(flq, big_index), throws_error())
    expect_that(test_FLQuantAdolc_set_single_index_accessor(flq, big_index, value), throws_error())
    expect_that(test_FLQuantAdolc_const_get_accessor(flq, big_indices1[1], big_indices1[2], big_indices1[3], big_indices1[4], big_indices1[5], big_indices1[6]), throws_error())
    expect_that(test_FLQuantAdolc_const_get_accessor(flq, big_indices2[1], big_indices2[2], big_indices2[3], big_indices2[4], big_indices2[5], big_indices2[6]), throws_error())
    expect_that(test_FLQuantAdolc_const_get_accessor(flq, big_indices3[1], big_indices3[2], big_indices3[3], big_indices3[4], big_indices3[5], big_indices3[6]), throws_error())
    expect_that(test_FLQuantAdolc_const_get_accessor(flq, big_indices4[1], big_indices4[2], big_indices4[3], big_indices4[4], big_indices4[5], big_indices4[6]), throws_error())
    expect_that(test_FLQuantAdolc_const_get_accessor(flq, big_indices5[1], big_indices5[2], big_indices5[3], big_indices5[4], big_indices5[5], big_indices5[6]), throws_error())
    expect_that(test_FLQuantAdolc_const_get_accessor(flq, big_indices6[1], big_indices6[2], big_indices6[3], big_indices6[4], big_indices6[5], big_indices6[6]), throws_error())
    expect_that(test_FLQuantAdolc_get_accessor(flq, big_indices1[1], big_indices1[2], big_indices1[3], big_indices1[4], big_indices1[5], big_indices1[6]), throws_error())
    expect_that(test_FLQuantAdolc_get_accessor(flq, big_indices2[1], big_indices2[2], big_indices2[3], big_indices2[4], big_indices2[5], big_indices2[6]), throws_error())
    expect_that(test_FLQuantAdolc_get_accessor(flq, big_indices3[1], big_indices3[2], big_indices3[3], big_indices3[4], big_indices3[5], big_indices3[6]), throws_error())
    expect_that(test_FLQuantAdolc_get_accessor(flq, big_indices4[1], big_indices4[2], big_indices4[3], big_indices4[4], big_indices4[5], big_indices4[6]), throws_error())
    expect_that(test_FLQuantAdolc_get_accessor(flq, big_indices5[1], big_indices5[2], big_indices5[3], big_indices5[4], big_indices5[5], big_indices5[6]), throws_error())
    expect_that(test_FLQuantAdolc_get_accessor(flq, big_indices6[1], big_indices6[2], big_indices6[3], big_indices6[4], big_indices6[5], big_indices6[6]), throws_error())
    expect_that(test_FLQuantAdolc_set_accessor(flq, big_indices1[1], big_indices1[2], big_indices1[3], big_indices1[4], big_indices1[5], big_indices1[6], value), throws_error())
    expect_that(test_FLQuantAdolc_set_accessor(flq, big_indices2[1], big_indices2[2], big_indices2[3], big_indices2[4], big_indices2[5], big_indices2[6], value), throws_error())
    expect_that(test_FLQuantAdolc_set_accessor(flq, big_indices3[1], big_indices3[2], big_indices3[3], big_indices3[4], big_indices3[5], big_indices3[6], value), throws_error())
    expect_that(test_FLQuantAdolc_set_accessor(flq, big_indices4[1], big_indices4[2], big_indices4[3], big_indices4[4], big_indices4[5], big_indices4[6], value), throws_error())
    expect_that(test_FLQuantAdolc_set_accessor(flq, big_indices5[1], big_indices5[2], big_indices5[3], big_indices5[4], big_indices5[5], big_indices5[6], value), throws_error())
    expect_that(test_FLQuantAdolc_set_accessor(flq, big_indices6[1], big_indices6[2], big_indices6[3], big_indices6[4], big_indices6[5], big_indices6[6], value), throws_error())
    # indices accessor
    expect_that(test_FLQuantAdolc_get_const_indices_accessor(flq, indices), is_identical_to(c(flq[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])))
    expect_that(test_FLQuantAdolc_get_const_indices_accessor(flq, c(indices,1)), throws_error())
    expect_that(test_FLQuantAdolc_get_const_indices_accessor(flq, indices[-1]), throws_error())
    expect_that(test_FLQuantAdolc_get_indices_accessor(flq, indices), is_identical_to(c(flq[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])))
    expect_that(test_FLQuantAdolc_get_indices_accessor(flq, c(indices,1)), throws_error())
    expect_that(test_FLQuantAdolc_get_indices_accessor(flq, indices[-1]), throws_error())
    value <- rnorm(1)
    flq_out <- test_FLQuantAdolc_set_indices_accessor(flq, indices, value)
    expect_that(c(flq_out[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
})

test_that("FLQuantAdolc match_dims method works", {
    flq <- random_FLQuant_generator()
    dim_flq <- dim(flq)
    dim_flq1 <- dim_flq + c(1,0,0,0,0,0)
    flq1 <- FLQuant(0, dim = dim_flq + c(1,0,0,0,0,0))
    flq2 <- FLQuant(0, dim = dim_flq + c(0,1,0,0,0,0)) 
    flq3 <- FLQuant(0, dim = dim_flq + c(0,0,1,0,0,0))
    flq4 <- FLQuant(0, dim = dim_flq + c(0,0,0,1,0,0))
    flq5 <- FLQuant(0, dim = dim_flq + c(0,0,0,0,1,0))
    flq6 <- FLQuant(0, dim = dim_flq + c(0,0,0,0,0,1))
    expect_that(test_FLQuantAdolc_FLQuantAdolc_match_dims(flq, flq), is_identical_to(1L))
    expect_that(test_FLQuantAdolc_FLQuantAdolc_match_dims(flq, flq1), is_identical_to(-1L))
    expect_that(test_FLQuantAdolc_FLQuantAdolc_match_dims(flq, flq2), is_identical_to(-2L))
    expect_that(test_FLQuantAdolc_FLQuantAdolc_match_dims(flq, flq3), is_identical_to(-3L))
    expect_that(test_FLQuantAdolc_FLQuantAdolc_match_dims(flq, flq4), is_identical_to(-4L))
    expect_that(test_FLQuantAdolc_FLQuantAdolc_match_dims(flq, flq5), is_identical_to(-5L))
    expect_that(test_FLQuantAdolc_FLQuantAdolc_match_dims(flq, flq6), is_identical_to(-6L))
    expect_that(test_FLQuantAdolc_FLQuant_match_dims(flq, flq), is_identical_to(1L))
    expect_that(test_FLQuantAdolc_FLQuant_match_dims(flq, flq1), is_identical_to(-1L))
    expect_that(test_FLQuantAdolc_FLQuant_match_dims(flq, flq2), is_identical_to(-2L))
    expect_that(test_FLQuantAdolc_FLQuant_match_dims(flq, flq3), is_identical_to(-3L))
    expect_that(test_FLQuantAdolc_FLQuant_match_dims(flq, flq4), is_identical_to(-4L))
    expect_that(test_FLQuantAdolc_FLQuant_match_dims(flq, flq5), is_identical_to(-5L))
    expect_that(test_FLQuantAdolc_FLQuant_match_dims(flq, flq6), is_identical_to(-6L))
    expect_that(test_FLQuant_FLQuantAdolc_match_dims(flq, flq), is_identical_to(1L))
    expect_that(test_FLQuant_FLQuantAdolc_match_dims(flq, flq1), is_identical_to(-1L))
    expect_that(test_FLQuant_FLQuantAdolc_match_dims(flq, flq2), is_identical_to(-2L))
    expect_that(test_FLQuant_FLQuantAdolc_match_dims(flq, flq3), is_identical_to(-3L))
    expect_that(test_FLQuant_FLQuantAdolc_match_dims(flq, flq4), is_identical_to(-4L))
    expect_that(test_FLQuant_FLQuantAdolc_match_dims(flq, flq5), is_identical_to(-5L))
    expect_that(test_FLQuant_FLQuantAdolc_match_dims(flq, flq6), is_identical_to(-6L))
})




