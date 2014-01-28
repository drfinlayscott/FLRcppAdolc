context("Implementation of FLSR - double and Adolc versions")

test_that("fwdSR constructors",{
    data(ple4)
    ple4.sr.ricker <- fmle(as.FLSR(ple4,model="ricker"))
    params.ricker <- as.FLQuant(params(ple4.sr.ricker))
    residuals.ricker <- FLQuant(rnorm(100), dimnames = list(year = 1:10, iter = 1:10))
    ple4.sr.bevholt <- fmle(as.FLSR(ple4,model="bevholt"))
    params.bevholt <- as.FLQuant(params(ple4.sr.bevholt))
    residuals.bevholt <- FLQuant(rnorm(100), dimnames = list(year = 1:10, iter = 1:10))
    residuals_mult <- TRUE
    # Empty constructor - shouldn't fail
    test_fwdSR_empty_constructor()
    # Wrap
    sr_op <- test_fwdSR_constructor_wrap("ricker", params.ricker, residuals.ricker, residuals_mult)
    expect_that(sr_op[["params"]], is_identical_to(params))
    expect_that(sr_op[["residuals"]], is_identical_to(residuals.ricker))
    expect_that(sr_op[["residuals_mult"]], is_identical_to(residuals_mult))
    # eval
    rec <- test_fwdSR_eval_simple("ricker", params.ricker, residuals.ricker, residuals_mult, c(ssb(ple4.sr.ricker)[1,1,]))
    expect_that(rec, is_identical_to(c(predict(ple4.sr.ricker)[1,1,])))
    rec <- test_fwdSR_eval_simple("Ricker", params.ricker, residuals.ricker, residuals_mult, c(ssb(ple4.sr.ricker)[1,1,]))
    expect_that(rec, is_identical_to(c(predict(ple4.sr.ricker)[1,1,])))
    rec <- test_fwdSR_eval_simple("bevholt", params.bevholt, residuals.bevholt, residuals_mult, c(ssb(ple4.sr.bevholt)[1,1,]))
    expect_that(rec, is_identical_to(c(predict(ple4.sr.bevholt)[1,1,])))
    rec <- test_fwdSR_eval_simple("Bevholt", params.bevholt, residuals.bevholt, residuals_mult, c(ssb(ple4.sr.bevholt)[1,1,]))
    expect_that(rec, is_identical_to(c(predict(ple4.sr.bevholt)[1,1,])))
    # test get_nparams
    expect_that(dim(params)[1], is_identical_to(test_fwdSR_get_nparams("ricker", params, residuals, residuals_mult)))

    # Copy constructor
    srs <- test_fwdSR_copy_constructor("ricker", params.ricker, residuals.ricker, residuals_mult, c(ssb(ple4.sr.bevholt)[1,1,]))
    expect_that(srs[[1]], is_identical_to(srs[[2]]))
    expect_that(srs[[3]], is_identical_to(srs[[4]]))

    # Assignment operator
    srs <- test_fwdSR_assignment_operator("ricker", params.ricker, residuals.ricker, residuals_mult, c(ssb(ple4.sr.bevholt)[1,1,]))
    expect_that(srs[[1]], is_identical_to(srs[[2]]))
    expect_that(srs[[3]], is_identical_to(srs[[4]]))



})

