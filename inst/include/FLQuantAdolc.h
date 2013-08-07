/* 
 * Copyright 2013 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

/* See notes in FLQuant_base.h
 * Developement of a special class has been halted until shown that it is actually necessary.
 */

//# include "FLQuant_base.h"

// The FLQuantAdolc class
/*
class FLQuantAdolc: public FLQuant_base<adouble> {
    public:
        // Constructors and copy methods
        FLQuantAdolc();
        FLQuantAdolc(SEXP flq_sexp);
        operator SEXP() const; // Used as intrusive 'wrap'

        // Stupid helper functions so that I can keep track of what is going on
        void what_am_i();
        int new_int;        
};

*/

// Or...
// Could use something like this structure instead if we want to template the FLQuantAD class
// so adouble and autodif variables can be used
/*
template <typename T>
class FLQuantAD_base : public FLQuant_base<T> {
    public:
        // Constructors and copy methods
        FLQuantAD_base();
        FLQuantAD_base(SEXP flq_sexp);
        operator SEXP() const; // Used as intrusive 'wrap'

        // Stupid helper functions so that I can keep track of what is going on
        void what_am_i();
        int new_int;        
};
*/
