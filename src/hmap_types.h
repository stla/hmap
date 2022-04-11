#ifndef _HMAPHEADER_
#define _HMAPHEADER_

//#define RCPP_USE_FINALIZE_ON_EXIT

#include <Rcpp.h>
#include "parallel_hashmap/phmap.h"

typedef phmap::flat_hash_map<std::string, Rcpp::RObject> hmapR;

// std::vector<std::string> vectordiff(Rcpp::StringVector, Rcpp::StringVector);

Rcpp::List Just(Rcpp::RObject);
Rcpp::List Nothing();


#endif