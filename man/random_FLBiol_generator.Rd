\name{random_FLBiol_generator}
\alias{random_FLBiol_generator}
\title{Generate randomly sized and filled FLBiol objects}
\usage{
random_FLBiol_generator(sd = 100, ...)
}
\arguments{
  \item{max_age}{The maximum number of ages of the FLBiol.
  Default is 10.}

  \item{max_year}{The maximum number of years of the
  FLBiol. Default is 10.}

  \item{max_unit}{The maximum number of units of the
  FLBiol. Default is 5.}

  \item{max_season}{The maximum number of seasons of the
  FLBiol. Default is 4.}

  \item{max_area}{The maximum number of areas of the
  FLBiol. Default is 4.}

  \item{max_iter}{The maximum number of iters of the
  FLBiol. Default is 50.}

  \item{sd}{The standard deviation of the random numbers.
  Passed to rnorm() Default is 100.}
}
\value{
An FLBiol
}
\description{
Generate an FLBiol of random size and filled with normally
distributed random numbers with a mean of 0. Used for
automatic testing, particularly of the fwdBiol class in
CPP.
}
\examples{
flb <- random_FLBiol_generator()
summary(flb)
}

