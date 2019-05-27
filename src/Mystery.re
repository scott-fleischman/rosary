/* We only have sorrowful mysteries for now */
type mysterySet =
  | Joyful
  | Sorrowful;

type mysteryOrdinal =
  | FirstMystery
  | SecondMystery
  | ThirdMystery
  | FourthMystery
  | FifthMystery;

type mystery = {
  mysterySet,
  mysteryOrdinal,
};

type location =
  | AnnounceMystery
  | OurFather
  | HailMary(int)
  | GloryBe
  | OMyJesus;

type mysteryLocation = {
  mystery,
  location,
};

type imageFormat =
  | Png
  | Jpeg;

type imageIndex =
  | ImageIndex(int);

let initialImageIndex = ImageIndex(1);

type mysteryImage = {
  mystery,
  imageIndex,
};

let initialMysteryImage = (mystery: mystery): mysteryImage => {
  mystery,
  imageIndex: initialImageIndex,
};

let mysterySetToDirectory = (mysterySet: mysterySet): string =>
  switch (mysterySet) {
  | Joyful => "joyful"
  | Sorrowful => "sorrowful"
  };

let mysteryToFilePrefix = ({mysterySet, mysteryOrdinal}): string =>
  switch (mysterySet, mysteryOrdinal) {
  | (Joyful, FirstMystery) => "1-annunciation"
  | (Joyful, SecondMystery) => "2-visitation"
  | (Joyful, ThirdMystery) => "3-birth"
  | (Joyful, FourthMystery) => "4-presentation"
  | (Joyful, FifthMystery) => "5-finding"
  | (Sorrowful, FirstMystery) => "1-agony"
  | (Sorrowful, SecondMystery) => "2-scourging"
  | (Sorrowful, ThirdMystery) => "3-crowning"
  | (Sorrowful, FourthMystery) => "4-carrying"
  | (Sorrowful, FifthMystery) => "5-crucifixion"
  };

let mysteryToImageFormats =
    ({mysterySet, mysteryOrdinal}): array(imageFormat) =>
  switch (mysterySet, mysteryOrdinal) {
  | (Joyful, FirstMystery) => [|Jpeg, Jpeg|]
  | (Joyful, SecondMystery) => [|Jpeg|]
  | (Joyful, ThirdMystery) => [|Jpeg|]
  | (Joyful, FourthMystery) => [|Jpeg, Jpeg, Jpeg|]
  | (Joyful, FifthMystery) => [|Jpeg|]
  | (Sorrowful, FirstMystery) => [|Png, Jpeg, Jpeg, Jpeg|]
  | (Sorrowful, SecondMystery) => [|Jpeg, Jpeg|]
  | (Sorrowful, ThirdMystery) => [|Jpeg, Jpeg|]
  | (Sorrowful, FourthMystery) => [|Jpeg|]
  | (Sorrowful, FifthMystery) => [|Jpeg, Jpeg|]
  };

let imageFormatToSuffix = (imageFormat: imageFormat): string =>
  switch (imageFormat) {
  | Png => "png"
  | Jpeg => "jpg"
  };

let imageIndexToString = (imageIndex: imageIndex): string =>
  switch (imageIndex) {
  | ImageIndex(index) => string_of_int(index)
  };

let getWrappedIndex = (imageIndex: imageIndex, items: array('a)): imageIndex => {
  let ImageIndex(inputIndex) = imageIndex;
  let validIndex = (inputIndex - 1) mod Array.length(items) + 1;
  ImageIndex(validIndex);
};

let getWrappedItem =
    (imageIndex: imageIndex, items: array('a)): (imageIndex, 'a) => {
  let validIndex = getWrappedIndex(imageIndex, items);
  let ImageIndex(oneBasedIndex) = validIndex;
  let zeroBasedIndex = oneBasedIndex - 1;
  (validIndex, items[zeroBasedIndex]);
};

let mysteryImageToFileName = ({mystery, imageIndex}: mysteryImage) => {
  let imageFormats = mysteryToImageFormats(mystery);
  let (actualIndex, imageFormat) = getWrappedItem(imageIndex, imageFormats);
  mysteryToFilePrefix(mystery)
  ++ "-"
  ++ imageIndexToString(actualIndex)
  ++ "."
  ++ imageFormatToSuffix(imageFormat);
};

let mysteryImageToFullPath = (mysteryImage: mysteryImage): string => {
  let {mystery} = mysteryImage;
  let {mysterySet} = mystery;
  let directory = mysterySetToDirectory(mysterySet);
  let fileName = mysteryImageToFileName(mysteryImage);
  "img/" ++ directory ++ "/" ++ fileName;
};

let nextImage = ({mystery, imageIndex}: mysteryImage): mysteryImage => {
  let ImageIndex(rawIndex) = imageIndex;
  let unsafeNextIndex = ImageIndex(rawIndex + 1);
  let imageFormats = mysteryToImageFormats(mystery);
  let nextIndex = getWrappedIndex(unsafeNextIndex, imageFormats);
  {mystery, imageIndex: nextIndex};
};

let nextMysteryOrdinal =
    (mysteryOrdinal: mysteryOrdinal): option(mysteryOrdinal) =>
  switch (mysteryOrdinal) {
  | FirstMystery => Some(SecondMystery)
  | SecondMystery => Some(ThirdMystery)
  | ThirdMystery => Some(FourthMystery)
  | FourthMystery => Some(FifthMystery)
  | FifthMystery => None
  };

let nextLocation = (location: location) =>
  switch (location) {
  | AnnounceMystery => Some(OurFather)
  | OurFather => Some(HailMary(1))
  | HailMary(value) =>
    if (value < 10) {
      Some(HailMary(value + 1));
    } else {
      Some(GloryBe);
    }
  | GloryBe => Some(OMyJesus)
  | OMyJesus => None
  };

let initialMysteryOrdinal: mysteryOrdinal = FirstMystery;
let initialLocation: location = AnnounceMystery;

let initialMysteryLocation = (mysterySet: mysterySet): mysteryLocation => {
  mystery: {
    mysterySet,
    mysteryOrdinal: initialMysteryOrdinal,
  },
  location: initialLocation,
};

let nextMysteryLocation =
    (mysteryLocation: mysteryLocation): option(mysteryLocation) => {
  let {mystery, location} = mysteryLocation;
  let {mysterySet, mysteryOrdinal} = mystery;
  switch (nextLocation(location)) {
  | Some(nextLocation) => Some({mystery, location: nextLocation})
  | None =>
    switch (nextMysteryOrdinal(mysteryOrdinal)) {
    | Some(nextOrdinal) =>
      Some({
        mystery: {
          mysterySet,
          mysteryOrdinal: nextOrdinal,
        },
        location: initialLocation,
      })
    | None => None
    }
  };
};

let nextMysteryLocationOption =
    (mysteryLocationOption: option(mysteryLocation))
    : option(mysteryLocation) =>
  switch (mysteryLocationOption) {
  | Some(location) => nextMysteryLocation(location)
  | None => None
  };