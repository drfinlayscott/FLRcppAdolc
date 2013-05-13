context("CPP implementation of FLQuant")

test_that("FLQuant as and wrap",{
    flq_in <- FLQuant(rnorm(10*30*4*2*4*500), dim = c(10,30,4,2,4,500))
    flq_out <- test_FLQuant_as_wrap(flq_in)
    expect_that(flq_in, is_identical_to(flq_out))
})


test_that("FLQuant constructors",{
    # SEXP constructor - used in as
    flq_in <- FLQuant(rnorm(10*30*4*2*4*500), dim = c(10,30,4,2,4,500))
    flq_out <- test_FLQuant_sexp_constructor(flq_in)
    expect_that(flq_in, is_identical_to(flq_out))
    # Copy constructor
    indices <- round(runif(6,min=1, max = dim(flq_in)))
    value_in <- rnorm(1)
    # Makes a copy of flq_in, changes a value of flq_in.
    flqs <-  test_FLQuant_copy_constructor(flq_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value_in)
    expect_that(flq_in, is_identical_to(flqs[["flq2"]]))
    expect_that(c(flqs[["flq1"]][indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value_in))
})

test_that("FLQuant get and set units accessors",{
    flq_in <- FLQuant(rnorm(10*30*4*2*4*500), dim = c(10,30,4,2,4,500), units = "Kells")
    # get
    expect_that(test_FLQuant_get_units(flq_in), is_identical_to("Kells"))
    # set
    expect_that(units(test_FLQuant_set_units(flq_in, "Chaos")), is_identical_to("Chaos"))
})

test_that("FLQuant get dim accessors",{
    flq_in <- FLQuant(rnorm(10*30*4*2*4*500), dim = c(10,30,4,2,4,500))
    expect_that(length(dimnames(flq_in)$quant), is_identical_to(test_FLQuant_get_nquant(flq_in)))
    expect_that(length(dimnames(flq_in)$year), is_identical_to(test_FLQuant_get_nyear(flq_in)))
    expect_that(length(dimnames(flq_in)$unit), is_identical_to(test_FLQuant_get_nunit(flq_in)))
    expect_that(length(dimnames(flq_in)$season), is_identical_to(test_FLQuant_get_nseason(flq_in)))
    expect_that(length(dimnames(flq_in)$area), is_identical_to(test_FLQuant_get_narea(flq_in)))
    expect_that(length(dimnames(flq_in)$iter), is_identical_to(test_FLQuant_get_niter(flq_in)))
})

test_that("FLQuant get and set data accessors", {
    flq_in <- FLQuant(rnorm(10*30*4*2*4*500), dim = c(10,30,4,2,4,500))
    indices <- round(runif(6,min=1, max = dim(flq_in)))
    # get
    value_out <- test_FLQuant_get_accessor(flq_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6])
    expect_that(c(flq_in[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value_out))
    # set
    value_in <- rnorm(1)
    flq_out <- test_FLQuant_set_accessor(flq_in, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value_in)
    expect_that(c(flq_out[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value_in))
})

