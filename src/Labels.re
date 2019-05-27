type language =
  | English;

let mysterySetToLabel =
    (language: language, mysterySet: Mystery.mysterySet): string =>
  switch (language) {
  | English =>
    switch (mysterySet) {
    | Mystery.Joyful => "Joyful Mysteries"
    | Mystery.Sorrowful => "Sorrowful Mysteries"
    }
  };

let mysteryToLabel =
    (language: language, {mysterySet, mysteryOrdinal}: Mystery.mystery)
    : string =>
  switch (language) {
  | English =>
    switch (mysterySet) {
    | Mystery.Joyful =>
      switch (mysteryOrdinal) {
      | FirstMystery => "1st Joyful Mystery: Annunciation to Mary"
      | SecondMystery => "2nd Joyful Mystery: Mary visits Elizabeth"
      | ThirdMystery => "3rd Joyful Mystery: Birth of Jesus"
      | FourthMystery => "4th Joyful Mystery: Presentation of Jesus"
      | FifthMystery => "5th Joyful Mystery: Finding of Jesus"
      }
    | Mystery.Sorrowful =>
      switch (mysteryOrdinal) {
      | FirstMystery => "1st Sorrowful Mystery: Agony in the Garden"
      | SecondMystery => "2nd Sorrowful Mystery: Scourging at the Pillar"
      | ThirdMystery => "3rd Sorrowful Mystery: Crowning with Thorns"
      | FourthMystery => "4th Sorrowful Mystery: Carrying of the Cross"
      | FifthMystery => "5th Sorrowful Mystery: Crucifixion"
      }
    }
  };

let mysteryLocationToLabel =
    (language: language, mysteryLocation: Mystery.mysteryLocation): string =>
  switch (language) {
  | English =>
    switch (mysteryLocation.location) {
    | AnnounceMystery => mysteryToLabel(language, mysteryLocation.mystery)
    | OurFather => "Our Father"
    | HailMary(value) => "Hail Mary (" ++ string_of_int(value) ++ ")"
    | GloryBe => "Glory Be"
    | OMyJesus => "O My Jesus"
    }
  };

let rosaryLabel = (language: language): string =>
  switch (language) {
  | English => "The Holy Rosary"
  };

let amenLabel = (language: language): string =>
  switch (language) {
  | English => "Amen"
  };