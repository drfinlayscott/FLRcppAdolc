# 
# Copyright 2013 FLR Team. Distributed under the GPL 2 or later
# Maintainer: Finlay Scott, JRC
#

#' Generate randomly sized and filled FLQuant objects
#'
#' Generate a randomly sized FLQuant filled with normally distributed random numbers with a mean of 0.
#' Used for automatic testing.
#' 
#' @param max_age The maximum number of ages of the FLQuant. Default is 10. 
#' @param max_year The maximum number of years of the FLQuant. Default is 10. 
#' @param max_unit The maximum number of units of the FLQuant. Default is 5. 
#' @param max_season The maximum number of seasons of the FLQuant. Default is 4. 
#' @param max_area The maximum number of areas of the FLQuant. Default is 4. 
#' @param max_iter The maximum number of iters of the FLQuant. Default is 50. 
#' @param sd The standard deviation of the random numbers. Passed to rnorm() Default is 100.
#' @export
#' @return An FLQuant
#' @examples
#' flq <- random_FLQuant_generator()
#' dim(flq)
#' summary(flq)
random_FLQuant_generator <- function(max_age = 10, max_year = 10, max_unit = 5, max_season = 4, max_area = 4, max_iter = 50, sd = 100){
    nage <- runif(1,min=1, max=max_age)
    nyear <- runif(1,min=1, max=max_year)
    nunit <- runif(1,min=1, max=max_unit)
    nseason <- runif(1,min=1, max=max_season)
    narea <- runif(1,min=1, max=max_area)
    niter <- runif(1,min=1, max=max_iter)
    values <- rnorm(nage*nyear*nunit*nseason*narea*niter, sd = sd)
    flq <- FLQuant(values, dimnames = list(age = 1:nage, year = 1:nyear, unit = 1:nunit, season = 1:nseason, area = 1:narea, iter = 1:niter))
    units(flq) <- as.character(signif(abs(rnorm(1)),3))
    return(flq)
}

#' Generate lists of randomly sized and filled FLQuant objects
#'
#' Generate a list of randomly sized FLQuant objects filled with normally distributed random numbers with a mean of 0.
#' Used for automatic testing, particularly of the FLQuant7_base<T> class in CPP.
#' 
#' @param max_elements The maximum number of elements in the list. Default is 10. 
#' @param max_age The maximum number of ages of the FLQuant. Default is 10. 
#' @param max_year The maximum number of years of the FLQuant. Default is 10. 
#' @param max_unit The maximum number of units of the FLQuant. Default is 5. 
#' @param max_season The maximum number of seasons of the FLQuant. Default is 4. 
#' @param max_area The maximum number of areas of the FLQuant. Default is 4. 
#' @param max_iter The maximum number of iters of the FLQuant. Default is 50. 
#' @param sd The standard deviation of the random numbers. Passed to rnorm() Default is 100.
#' @export
#' @return A list of FLQuant objects
#' @examples
#' flq_list <- random_FLQuant_list_generator()
#' length(flq_list)
#' summary(flq_list)
#' lapply(flq_list, summary)
random_FLQuant_list_generator <- function(max_elements = 10, ...){
    nelements <- runif(1,min=1, max=max_elements)
    op <- list()
    for (i in 1:nelements){
        op[[i]] <- random_FLQuant_generator(...)
    }
    return(op)
}

#' Generate randomly sized and filled FLBiol objects
#'
#' Generate an FLBiol of random size and filled with normally distributed random numbers with a mean of 0.
#' Used for automatic testing, particularly of the fwdBiol class in CPP.
#' 
#' @param max_age The maximum number of ages of the FLBiol. Default is 10. 
#' @param max_year The maximum number of years of the FLBiol. Default is 10. 
#' @param max_unit The maximum number of units of the FLBiol. Default is 5. 
#' @param max_season The maximum number of seasons of the FLBiol. Default is 4. 
#' @param max_area The maximum number of areas of the FLBiol. Default is 4. 
#' @param max_iter The maximum number of iters of the FLBiol. Default is 50. 
#' @param sd The standard deviation of the random numbers. Passed to rnorm() Default is 100.
#' @export
#' @return An FLBiol
#' @examples
#' flb <- random_FLBiol_generator()
#' summary(flb)
random_FLBiol_generator <- function(sd=100, ...){
    flq <- random_FLQuant_generator(sd=sd, ...)
    biol <- FLBiol(n = flq)
    m(biol) <- rnorm(prod(dim(flq)),sd=sd)
    wt(biol) <- rnorm(prod(dim(flq)),sd=sd)
    fec(biol) <- rnorm(prod(dim(flq)),sd=sd)
    spwn(biol) <- rnorm(prod(dim(flq)),sd=sd)
    name(biol) <- as.character(rnorm(1)*1000)
    desc(biol) <- as.character(rnorm(1)*1000)
    return(biol)
}

#' Generate randomly sized and filled FLCatch objects
#'
#' Generate an FLCatch of random size and filled with normally distributed random numbers with a mean of 0.
#' Used for automatic testing, particularly of the FLCatch class in CPP.
#' 
#' @param max_age The maximum number of ages of the FLCatch. Default is 10. 
#' @param max_year The maximum number of years of the FLCatch. Default is 10. 
#' @param max_unit The maximum number of units of the FLCatch. Default is 5. 
#' @param max_season The maximum number of seasons of the FLCatch. Default is 4. 
#' @param max_area The maximum number of areas of the FLCatch. Default is 4. 
#' @param max_iter The maximum number of iters of the FLCatch. Default is 50. 
#' @param sd The standard deviation of the random numbers. Passed to rnorm() Default is 100.
#' @export
#' @return An FLCatch
#' @examples
#' flc <- random_FLCatch_generator()
#' summary(flc)
random_FLCatch_generator <- function(sd=100, ...){
    flq <- random_FLQuant_generator(sd=sd, ...)
    catch <- FLCatch(landings.n = flq)
    #landings.wt(catch) <- rnorm(prod(dim(flq)),sd=sd)
    #discards.n(catch) <- rnorm(prod(dim(flq)),sd=sd)
    #discards.wt(catch) <- rnorm(prod(dim(flq)),sd=sd)
    #catch.sel(catch) <- rnorm(prod(dim(flq)),sd=sd)
    #price(catch) <- rnorm(prod(dim(flq)),sd=sd)
    landings.wt(catch)[] <- rnorm(prod(dim(flq)),sd=sd)
    discards.n(catch)[] <- rnorm(prod(dim(flq)),sd=sd)
    discards.wt(catch)[] <- rnorm(prod(dim(flq)),sd=sd)
    catch.sel(catch)[] <- rnorm(prod(dim(flq)),sd=sd)
    price(catch)[] <- rnorm(prod(dim(flq)),sd=sd)
    # catch.q(catch) # undefined right now
    name(catch) <- as.character(rnorm(1)*1000)
    desc(catch) <- as.character(rnorm(1)*1000)
    return(catch)
}

