open Revery;
open Revery.UI;
open Revery.UI.Components;
open Files;

type state = {
  currentFpath: Fpath.t
}

type action =
  | GoTo(Fpath.t)

let reducer = (action, state) => {
  switch (action) {
  | GoTo(fpath) => { currentFpath: fpath }
  }
}

let component = React.component("FilesView");

let createElement = (~children as _, ()) =>
  component(hooks => {
    let (state, dispatch, hooks) =
      React.Hooks.reducer(
        ~initialState={
          currentFpath: Rresult.R.get_ok(Fpath.of_string("C:\\"))
        },
        reducer,
        hooks
      );

  let goto = fpath => dispatch(GoTo(fpath))

  let innerStyle = Style.[flexDirection(`Column), alignItems(`FlexEnd), justifyContent(`FlexStart)];

  let textStyle =
        Style.[
          color(Colors.black),
          fontFamily("Roboto-Regular.ttf"),
          fontSize(14),
        ];

  let files = switch (getFiles(state.currentFpath)) {
    | Ok(filenames) => List.map(
      filesystemItem => {
        if (filesystemItem.isDir) {
          <Clickable onClick={() => goto(filesystemItem.fpath)}>
            <Text style=textStyle text={filesystemItem.title ++ "_Dir"} />
          </Clickable>
        } else {
          <Text style=textStyle text={filesystemItem.title ++ "_File"} />
        }
      },
      filenames)
    | Error(error) => [<Text style=textStyle text="Error" />]
  };

  let back = <Clickable onClick={() => goto(Fpath.parent(state.currentFpath))}><Text style=textStyle text=".." /></Clickable>;
  let filesWithBack = [back, ...files];

  (hooks, <View style=innerStyle>...filesWithBack</View>);
  });