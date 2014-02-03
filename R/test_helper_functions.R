# 
# Copyright 2013 FLR Team. Distributed under the GPL 2 or later
# Maintainer: Finlay Scott, JRC
#

#' Generate randomly sized and filled FLQuant objects
#'
#' Generate a randomly or fixed sized FLQuant filled with normally distributed random numbers with a mean of 0.
#' Used for automatic testing.
#' All dimensions have at least length 2.
#' 
#' @param fixed_dims A vector of length 6 with the fixed length of each of the FLQuant dimensions. If any value is NA it is randomly set using the max_dims argument. Default value is rep(NA,6).
#' @param max_dims A vector of length 6 with maximum size of each of the FLQuant dimensions. Default value is c(5,10,5,4,4,5).
#' @param sd The standard deviation of the random numbers. Passed to rnorm() Default is 100.
#' @export
#' @return An FLQuant
#' @examples
#' flq <- random_FLQuant_generator()
#' dim(flq)
#' summary(flq)
#' flq <- random_FLQuant_generator(fixed_dims = c(NA,10,1,4,1,NA))
#' dim(flq)
#' summary(flq)
random_FLQuant_generator <- function(fixed_dims = rep(NA,6), max_dims = c(5,10,5,4,4,5), sd = 100){
    nage <- ifelse(is.na(fixed_dims[1]),runif(1,min=2, max=max_dims[1]),fixed_dims[1])
    nyear <- ifelse(is.na(fixed_dims[2]),runif(1,min=2, max=max_dims[2]),fixed_dims[2])
    nunit <- ifelse(is.na(fixed_dims[3]),runif(1,min=2, max=max_dims[3]),fixed_dims[3])
    nseason <- ifelse(is.na(fixed_dims[4]),runif(1,min=2, max=max_dims[4]),fixed_dims[4])
    narea <- ifelse(is.na(fixed_dims[5]),runif(1,min=2, max=max_dims[5]),fixed_dims[5])
    niter <- ifelse(is.na(fixed_dims[6]),runif(1,min=2, max=max_dims[6]),fixed_dims[6])
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
#' @param fixed_dims A vector of length 6 with the fixed length of each of the FLQuant dimensions. If any value is NA it is randomly set using the max_dims argument. Default value is rep(NA,6).
#' @param max_dims A vector of length 6 with maximum size of each of the FLQuant dimensions. Default value is c(5,5,5,4,4,10).
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
#' @param fixed_dims A vector of length 6 with the fixed length of each of the FLQuant dimensions. If any value is NA it is randomly set using the max_dims argument. Default value is rep(NA,6).
#' @param max_dims A vector of length 6 with maximum size of each of the FLQuant dimensions. Default value is c(5,5,5,4,4,10).
#' @param sd The standard deviation of the random numbers. Passed to rnorm() Default is 100.
#' @export
#' @return An FLBiol
#' @examples
#' flb <- random_FLBiol_generator()
#' summary(flb)
random_FLBiol_generator <- function(sd=100, ...){
    flq <- abs(random_FLQuant_generator(sd=sd, ...))
    biol <- FLBiol(n = flq)
    m(biol) <- abs(rnorm(prod(dim(flq)),sd=sd))
    wt(biol) <- abs(rnorm(prod(dim(flq)),sd=sd))
    fec(biol) <- abs(rnorm(prod(dim(flq)),sd=sd))
    spwn(biol) <- abs(rnorm(prod(dim(flq)),sd=sd))
    name(biol) <- as.character(signif(rnorm(1)*1000,3))
    desc(biol) <- as.character(signif(rnorm(1)*1000,3))
    return(biol)
}

#' Generate randomly sized and filled FLCatch objects
#'
#' Generate an FLCatch of random size and filled with normally distributed random numbers with a mean of 0.
#' Used for automatic testing, particularly of the FLCatch class in CPP.
#' 
#' @param fixed_dims A vector of length 6 with the fixed length of each of the FLQuant dimensions. If any value is NA it is randomly set using the max_dims argument. Default value is rep(NA,6).
#' @param max_dims A vector of length 6 with maximum size of each of the FLQuant dimensions. Default value is c(5,5,5,4,4,10).
#' @param sd The standard deviation of the random numbers. Passed to rnorm() Default is 100.
#' @export
#' @return An FLCatch
#' @examples
#' flc <- random_FLCatch_generator()
#' summary(flc)
random_FLCatch_generator <- function(sd=100, ...){
    flq <- abs(random_FLQuant_generator(sd=sd, ...))
    catch <- FLCatch(landings.n = flq)
    landings.wt(catch)[] <- abs(rnorm(prod(dim(flq)),sd=sd))
    discards.n(catch)[] <- abs(rnorm(prod(dim(flq)),sd=sd))
    discards.wt(catch)[] <- abs(rnorm(prod(dim(flq)),sd=sd))
    catch.sel(catch)[] <- abs(rnorm(prod(dim(flq)),sd=sd))
    price(catch)[] <- abs(rnorm(prod(dim(flq)),sd=sd))
    # catch.q(catch) # undefined right now
    name(catch) <- as.character(signif(rnorm(1)*1000,3))
    desc(catch) <- as.character(signif(rnorm(1)*1000,3))
    return(catch)
}

#' Generates an FLCatches object - a list of randomly sized and filled FLCatch objects 
#'
#' Generates a list of randomly sized FLCatch objects filled with normally distributed random numbers with a mean of 0.
#' Used for automatic testing, particularly of the FLCatches_base<T> class in CPP.
#' 
#' @param max_catches The maximum number of catches. Default is 5. 
#' @param fixed_dims A vector of length 6 with the fixed length of each of the FLQuant dimensions. If any value is NA it is randomly set using the max_dims argument. 
#' @param max_dims A vector of length 6 with maximum size of each of the FLQuant dimensions. Default value is c(5,5,5,4,4,10).
#' @param sd The standard deviation of the random numbers. Passed to rnorm() Default is 100.
#' @export
#' @return An FLCatches objects
#' @examples
#' flcs <- random_FLCatches_generator()
#' length(flcs)
#' summary(flcs)
#' lapply(flcs, summary)
random_FLCatches_generator <- function(max_catches = 5, ...){
    args <- list(...)
    ncatches <- runif(1,min=2, max=max_catches)
    op_list <- list()
    flq <- random_FLQuant_generator(...)
    # cat("dim flq: ", dim(flq), "\n")
    fixed_dims <- dim(flq)
    #fixed_dims[1] <- NA
    args[["fixed_dims"]] <- fixed_dims
    for (i in 1:ncatches){
        op_list[[i]] <- do.call(random_FLCatch_generator,args)    
    }
    names(op_list) <- paste("Catch ",as.character(1:ncatches),sep="")
    op <- FLCatches(op_list)
    op@desc <- as.character(signif(rnorm(1)*1000,3))
    return(op)
}


#' Generate a randomly filled and sized FLFishery object
#'
#' Generate a randomly sized FLFishery object filled with normally distributed random numbers with a mean of 0.
#' Used for automatic testing, particularly of the FLFishery_base<T> class in CPP.
#' 
#' @param max_catches The maximum number of FLCatches in the catches list. Default is 5. 
#' @param fixed_dims A vector of length 6 with the fixed length of each of the FLQuant dimensions. If any value is NA it is randomly set using the max_dims argument. Default value is rep(NA,6).
#' @param max_dims A vector of length 6 with maximum size of each of the FLQuant dimensions. Default value is c(5,5,5,4,4,10).
#' @param sd The standard deviation of the random numbers. Passed to rnorm() Default is 100.
#' @export
#' @return An FLFishery object 
#' @examples
#' flf <- random_FLFishery_list_generator()
#' summary(flf)
#' flf <- random_FLFishery_generator(fixed_dims = c(NA,10,1,1,1,1))
#' lapply(flf, summary)
#' flf <- random_FLFishery_generator(fixed_dims = c(NA,10,1,1,1,1), max_dims = c(100,NA,NA,NA,NA,NA))
random_FLFishery_generator <- function(max_catches = 5, sd = 100,  ...){
    catches <- random_FLCatches_generator(max_catches, ...)
    fishery <- FLFishery(catches)
    # fill up effort, vcost and fcost
    effort(fishery)[] <- rnorm(prod(dim(effort(fishery))),sd=sd)
    vcost(fishery)[] <- rnorm(prod(dim(vcost(fishery))),sd=sd)
    fcost(fishery)[] <- rnorm(prod(dim(fcost(fishery))),sd=sd)
    fishery@desc <- as.character(signif(rnorm(1)*1000,3))
    fishery@name <- as.character(signif(rnorm(1)*1000,3))
    return(fishery)
}


#' Generate a randomly filled and sized FLFisheries object
#'
#' Generate a randomly sized FLFisheries object filled with normally distributed random numbers with a mean of 0.
#' Used for automatic testing, particularly of the FLFisheries_base<T> class in CPP.
#' 
#' @param max_fisheries The maximum number of FLFisheries in the fisheries list. Default is 5. 
#' @param min_fisheries The minimum number of FLFisheries in the fisheries list. Default is 2. 
#' @param max_catches The maximum number of FLCatches in the catches list. Default is 5. 
#' @param fixed_dims A vector of length 6 with the fixed length of each of the FLQuant dimensions. If any value is NA it is randomly set using the max_dims argument. Default value is rep(NA,6).
#' @param max_dims A vector of length 6 with maximum size of each of the FLQuant dimensions. Default value is c(5,5,5,4,4,10).
#' @param sd The standard deviation of the random numbers. Passed to rnorm() Default is 100.
#' @export
#' @return An FLFishery object 
#' @examples
#' flf <- random_FLFishery_list_generator()
#' summary(flf)
#' flf <- random_FLFishery_generator(fixed_dims = c(NA,10,1,1,1,1))
#' lapply(flf, summary)
#' flf <- random_FLFishery_generator(fixed_dims = c(NA,10,1,1,1,1), max_dims = c(100,NA,NA,NA,NA,NA))
random_FLFisheries_generator <- function(min_fisheries = 2, max_fisheries = 5, ...){
    fisheries_list <- list()
    nfisheries <- runif(1,min=min_fisheries, max=max_fisheries)
    for (i in 1:nfisheries){
        fisheries_list[[i]] <- random_FLFishery_generator(...)
    }
    names(fisheries_list) <- paste("Fishery ",as.character(1:nfisheries),sep="")
    fisheries <- FLFisheries(fisheries_list)
    fisheries@desc <- as.character(signif(rnorm(1)*1000,3))
    return(fisheries)
}


