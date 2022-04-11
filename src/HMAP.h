hmapR hmapNew(Rcpp::StringVector, Rcpp::List);

class HMAP {

 public:
  hmapR hmap;
  Rcpp::XPtr<hmapR> ptr;
  HMAP(Rcpp::StringVector keys_, Rcpp::List values_)
      : hmap(hmapNew(keys_, values_)), ptr(Rcpp::XPtr<hmapR>(&hmap, false)) {}
  HMAP(Rcpp::XPtr<hmapR> ptr_)
      : hmap(*(ptr_.get())), ptr(Rcpp::XPtr<hmapR>(&hmap, false)) {}
  ~HMAP() {
  }

  unsigned size() { return hmap.size(); }

  // Rcpp::List at(std::string key) {
  //   umapR::iterator it = umap.find(key);
  //   if(it != umap.end()) {
  //     return Just(it->second);
  //   } else {
  //     return Nothing();
  //   }
  // }
  
  Rcpp::RObject at2(std::string key) {
    return hmap.at(key);
  }
    
  
  bool has_key(std::string key) { return hmap.find(key) != hmap.end(); }

  Rcpp::StringVector keys() {
    const unsigned s = hmap.size();
    Rcpp::StringVector out(s);
    unsigned i = 0;
    for(hmapR::iterator it = hmap.begin(); it != hmap.end(); it++) {
      out[i] = it->first;
      i++;
    }
    return out;
  }

  Rcpp::List values() {
    const unsigned s = hmap.size();
    Rcpp::List out(s);
    unsigned i = 0;
    for(hmapR::iterator it = hmap.begin(); it != hmap.end(); it++) {
      out(i) = it->second;
      i++;
    }
    return out;
  }

  Rcpp::List toList() {
    const unsigned s = hmap.size();
    Rcpp::StringVector Keys(s);
    Rcpp::List Values(s);
    unsigned i = 0;
    for(hmapR::iterator it = hmap.begin(); it != hmap.end(); it++) {
      Keys(i) = it->first;
      Values(i) = it->second;
      i++;
    }
    Rcpp::List out;
    out["keys"] = Keys;
    out["values"] = Values;
    return out;
  }

  bool insert(std::string key, Rcpp::RObject value) {
    std::pair<hmapR::iterator, bool> x = hmap.emplace(key, value);
    return x.second;
  }

  bool assign(std::string key, Rcpp::RObject value) {
    std::pair<hmapR::iterator, bool> x = hmap.insert_or_assign(key, value);
    return x.second;
  }

  void erase(std::string key) {
    hmap.erase(key);
  }

  void merase(Rcpp::StringVector keys) {
    for(Rcpp::String key : keys) {
      hmap.erase(key);
    }
  }

  Rcpp::XPtr<hmapR> extract(Rcpp::StringVector keys) {
    hmapR submap;
    // umapR* submapptr = &submap;
    for(Rcpp::String key : keys) {
      hmapR::iterator it = hmap.find(key);
      if(it != hmap.end()) {
        submap.emplace(key, it->second);
      }
    }
    // std::unique_ptr<umapR> submapptr(new umapR(submap));
    hmapR* submapptr(new hmapR(submap));  //&submap;
    Rcpp::XPtr<hmapR> out = Rcpp::XPtr<hmapR>(submapptr, false);
    //    delete submapptr;
    return out;  // new umapR(submap), true);
  }

  void extract_inplace(Rcpp::StringVector keys) {
    hmapR submap;
    for(Rcpp::String key : keys) {
      hmapR::iterator it = hmap.find(key);
      if(it != hmap.end()) {
        submap.emplace(key, it->second);
      }
    }
    hmap = submap;
  }

  Rcpp::XPtr<hmapR> extract_by_erasing(Rcpp::StringVector keys) {
    hmapR* submapptr = new hmapR(hmap);
    hmapR submap = *submapptr;
    for(hmapR::iterator it = submap.begin(); it != submap.end(); it++) {
      if(std::find(keys.begin(), keys.end(), it->first) == keys.end()) {
        submap.erase(it->first);
      }
    }
    // Rcpp::StringVector allkeys = this.keys2();
    // for(Rcpp::String key : allkeys) {
    //   if(std::find(keys.begin(), keys.end(), key) == keys.end()){
    //     submap.erase(key);
    //   }
    // }
    Rcpp::XPtr<hmapR> out = Rcpp::XPtr<hmapR>(new hmapR(submap), false);
    delete submapptr;
    return out;
  }

  void extract_by_erasing_inplace(Rcpp::StringVector keys) {
    for(hmapR::iterator it = hmap.begin(); it != hmap.end(); it++) {
      if(std::find(keys.begin(), keys.end(), it->first) == keys.end()) {
        hmap.erase(it->first);
      }
    }
  }

  // void merge(Rcpp::XPtr<umapR> umap2ptr) {
  //   umapR umap2 = *(umap2ptr.get());
  //   umap.merge(umap2);
  //   // ptr = Rcpp::XPtr<umapR>(new umapR(umap, true));
  // }
};