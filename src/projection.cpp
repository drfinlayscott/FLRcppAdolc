/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../inst/include/projection.h"

// Make these methods of FLQuant_base<T>?

template <typename T>
void year_season_to_timestep(const int year, const int season, const FLQuant_base<T>& flq, int& timestep){
    timestep = (year-1) * flq.get_nseason() + season;
}

template <typename T>
void timestep_to_year_season(const int timestep, const FLQuant_base<T>& flq, int& year, int& season){
    year =  (timestep-1) / flq.get_nseason() + 1; // integer divide - takes the floor
    season = (timestep-1) % flq.get_nseason() + 1;
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
    const int nindep = indep.size();
    Rprintf("nindep: %i\n", nindep);
    //double* x, w, y;
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
        Rprintf("x0 %f\n", x[0]);
        //Rprintf("x1 %f\n\n", x[1]);
    }
    // load final values
    for (int i=0; i<nindep; ++i){
        indep[i] = x[i];
    }
    delete[] x;
    delete[] w;
    return reason_for_stopping;
}



/*----------------------------------------------------------------------------------*/
// Stuff to migrate
// [[Rcpp::export]]
std::vector<double> run(FLFisheriesAdolc fisheries, fwdBiolAdolc biol, std::string srr_model_name, FLQuant srr_params, FLQuant srr_residuals, bool srr_residuals_mult, FLQuantAdolc7 f){
    Rprintf("In run\n");

    FLQuantAdolc7 f_tape = f; // Make a copy to be used in the tape loop
    // Where does the iter loop go? Here or in project_timestep?
    int iter_count = 1;
    int max_timestep = 3;
    adouble fmult; // independent variable
    double target_hat;
    adouble target_hat_ad; // dependent variable
    double fmult_initial = 1;//0.5;
    int tape_tag = 1;
    int year = 0;
    int season = 0;
    double catch_target = 5;
    std::vector<double> indep(1); // For the solver
//for (int timestep = 1; timestep < max_timestep; ++timestep){
    int timestep=1;

    // Turn on tape
    Rprintf("Turning on the tape\n");
    trace_on(tape_tag);
    // Dim checking
    fmult <<= fmult_initial;
    // Update f
    timestep_to_year_season(timestep, f(1), year, season);
    for (int quant_count = 1; quant_count <= f(1).get_nquant(); ++quant_count){
        f_tape(quant_count,year,1,season,1,iter_count,1) = f_tape(quant_count,year,1,season,1,iter_count,1) * fmult;
    }
    // Do 1 timestep projection
    project_timestep(fisheries, biol, srr_model_name, srr_params, srr_residuals, srr_residuals_mult, f_tape, timestep);
    // Calculate catch or whatever
    //target_hat_ad = 1000;
    target_hat_ad = fisheries(1)(1).catches()(1, year, 1, season, 1, iter_count);
    Rprintf("target_hat_ad %f\n", target_hat_ad.value());
    // Offset by target
    target_hat_ad = target_hat_ad - catch_target;
    // Set dependent variable
    target_hat_ad >>= target_hat;
    // stop the tape
    Rprintf("Turning off the tape\n");
    trace_off();

    // Do the solving for that timestep (and iter? should we do all iters at once?)
    indep[0] = fmult_initial;
    int out = newton_raphson(indep, tape_tag);

//}

    // Do something with the tape
    //double *x = new double[1];
    //double *y = new double[1];
    //x[0] = fmult_initial;
    //y[0] = 0.0;
    //function(tape_tag,1,1,x,y);
    //jac_solv(tape_tag,1,x,y,2);
    ////gradient(tape_tag, 1, x, y);

//double yout = y[0];

 //   delete [] x;
 //   delete [] y;
    //return 1;
    //return f_tape;
    //return flfs;
    //return biol;
 //   return yout;
 return indep;

}

// Currently only for a single biol and a single catch
// Updates catch in timestep and biol in timestep+1
void project_timestep(FLFisheriesAdolc& fisheries, fwdBiolAdolc& biol, std::string srr_model_name, FLQuant params, FLQuant residuals, bool residuals_mult, FLQuantAdolc7& f, const int timestep){
    Rprintf("In project_timestep.\n");
    // Check dims of landings slots, F and biol are the same
    int year = 0;
    int season = 0;
    int next_year = 0;
    int next_season = 0;
    timestep_to_year_season(timestep, f(1), year, season);
    timestep_to_year_season(timestep+1, f(1), next_year, next_season); // check for bounds on these
    // Check that timestep does not exceed biol
    if (next_year > biol.n().get_nyear()){
        Rcpp::stop("In project_timestep. Trying to access year larger than biol years.\n");
    }
    adouble rec_temp = 0;
    adouble z = 0;
    adouble catch_temp = 0;
    const int max_quant = f(1).get_nquant();

    // Loop over iters
    int iter_count = 1;

    // Calculate the landings and discards
    FLQuantAdolc discards_ratio_temp = fisheries(1)(1).discards_ratio();
    for (int quant_count = 1; quant_count <= max_quant; ++quant_count){
        z =  f(quant_count, year, 1, season, 1, iter_count, 1) + biol.m()(quant_count, year, 1, season, 1, iter_count);
        catch_temp = (f(quant_count, year, 1, season, 1, iter_count, 1) / z) * (1 - exp(-z)) * biol.n()(quant_count, year, 1, season, 1, iter_count);
        fisheries(1)(1).landings_n()(quant_count, year, 1, season, 1, iter_count) = (1 - discards_ratio_temp(quant_count, year, 1, season, 1, iter_count)) * catch_temp;
        fisheries(1)(1).discards_n()(quant_count, year, 1, season, 1, iter_count) = discards_ratio_temp(quant_count, year, 1, season, 1, iter_count) * catch_temp;
    }

    // Update population
    // Get the recruitment
    // ssb = ssb in timestep = current
    rec_temp = 1000;
    biol.n()(1, next_year, 1, next_season, 1, iter_count) = rec_temp;
    for (int quant_count = 1; quant_count < max_quant; ++quant_count){
        z =  f(quant_count, year, 1, season, 1, iter_count,1) + biol.m()(quant_count, year, 1, season, 1, iter_count);
        biol.n()(quant_count+1, next_year, 1, next_season, 1, iter_count) = biol.n()(quant_count, year, 1, season, 1, iter_count) * exp(-z);
    }
    // Assume the last age is a plus group
    z =  f(max_quant, year, 1, season, 1, iter_count, 1) + biol.m()(max_quant, year, 1, season, 1, iter_count);
    biol.n()(max_quant, next_year, 1, next_season, 1, iter_count) = biol.n()(max_quant, next_year, 1, next_season, 1, iter_count) + (biol.n()(max_quant, year, 1, season, 1, iter_count) * exp(-z));

}

// [[Rcpp::export]]
Rcpp::List test_project_timestep(FLFisheriesAdolc fisheries, fwdBiolAdolc biol, std::string srr_model_name, FLQuant params, FLQuant residuals, bool residuals_mult, FLQuantAdolc7 f, const int timestep){
    project_timestep(fisheries, biol, srr_model_name, params, residuals, residuals_mult, f, timestep);
	return Rcpp::List::create(Rcpp::Named("fisheries", fisheries),
                            Rcpp::Named("biol",biol));
}

/*------------------------------------------------------------*/
// operatingModel class

// Empty constructor
template <typename T>
operatingModel_base<T>::operatingModel_base(){
    biol = fwdBiol_base<T>();
    fisheries = FLFisheries_base<T>();
    f = FLQuant7_base<T>();
    f_spwn = FLQuant7_base<T>();
}

// Main constructor
template <typename T>
operatingModel_base<T>::operatingModel_base(const FLFisheries_base<T> fisheries_in, const fwdBiol_base<T> biol_in, const FLQuant7_base<T> f_in, const FLQuant7_base<T> f_spwn_in){
    // Check dims!!
    // Check dims (1 - 5) of landings slots, F and biol are the same
    // Single Biol at the moment.
    // The Biol can be fished by multiple Catches - but each Catch must come from a seperate Fishery
    // Here we assume that each Fishery has one Catch that fishes that Biol - this assumption will break with multiple Biols
    // Biol dims (1 - 5) must therefore match the Catch dims (Fishery[[1]]) and all FLQuants in f and f_spwn
    // Dim 6 must be 1 or n
    const int nfisheries = fisheries_in.get_nfisheries();
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
    for (int fishery_counter = 1; fishery_counter <= nfisheries; ++fishery_counter){
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
}

// Copy constructor - else members can be pointed at by multiple instances
template <typename T>
operatingModel_base<T>::operatingModel_base(const operatingModel_base<T>& operatingModel_source){
    biol = operatingModel_source.biol;
    fisheries = operatingModel_source.fisheries;
    f = operatingModel_source.f;
    f_spwn = operatingModel_source.f_spwn;
}

// Assignment operator to ensure deep copy - else 'data' can be pointed at by multiple instances
template <typename T>
operatingModel_base<T>& operatingModel_base<T>::operator = (const operatingModel_base<T>& operatingModel_source){
	if (this != &operatingModel_source){
        biol = operatingModel_source.biol;
        fisheries = operatingModel_source.fisheries;
        f = operatingModel_source.f;
        f_spwn = operatingModel_source.f_spwn;
	}
	return *this;
}

/* Intrusive 'wrap' */
// Returns a list of stuff
template <typename T>
operatingModel_base<T>::operator SEXP() const{
    Rprintf("Wrapping operatingModel_base<T>.\n");
    return Rcpp::List::create(Rcpp::Named("biol", biol),
                            Rcpp::Named("fisheries",fisheries),
                            Rcpp::Named("f",f),
                            Rcpp::Named("f_spwn",f_spwn));
}


// SSB calculations
template <typename T>
FLQuant_base<T> operatingModel_base<T>::ssb() const {
    FLQuant_base<T> ssb = quant_sum(biol.n() * biol.wt() * biol.fec() * exp(-1.0*(biol.m() * biol.spwn() + f() * f_spwn())));
    return ssb;
}


template <typename T>
FLQuant_base<T> operatingModel_base<T>::ssb(const int timestep, const int unit, const int area) const {
    Rprintf("In vector op\n");
    FLQuant_base<T> full_ssb = ssb();
    int year = 0;
    int season = 0;
    timestep_to_year_season(timestep, full_ssb, year, season);
    FLQuant_base<T> out = full_ssb(1,1,year,year,unit,unit,season,season,area,area,1,full_ssb.get_niter());
    return out;
}

template <typename T>
T operatingModel_base<T>::ssb(const int timestep, const int unit, const int area, const int iter) const {
    Rprintf("In T op\n");
    FLQuant_base<T> full_ssb = ssb();
    int year = 0;
    int season = 0;
    timestep_to_year_season(timestep, full_ssb, year, season);
    T out = full_ssb(1,year,unit,season,area,iter);
    return out;
}

// Currently only for a single biol and a single catch
// Updates catch in timestep and biol in timestep+1
template <typename T>
void operatingModel_base<T>::project_timestep(const int timestep){
    Rprintf("In operatingModel project_timestep.\n");
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

    T rec_temp = 0;
    T catch_temp = 0;
    T z = 0;


    const int max_quant = f(1).get_nquant();

    // Loop over iters
    //int iter_count = 1;
    FLQuant_base<T> discards_ratio_temp = fisheries(fishery_count)(catches_count).discards_ratio();
    for (int iter_count = 1; iter_count <= biol.n().get_niter(); ++iter_count){
        // Calculate the landings and discards
        for (int quant_count = 1; quant_count <= max_quant; ++quant_count){
            z =  f(quant_count, year, 1, season, 1, iter_count, catches_count) + biol.m()(quant_count, year, 1, season, 1, iter_count);
            catch_temp = (f(quant_count, year, 1, season, 1, iter_count, 1) / z) * (1 - exp(-z)) * biol.n()(quant_count, year, 1, season, 1, iter_count);
            fisheries(fishery_count)(catches_count).landings_n()(quant_count, year, 1, season, 1, iter_count) = (1 - discards_ratio_temp(quant_count, year, 1, season, 1, iter_count)) * catch_temp;
            fisheries(fishery_count)(catches_count).discards_n()(quant_count, year, 1, season, 1, iter_count) = discards_ratio_temp(quant_count, year, 1, season, 1, iter_count) * catch_temp;
        }

    // Update population
    // Get the recruitment
    // ssb = ssb in timestep = current
    rec_temp = 1000;
    biol.n()(1, next_year, 1, next_season, 1, iter_count) = rec_temp;
    for (int quant_count = 1; quant_count < max_quant; ++quant_count){
        z =  f(quant_count, year, 1, season, 1, iter_count,1) + biol.m()(quant_count, year, 1, season, 1, iter_count);
        biol.n()(quant_count+1, next_year, 1, next_season, 1, iter_count) = biol.n()(quant_count, year, 1, season, 1, iter_count) * exp(-z);
    }
    // Assume the last age is a plus group
    z =  f(max_quant, year, 1, season, 1, iter_count, 1) + biol.m()(max_quant, year, 1, season, 1, iter_count);
    biol.n()(max_quant, next_year, 1, next_season, 1, iter_count) = biol.n()(max_quant, next_year, 1, next_season, 1, iter_count) + (biol.n()(max_quant, year, 1, season, 1, iter_count) * exp(-z));
    }

}

// Explicit instantiation of class
template class operatingModel_base<double>;
template class operatingModel_base<adouble>;
