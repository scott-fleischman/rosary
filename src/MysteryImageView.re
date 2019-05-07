let imageBoxStyle =
  ReactDOMRe.Style.make(
    ~margin="0px",
    ~padding="0px",
    ~display="grid",
    ~height="100%",
    (),
  );
let imageStyle =
  ReactDOMRe.Style.make(
    ~margin="auto",
    ~padding="0px",
    ~maxWidth="100%",
    ~maxHeight="100vh",
    (),
  );

[@react.component]
let make = (~mysteryImage: Mystery.mysteryImage) =>
  <div style=imageBoxStyle>
    <img
      style=imageStyle
      src={Mystery.mysteryImageToFullPath(mysteryImage)}
    />
  </div>;