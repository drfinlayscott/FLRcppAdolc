\name{random_FLCatch_generator}
\alias{random_FLCatch_generator}
\title{Generate randomly sized and filled FLCatch objects}
\usage{
random_FLCatch_generator(sd = 100, ...)
}
\arguments{
  \item{max_age}{The maximum number of ages of the FLCatch.
  Default is 10.}

  \item{max_year}{The maximum number of years of the
  FLCatch. Default is 10.}

  \item{max_unit}{The maximum number of units of the
  FLCatch. Default is 5.}

  \item{max_season}{The maximum number of seasons of the
  FLCatch. Default is 4.}

  \item{max_area}{The maximum number of areas of the
  FLCatch. Default is 4.}

  \item{max_iter}{The maximum number of iters of the
  FLCatch. Default is 50.}

  \item{sd}{The standard deviation of the random numbers.
  Passed to rnorm() Default is 100.}
}
\value{
An FLCatch
}
\description{
Generate an FLCatch of random size and filled with normally
distributed random numbers with a mean of 0. Used for
automatic testing, particularly of the FLCatch class in
CPP.
}
\examples{
flc <- random_FLCatch_generator()
summary(flc)
}

