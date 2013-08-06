context("CPP implementation of FLQuant")

#test_that("FLQuant as and wrap",{
#    flq_in <- FLQuant(rnorm(10*30*4*2*4*500), dim = c(10,30,4,2,4,500))
#    flq_out <- test_FLQuant_as_wrap(flq_in)
#    expect_that(flq_in, is_identical_to(flq_out))
#})


#test_that("FLQuant constructors",{
#    flq_in <- FLQuant(rnorm(10*30*4*2*4*500), dim = c(10,30,4,2,4,500))
#    # SEXP constructor - used in as
#    flq_out <- test_FLQuant_sexp_constructor(flq_in)
#    expect_that(flq_in, is_identical_to(flq_out))
#    # Copy constructor
#    indices <- round(runif(6,min=1, max = dim(flq_in)))
#    value_in <- rnorm(1)
#    # Makes a copy of flq_in, changes a value of flq_in, returns original and new FLQuant
#    # Checks that the copy constuctor makes a 'deep' copy else changing a value in the copy FLQ will also change a value in the original FLQ
#    flqs <-  test_FLQuant_copy_constructor(flq_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value_in)
#    expect_that(flq_in, is_identical_to(flqs[["flq2"]]))
#    expect_that(c(flqs[["flq1"]][indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value_in))
#})
#
#test_that("FLQuant get and set units accessors",{
#    flq_in <- FLQuant(rnorm(10*30*4*2*4*500), dim = c(10,30,4,2,4,500), units = "Kells")
#    # get
#    expect_that(test_FLQuant_get_units(flq_in), is_identical_to("Kells"))
#    # set
#    expect_that(units(test_FLQuant_set_units(flq_in, "Chaos")), is_identical_to("Chaos"))
#})
#
## Set dimnames not tested
#test_that("FLQuant get and set dim and dimnames accessors",{
#    flq_in <- FLQuant(rnorm(10*30*4*2*4*500), dim = c(10,30,4,2,4,500), dimnames = list(age=0:9, year=1971:2000, unit = 1:4, season=1:2, area = 1:4, iter=1:500))
#    # get
#    expect_that(test_FLQuant_get_dim(flq_in), is_identical_to(dim(flq_in)))
#    expect_that(test_FLQuant_get_dimnames(flq_in), is_identical_to(dimnames(flq_in)))
#    # set
#    wrong_dim <- c(3,10,1,1,4,50)
#    small_dim <- c(10,100)
#    # Try to set incorrect dims
#    expect_that(test_FLQuant_set_dim(flq_in, wrong_dim), throws_error())
#    expect_that(test_FLQuant_set_dim(flq_in, small_dim), throws_error())
#    new_dim <- c(5,60,2,4,8,250) # Same TOTAL dim as original
#    # This throws an Rcpp error - interesting - restricted by dimnames
#    expect_that(test_FLQuant_set_dim(flq_in, new_dim), throws_error())
#    #dmns <- list(length=6:10, year=1901:1960, unit=c("male","female"), season=1:4,area=1:8,iter=1:250)
#})
#
#

test_that("FLQuant get and set data accessors",{
    flq1 <- random_FLQuant_generator()
    flq2 <- flq1
    flq2[] <- rnorm(prod(dim(flq1)),sd = 10)
    # get
    expect_that(test_FLQuant_get_data(flq1), is_identical_to(c(flq1@.Data)))
    # set
    flq_out <- test_FLQuant_set_data(flq1, flq2@.Data)
    expect_that(flq_out, is_identical_to(flq2))
    # Try with different dims
    dim_flq1 <- dim(flq1)
    random_dim <- runif(1,min = 1, max = 6)
    dim_flq1[random_dim] <- dim_flq1[random_dim] + 1
    flq3 <- FLQuant(1, dim = dim_flq1)
    expect_that(test_FLQuant_set_data(flq1, flq3@.Data), throws_error())
})

#
#test_that("FLQuant match_dims method works", {
#    flq_in <- FLQuant(rnorm(10*30*4*2*4*500), dim = c(10,30,4,2,4,500))
#    flq_in1 <- FLQuant(rnorm(5*30*4*2*4*500), dim = c(5,30,4,2,4,500))
#    flq_in2 <- FLQuant(rnorm(10*20*4*2*4*500), dim = c(10,20,4,2,4,500))
#    flq_in3 <- FLQuant(rnorm(10*30*3*2*4*500), dim = c(10,30,3,2,4,500))
#    flq_in4 <- FLQuant(rnorm(10*30*4*3*4*500), dim = c(10,30,4,3,4,500))
#    flq_in5 <- FLQuant(rnorm(10*30*4*2*8*500), dim = c(10,30,4,2,8,500))
#    flq_in6 <- FLQuant(rnorm(10*30*4*2*4*200), dim = c(10,30,4,2,4,200))
#    expect_that(test_FLQuant_match_dims(flq_in, flq_in), is_identical_to(1L))
#    expect_that(test_FLQuant_match_dims(flq_in, flq_in1), is_identical_to(-1L))
#    expect_that(test_FLQuant_match_dims(flq_in, flq_in2), is_identical_to(-2L))
#    expect_that(test_FLQuant_match_dims(flq_in, flq_in3), is_identical_to(-3L))
#    expect_that(test_FLQuant_match_dims(flq_in, flq_in4), is_identical_to(-4L))
#    expect_that(test_FLQuant_match_dims(flq_in, flq_in5), is_identical_to(-5L))
#    expect_that(test_FLQuant_match_dims(flq_in, flq_in6), is_identical_to(-6L))
#})
#
#
#test_that("FLQuant get dimension accessors",{
#    flq_in <- FLQuant(rnorm(10*30*4*2*4*500), dim = c(10,30,4,2,4,500))
#    expect_that(length(dimnames(flq_in)$quant), is_identical_to(test_FLQuant_get_nquant(flq_in)))
#    expect_that(length(dimnames(flq_in)$year), is_identical_to(test_FLQuant_get_nyear(flq_in)))
#    expect_that(length(dimnames(flq_in)$unit), is_identical_to(test_FLQuant_get_nunit(flq_in)))
#    expect_that(length(dimnames(flq_in)$season), is_identical_to(test_FLQuant_get_nseason(flq_in)))
#    expect_that(length(dimnames(flq_in)$area), is_identical_to(test_FLQuant_get_narea(flq_in)))
#    expect_that(length(dimnames(flq_in)$iter), is_identical_to(test_FLQuant_get_niter(flq_in)))
#})
#
#test_that("FLQuant get and set data accessors", {
#    flq_in <- FLQuant(rnorm(10*30*4*2*4*500), dim = c(10,30,4,2,4,500))
#    indices <- round(runif(6,min=1, max = dim(flq_in)))
#    # Get - flq(q,y,u,s,a,i)
#    value_out <- test_FLQuant_get_accessor(flq_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6])
#    expect_that(c(flq_in[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value_out))
#    # Testing accessing outside of dim range
#    expect_that(test_FLQuant_get_accessor(flq_in, 100, indices[2], indices[3], indices[4], indices[5], indices[6]), throws_error())
#    # Set - flq(q,y,u,s,a,i) = value
#    value_in <- rnorm(1)
#    flq_out <- test_FLQuant_set_accessor(flq_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value_in)
#    expect_that(c(flq_out[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value_in))
#    # Testing accessing outside of dim range
#    expect_that(test_FLQuant_set_accessor(flq_in, 100, indices[2], indices[3], indices[4], indices[5], indices[6], value_in), throws_error())
#    # Single element get and set -  flq(index)
#    element <- round(runif(1,min=1,max=prod(dim(flq_in))))
#    expect_that(test_FLQuant_get_single_index_accessor(flq_in,element), is_identical_to(c(flq_in)[element]))
#    value_in <- rnorm(1)
#    flq_out <- test_FLQuant_set_single_index_accessor(flq_in,element,value_in)
#    expect_that(c(flq_out)[element], is_identical_to(value_in))
#    # Checking that returning a reference doesn't cause problems when reassigning
#    flq_out <- test_FLQuant_get_single_index_accessor2(flq_in, element)[["flq_out"]]
#    expect_that(c(flq_out)[element], is_identical_to(c(flq_in)[element]))
#})
#
## Tests that a 'deep' copy has been made
#test_that("FLQuant assignment operator",{
#    flq_in <- FLQuant(rnorm(10*30*4*2*4*500), dim = c(10,30,4,2,4,500))
#    indices <- round(runif(6,min=1, max = dim(flq_in)))
#    value_in <- rnorm(1)
#    # Makes a copy of flq_in, changes a value of flq_in.
#    flqs <-  test_FLQuant_assignment_operator(flq_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value_in)
#    expect_that(flq_in, is_identical_to(flqs[["flq2"]]))
#    expect_that(c(flqs[["flq1"]][indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value_in))
#})
#
#test_that("FLQuant multiplier operators", {
#    flq_in <- FLQuant(rnorm(10*20*4*2*4*100), dim = c(10,20,4,2,4,100))
#    flq_in2 <- FLQuant(rnorm(10*20*4*2*4*100), dim = c(10,20,4,2,4,100))
#    flq_in3 <- FLQuant(rnorm(5*20*4*2*4*100), dim = c(5,20,4,2,4,100))
#    # FLQ *= FLQ
#    flq_out <- test_FLQuant_FLQuant_multiplier_assignment_operator(flq_in,flq_in2)
#    expect_that(flq_out@.Data, is_identical_to((flq_in * flq_in2)@.Data)) # units will be different so only check data
#    expect_that(test_FLQuant_FLQuant_multiplier_assignment_operator(flq_in,flq_in3), throws_error())
#    # FLQ * FLQ
#    flq_out <- test_FLQuant_FLQuant_multiplier_operator(flq_in,flq_in2)
#    expect_that((flq_in * flq_in2)@.Data, is_identical_to(flq_out@.Data))
#    expect_that(test_FLQuant_FLQuant_multiplier_operator(flq_in,flq_in3), throws_error())
#    # Deep copy check
#    flqs_out <- test_FLQuant_FLQuant_multiplier_uses_deep_copy(flq_in, flq_in2)
#    expect_that((flq_in * flq_in2)@.Data, is_identical_to(flqs_out[["flq3"]]@.Data))
#    expect_that(flq_in, is_identical_to(flqs_out[["flq1"]]))
#    expect_that(flq_in2, is_identical_to(flqs_out[["flq2"]]))
#    # FLQ *= and * double
#    value <- rnorm(1)
#    expect_that(test_FLQuant_double_multiplier_assignment_operator(flq_in, value), is_identical_to(flq_in * value))
#    expect_that(test_FLQuant_double_multiplier_operator(flq_in, value), is_identical_to(flq_in * value))
#})
#
#test_that("FLQuant divide operators", {
#    flq_in <- FLQuant(rnorm(10*20*4*2*4*100), dim = c(10,20,4,2,4,100))
#    flq_in2 <- FLQuant(rnorm(10*20*4*2*4*100), dim = c(10,20,4,2,4,100))
#    flq_in3 <- FLQuant(rnorm(5*20*4*2*4*100), dim = c(5,20,4,2,4,100))
#    # FLQ /= FLQ
#    flq_out <- test_FLQuant_FLQuant_divide_assignment_operator(flq_in,flq_in2)
#    expect_that(flq_out@.Data, is_identical_to((flq_in / flq_in2)@.Data)) # units will be different so only check data
#    expect_that(test_FLQuant_FLQuant_divide_assignment_operator(flq_in,flq_in3), throws_error())
#    # FLQ / FLQ
#    flq_out <- test_FLQuant_FLQuant_divide_operator(flq_in,flq_in2)
#    expect_that((flq_in / flq_in2)@.Data, is_identical_to(flq_out@.Data))
#    expect_that(test_FLQuant_FLQuant_divide_operator(flq_in,flq_in3), throws_error())
#    # FLQ /= and / double
#    value <- rnorm(1)
#    expect_that(test_FLQuant_double_divide_assignment_operator(flq_in, value), is_identical_to(flq_in / value))
#    expect_that(test_FLQuant_double_divide_operator(flq_in, value), is_identical_to(flq_in / value))
#})
#
#test_that("FLQuant addition operators", {
#    flq_in <- FLQuant(rnorm(10*20*4*2*4*100), dim = c(10,20,4,2,4,100))
#    flq_in2 <- FLQuant(rnorm(10*20*4*2*4*100), dim = c(10,20,4,2,4,100))
#    flq_in3 <- FLQuant(rnorm(5*20*4*2*4*100), dim = c(5,20,4,2,4,100))
#    # FLQ += FLQ
#    flq_out <- test_FLQuant_FLQuant_addition_assignment_operator(flq_in,flq_in2)
#    expect_that(flq_out@.Data, is_identical_to((flq_in + flq_in2)@.Data)) # units will be different so only check data
#    expect_that(test_FLQuant_FLQuant_addition_assignment_operator(flq_in,flq_in3), throws_error())
#    # FLQ + FLQ
#    flq_out <- test_FLQuant_FLQuant_addition_operator(flq_in,flq_in2)
#    expect_that((flq_in + flq_in2)@.Data, is_identical_to(flq_out@.Data))
#    expect_that(test_FLQuant_FLQuant_addition_operator(flq_in,flq_in3), throws_error())
#    # FLQ += and + double
#    value <- rnorm(1)
#    expect_that(test_FLQuant_double_addition_assignment_operator(flq_in, value), is_identical_to(flq_in + value))
#    expect_that(test_FLQuant_double_addition_operator(flq_in, value), is_identical_to(flq_in + value))
#})
#
#test_that("FLQuant difference operators", {
#    flq_in <- FLQuant(rnorm(10*20*4*2*4*100), dim = c(10,20,4,2,4,100))
#    flq_in2 <- FLQuant(rnorm(10*20*4*2*4*100), dim = c(10,20,4,2,4,100))
#    flq_in3 <- FLQuant(rnorm(5*20*4*2*4*100), dim = c(5,20,4,2,4,100))
#    # FLQ += FLQ
#    flq_out <- test_FLQuant_FLQuant_difference_assignment_operator(flq_in,flq_in2)
#    expect_that(flq_out@.Data, is_identical_to((flq_in - flq_in2)@.Data)) # units will be different so only check data
#    expect_that(test_FLQuant_FLQuant_difference_assignment_operator(flq_in,flq_in3), throws_error())
#    # FLQ + FLQ
#    flq_out <- test_FLQuant_FLQuant_difference_operator(flq_in,flq_in2)
#    expect_that((flq_in - flq_in2)@.Data, is_identical_to(flq_out@.Data))
#    expect_that(test_FLQuant_FLQuant_difference_operator(flq_in,flq_in3), throws_error())
#    # FLQ -= and - double
#    value <- rnorm(1)
#    expect_that(test_FLQuant_double_difference_assignment_operator(flq_in, value), is_identical_to(flq_in - value))
#    expect_that(test_FLQuant_double_difference_operator(flq_in, value), is_identical_to(flq_in - value))
#})
#
## What happens to logging negative values?
#test_that("FLQuant log and exp functions", {
#    flq_in <- abs(FLQuant(rnorm(10*20*4*2*4*100), dim = c(10,20,4,2,4,100)))
#    expect_that(log(flq_in), is_identical_to(test_FLQuant_log_function(flq_in)))
#    flq_in2 <- (FLQuant(rnorm(10*20*4*2*4*100), dim = c(10,20,4,2,4,100)))
#    expect_that(exp(flq_in2), is_identical_to(test_FLQuant_exp_function(flq_in2)))
#})
#
#test_that("FLQuant chaining operators", {
#    flq_in <- abs(FLQuant(rnorm(10*20*4*2*4*100), dim = c(10,20,4,2,4,100)))
#    flq_out <- test_FLQuant_chaining_operators(flq_in)
#    out = (log(flq_in + flq_in * flq_in * exp(flq_in)) - flq_in) / flq_in
#    expect_that(out@.Data, is_identical_to(flq_out@.Data))
#})
#
