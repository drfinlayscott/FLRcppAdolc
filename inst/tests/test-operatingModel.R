context("Implementation of operatingModel")

test_that("operatingModel constructors",{
    # Empty constructor - jusy check they don't fail
    test_operatingModel_empty_constructor()
    # Set up parameters for full test - lots of things needed
    flq <- random_FLQuant_generator()
    flb <- random_FLBiol_generator(fixed_dims = dim(flq))
    flfs <- random_FLFisheries_generator(fixed_dims = dim(flq), min_fisheries=1, max_fisheries=1)
    data(ple4)
    ple4.sr.ricker <- fmle(as.FLSR(ple4,model="ricker"), control  = list(trace=0))
    params.ricker <- as.FLQuant(params(ple4.sr.ricker))
    residuals.ricker <- FLQuant(rnorm(100), dimnames = list(year = 1:10, iter = 1:10))
    residuals_mult <- TRUE
    timelag <- 0
    f <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq))
    f <- lapply(f,abs)
    f_spwn <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq))
    f_spwn <- lapply(f_spwn,abs)
    # At last, a test
    # Full constructor with wrap
    fc <- dummy_fwdControl_generator(years = 1, niters = dim(n(flb))[6])
    out <- test_operatingModel_full_constructor(flfs, flb, "ricker", params.ricker, timelag, residuals.ricker, residuals_mult, f, f_spwn, fc)
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
    expect_that(test_operatingModel_full_constructor(flfs, new_flb, "ricker", params.ricker, timelag, residuals.ricker, residuals_mult, f, f_spwn, fc), throws_error()) 
    expect_that(test_operatingModel_full_constructor(new_flfs, flb, "ricker", params.ricker, timelag, residuals.ricker, residuals_mult, f, f_spwn, fc), throws_error())
    expect_that(test_operatingModel_full_constructor(flfs, flb, "ricker", params.ricker, timelag, residuals.ricker, residuals_mult, new_f, f_spwn, fc), throws_error())
    expect_that(test_operatingModel_full_constructor(flfs, flb, "ricker", params.ricker, timelag, residuals.ricker, residuals_mult, f, new_f_spwn, fc), throws_error())
})

#test_that("operatingModel SRR methods", {
#    # Bits
#    data(ple4)
#    ple4_sr_ricker <- fmle(as.FLSR(ple4,model="ricker"), control  = list(trace=0))
#    params_ricker <- as.FLQuant(params(ple4_sr_ricker))
#
#    flq <- random_FLQuant_generator(sd=1)
#    flb <- random_FLBiol_generator(fixed_dims = dim(flq), sd = 1 )
#    flfs <- random_FLFisheries_generator(fixed_dims = dim(flq), min_fisheries=1, max_fisheries=1, sd=1)
#    residuals_ricker <- FLQuant(rnorm(dim(flq)[2] * dim(flq)[6]), dimnames = list(year = 1:dim(flq)[2], iter = 1:dim(flq)[6]))
#    residuals_mult <- TRUE
#    f <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq), sd=1)
#    f <- lapply(f,abs)
#    f_spwn <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq), sd=1)
#    f_spwn <- lapply(f_spwn,abs)
#
#})


test_that("operatingModel SSB methods", {
    #  Lots of things needed for test
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
    timelag <- 0
    fc <- dummy_fwdControl_generator(years = 1, niters = dim(n(flb))[6])

    # SSB - FLQuant - lots of time steps
    ssb_in <- quantSums(n(flb) * wt(flb) * fec(flb) * exp(-f[[1]]*f_spwn[[1]] - m(flb) * spwn(flb)))
    ssb_out <- test_operatingModel_SSB_FLQ(flfs, flb, 'ricker', params_ricker, timelag, residuals_ricker, residuals_mult, f, f_spwn, fc)
    expect_that(ssb_in@.Data, equals(ssb_out@.Data))
    # SSB - FLQuant - single single timestep - all iters
    timestep <- floor(runif(1, min=1, max = dim(flq)[2] * dim(flq)[4]))
    unit <- floor(runif(1, min=1, max = dim(flq)[3]))
    area <- floor(runif(1, min=1, max = dim(flq)[5]))
    ssb_out <- test_operatingModel_SSB_iters(flfs, flb, 'ricker', params_ricker, timelag, residuals_ricker, residuals_mult, f, f_spwn, timestep, unit, area, fc)
    year <-  floor((timestep-1) / dim(flq)[4] + 1)
    season <- (timestep-1) %% dim(flq)[4] + 1;
    expect_that((ssb_in[,year,unit,season,area])@.Data, equals(ssb_out@.Data))
    # SSB - numeric - single timestep - single iter
    iter <- floor(runif(1, min=1, max = dim(flq)[6]))
    ssb_out <- test_operatingModel_SSB_single_iter(flfs, flb, 'ricker', params_ricker, timelag, residuals_ricker, residuals_mult, f, f_spwn, timestep, unit, area, iter, fc)
    expect_that(c(ssb_in[,year,unit,season,area,iter]), equals(c(ssb_out)))
    # SSB non-conformable FLQuant iters, e.g. wt has only 1 iter, but n has many
    single_iter <- round(runif(1,min=1,max=dim(flq)[6]))
    flb2 <- flb
    wt(flb2) <- iter(wt(flb2),single_iter)
    fec(flb2) <- iter(fec(flb2),single_iter)
    m(flb2) <- iter(m(flb2),single_iter)
    ssb_out <- test_operatingModel_SSB_single_iter(flfs, flb2, 'ricker', params_ricker, timelag, residuals_ricker, residuals_mult, f, f_spwn, timestep, unit, area, iter, fc)
    ssb_in <- quantSums(n(flb2) * wt(flb2) * fec(flb2) * exp(-f[[1]]*f_spwn[[1]] - m(flb2) * spwn(flb2)))
    expect_that(c(ssb_in[,year,unit,season,area,iter]), equals(c(ssb_out)))
    # SSB with year and season
    ssb_out <- test_operatingModel_SSB_single_iter_year_season(flfs, flb2, 'ricker', params_ricker, timelag, residuals_ricker, residuals_mult, f, f_spwn, year, unit, season, area, iter, fc)
    expect_that(c(ssb_in[,year,unit,season,area,iter]), equals(c(ssb_out)))
})


test_that("operatingModel project_timestep", {
    # Get the components
    data(ple4)
    srr_model_name <- "ricker"
    ple4_sr <- fmle(as.FLSR(ple4,model=srr_model_name), control  = list(trace=0))
    params_sr <- as.FLQuant(params(ple4_sr))
    # Have at least 5 years
    flq <- random_FLQuant_generator(fixed_dim=c(NA,5,1,NA,1,NA), sd=1)
    flb <- random_FLBiol_generator(fixed_dims = dim(flq), sd = 1 )
    flfs <- random_FLFisheries_generator(fixed_dims = dim(flq), min_fisheries=1, max_fisheries=1, sd=1)
    f <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq), sd=1)
    f <- lapply(f,abs)
    f_spwn <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq), sd=1)
    f_spwn <- lapply(f_spwn,abs)
    residuals_sr <- abs(FLQuant(rnorm(prod(dim(flq)[-1])), dimnames = list(year = 1:dim(flq)[2], unit = 1:dim(flq)[3], season = 1:dim(flq)[4], area = 1:dim(flq)[5], iter = 1:dim(flq)[6])))
    residuals_mult <- TRUE
    timelag <- 1
    fc <- dummy_fwdControl_generator(years = 1, niters = dim(n(flb))[6])

    # Test seasonal projection - ignore SRR
    nseason <- dim(flq)[4]
    timestep <- round(runif(1, min=1,max=(nseason * dim(flq)[2])-1))
    om_out <- test_operating_model_project(flfs, flb, srr_model_name, params_sr, timelag, residuals_sr, residuals_mult, f, f_spwn, timestep, fc)
    om_R <- simple_fisheries_project(flfs, flb, ple4_sr, f, f_spwn, residuals_sr, residuals_mult, timestep)
    year =  (timestep-1) / nseason + 1; 
    season = (timestep-1) %% nseason + 1;
    next_year =  (timestep+1-1) / nseason + 1; 
    next_season = (timestep+1-1) %% nseason + 1;
    # check the catches etc
    expect_that(catch.n(om_out[["fisheries"]][[1]][[1]])[,year,1,season,1,]@.Data, is_identical_to(catch.n(om_R[["flfs"]][[1]][[1]])[,year,1,season,1,]@.Data))
    expect_that(landings.n(om_out[["fisheries"]][[1]][[1]])[,year,1,season,1,]@.Data, is_identical_to(landings.n(om_R[["flfs"]][[1]][[1]])[,year,1,season,1,]@.Data))
    expect_that(discards.n(om_out[["fisheries"]][[1]][[1]])[,year,1,season,1,]@.Data, is_identical_to( discards.n(om_R[["flfs"]][[1]][[1]])[,year,1,season,1,]@.Data))
    # Check n (not recs)
    expect_that(om_out[["biol"]]@n[-1,next_year,1,next_season,1,]@.Data, is_identical_to( om_R[["flb"]]@n[-1,next_year,1,next_season,1,]@.Data))

    # Check with annual SRR
    # Test annual model to start with
    flq <- random_FLQuant_generator(fixed_dim=c(NA,5,1,1,1,NA),sd=1)
    flb <- random_FLBiol_generator(fixed_dims = dim(flq), sd = 1 )
    flfs <- random_FLFisheries_generator(fixed_dims = dim(flq), min_fisheries=1, max_fisheries=1, sd=1)
    f <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq), sd=1)
    units(f[[1]]) <- "f"
    f <- lapply(f,abs)
    f_spwn <- random_FLQuant_list_generator(max_elements=1, fixed_dims = dim(flq), sd=1)
    units(f_spwn[[1]]) <- "prop"
    f_spwn <- lapply(f_spwn,abs)
    residuals_sr <- abs(FLQuant(rnorm(prod(dim(flq)[-1])), dimnames = list(year = 1:dim(flq)[2], unit = 1:dim(flq)[3], season = 1:dim(flq)[4], area = 1:dim(flq)[5], iter = 1:dim(flq)[6])))
    #residuals_sr <- abs(FLQuant(1, dimnames = list(year = 1:dim(flq)[2], unit = 1:dim(flq)[3], season = 1:dim(flq)[4], area = 1:dim(flq)[5], iter = 1:dim(flq)[6])))
    residuals_mult <- TRUE
    fc <- dummy_fwdControl_generator(years = 1, niters = dim(n(flb))[6])

    timesteps <- 1:(dim(flq)[2]-1)
    project_r <- list(flfs = flfs, flb=flb)

    for (timestep in timesteps){
        project_r <- simple_fisheries_project(project_r[["flfs"]], project_r[["flb"]], ple4_sr, f, f_spwn, residuals_sr, residuals_mult, timestep)
    }
    # Check recruitment in R method
    project_c <- list(fisheries = flfs, biol=flb)
    for (timestep in timesteps){
        project_c <- test_operating_model_project(project_c[["fisheries"]], project_c[["biol"]], "ricker", params_sr, 1, residuals_sr, residuals_mult, f, f_spwn, timestep, fc)
    }
    # Check biol timestep up to max timesteps + 1
    expect_that((project_c[["biol"]]), equals((project_r[["flb"]])))


    # Check fisheries catch timestep up to max timesteps
    flfs_c <- window(project_c[["fisheries"]][[1]][[1]], start=timesteps[1], end=max(timesteps))
    flfs_r <- window(project_r[["flfs"]][[1]][[1]], start=timesteps[1], end=max(timesteps))
    # expect_that(flfs_c, equals(flfs_r)) # cannot check units as c++ code does not adapt units
    expect_that(flfs_c@discards.n@.Data, equals(flfs_r@discards.n@.Data))
    expect_that(flfs_c@landings.n@.Data, equals(flfs_r@landings.n@.Data))

    # What about SRR on a different timestep
})


test_that("operatingModel target values", {
    # Make an FLFishery with X FLFishery objects. Each FLFishery has an FLCatch that catches the FLBiol
    # This is all a massive faff
    # Have at least 5 years and 10 ages, random number of seasons
    flq <- random_FLQuant_generator(fixed_dim=c(10,5,NA,NA,NA,NA), sd=1)
    # Single FLBiol
    flb <- random_FLBiol_generator(fixed_dims = dim(flq), sd = 1 )
    flfs <- random_FLFisheries_generator(fixed_dims = dim(flq), min_fisheries=2, max_fisheries=5, min_catches = 1, max_catches = 3, sd=1)
    # Each element of F is F from an FLCatch attacking the same FLBiol
    f <- random_FLQuant_list_generator(min_elements=length(flfs), max_elements=length(flfs), fixed_dims = dim(flq), sd=1)
    f <- lapply(f,abs)
    f_spwn <- random_FLQuant_list_generator(min_elements=length(flfs), max_elements=length(flfs), fixed_dims = dim(flq), sd=1)
    f_spwn <- lapply(f_spwn,abs)
    # SRR bits
    srr_model_name <- "ricker"
    params_sr <- as.FLQuant(FLPar(a=10, b = 4))
    residuals_sr <- flq[1,]
    residuals_mult <- TRUE
    srr_timelag <- 1
    fc <- dummy_fwdControl_generator(years = 1, niters = dim(n(flb))[6])
    # Hack fbar range in catch
    minfbar <- round(runif(n=1,min=1,max=4))
    maxfbar <- round(runif(n=1,min=5,max=10))
    for (i in 1:length(flfs)){
        for (j in 1:length(flfs[[i]])){
            flfs[[i]][[j]]@range <- c(flfs[[i]][[j]]@range, minfbar = minfbar, maxfbar = maxfbar)
        }
    }
    # WTF? why does description get reset to nothing? flfs@desc
    flfs@desc <- "xxx"
    # Catch no has be to 1 at the moment - we only have 1 biol and we need to think about how to link a biol to a catch
    catch_no <- 1 # round(runif(n=1,min=1,max=min(unlist(lapply(flfs, length))))) # which catch no of each fishery
    fishery_no <- round(runif(1, min=1, max=length(flfs)))

    # Get the target values from the C++ code
    targets <- test_operating_model_targets(flfs, flb, "ricker", params_sr, 1, residuals_sr, residuals_mult, f, f_spwn, fc, fishery_no, catch_no)
    # fbar of a single catch 
    expect_that(targets[["fbar_catch"]], equals(apply(f[[fishery_no]][minfbar:maxfbar,],2:6,mean)))
    # total fbar of all fisheries
    f2 <- lapply(f, function(x) apply(x[minfbar:maxfbar,],2:6,mean))
    f_total <- f2[[1]]
    f_total[] <- 0
    for (i in 1:length(flfs)){
        f_total <- f_total + f2[[i]]
    }
    expect_that(targets[["fbar"]], is_identical_to(targets[["fbar"]]))

    # catches - single
    expect_that( targets[["catches_catch"]]@.Data , equals(catch(flfs[[fishery_no]][[catch_no]])@.Data))
    # catches - total
    catches_total <- catch(flfs[[fishery_no]][[catch_no]])
    catches_total[] <- 0
    for (i in 1:length(flfs)){
        catches_total <- catches_total + catch(flfs[[i]][[catch_no]])
    }
    expect_that(targets[["catches"]]@.Data, equals(catches_total@.Data))
})
