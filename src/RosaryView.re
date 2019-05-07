type state = {mysteryImage: Mystery.mysteryImage};

type action =
  | NextImage;

let initialMysteryImage: Mystery.mysteryImage = {
  mystery: {
    mysterySet: Mystery.Sorrowful,
    mysteryOrdinal: FirstMystery,
  },
  imageIndex: Mystery.initialImageIndex,
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | NextImage => {
            ...state,
            mysteryImage: Mystery.nextImage(state.mysteryImage),
          }
        },
      {mysteryImage: initialMysteryImage},
    );
  let mysteryImage: Mystery.mysteryImage = state.mysteryImage;
  <div onClick={_event => dispatch(NextImage)}>
    <MysteryImageView mysteryImage />
  </div>;
};