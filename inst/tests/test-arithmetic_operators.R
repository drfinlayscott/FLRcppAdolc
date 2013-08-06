context("Arithmetic operators for FLQuant and FLQuantAdolc")

random_FLQuant_generator <- function(max_age = 10, max_year = 10, max_unit = 5, max_season = 4, max_area = 4, max_iter = 50){
    nage <- runif(1,min=1, max=max_age)
    nyear <- runif(1,min=1, max=max_year)
    nunit <- runif(1,min=1, max=max_unit)
    nseason <- runif(1,min=1, max=max_season)
    narea <- runif(1,min=1, max=max_area)
    niter <- runif(1,min=1, max=max_iter)
    values <- rnorm(nage*nyear*nunit*nseason*narea*niter, sd = 100)
    flq <- FLQuant(values, dimnames = list(age = 1:nage, year = 1:nyear, unit = 1:nunit, season = 1:nseason, area = 1:narea, iter = 1:niter))
    units(flq) <- as.character(abs(rnorm(1)))
    return(flq);
}

# There are 18 options per operator
# For example, consider the '*' operator:
# 6 operator assignment
# FLQ   = FLQ     *= FLQ
# FLQAD = FLQAD   *= FLQ
# FLQAD = FLQAD   *= FLQAD
# FLQ   = FLQ     *= double
# FLQAD = FLQAD   *= double
# FLQAD = FLQAD   *= adouble
# 4 binary 'FLQ FLQ' arithmetic operator
# FLQ   = FLQ     *  FLQ
# FLQAD = FLQAD   *  FLQ
# FLQAD = FLQ     *  FLQAD
# FLQAD = FLQAD   *  FLQAD
# 8 binary 'FLQ scalar' arithmetic operator
# FLQ   = FLQ     *  double
# FLQ   = double  *  FLQ
# FLQAD = FLQAD   *  double
# FLQAD = double  *  FLQAD
# FLQAD = FLQ     *  adouble
# FLQAD = adouble *  FLQ
# FLQAD = FLQAD   *  adouble
# FLQAD = adouble *  FLQAD

test_that("multiplication",{
    flq1 <- random_FLQuant_generator()
    flq2 <- flq1
    flq2[] <- rnorm(prod(dim(flq1)),sd = 10)
    value <- rnorm(1)
    # Multiplier assignment
    flq_out <- test_FLQuant_FLQuant_multiplier_assignment_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data * flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuant_multiplier_assignment_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data * flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuantAdolc_multiplier_assignment_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data * flq2@.Data))
    flq_out <- test_FLQuant_double_multiplier_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 * value))
    flq_out <- test_FLQuantAdolc_double_multiplier_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 * value))
    flq_out <- test_FLQuantAdolc_adouble_multiplier_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 * value))
    # Binary multiplers FLQ<> * FLQ<>
    flq_out <- test_FLQuant_FLQuant_multiplier_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data * flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuant_multiplier_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data * flq2@.Data))
    flq_out <- test_FLQuant_FLQuantAdolc_multiplier_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data * flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuantAdolc_multiplier_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data * flq2@.Data))
    # Binary multiplers FLQ<> * scalar
    flq_out <- test_FLQuant_double_multiplier_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 * value))
    flq_out <- test_double_FLQuant_multiplier_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value * flq1))
    flq_out <-  test_FLQuantAdolc_double_multiplier_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(value * flq1))
    flq_out <-  test_double_FLQuantAdolc_multiplier_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value * flq1))
    flq_out <- test_FLQuant_adouble_multiplier_operator(flq1, value)
    expect_that(flq_out, is_identical_to(value * flq1))
    flq_out <- test_adouble_FLQuant_multiplier_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value * flq1))
    flq_out <- test_FLQuantAdolc_adouble_multiplier_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 * value))
    flq_out <- test_adouble_FLQuantAdolc_multiplier_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value * flq1))
})

test_that("division",{
    flq1 <- random_FLQuant_generator()
    flq2 <- flq1
    flq2[] <- rnorm(prod(dim(flq1)),sd = 10)
    value <- rnorm(1)
    # Division assignment
    flq_out <- test_FLQuant_FLQuant_division_assignment_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data / flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuant_division_assignment_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data / flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuantAdolc_division_assignment_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data / flq2@.Data))
    flq_out <- test_FLQuant_double_division_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 / value))
    flq_out <- test_FLQuantAdolc_double_division_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 / value))
    flq_out <- test_FLQuantAdolc_adouble_division_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 / value))
    # Binary division FLQ<> * FLQ<>
    flq_out <- test_FLQuant_FLQuant_division_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data / flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuant_division_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data / flq2@.Data))
    flq_out <- test_FLQuant_FLQuantAdolc_division_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data / flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuantAdolc_division_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data / flq2@.Data))
    # Binary division FLQ<> * scalar
    flq_out <- test_FLQuant_double_division_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 / value))
    flq_out <- test_double_FLQuant_division_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value / flq1))
    flq_out <-  test_FLQuantAdolc_double_division_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 / value))
    flq_out <-  test_double_FLQuantAdolc_division_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value / flq1))
    flq_out <- test_FLQuant_adouble_division_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 / value))
    flq_out <- test_adouble_FLQuant_division_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value / flq1))
    flq_out <- test_FLQuantAdolc_adouble_division_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 / value))
    flq_out <- test_adouble_FLQuantAdolc_division_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value / flq1))
})

