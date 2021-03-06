context("Implementation of FLFisheries - double and Adolc versions")

test_that("FLFisheries constructors - double",{
    flfs_in <- random_FLFisheries_generator() 
    flfs_out <- test_FLFisheries_sexp_constructor(flfs_in)
    expect_that(flfs_in, is_identical_to(flfs_out))
    flfs_out <- test_FLFisheries_as_wrap(flfs_in)
    expect_that(flfs_in, is_identical_to(flfs_out))
    # Copy constructor
    flfs_out <- test_FLFisheries_copy_constructor(flfs_in)
    expect_that(flfs_in, is_identical_to(flfs_out))
    # Copy constructor2 - checking for deep copy
    fishery <- round(runif(1,min=1, max = length(flfs_in)))
    catches <- round(runif(1,min=1, max = length(flfs_in[[fishery]])))
    indices <- as.integer(round(runif(6,min=1, max = dim(landings.n(flfs_in[[fishery]][[catches]])))))
    value <- rnorm(1)
    # Makes a copy of flcs_in, changes a value of flcs_in, returns original and new FLQuant
    flfss <- test_FLFisheries_copy_constructor2(flfs_in, fishery, catches, indices, value)
    expect_that(flfs_in, is_identical_to(flfss[["flfs1"]]))
    expect_that(c(landings.n(flfss[["flfs2"]][[fishery]][[catches]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
    # Assignment operator
    flfs_out <- test_FLFisheries_assignment_operator(flfs_in)
    expect_that(flfs_in, is_identical_to(flfs_out))
    # Assignment operator2
    flfss <- test_FLFisheries_assignment_operator2(flfs_in, fishery, catches, indices, value)
    expect_that(flfs_in, is_identical_to(flfss[["flfs1"]]))
    expect_that(c(landings.n(flfss[["flfs2"]][[fishery]][[catches]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
})

test_that("FLFisheries get accessors - double",{
    flfs_in <- random_FLFisheries_generator()
    expect_that(test_FLFisheries_get_nfisheries(flfs_in), is_identical_to(length(flfs_in)))
})

test_that("FLFisheries get and set data accessors - double", {
    flfs_in <- random_FLFisheries_generator()
    fishery <- round(runif(1,min=1, max = length(flfs_in)))
    catches <- round(runif(1,min=1, max = length(flfs_in[[fishery]])))
    indices <- as.integer(round(runif(6,min=1, max = dim(landings.n(flfs_in[[fishery]][[catches]])))))
    # single gets
    list_op <- test_FLFisheries_const_get_single(flfs_in, fishery, catches, indices)
    expect_that(list_op[["flf"]], is_identical_to(flfs_in[[fishery]]))
    expect_that(list_op[["flc"]], is_identical_to(flfs_in[[fishery]][[catches]]))
    expect_that(list_op[["landings_n"]], is_identical_to(landings.n(flfs_in[[fishery]][[catches]])))
    expect_that(list_op[["value"]], is_identical_to(c(landings.n(flfs_in[[fishery]][[catches]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])))
    list_op <- test_FLFisheries_get_single(flfs_in, fishery, catches, indices)
    expect_that(list_op[["flf"]], is_identical_to(flfs_in[[fishery]]))
    expect_that(list_op[["flc"]], is_identical_to(flfs_in[[fishery]][[catches]]))
    expect_that(list_op[["landings_n"]], is_identical_to(landings.n(flfs_in[[fishery]][[catches]])))
    expect_that(list_op[["value"]], is_identical_to(c(landings.n(flfs_in[[fishery]][[catches]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])))
    # double gets
    list_op <- test_FLFisheries_const_get_double(flfs_in, fishery, catches, indices)
    expect_that(list_op[["flf"]], is_identical_to(flfs_in[[fishery]]))
    expect_that(list_op[["flc"]], is_identical_to(flfs_in[[fishery]][[catches]]))
    expect_that(list_op[["landings_n"]], is_identical_to(landings.n(flfs_in[[fishery]][[catches]])))
    expect_that(list_op[["value"]], is_identical_to(c(landings.n(flfs_in[[fishery]][[catches]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])))
    # Bounds check
    expect_that(test_FLFisheries_get_double(flfs_in, fishery, length(flfs_in[[fishery]])+1, indices), throws_error())
    list_op <- test_FLFisheries_get_double(flfs_in, fishery, catches, indices)
    expect_that(list_op[["flf"]], is_identical_to(flfs_in[[fishery]]))
    expect_that(list_op[["flc"]], is_identical_to(flfs_in[[fishery]][[catches]]))
    expect_that(list_op[["landings_n"]], is_identical_to(landings.n(flfs_in[[fishery]][[catches]])))
    expect_that(list_op[["value"]], is_identical_to(c(landings.n(flfs_in[[fishery]][[catches]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])))
    # Bounds check
    expect_that(test_FLFisheries_get_double(flfs_in, fishery, length(flfs_in[[fishery]])+1, indices), throws_error())
    # Set a value in landings_n
    value <- rnorm(1)
    flfs_out <- test_FLFisheries_set_single(flfs_in, fishery, catches, indices, value)
    expect_that(c(landings.n(flfs_out[[fishery]][[catches]][indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])), is_identical_to(value))
    flfs_out <- test_FLFisheries_set_double(flfs_in, fishery, catches, indices, value)
    expect_that(c(landings.n(flfs_out[[fishery]][[catches]][indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])), is_identical_to(value))
})
#----------------------------------
test_that("FLFisheriesAdolc constructors - adouble",{
    flfs_in <- random_FLFisheries_generator() 
    flfs_out <- test_FLFisheriesAdolc_sexp_constructor(flfs_in)
    expect_that(flfs_in, is_identical_to(flfs_out))
    flfs_out <- test_FLFisheriesAdolc_as_wrap(flfs_in)
    expect_that(flfs_in, is_identical_to(flfs_out))
    # Copy constructor
    flfs_out <- test_FLFisheriesAdolc_copy_constructor(flfs_in)
    expect_that(flfs_in, is_identical_to(flfs_out))
    # Copy constructor2 - checking for deep copy
    fishery <- round(runif(1,min=1, max = length(flfs_in)))
    catches <- round(runif(1,min=1, max = length(flfs_in[[fishery]])))
    indices <- as.integer(round(runif(6,min=1, max = dim(landings.n(flfs_in[[fishery]][[catches]])))))
    value <- rnorm(1)
    # Makes a copy of flcs_in, changes a value of flcs_in, returns original and new FLQuant
    flfss <- test_FLFisheriesAdolc_copy_constructor2(flfs_in, fishery, catches, indices, value)
    expect_that(flfs_in, is_identical_to(flfss[["flfs1"]]))
    expect_that(c(landings.n(flfss[["flfs2"]][[fishery]][[catches]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
    # Assignment operator
    flfs_out <- test_FLFisheriesAdolc_assignment_operator(flfs_in)
    expect_that(flfs_in, is_identical_to(flfs_out))
    # Assignment operator2
    flfss <- test_FLFisheriesAdolc_assignment_operator2(flfs_in, fishery, catches, indices, value)
    expect_that(flfs_in, is_identical_to(flfss[["flfs1"]]))
    expect_that(c(landings.n(flfss[["flfs2"]][[fishery]][[catches]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value))
})

test_that("FLFisheriesAdolc get accessors - double",{
    flfs_in <- random_FLFisheries_generator()
    expect_that(test_FLFisheriesAdolc_get_nfisheries(flfs_in), is_identical_to(length(flfs_in)))
})

test_that("FLFisheriesAdolc get and set data accessors - double", {
    flfs_in <- random_FLFisheries_generator()
    fishery <- round(runif(1,min=1, max = length(flfs_in)))
    catches <- round(runif(1,min=1, max = length(flfs_in[[fishery]])))
    indices <- as.integer(round(runif(6,min=1, max = dim(landings.n(flfs_in[[fishery]][[catches]])))))
    # single gets
    list_op <- test_FLFisheriesAdolc_const_get_single(flfs_in, fishery, catches, indices)
    expect_that(list_op[["flf"]], is_identical_to(flfs_in[[fishery]]))
    expect_that(list_op[["flc"]], is_identical_to(flfs_in[[fishery]][[catches]]))
    expect_that(list_op[["landings_n"]], is_identical_to(landings.n(flfs_in[[fishery]][[catches]])))
    expect_that(list_op[["value"]], is_identical_to(c(landings.n(flfs_in[[fishery]][[catches]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])))
    list_op <- test_FLFisheriesAdolc_get_single(flfs_in, fishery, catches, indices)
    expect_that(list_op[["flf"]], is_identical_to(flfs_in[[fishery]]))
    expect_that(list_op[["flc"]], is_identical_to(flfs_in[[fishery]][[catches]]))
    expect_that(list_op[["landings_n"]], is_identical_to(landings.n(flfs_in[[fishery]][[catches]])))
    expect_that(list_op[["value"]], is_identical_to(c(landings.n(flfs_in[[fishery]][[catches]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])))
    # double gets
    list_op <- test_FLFisheriesAdolc_const_get_double(flfs_in, fishery, catches, indices)
    expect_that(list_op[["flf"]], is_identical_to(flfs_in[[fishery]]))
    expect_that(list_op[["flc"]], is_identical_to(flfs_in[[fishery]][[catches]]))
    expect_that(list_op[["landings_n"]], is_identical_to(landings.n(flfs_in[[fishery]][[catches]])))
    expect_that(list_op[["value"]], is_identical_to(c(landings.n(flfs_in[[fishery]][[catches]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])))
    # Bounds check
    expect_that(test_FLFisheriesAdolc_get_double(flfs_in, fishery, length(flfs_in[[fishery]])+1, indices), throws_error())
    list_op <- test_FLFisheriesAdolc_get_double(flfs_in, fishery, catches, indices)
    expect_that(list_op[["flf"]], is_identical_to(flfs_in[[fishery]]))
    expect_that(list_op[["flc"]], is_identical_to(flfs_in[[fishery]][[catches]]))
    expect_that(list_op[["landings_n"]], is_identical_to(landings.n(flfs_in[[fishery]][[catches]])))
    expect_that(list_op[["value"]], is_identical_to(c(landings.n(flfs_in[[fishery]][[catches]])[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])))
    # Bounds check
    expect_that(test_FLFisheriesAdolc_get_double(flfs_in, fishery, length(flfs_in[[fishery]])+1, indices), throws_error())
    # Set a value in landings_n
    value <- rnorm(1)
    flfs_out <- test_FLFisheriesAdolc_set_single(flfs_in, fishery, catches, indices, value)
    expect_that(c(landings.n(flfs_out[[fishery]][[catches]][indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])), is_identical_to(value))
    flfs_out <- test_FLFisheriesAdolc_set_double(flfs_in, fishery, catches, indices, value)
    expect_that(c(landings.n(flfs_out[[fishery]][[catches]][indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]])), is_identical_to(value))
})
