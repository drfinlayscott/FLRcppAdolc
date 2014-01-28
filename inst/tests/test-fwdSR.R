context("Implementation of FLSR - double and Adolc versions")

test_that("fwdSR constructors",{

      data(ple4)
      ple4.sr <- fmle(as.FLSR(ple4,model="ricker"))
          


    test_fwdSR_empty_constructor()

    #test_fwdSR_sexp_constructor(ple4.sr)
    #test_fwdSR_eval_model(ple4.sr)
    #predict(ple4.sr)
    params <- as.FLQuant(params(ple4.sr))
    residuals <- FLQuant(rnorm(100), dimnames = list(year = 1:10, iter = 1:10))
    residuals_mult <- TRUE
    test_fwdSR_constructor("ricker", params, residuals, residuals_mult)

    sr_op <- test_fwdSR_constructor_wrap("ricker", params, residuals, residuals_mult)
    expect_that(sr_op[["params"]], is_identical_to(params))
    expect_that(sr_op[["residuals"]], is_identical_to(residuals))
    expect_that(sr_op[["residuals_mult"]], is_identical_to(residuals_mult))


test_fwdSR_constructor_value("ricker", params, residuals, residuals_mult)
test_fwdSR_constructor_value("bevholt", params, residuals, residuals_mult)

    # test get_nparams
    expect_that(dim(params)[1], is_identical_to(test_fwdSR_get_nparams("ricker", params, residuals, residuals_mult)))

})

