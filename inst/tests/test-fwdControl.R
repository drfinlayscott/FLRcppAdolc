context("Implementation of fwdControl")

test_that("fwdControl as and wrap",{
    # We need to have a proper R version of the class
    # And an automatic generator
    ctrl_df <- data.frame(
                       year = 1:10,
                       season = NA, # by default
                       quantity = "f", # the target type
                       value =  0.2,
                       min_value = NA,
                       max_value = NA,
                       rel_year = NA,
                       rel_season = NA,
                       flcatch = NA, # what is this? a number or name? Some way of referring 
                       rel_flcatch = NA # as above
                       )

    fc <- new("fwdControl")
    fc@target <- ctrl_df

})


#test_that("FLCatch as and wrap",{
#    flc_in <- random_FLCatch_generator()
#    expect_that(test_simple_FLCatch_sexp_constructor(flc_in), is_identical_to(as.integer(0)))
#    flc_out <- test_FLCatch_as_wrap(flc_in)
#    expect_that(flc_in, is_identical_to(flc_out))
#    flc_out <- test_FLCatchAdolc_as_wrap(flc_in)
#    expect_that(flc_in, is_identical_to(flc_out))
#})
#
