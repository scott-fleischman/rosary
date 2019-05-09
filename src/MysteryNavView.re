let containerStyle =
  ReactDOMRe.Style.make(
    ~position="absolute",
    ~right="0",
    ~bottom="0",
    ~cursor="pointer",
    ~background="rgba(255,255,255,0.1)",
    ~padding="4px",
    (),
  );

let titleStyle =
  ReactDOMRe.Style.make(~fontSize="48pt", ~margin="16px 0", ());

[@react.component]
let make =
    (
      ~language: Labels.language,
      ~mysteryLocation: option(Mystery.mysteryLocation),
      ~updateLocation,
    ) => {
  let onClick = event => {
    updateLocation(Mystery.nextMysteryLocationOption(mysteryLocation));
    ReactEvent.Synthetic.stopPropagation(event);
  };
  let navText =
    switch (mysteryLocation) {
    | Some(location) => Labels.mysteryLocationToLabel(language, location)
    | None => Labels.amenLabel(language)
    };
  <div style=containerStyle onClick>
    <p style=titleStyle> {ReasonReact.string(navText)} </p>
  </div>;
};