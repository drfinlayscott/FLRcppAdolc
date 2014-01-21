\name{random_FLCatch_list_generator}
\alias{random_FLCatch_list_generator}
\title{Generate lists of randomly sized and filled FLCatch objects}
\usage{
random_FLCatch_list_generator(max_elements = 5, ...)
}
\arguments{
  \item{max_elements}{The maximum number of elements in the
  list. Default is 5.}

  \item{fixed_dims}{A vector of length 6 with the fixed
  length of each of the FLQuant dimensions. If any value is
  NA it is randomly set using the max_dims argument.
  Default value is rep(NA,6).}

  \item{max_dims}{A vector of length 6 with maximum size of
  each of the FLQuant dimensions. Default value is
  c(5,5,5,4,4,10).}

  \item{sd}{The standard deviation of the random numbers.
  Passed to rnorm() Default is 100.}
}
\value{
A list of FLCatch objects
}
\description{
Generate a list of randomly sized FLCatch objects filled
with normally distributed random numbers with a mean of 0.
Used for automatic testing, particularly of the
FLCatches_base<T> class in CPP.
}
\examples{
flc_list <- random_FLCatch_list_generator()
length(flc_list)
summary(flc_list)
lapply(flc_list, summary)
}

