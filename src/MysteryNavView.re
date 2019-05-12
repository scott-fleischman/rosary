let containerStyle =
  ReactDOMRe.Style.make(
    ~position="fixed",
    ~right="0",
    ~bottom="0",
    ~left="0",
    ~cursor="pointer",
    ~background="rgba(255,255,255,0.1)",
    ~padding="4px",
    ~display="grid",
    ~gridTemplateColumns="1fr 80px",
    ~alignItems="center",
    (),
  );

let titleStyle =
  ReactDOMRe.Style.make(~fontSize="48pt", ~margin="16px 16px", ());

[@react.component]
let make =
    (
      ~language: Labels.language,
      ~mysteryLocation: option(Mystery.mysteryLocation),
      ~updateLocation,
      ~nextImage,
    ) => {
  let onClickNextLocation = event => {
    updateLocation(Mystery.nextMysteryLocationOption(mysteryLocation));
    ReactEvent.Synthetic.stopPropagation(event);
  };
  let onClickChangeImage = event => {
    nextImage();
    ReactEvent.Synthetic.stopPropagation(event);
  };
  let navText =
    switch (mysteryLocation) {
    | Some(location) => Labels.mysteryLocationToLabel(language, location)
    | None => Labels.amenLabel(language)
    };
  <div style=containerStyle>
    <div style=titleStyle onClick=onClickNextLocation>
      {ReasonReact.string(navText)}
    </div>
    <ChangeImageButton onClick=onClickChangeImage />
  </div>;
};