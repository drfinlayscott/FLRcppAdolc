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

