/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#ifndef _FLFishery_
#define _FLFishery_
#include "FLFishery.h"
#endif 

#ifndef _fwdBiol_
#define _fwdBiol_
#include "fwdBiol.h"
#endif 

#ifndef _fwdSR_
#define _fwdSR_
#include "fwdSR.h"
#endif 

#ifndef _FLQuant_multidim_
#define _FLQuant_multidim_
#include "FLQuant_multidim.h"
#endif

template <typename T>
void year_season_to_timestep(const int year, const int season, const FLQuant_base<T>& flq, int& timestep);

template <typename T>
void timestep_to_year_season(const int timestep, const FLQuant_base<T>& flq, int& year, int& season);

double euclid_norm(double* x, const int size_x);

int newton_raphson(std::vector<double>& indep, const int adolc_tape, const int max_iters= 50, const double max_limit = 100, const double tolerance = 1e-12);

void project_timestep(FLFisheriesAdolc& fisheries, fwdBiolAdolc& biol, std::string srr_model_name, FLQuant params, FLQuant residuals, bool residuals_mult, FLQuantAdolc7& f, const int timestep);
