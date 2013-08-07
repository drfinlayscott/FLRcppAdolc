context("Arithmetic operators for FLQuant and FLQuantAdolc")

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

test_that("subtraction",{
    flq1 <- random_FLQuant_generator()
    flq2 <- flq1
    flq2[] <- rnorm(prod(dim(flq1)),sd = 10)
    value <- rnorm(1)
    # Subtraction assignment
    flq_out <- test_FLQuant_FLQuant_subtraction_assignment_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data - flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuant_subtraction_assignment_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data - flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuantAdolc_subtraction_assignment_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data - flq2@.Data))
    flq_out <- test_FLQuant_double_subtraction_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 - value))
    flq_out <- test_FLQuantAdolc_double_subtraction_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 - value))
    flq_out <- test_FLQuantAdolc_adouble_subtraction_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 - value))
    # Binary subtraction FLQ<> * FLQ<>
    flq_out <- test_FLQuant_FLQuant_subtraction_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data - flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuant_subtraction_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data - flq2@.Data))
    flq_out <- test_FLQuant_FLQuantAdolc_subtraction_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data - flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuantAdolc_subtraction_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data - flq2@.Data))
    # Binary subtraction FLQ<> * scalar
    flq_out <- test_FLQuant_double_subtraction_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 - value))
    flq_out <- test_double_FLQuant_subtraction_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value - flq1))
    flq_out <-  test_FLQuantAdolc_double_subtraction_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 - value))
    flq_out <-  test_double_FLQuantAdolc_subtraction_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value - flq1))
    flq_out <- test_FLQuant_adouble_subtraction_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 - value))
    flq_out <- test_adouble_FLQuant_subtraction_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value - flq1))
    flq_out <- test_FLQuantAdolc_adouble_subtraction_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 - value))
    flq_out <- test_adouble_FLQuantAdolc_subtraction_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value - flq1))
})

test_that("addition",{
    flq1 <- random_FLQuant_generator()
    flq2 <- flq1
    flq2[] <- rnorm(prod(dim(flq1)),sd = 10)
    value <- rnorm(1)
    # Addition assignment
    flq_out <- test_FLQuant_FLQuant_addition_assignment_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data + flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuant_addition_assignment_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data + flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuantAdolc_addition_assignment_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data + flq2@.Data))
    flq_out <- test_FLQuant_double_addition_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 + value))
    flq_out <- test_FLQuantAdolc_double_addition_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 + value))
    flq_out <- test_FLQuantAdolc_adouble_addition_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 + value))
    # Binary addition FLQ<> + FLQ<>
    flq_out <- test_FLQuant_FLQuant_addition_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data + flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuant_addition_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data + flq2@.Data))
    flq_out <- test_FLQuant_FLQuantAdolc_addition_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data + flq2@.Data))
    flq_out <- test_FLQuantAdolc_FLQuantAdolc_addition_operator(flq1, flq2)
    expect_that(flq_out@.Data, is_identical_to(flq1@.Data + flq2@.Data))
    # Binary addition FLQ<> + scalar
    flq_out <- test_FLQuant_double_addition_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 + value))
    flq_out <- test_double_FLQuant_addition_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value + flq1))
    flq_out <-  test_FLQuantAdolc_double_addition_assignment_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 + value))
    flq_out <-  test_double_FLQuantAdolc_addition_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value + flq1))
    flq_out <- test_FLQuant_adouble_addition_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 + value))
    flq_out <- test_adouble_FLQuant_addition_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value + flq1))
    flq_out <- test_FLQuantAdolc_adouble_addition_operator(flq1, value)
    expect_that(flq_out, is_identical_to(flq1 + value))
    flq_out <- test_adouble_FLQuantAdolc_addition_operator(value, flq1)
    expect_that(flq_out, is_identical_to(value + flq1))
})

test_that("composite_arithmetic",{
    flq <- random_FLQuant_generator()
    flqad <- flq
    flqad[] <- rnorm(prod(dim(flq)),sd = 10)
    value <- rnorm(1)
    flq_out <- test_composite_arithmetic_operators(flqad, flq, value)
    result <- ((((value * flq) + value) - flq) / flq) * ((value / flqad) - value)
    expect_that(flq_out@.Data, is_identical_to(result@.Data))
})

test_that("log and exp",{
    flq <- abs(random_FLQuant_generator())
    # log
    flq_out <- test_FLQuant_log(flq)
    expect_that(flq_out@.Data, is_identical_to(log(flq)@.Data))
    flq_out <- test_FLQuantAdolc_log(flq)
    expect_that(flq_out@.Data, is_identical_to(log(flq)@.Data))
    # exp
    flq_out <- test_FLQuant_exp(flq)
    expect_that(flq_out@.Data, is_identical_to(exp(flq)@.Data))
    flq_out <- test_FLQuantAdolc_exp(flq)
    expect_that(flq_out@.Data, is_identical_to(exp(flq)@.Data))
})
