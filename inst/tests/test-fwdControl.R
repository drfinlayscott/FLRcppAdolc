context("Implementation of fwdControl")

test_that("fwdControl as and wrap",{
    fc_in <- dummy_fwdControl_generator(years = 1:10, niters = 10)
    fc_out <- test_as_wrap_fwdControl(fc_in)
    expect_that(fc_in, is_identical_to(fc_out))
})

test_that("fwdControl copy constructor and assignement operator", {
# Limited tests as we cannot change the values of fwdControl
    fc_in <- dummy_fwdControl_generator(years = 1:10, niters = 10)
    fcs <- test_fwdControl_copy_constructor2(fc_in)
    expect_that(fc_in, is_identical_to(fcs[["fc1"]]))
    expect_that(fc_in, is_identical_to(fcs[["fc2"]]))

    fc_out <- test_fwdControl_assignment_operator(fc_in)
    expect_that(fc_in, is_identical_to(fc_out))

})


test_that("fwdControl accessors", {
    fc <- dummy_fwdControl_generator()
    # get target
    target <- test_fwdControl_get_target(fc)
    expect_that(target, is_identical_to(fc@target))
    # get ntarget
    ntarget <- test_fwdControl_get_ntarget(fc)
    expect_that(ntarget, is_identical_to(nrow(fc@target)))
    # get niter
    niter <- test_fwdControl_get_niter(fc)
    expect_that(niter, is_identical_to(dim(fc@target_iters)[3]))

    # get target value
    target_no <- round(runif(1,min=1,max=dim(fc@target)[1]))
    col_no <- round(runif(1,min=1,max=3))
    iter <- round(runif(1,max=dim(fc@target_iters)[3]))
    value_list <- test_fwdControl_get_target_value(fc, target_no, col_no, iter)
    expect_that(fc@target_iters[target_no, col_no, iter], is_identical_to(value_list[["value"]]))
    expect_that(unname(fc@target_iters[target_no, col_no,]), is_identical_to(value_list[["values"]]))
    # get year, season, fishery of target
    target_no <- round(runif(1, min=1, max=nrow(fc@target)))
    year <- test_fwdControl_get_target_year(fc, target_no)
    expect_that(fc@target[target_no, "year"], is_identical_to(year))
    season <- test_fwdControl_get_target_season(fc, target_no)
    expect_that(fc@target[target_no, "season"], is_identical_to(season))
    fc@target[target_no,"fishery"] <- as.integer(round(runif(1)))
    # get rel_year and rel_season of target
    target_no <- round(runif(1, min=1, max=nrow(fc@target)))
    fc@target$rel_year <- as.integer(NA)
    fc@target$rel_season <- as.integer(NA)
    rel_year <- test_fwdControl_get_target_rel_year(fc, target_no)
    rel_season <- test_fwdControl_get_target_rel_season(fc, target_no)
    expect_that(rel_year, is_identical_to(fc@target[target_no, "rel_year"]))
    expect_that(rel_season, is_identical_to(fc@target[target_no, "rel_season"]))
    fc@target$rel_year <- fc@target[target_no, "year"]
    fc@target$rel_season <- fc@target[target_no, "season"]
    rel_year <- test_fwdControl_get_target_rel_year(fc, target_no)
    rel_season <- test_fwdControl_get_target_rel_season(fc, target_no)
    expect_that(rel_year, is_identical_to(fc@target[target_no, "rel_year"]))
    expect_that(rel_season, is_identical_to(fc@target[target_no, "rel_season"]))
    # force fishery column to be integer
    fishery <- test_fwdControl_get_target_fishery(fc, target_no)
    expect_that(fc@target[target_no, "fishery"], is_identical_to(fishery))
    # get target type / quantity
    type <- test_fwdControl_get_target_quantity(fc, target_no)
    expect_that(type, is_identical_to(as.character(fc@target[target_no, "quantity"])))
    expect_that(test_fwdControl_get_target_quantity(fc, nrow(fc@target)+1), throws_error())

})
