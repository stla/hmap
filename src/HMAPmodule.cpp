#ifndef _HMAPHEADER_
#include "hmap_types.h"
#endif

#include "HMAP.h"

void finalizer_of_hmap(HMAP* ptr) {
  // Rcpp::Rcout << "finalizer of uMAPR has been called\n";
  // Rcpp::XPtr<umapR> ptrptr = ptr->ptr;
  // delete ptrptr.get();
  hmapR hmap = ptr->hmap;
  hmap.clear();
  //  delete ptr;
}

RCPP_MODULE(class_HMAP) {
  using namespace Rcpp;

  class_<HMAP>("HMAP")

      .constructor<Rcpp::StringVector, Rcpp::List>()
      .constructor<Rcpp::XPtr<hmapR>>()

      .field("ptr", &HMAP::ptr)

      .method("size", &HMAP::size)
//      .method("at", &HMAP::at)
      .method("at2", &HMAP::at2)
      .method("has_key", &HMAP::has_key)
      .method("insert", &HMAP::insert)
      .method("assign", &HMAP::assign)
      .method("erase", &HMAP::erase)
      .method("merase", &HMAP::merase)
      .method("extract", &HMAP::extract)
      .method("extract_inplace", &HMAP::extract_inplace)
      .method("extract_by_erasing", &HMAP::extract_by_erasing)
      .method("extract_by_erasing_inplace", &HMAP::extract_by_erasing_inplace)
//      .method("merge", &HMAP::merge)
      .method("keys", &HMAP::keys)
      .method("values", &HMAP::values)
      .method("toList", &HMAP::toList)
      .finalizer(&finalizer_of_hmap);
}