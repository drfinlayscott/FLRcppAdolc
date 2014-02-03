context("Implementation of operatingModel- double and Adolc versions")

test_that("operatingModel constructors",{
    # Empty constructor
    test_operatingModel_empty_constructor()
    test_operatingModelAdolc_empty_constructor()
    # Full constructor with wrap
    flq <- random_FLQuant_generator()
    flb <- random_FLBiol_generator(fixed_dims = dim(flq))
    flfs <- random_FLFisheries_generator(fixed_dims = dim(flq), min_fisheries=1, max_fisheries=1)
    #dim(flq)
    #summary(flb)
    #summary(flfs[[1]][[1]])
    data(ple4)
    ple4.sr.ricker <- fmle(as.FLSR(ple4,model="ricker"), control  = list(trace=0))
    params.ricker <- as.FLQuant(params(ple4.sr.ricker))
    residuals.ricker <- FLQuant(rnorm(100), dimnames = list(year = 1:10, iter = 1:10))
    residuals_mult <- TRUE
    f <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq))
    f <- lapply(f,abs)
    f_spwn <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq))
    f_spwn <- lapply(f_spwn,abs)
    out <- test_operatingModel_full_constructor(flfs, flb, "ricker", params.ricker, residuals.ricker, residuals_mult, f, f_spwn)
    expect_that(out[["biol"]], is_identical_to(flb))
    expect_that(out[["fisheries"]], is_identical_to(flfs))
    expect_that(out[["f"]], is_identical_to(f))
    expect_that(out[["f_spwn"]], is_identical_to(f_spwn))



})

