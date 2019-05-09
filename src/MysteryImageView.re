let imageBoxStyle =
  ReactDOMRe.Style.make(~display="grid", ~height="100%", ~zIndex="-1", ());
let imageStyle =
  ReactDOMRe.Style.make(
    ~maxWidth="100%",
    ~maxHeight="100vh",
    ~margin="auto",
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