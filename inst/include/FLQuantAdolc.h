# include "FLQuant_base.h"

// The FLQuantAdolc class
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


