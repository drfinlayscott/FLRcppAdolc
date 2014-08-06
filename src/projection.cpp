/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../inst/include/projection.h"

// Converting timestep to year and season and vice versa
// These are based on INDICES, not characters
template <typename T>
void year_season_to_timestep(const int year, const int season, const FLQuant_base<T>& flq, int& timestep){
    year_season_to_timestep(year, season, flq.get_nseason(), timestep);
}

template <typename T>
void timestep_to_year_season(const int timestep, const FLQuant_base<T>& flq, int& year, int& season){
    timestep_to_year_season(timestep, flq.get_nseason(), year, season);
}

void year_season_to_timestep(const int year, const int season, const int nseason, int& timestep){
    timestep = (year-1) * nseason + season;
}

void timestep_to_year_season(const int timestep, const int nseason, int& year, int& season){
    year =  (timestep-1) / nseason + 1; // integer divide - takes the floor
    season = (timestep-1) % nseason + 1;
}

// Instantiate
template void year_season_to_timestep(const int year, const int season, const FLQuant_base<double>& flq, int& timestep);
template void year_season_to_timestep(const int year, const int season, const FLQuant_base<adouble>& flq, int& timestep);

template void timestep_to_year_season(const int timestep, const FLQuant_base<double>& flq, int& year, int& season);
template void timestep_to_year_season(const int timestep, const FLQuant_base<adouble>& flq, int& year, int& season);

double euclid_norm(double* x, const int size_x){
    double xsum = 0;
    for (int i=0; i<size_x; ++i){
        xsum += x[i] * x[i];
    }
    xsum = sqrt(xsum);
    return xsum;
}

int newton_raphson(std::vector<double>& indep, const int adolc_tape, const int max_iters, const double max_limit, const double tolerance){
    Rprintf("In Newton-Raphson\n");
    const int nindep = indep.size();
    double *x = new double[nindep];
    double *w = new double[nindep];
    // load initial values
    for (int i=0; i<nindep; ++i){
        x[i] = indep[i];
        w[i] = 1.0;
    }
    // solver continues until either the tolerance is reached, the maximum limit is reached, or the maximum iterations are reached
    int iter_count = 0;
    int reason_for_stopping = 0; // 0 - tolerance met; 1 - iter limit reached; 2 - max limit reached
    //while ((euclid_norm(w,nindep) > tolerance) && (euclid_norm(x,nindep) < max_limit) && (++iter_count < max_iters)){
    // First pass to get w
    function(adolc_tape, nindep, nindep, x, w);
    jac_solv(adolc_tape, nindep, x, w, 2);
    while(euclid_norm(w,nindep) > tolerance){
        iter_count++;
        if (euclid_norm(x,nindep) >= max_limit){
            reason_for_stopping = 2;
            Rprintf("Exiting Newton-Raphson early as x > max_limit.\n");
            break;
        }
        if (iter_count > max_iters){
            reason_for_stopping = 1;
            Rprintf("Exiting Newton-Raphson early as maxi_iters exceeded.\n");
            break;
        }
        function(adolc_tape, nindep, nindep, x, w);
        jac_solv(adolc_tape, nindep, x, w, 2);
        for (int i=0; i<nindep; ++i){
            x[i] -= w[i];	   
        }
        //Rprintf("x0 %f\n", x[0]);
        //Rprintf("x1 %f\n\n", x[1]);
    }
    Rprintf("NR iters: %i\n", iter_count);
    // load final values
    for (int i=0; i<nindep; ++i){
        indep[i] = x[i];
    }
    delete[] x;
    delete[] w;
    return reason_for_stopping;
}



/*------------------------------------------------------------*/
// operatingModel class

// Empty constructor
operatingModel::operatingModel(){
    biol = fwdBiolAdolc();
    fisheries = FLFisheriesAdolc();
    f = FLQuant7Adolc();
    f_spwn = FLQuant7();
}

// Main constructor
operatingModel::operatingModel(const FLFisheriesAdolc fisheries_in, const fwdBiolAdolc biol_in, const FLQuant7Adolc f_in, const FLQuant7 f_spwn_in, const fwdControl ctrl_in){
    // Check dims!!
    // Check dims (1 - 5) of landings slots, F and biol are the same
    // Single Biol at the moment.
    // The Biol can be fished by multiple Catches - but each Catch must come from a seperate Fishery
    // Here we assume that each Fishery has one Catch that fishes that Biol - this assumption will break with multiple Biols
    // Biol dims (1 - 5) must therefore match the Catch dims (Fishery[[1]]) and all FLQuants in f and f_spwn
    // Dim 6 must be 1 or n
    const unsigned int nfisheries = fisheries_in.get_nfisheries();
    // nfisheries must equal length of f and f_spwn
    if (nfisheries != f_in.get_ndim7()){
        Rcpp::stop("operatingModel constructor: Number of fisheries must equal number F FLQuants\n");
    }
    if (nfisheries != f_spwn_in.get_ndim7()){
        Rcpp::stop("operatingModel constructor: Number of fisheries must equal number F_SPWN FLQuants\n");
    }
    Rcpp::IntegerVector catch_dim;
    Rcpp::IntegerVector f_dim;
    Rcpp::IntegerVector f_spwn_dim;
    Rcpp::IntegerVector biol_dim = biol_in.n().get_dim();
    for (int unsigned fishery_counter = 1; fishery_counter <= nfisheries; ++fishery_counter){
        catch_dim = fisheries_in(fishery_counter)(1).landings_n().get_dim(); // First catch of the fishery
        f_dim = f_in(fishery_counter).get_dim();
        f_spwn_dim = f_spwn_in(fishery_counter).get_dim();
        for (int dim_counter = 0; dim_counter < 5; ++dim_counter){
            if((biol_dim[dim_counter] != catch_dim[dim_counter]) || (biol_dim[dim_counter] != f_dim[dim_counter]) || (biol_dim[dim_counter] != f_spwn_dim[dim_counter])){
                Rcpp::stop("In operatingModel constructor: Biol dims must be the same as Catch, F and F_SPWN dims\n");
            }
        }
    }
    // Add ITER check
    biol = biol_in;
    fisheries = fisheries_in;
    f = f_in;
    f_spwn = f_spwn_in;
    ctrl = ctrl_in;
}

// Copy constructor - else members can be pointed at by multiple instances
operatingModel::operatingModel(const operatingModel& operatingModel_source){
    biol = operatingModel_source.biol;
    fisheries = operatingModel_source.fisheries;
    f = operatingModel_source.f;
    f_spwn = operatingModel_source.f_spwn;
    ctrl = operatingModel_source.ctrl;
}

// Assignment operator to ensure deep copy - else 'data' can be pointed at by multiple instances
operatingModel& operatingModel::operator = (const operatingModel& operatingModel_source){
	if (this != &operatingModel_source){
        biol = operatingModel_source.biol;
        fisheries = operatingModel_source.fisheries;
        f = operatingModel_source.f;
        f_spwn = operatingModel_source.f_spwn;
        ctrl = operatingModel_source.ctrl;
	}
	return *this;
}

/* Intrusive 'wrap' */
// Returns a list of stuff
operatingModel::operator SEXP() const{
    //Rprintf("Wrapping operatingModel_base<T>.\n");
    return Rcpp::List::create(Rcpp::Named("biol", biol),
                            Rcpp::Named("fisheries", fisheries),
                            Rcpp::Named("f", f),
                            Rcpp::Named("f_spwn", f_spwn),
                            Rcpp::Named("ctrl", ctrl));
}


// SSB calculations
// Return an FLQuant
FLQuantAdolc operatingModel::ssb() const {
    FLQuantAdolc ssb = quant_sum(biol.n() * biol.wt() * biol.fec() * exp(-1.0*(biol.m() * biol.spwn() + f() * f_spwn())));
    return ssb;
}

// Return all iterations but single timestep as an FLQuant
FLQuantAdolc operatingModel::ssb(const int timestep, const int unit, const int area) const {
    FLQuantAdolc full_ssb = ssb();
    int year = 0;
    int season = 0;
    timestep_to_year_season(timestep, full_ssb, year, season);
    FLQuantAdolc out = full_ssb(1,1,year,year,unit,unit,season,season,area,area,1,full_ssb.get_niter());
    return out;
}

// Return a single value given timestep, unit, area and iter
adouble operatingModel::ssb(const int timestep, const int unit, const int area, const int iter) const {
    FLQuantAdolc full_ssb = ssb();
    int year = 0;
    int season = 0;
    timestep_to_year_season(timestep, full_ssb, year, season);
    adouble out = full_ssb(1,year,unit,season,area,iter);
    return out;
}

// Return a single value given year, season, unit, area and iter
adouble operatingModel::ssb(const int year, const int unit, const int season, const int area, const int iter) const {
    FLQuantAdolc full_ssb = ssb();
    adouble out = full_ssb(1,year,unit,season,area,iter);
    return out;
}

// Currently only for a single biol and a single catch
// Updates catch in timestep and biol in timestep+1
// Timestep is based on year / season
// The components of an operatingNodel (Biol and Fisheries) should all have the same time dims
void operatingModel::project_timestep(const int timestep, const int min_iter, const int max_iter){
    // Check iters
    if (min_iter < 1){
        Rcpp::stop("project_timestep: min_iter is less than 1\n");
    }
    if (max_iter > biol.n().get_niter()){
        Rcpp::stop("project_timestep: max_iter is greater than number of iters\n");
    }
    // In preparation for multiple fisheries and catches!
    int fishery_count = 1;
    int catches_count = 1;
    // Time placeholders
    int year = 0;
    int season = 0;
    int next_year = 0;
    int next_season = 0;
    timestep_to_year_season(timestep, biol.n(), year, season);
    timestep_to_year_season(timestep+1, biol.n(), next_year, next_season); 
    // Check that timestep does not exceed biol
    if (next_year > biol.n().get_nyear()){
        Rcpp::stop("In project_timestep. Trying to access year larger than biol years.\n");
    }
    adouble rec_temp = 0.0;
    adouble catch_temp = 0.0;
    adouble z = 0.0;
    adouble ssb_temp = 0.0;
    const int max_quant = f(1).get_nquant();
    FLQuantAdolc discards_ratio_temp = fisheries(fishery_count)(catches_count).discards_ratio();

    // Loop over iters - or should we do iter in Run loop?
    for (int iter_count = min_iter; iter_count <= max_iter; ++iter_count){
        // Calculate the landings and discards
        // quant_count is over the first dimension which is age
        for (int quant_count = 1; quant_count <= max_quant; ++quant_count){
            z =  f(quant_count, year, 1, season, 1, iter_count, 1) + biol.m()(quant_count, year, 1, season, 1, iter_count);
            catch_temp = (f(quant_count, year, 1, season, 1, iter_count, 1) / z) * (1 - exp(-z)) * biol.n()(quant_count, year, 1, season, 1, iter_count);
            fisheries(fishery_count)(catches_count).landings_n()(quant_count, year, 1, season, 1, iter_count) = (1 - discards_ratio_temp(quant_count, year, 1, season, 1, iter_count)) * catch_temp;
            fisheries(fishery_count)(catches_count).discards_n()(quant_count, year, 1, season, 1, iter_count) = discards_ratio_temp(quant_count, year, 1, season, 1, iter_count) * catch_temp;
        }

        // Update population
        // Calculate the SSB that will lead to the recruitment in the NEXT TIME STEP, e.g. current SSB 
        // Add one to timestep because we are getting the recruitment in timestep+1
        ssb_temp = ssb(timestep - biol.srr.get_timelag() + 1, 1, 1, iter_count);  
        // Get the recruitment - year and season passed in for time varying SRR parameters
        rec_temp = biol.srr.eval_model(ssb_temp, next_year, 1, next_season, 1, iter_count);

        // Apply the residuals
        // Use of if statement is OK because for each taping it will only branch the same way (depending on residuals_mult)
        if (biol.srr.get_residuals_mult()){
            rec_temp = rec_temp * biol.srr.get_residuals()(1,next_year,1,next_season,1,iter_count);
        }
        else{
            rec_temp = rec_temp + biol.srr.get_residuals()(1,next_year,1,next_season,1,iter_count);
        }
        biol.n()(1, next_year, 1, next_season, 1, iter_count) = rec_temp;

        for (int quant_count = 1; quant_count < max_quant; ++quant_count){
            z =  f(quant_count, year, 1, season, 1, iter_count,1) + biol.m()(quant_count, year, 1, season, 1, iter_count);
            biol.n()(quant_count+1, next_year, 1, next_season, 1, iter_count) = biol.n()(quant_count, year, 1, season, 1, iter_count) * exp(-z);
        }
        // Assume the last age is a plus group
        z =  f(max_quant, year, 1, season, 1, iter_count, 1) + biol.m()(max_quant, year, 1, season, 1, iter_count);
        biol.n()(max_quant, next_year, 1, next_season, 1, iter_count) = biol.n()(max_quant, next_year, 1, next_season, 1, iter_count) + (biol.n()(max_quant, year, 1, season, 1, iter_count) * exp(-z));
    }

    return;
}

// Assume 1 fishery and 1 biol for now
std::vector<adouble> operatingModel::eval_target_hat(const fwdControlTargetType target_type, const int year, const int unit, const int season, const int area) const{
    int biol_no = 1;
    FLQuantAdolc out_flq;
    switch(target_type){
        case target_f:
            // If no fishery in the control object get total fbar on biol
            //if (Rcpp::IntegerVector::is_na(fishery_no)){
                out_flq = fbar(biol_no);
            //}
            //else {
            //    out_flq = fbar(fishery_no, catch_no, biol_no);
            //}
           break;
       case target_catch:
            // If no fishery in the control object get total fbar on biol
            //if (Rcpp::IntegerVector::is_na(fishery_no)){
                out_flq = catches(biol_no);
            //}
            //else {
            //    out_flq = catches(fishery_no, catch_no, biol_no);
            //}
           break;
       default:
           Rcpp::stop("target_type not found in switch statement - giving up\n");
           break;
    }
    std::vector<adouble> out(out_flq.get_niter(), 0.0); 
    for (unsigned int iter_count = 1; iter_count <= out_flq.get_niter(); ++iter_count){
        out[iter_count-1] = out_flq(1, year, unit, season, area, iter_count);
    }
    return out;
}

// Given the target no, return the corresponding value from the operatingModel that can be compared to the desired target
std::vector<adouble> operatingModel::eval_target_hat(const int target_no, const int min_iter, const int max_iter) const{
    // get the target type string from the control
    fwdControlTargetType target_type = ctrl.get_target_type(target_no);
    // get fishery info - who is catching what
    const int catch_no = 1; // not available yet
    const int biol_no = 1; // not available yet
    const int fishery_no = ctrl.get_target_fishery(target_no); // if NA it's total across fishery
    const int year = ctrl.get_target_year(target_no); // these are indices of the FLQuant - not characters of actual years
    const int season = ctrl.get_target_season(target_no);
    const int unit = 1;
    const int area = 1;
    FLQuantAdolc out_flq;
    // get all iterations
    std::vector<adouble> out_all_iters = eval_target_hat(target_type, year, unit, season, area);

    // subset would be better?
    std::vector<adouble> out(max_iter - min_iter + 1, 0.0); // can we initialise at this point? Or pass in as reference?
    for (unsigned int iter_count = 0; iter_count <= (max_iter - min_iter); ++iter_count){
        //out[iter_count] = out_flq(1, year, unit, season, area, min_iter + iter_count);
        out[iter_count] = out_all_iters[min_iter + iter_count - 1];
    }
    return out;
}

FLQuantAdolc operatingModel::fbar(const int fishery_no, const int catch_no, const int biol_no) const{
    Rcpp::IntegerVector fbar_range = fisheries(fishery_no)(catch_no).get_fbar_range_indices(); // starts at 0 so need to +1 if we use for FLQ accessor - bit inconsistent, sorry
    // Grab the Fs over this range
    Rcpp::IntegerVector fdim = f(fishery_no).get_dim();
    FLQuantAdolc f_age_trim = f(fishery_no)(fbar_range[0]+1, fbar_range[1]+1, 1, fdim[1], 1, fdim[2], 1, fdim[3], 1, fdim[4], 1, fdim[5]);  // subsetting
    FLQuantAdolc fbar_out = quant_mean(f_age_trim);
    // Age mean
    // Return
    return fbar_out;
    //return f_age_trim;

}

// Assume that catch is catches[[1]] for the moment
FLQuantAdolc operatingModel::fbar(const int biol_no) const{
    //// Make an empty FLQ with the right dims - based on the first fishery
    FLQuantAdolc fbar_out = fbar(1,1,biol_no);
    for (unsigned int fishery_count = 2; fishery_count <= fisheries.get_nfisheries(); ++fishery_count){
        fbar_out = fbar_out + fbar(fishery_count,1,biol_no);
    }
    return fbar_out;
}

// Catch of a particular fishery
FLQuantAdolc operatingModel::catches(const int fishery_no, const int catch_no, const int biol_no) const{
    return fisheries(fishery_no, catch_no).catches();
}

// Total catch from an FLBiol
// Assumes the catch is the first FLCatch in the FLFishery
FLQuantAdolc operatingModel::catches(const int biol_no) const{
    // Get the catch from the first fishery
    FLQuantAdolc catches_out = catches(1,1,biol_no);
    for (unsigned int fishery_count = 2; fishery_count <= fisheries.get_nfisheries(); ++fishery_count){
        catches_out = catches_out + catches(fishery_count,1,biol_no);
    }
    return catches_out;
}

// Similar to fwdControl::get_target_value but calcs value from relative values
// gets all iters. col: 1 = min, 2 = value, 3 = max
std::vector<double> operatingModel::calc_target_value(const int target_no, const int col) const{
    //Rcpp::IntegerVector dim = target_iters.attr("dim");
    //std::vector<double> out(dim[2], 0.0);

    int target_year = ctrl.get_target_year(target_no);
    int target_season = ctrl.get_target_season(target_no);
    int target_rel_year = ctrl.get_target_rel_year(target_no);
    int target_rel_season = ctrl.get_target_rel_season(target_no);
    // Are rel_year and rel_season NAs or do they have values?
    bool target_rel_year_na = Rcpp::IntegerVector::is_na(target_rel_year);
    bool target_rel_season_na = Rcpp::IntegerVector::is_na(target_rel_season);
    // Both are either NA, or neither are, if one or other is NA then something has gone wrong (XOR)
    if (!(target_rel_year_na ^ target_rel_season_na)){
        Rcpp::stop("in operatingModel::calc_target_value. Only one of rel_year or re_season is NA. Must be neither or both.\n");
    }
    // Target is not a relative value so just return the values
    //if (target_rel_year_na){
        std::vector<double> value = ctrl.get_target_value(target_no, col);
    //}
    // Target is relative so we have calc the value
    //else {

    //}

    // Is it a relative value
    // If no
    // If yes
    // eval_target * value
    return value;
}

void operatingModel::run(){

    const int ntarget = ctrl.get_ntarget();
    const int niter = ctrl.get_niter(); // number of iters taken from control object - not from Biol or Fisheries
    int target_year = 0;
    int target_season = 0;
    int target_timestep = 0;
    // independent variables
    double fmult_initial = 1;
    std::vector<double> fmult(1,fmult_initial); // For the solver
    std::vector<adouble> fmult_ad(1,fmult_initial); 
    //adouble fmult; 
    // Only length 
    std::vector<double> indep(1); // For the solver
    std::vector<double> dep(1); // For the solver
    // dependent variables
    // Just doing 1 iter at a time for the moment 
    std::vector<double> error(1,0.0);
    std::vector<adouble> target_value_hat(1,0.0);
    // from control object
    //double target_value; 
    std::vector<double> target_value(niter, 0.0); 

    int tape_tag = 1;

    int nr_out = 0;

    for (int target_count = 1; target_count <= ntarget; ++target_count){
        Rprintf("\nResolving target: %i\n", target_count);
        // What time step are we hitting this target?
        target_year = ctrl.get_target_year(target_count);
        target_season = ctrl.get_target_season(target_count);
        year_season_to_timestep(target_year, target_season, biol.n(), target_timestep);
        //Rprintf("target_year: %i\n", target_year);
        //Rprintf("target_season: %i\n", target_season);
        Rprintf("target_timestep: %i\n", target_timestep);

        target_value = ctrl.get_target_value(target_count, 2); // better to return all iters and move to outside iter loop
        //fisheries(1)(1).get_fbar_range_indices();
        for (int iter_count = 1; iter_count <= niter; ++iter_count){
            Rprintf("Resolving iter: %i\n", iter_count);

            // Tape the process
            trace_on(tape_tag);
            fmult_ad[0] <<= fmult_initial; // Or move this above iter loop and do all iters at same time
            // Update om.f = om.f * fmult in that year / season
            for (int quant_count = 1; quant_count <= f(1).get_nquant(); ++quant_count){
                f(quant_count,target_year,1,target_season,1,iter_count,1) = f(quant_count,target_year,1,target_season,1,iter_count,1) * fmult_ad[0];
            }
            project_timestep(target_timestep, iter_count, iter_count); 

            // Sort out target stuff to calculate error (difference)

            // Is it a min / max / value?
            //target_value = ctrl.get_target_value(target_count, 2, iter_count); // better to return all iters and move to outside iter loop

            target_value_hat = eval_target_hat(target_count, iter_count, iter_count);

            // Calculate the error term that we want to be 0
            target_value_hat[0] = (target_value_hat[0] - target_value[iter_count-1]); // this works better - no need to reset initial fmult each time?
            //target_value_hat[0] = (target_value_hat[0] - target_value) * (target_value_hat[0] - target_value); // squared error - less stable

            // Set dependent variable
            target_value_hat[0] >>= error[0];
            trace_off();

            // Solve
            // reset initial solver value - also can just use: error = target_hat - target without squaring
            // faster to do this outside of the iter loop and start NR with solution of previous iter - OK until a bad iter
            fmult[0] = 1.0; 
            //Rprintf("fmult pre NR: %f\n", fmult[0]);
            nr_out = newton_raphson(fmult, tape_tag);
            // Run some check on this


            //Rprintf("fmult post NR: %f\n", fmult[0]);
            // Test output code for what happened
            // Correct values are now in fmult
            // Project with these values
            for (int quant_count = 1; quant_count <= f(1).get_nquant(); ++quant_count){
                f(quant_count,target_year,1,target_season,1,iter_count,1) = f(quant_count,target_year,1,target_season,1,iter_count,1) * fmult[0];
            }
            project_timestep(target_timestep, iter_count, iter_count); 
            // We're done!
        }

    }
}

/*
void operatingModel::run_all_iters(){

    const int ntarget = ctrl.get_ntarget();
    const int niter = ctrl.get_niter(); // number of iters taken from control object - not from Biol or Fisheries
    int target_year = 0;
    int target_season = 0;
    int target_timestep = 0;
    // independent variables
    double fmult_initial = 1;
    std::vector<double> fmult(niter,fmult_initial); // For the solver
    std::vector<adouble> fmult_ad(niter,fmult_initial); 
    //adouble fmult; 
    // dependent variables
    // Just doing 1 iter at a time for the moment 
    std::vector<double> target_value_hat(niter,0.0);
    std::vector<adouble> target_value_hat_ad(niter,0.0);
    // from control object
    //double target_value; 
    std::vector<double> target_value(niter, 0.0); 

    int tape_tag = 1;

    int nr_out = 0;

    for (int target_count = 1; target_count <= ntarget; ++target_count){
        Rprintf("\nResolving target: %i\n", target_count);
        // What time step are we hitting this target?
        target_year = ctrl.get_target_year(target_count);
        target_season = ctrl.get_target_season(target_count);
        year_season_to_timestep(target_year, target_season, biol.n(), target_timestep);
        Rprintf("target_year: %i\n", target_year);
        Rprintf("target_season: %i\n", target_season);
        Rprintf("target_timestep: %i\n", target_timestep);

        target_value = ctrl.get_target_value(target_count, 2); // better to return all iters and move to outside iter loop
        
        // Tape the process
        trace_on(tape_tag);
        // Load up fmult and adjust f
        for (int iter_count = 0; iter_count < niter; ++iter_count){
            fmult_ad[iter_count] <<= fmult_initial; // Or move this above iter loop and do all iters at same time
            for (int quant_count = 1; quant_count <= f(1).get_nquant(); ++quant_count){
                f(quant_count,target_year,1,target_season,1,iter_count+1,1) = f(quant_count,target_year,1,target_season,1,iter_count+1,1) * fmult_ad[iter_count];
            }
        }

        project_timestep(target_timestep, 1, niter); 
        // Is it a min / max / value?
        //target_value = ctrl.get_target_value(target_count, 2, iter_count); // better to return all iters and move to outside iter loop
        target_value_hat_ad = eval_target(target_count, 1, niter);
        for (int iter_count = 0; iter_count < niter; ++iter_count){
            // Calculate the error term that we want to be 0
            target_value_hat_ad[iter_count] = (target_value_hat_ad[iter_count] - target_value[iter_count]); // this works better - no need to reset initial fmult each time?
            // Set dependent variable
            target_value_hat_ad[iter_count] >>= target_value_hat[iter_count];
        }
        trace_off();

        // Solve
        // reset initial solver value - also can just use: error = target_hat - target without squaring
        // faster to do this outside of the iter loop and start NR with solution of previous iter - OK until a bad iter
        for (int iter_count = 0; iter_count < niter; ++iter_count){
            fmult[iter_count] = 1.0; 
        }
        nr_out = newton_raphson(fmult, tape_tag);


        // Test output code for what happened
        // Correct values are now in fmult
        // Project with these values
        for (int iter_count = 0; iter_count < niter; ++iter_count){
            for (int quant_count = 1; quant_count <= f(1).get_nquant(); ++quant_count){
                f(quant_count,target_year,1,target_season,1,iter_count+1,1) = f(quant_count,target_year,1,target_season,1,iter_count+1,1) * fmult[iter_count];
            }
        }
        project_timestep(target_timestep, 1, niter); 
        // We're done!
    }
}
*/

/*----------------------------------------------------------------------------------*/

// Assumes the targets are already ordered by time

// [[Rcpp::export]]
operatingModel test_run (const FLFisheriesAdolc fisheries, SEXP FLBiolSEXP, const std::string srr_model_name, const FLQuant srr_params, const FLQuant srr_residuals, const bool srr_residuals_mult, const int srr_timelag, FLQuant7Adolc f, FLQuant7 f_spwn, fwdControl ctrl){

    // Make the fwdBiol from the FLBiol and SRR bits
    fwdBiolAdolc biol(FLBiolSEXP, srr_model_name, srr_params, srr_timelag, srr_residuals, TRUE); 
    // Make the OM
    operatingModel om(fisheries, biol, f, f_spwn, ctrl);

    om.run();

    return om;

}


// [[Rcpp::export]]
operatingModel test_run_all_iters(const FLFisheriesAdolc fisheries, SEXP FLBiolSEXP, const std::string srr_model_name, const FLQuant srr_params, const FLQuant srr_residuals, const bool srr_residuals_mult, const int srr_timelag, FLQuant7Adolc f, FLQuant7 f_spwn, fwdControl ctrl){

    // Make the fwdBiol from the FLBiol and SRR bits
    fwdBiolAdolc biol(FLBiolSEXP, srr_model_name, srr_params, srr_timelag, srr_residuals, TRUE); 
    // Make the OM
    operatingModel om(fisheries, biol, f, f_spwn, ctrl);

    //om.run_all_iters();

    return om;

}


