open Bos_setup;

type filesystemItem = {
  fpath: Fpath.t,
  title: string,
  isDir: bool,
}

let getFiles = (fpath) => OS.Dir.contents(fpath, ~dotfiles=true, ~rel=false)
  >>| fpaths => List.map(fpath => (fpath, OS.Path.stat(fpath)), fpaths)
  |> List.filter(((_, statResult)) => Rresult.R.is_ok(statResult))
  |> List.map(((fpath, statResult)) => {
    let stat: Unix.stats = Rresult.R.get_ok(statResult);
    let isDir = switch(stat.st_kind) {
      | Unix.S_DIR => true
      | _ => false
    };
    { title: Fpath.filename(fpath), isDir, fpath };
  })
  /*
  >>| fpaths => List.map(fpath => ({ title: String.concat(~sep="/", Fpath.segs(fpath)), isDir: Fpath.is_dir_path(fpath) }), fpaths);
  */