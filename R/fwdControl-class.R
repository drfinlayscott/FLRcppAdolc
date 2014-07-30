# 
# Copyright 2014 FLR Team. Distributed under the GPL 2 or later
# Maintainer: Finlay Scott, JRC
#

# Class outline for the fwd control object in FLasher 

# Write a validity function

# Some thoughts

# The value column of target is not actually used in the C code.
# Users can enter it in when passing the DF to the constructor
# But in the C++ code, the values are really taken from target_iters

# Season cannot be NA when it get's dispatched to C++ - force it to be 1

# Season and Year are NOT the names of the season or years (even if numeric). They are the indices.
# e.g. ple4, year = 2006, year is actually 50

# Before calling project, SRR residuals must have same time dimensions as fisheries and biol
# Window everything beforehand
# Check for NA values in target timesteps (watch the lag for SSB target)
# NAs are OK after windowing, IF that timestep is not being used in the projection

# What kind of 'quantity' are we allowed?
# f
# catch


# Soundtrack: Electric Wizard - Let Us Prey
#' fwdControl
#'
#' A class to hold the parameters for running a projection using \code{fwd}.
#' Add something about the constructors
#'
#' @section Slots:
#' \describe{
#'    \item{\code{target}:}{A \code{data.frame}. See details below.}
#'    \item{\code{target_iters}:}{An array with the values of the targets (\code{min_value}, \code{value} and \code{max_value} by iteration.}
#'     }
#' @details 
#' Something about the columns and checks
#'
#' @name fwdControl-class
#' @rdname fwdControl-class
#' @docType class
#' @export
setClass("fwdControl",
    representation(
        target = "data.frame",
        target_iters = "array"
    ),
    prototype = prototype(
        target_iters= array(NA, dim=c(1,3,1), dimnames=list(target_no=1, c("min","value","max"), iter=1))
    )
)

