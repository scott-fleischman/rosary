type state = {
  mysteryImage: Mystery.mysteryImage,
  mysteryLocation: option(Mystery.mysteryLocation),
};

type action =
  | NextImage
  | UpdateLocation(option(Mystery.mysteryLocation));

let makeInitialMysteryImage =
    (mysterySet: Mystery.mysterySet): Mystery.mysteryImage => {
  mystery: {
    mysterySet,
    mysteryOrdinal: FirstMystery,
  },
  imageIndex: Mystery.initialImageIndex,
};

let updateMysteryImage =
    (
      mysteryLocation: Mystery.mysteryLocation,
      mysteryImage: Mystery.mysteryImage,
    ) =>
  if (mysteryLocation.mystery == mysteryImage.mystery) {
    mysteryImage;
  } else {
    Mystery.initialMysteryImage(mysteryLocation.mystery);
  };

let reducer = (state, action) =>
  switch (action) {
  | NextImage => {
      ...state,
      mysteryImage: Mystery.nextImage(state.mysteryImage),
    }
  | UpdateLocation(mysteryLocation) => {
      mysteryImage:
        switch (mysteryLocation) {
        | Some(location) => updateMysteryImage(location, state.mysteryImage)
        | None => state.mysteryImage
        },
      mysteryLocation,
    }
  };

let initialState = (mysterySet: Mystery.mysterySet) => {
  mysteryImage: makeInitialMysteryImage(mysterySet),
  mysteryLocation: Some(Mystery.initialMysteryLocation(mysterySet)),
};

[@react.component]
let make = (~mysterySet: Mystery.mysterySet, ~language: Labels.language) => {
  let (state, dispatch) =
    React.useReducer(reducer, initialState(mysterySet));
  let {mysteryImage, mysteryLocation} = state;

  let updateLocation = (location: option(Mystery.mysteryLocation)) =>
    dispatch(UpdateLocation(location));
  let onClickNextLocation = _event =>
    updateLocation(Mystery.nextMysteryLocationOption(state.mysteryLocation));
  let nextImage = () => dispatch(NextImage);

  <div onClick=onClickNextLocation>
    <MysteryImageView mysteryImage />
    <MysteryNavView mysteryLocation language updateLocation nextImage />
  </div>;
};