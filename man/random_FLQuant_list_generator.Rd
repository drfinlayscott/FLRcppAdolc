\name{random_FLQuant_list_generator}
\alias{random_FLQuant_list_generator}
\title{Generate lists of randomly sized and filled FLQuant objects}
\usage{
random_FLQuant_list_generator(max_elements = 10, ...)
}
\arguments{
  \item{max_elements}{The maximum number of elements in the
  list. Default is 10.}

  \item{max_age}{The maximum number of ages of the FLQuant.
  Default is 10.}

  \item{max_year}{The maximum number of years of the
  FLQuant. Default is 10.}

  \item{max_unit}{The maximum number of units of the
  FLQuant. Default is 5.}

  \item{max_season}{The maximum number of seasons of the
  FLQuant. Default is 4.}

  \item{max_area}{The maximum number of areas of the
  FLQuant. Default is 4.}

  \item{max_iter}{The maximum number of iters of the
  FLQuant. Default is 50.}

  \item{sd}{The standard deviation of the random numbers.
  Passed to rnorm() Default is 100.}
}
\value{
An FLQuant
}
\description{
Generate a list of randomly sized FLQuant objects filled
with normally distributed random numbers with a mean of 0.
Used for automatic testing, particularly of the
FLQuant7_base<T> class in CPP.
}
\examples{
flq <- random_FLQuant_generator()
dim(flq)
summary(flq)
}

