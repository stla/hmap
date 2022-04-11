dllunload <- function(){
  dyn.unload(
    system.file("libs", "x64", "hmap.dll", package = "hmap")
  )
}

makedoc <- function(){
  roxygen2::roxygenise(load_code = roxygen2::load_installed)
}
