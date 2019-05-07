/* We only have sorrowful mysteries for now */
type mysterySet =
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

let mysterySetToDirectory = (mysterySet: mysterySet): string =>
  switch (mysterySet) {
  | Sorrowful => "sorrowful"
  };

let mysteryToFilePrefix = ({mysterySet, mysteryOrdinal}): string =>
  switch (mysterySet, mysteryOrdinal) {
  | (Sorrowful, FirstMystery) => "1-agony"
  | (Sorrowful, SecondMystery) => "2-scourging"
  | (Sorrowful, ThirdMystery) => "3-crowning"
  | (Sorrowful, FourthMystery) => "4-carrying"
  | (Sorrowful, FifthMystery) => "5-crucifixion"
  };

let mysteryToImageFormats =
    ({mysterySet, mysteryOrdinal}): array(imageFormat) =>
  switch (mysterySet, mysteryOrdinal) {
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