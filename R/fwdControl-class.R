# 
# Copyright 2014 FLR Team. Distributed under the GPL 2 or later
# Maintainer: Finlay Scott, JRC
#

# Class outline for the fwd control object in FLasher 

# Write a validity function

# Soundtrack: Electric Wizard - Let Us Prey
#' fwdControl
#'
#' A class to hold the parameters for running a projection using \code{fwd}.
#' Add something about the constructors
#'
#' @section Slots:
#' \describe{
#'    \item{\code{target}:}{A \code{data.frame}. See details below.}
#'    \item{\code{target_iters}:}{An array with the values of the targets (\code{min_value}, \code{value} and \code{max_value} by iteration.)
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

