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
    units(flq) <- as.character(abs(rnorm(1)))
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
#' @return An FLQuant
#' @examples
#' flq <- random_FLQuant_generator()
#' dim(flq)
#' summary(flq)
#random_FLQuant_generator <- function(max_elements = 10, max_age = 10, max_year = 10, max_unit = 5, max_season = 4, max_area = 4, max_iter = 50, sd = 100){
random_FLQuant_list_generator <- function(max_elements = 10, ...){
    nelements <- runif(1,min=1, max=max_elements)
    op <- list()
    for (i in 1:nelements){
        op[[i]] <- random_FLQuant_generator(...)
    }
    return(op)
}

