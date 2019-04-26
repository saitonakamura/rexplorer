open Bos_setup;

type filesystemItem = {
  title: string,
  isDir: bool,
}

let path = Fpath.of_string("C:/");

let getFiles = () => path
  >>= fpath => OS.Dir.contents(fpath, ~dotfiles=true, ~rel=false)
  >>| fpaths => List.map(fpath => (fpath, OS.Path.stat(fpath)), fpaths)
  |> List.filter(((_, statResult)) => Rresult.R.is_ok(statResult))
  |> List.map(((fpath, statResult)) => {
    let stat: Unix.stats = Rresult.R.get_ok(statResult);
    let isDir = switch(stat.st_kind) {
      | Unix.S_DIR => true
      | _ => false
    };
    { title: Fpath.filename(fpath), isDir };
  })
  /*
  >>| fpaths => List.map(fpath => ({ title: String.concat(~sep="/", Fpath.segs(fpath)), isDir: Fpath.is_dir_path(fpath) }), fpaths);
  */

