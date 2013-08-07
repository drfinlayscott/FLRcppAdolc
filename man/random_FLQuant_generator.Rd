\name{random_FLQuant_generator}
\alias{random_FLQuant_generator}
\title{Generate random FLQuant objects}
\usage{
  random_FLQuant_generator(max_age = 10, max_year = 10,
    max_unit = 5, max_season = 4, max_area = 4,
    max_iter = 50, sd = 100)
}
\arguments{
  \item{max_age}{The maximum number of ages of the FLQuant.
  Default is 10.}

  \item{max_year}{The maximum number of years of the
  FLQuant. Default is 10.}

  \item{max_unit}{The maximum number of units of the
  FLQuant. Default is 10.}

  \item{max_season}{The maximum number of seasons of the
  FLQuant. Default is 10.}

  \item{max_area}{The maximum number of areas of the
  FLQuant. Default is 10.}

  \item{max_iter}{The maximum number of iters of the
  FLQuant. Default is 10.}

  \item{sd}{The standard deviation of the random numbers.
  Passed to rnorm().}
}
\value{
  An FLQuant
}
\description{
  Generate a randomly sized FLQuant filled with normally
  distributed random numbers with a mean of 0. Used for
  automatic testing.
}
\examples{
flq <- random_FLQuant_generator()
dim(flq)
summary(flq)
}

