#ifndef _HMAPHEADER_
#include "hmap_types.h"
#endif

hmapR hmapNew(Rcpp::StringVector keys, Rcpp::List values) {
  hmapR hmap;
  for(R_xlen_t i = 0; i < keys.size(); i++) {
    hmap.emplace(keys[i], values[i]);
  }
  return hmap;
}

