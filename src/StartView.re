type mode =
  | SelectMystery
  | InMystery(Mystery.mysterySet);

type state = {
  mode,
  language: Labels.language,
};

let initialState = {mode: SelectMystery, language: Labels.English};

type action =
  | GoHome
  | SelectMystery(Mystery.mysterySet);

let containerStyle = ReactDOMRe.Style.make(~display="grid", ());

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | GoHome => {...state, mode: SelectMystery}
        | SelectMystery(mystery) => {...state, mode: InMystery(mystery)}
        },
      initialState,
    );
  let selectMysterySet = (mysterySet: Mystery.mysterySet) =>
    dispatch(SelectMystery(mysterySet));
  let language: Labels.language = state.language;
  let innerComponent =
    switch (state.mode) {
    | SelectMystery => <MysterySelectorView selectMysterySet language />
    | InMystery(mysterySet) => <RosaryView mysterySet language />
    };
  <div style=containerStyle> innerComponent </div>;
};