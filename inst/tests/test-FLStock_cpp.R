context("CPP implementation of FLStock")

test_that("FLStock SEXP constructor",{
    data(ple4)
    sn <- test_FLStock_sexp_constructor(ple4)
    expect_that(sn, is_identical_to(ple4@stock.n))
})

test_that("FLStock wrap and as",{
    data(ple4)
    fls <- test_FLStock_wrap(ple4)
    expect_that(fls, is_identical_to(ple4))
    flq <- test_FLStock_as(ple4)
    expect_that(flq, is_identical_to(ple4@stock.n))
})

test_that("FLStock copy constructor works properly",{
    data(ple4)
    indices <- round(runif(6,min=1, max = dim(ple4@stock.n)))
    value_in <- rnorm(1)
    # Makes a copy of ple4@stock.n, changes a value, returns original and new FLStock
    # Checks that the copy constuctor makes a 'deep' copy else changing a value in the copy FLS will also change a value in the original FLS
    flss <- test_FLStock_copy_constructor(ple4, indices[1], indices[2], indices[3], indices[4], indices[5], indices[6], value_in)
    expect_that(ple4, is_identical_to(flss[["fls2"]]))
    expect_that(c(flss[["fls1"]]@stock.n[indices[1], indices[2], indices[3], indices[4], indices[5], indices[6]]), is_identical_to(value_in))
})
