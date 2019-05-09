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

[@react.component]
let make = (~mysterySet: Mystery.mysterySet, ~language: Labels.language) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | NextImage => {
            ...state,
            mysteryImage: Mystery.nextImage(state.mysteryImage),
          }
        | UpdateLocation(mysteryLocation) => {
            mysteryImage:
              switch (mysteryLocation) {
              | Some(location) =>
                updateMysteryImage(location, state.mysteryImage)
              | None => state.mysteryImage
              },
            mysteryLocation,
          }
        },
      {
        mysteryImage: makeInitialMysteryImage(mysterySet),
        mysteryLocation: Some(Mystery.initialMysteryLocation(mysterySet)),
      },
    );
  let {mysteryImage, mysteryLocation} = state;
  let updateLocation = (location: option(Mystery.mysteryLocation)) =>
    dispatch(UpdateLocation(location));
  <div onClick={_event => dispatch(NextImage)}>
    <MysteryImageView mysteryImage />
    <MysteryNavView mysteryLocation updateLocation language />
  </div>;
};