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
    # Change dim of f, f_spwn and biol - dimension check
    new_dim <- dim(flq) + round(runif(6,min=1,max=3))
    new_flb <- random_FLBiol_generator(fixed_dims = new_dim)
    new_flfs <- random_FLFisheries_generator(fixed_dims = new_dim, min_fisheries=1, max_fisheries=1)
    new_f <- random_FLQuant_list_generator(max_elements=1, fixed_dims = new_dim)
    new_f <- lapply(new_f,abs)
    new_f_spwn <- random_FLQuant_list_generator(max_elements=1, fixed_dims = new_dim)
    new_f_spwn <- lapply(new_f_spwn,abs)
    expect_that(test_operatingModel_full_constructor(flfs, new_flb, "ricker", params.ricker, residuals.ricker, residuals_mult, f, f_spwn), throws_error()) 
    expect_that(test_operatingModel_full_constructor(new_flfs, flb, "ricker", params.ricker, residuals.ricker, residuals_mult, f, f_spwn), throws_error())
    expect_that(test_operatingModel_full_constructor(flfs, flb, "ricker", params.ricker, residuals.ricker, residuals_mult, new_f, f_spwn), throws_error())
    expect_that(test_operatingModel_full_constructor(flfs, flb, "ricker", params.ricker, residuals.ricker, residuals_mult, f, new_f_spwn), throws_error())
})

test_that("operatingModel SRR methods", {
    # Bits
    data(ple4)
    ple4_sr_ricker <- fmle(as.FLSR(ple4,model="ricker"), control  = list(trace=0))
    params_ricker <- as.FLQuant(params(ple4_sr_ricker))
    residuals_ricker <- FLQuant(rnorm(dim(flq)[2] * dim(flq)[6]), dimnames = list(year = 1:dim(flq)[2], iter = 1:dim(flq)[6]))
    residuals_mult <- TRUE

    flq <- random_FLQuant_generator(sd=1)
    flb <- random_FLBiol_generator(fixed_dims = dim(flq), sd = 1 )
    flfs <- random_FLFisheries_generator(fixed_dims = dim(flq), min_fisheries=1, max_fisheries=1, sd=1)
    dim(flq)
    summary(flb)
    summary(flfs[[1]][[1]])
    f <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq), sd=1)
    f <- lapply(f,abs)
    f_spwn <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq), sd=1)
    f_spwn <- lapply(f_spwn,abs)

})


test_that("operatingModel SSB methods", {
    data(ple4)
    ple4_sr_ricker <- fmle(as.FLSR(ple4,model="ricker"), control  = list(trace=0))
    params_ricker <- as.FLQuant(params(ple4_sr_ricker))

    flq <- random_FLQuant_generator(sd=1)
    flb <- random_FLBiol_generator(fixed_dims = dim(flq), sd = 1 )
    flfs <- random_FLFisheries_generator(fixed_dims = dim(flq), min_fisheries=1, max_fisheries=1, sd=1)
    f <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq), sd=1)
    f <- lapply(f,abs)
    f_spwn <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq), sd=1)
    f_spwn <- lapply(f_spwn,abs)
    residuals_ricker <- FLQuant(rnorm(dim(flq)[2] * dim(flq)[6]), dimnames = list(year = 1:dim(flq)[2], iter = 1:dim(flq)[6]))
    residuals_mult <- TRUE

    # SSB
    ssb_in <- quantSums(n(flb) * wt(flb) * fec(flb) * exp(-f[[1]]*f_spwn[[1]] - m(flb) * spwn(flb)))
    ssb_out <- test_operatingModel_SSB_FLQ(flfs, flb, 'ricker', params_ricker, residuals_ricker, residuals_mult, f, f_spwn)
    expect_that(ssb_in@.Data, equals(ssb_out@.Data))
    ssb_out <- test_operatingModelAdolc_SSB_FLQ(flfs, flb, 'ricker', params_ricker, residuals_ricker, residuals_mult, f, f_spwn)
    expect_that(ssb_in@.Data, equals(ssb_out@.Data))
    # SSB all iters
    timestep <- floor(runif(1, min=1, max = dim(flq)[2] * dim(flq)[4]))
    unit <- floor(runif(1, min=1, max = dim(flq)[3]))
    area <- floor(runif(1, min=1, max = dim(flq)[5]))
    ssb_out <- test_operatingModel_SSB_iters(flfs, flb, 'ricker', params_ricker, residuals_ricker, residuals_mult, f, f_spwn, timestep, unit, area)
    year <-  floor((timestep-1) / dim(flq)[4] + 1)
    season <- (timestep-1) %% dim(flq)[4] + 1;
    expect_that((ssb_in[,year,unit,season,area])@.Data, equals(ssb_out@.Data))
    # SSB single iter
    iter <- floor(runif(1, min=1, max = dim(flq)[6]))
    ssb_out <- test_operatingModel_SSB_single_iter(flfs, flb, 'ricker', params_ricker, residuals_ricker, residuals_mult, f, f_spwn, timestep, unit, area, iter)
    expect_that(c(ssb_in[,year,unit,season,area,iter]), equals(c(ssb_out)))


})
