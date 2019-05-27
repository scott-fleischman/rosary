let containerStyle =
  ReactDOMRe.Style.make(
    ~margin="auto",
    ~display="flex",
    ~flexDirection="column",
    ~alignItems="center",
    (),
  );

let titleStyle =
  ReactDOMRe.Style.make(~fontSize="60pt", ~margin="16px 0", ());
let linkStyle =
  ReactDOMRe.Style.make(~cursor="pointer", ~fontSize="48pt", ());

[@react.component]
let make = (~selectMysterySet, ~language: Labels.language) => {
  let clickSelectMystery = (mysterySet: Mystery.mysterySet, _event) =>
    selectMysterySet(mysterySet);
  <div style=containerStyle>
    <div style=titleStyle>
      {ReasonReact.string(Labels.rosaryLabel(language))}
    </div>
    <div style=linkStyle onClick={clickSelectMystery(Mystery.Joyful)}>
      {ReasonReact.string(Labels.mysterySetToLabel(language, Mystery.Joyful))}
    </div>
    <div style=linkStyle onClick={clickSelectMystery(Mystery.Sorrowful)}>
      {ReasonReact.string(
         Labels.mysterySetToLabel(language, Mystery.Sorrowful),
       )}
    </div>
  </div>;
};