open Bos_setup;

let path = Fpath.of_string("C:/");

let getFiles = () => path
  >>= fpath => OS.Dir.contents(fpath, ~dotfiles=true, ~rel=true)
  >>= fpaths => Rresult.Ok(List.map(fpath => Fpath.to_string(fpath), fpaths));