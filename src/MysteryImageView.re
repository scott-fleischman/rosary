let imageBoxStyle = ReactDOMRe.Style.make(~display="grid", ());
let imageStyle = ReactDOMRe.Style.make(~height="100vh", ~margin="auto", ());

[@react.component]
let make = (~mysteryImage: Mystery.mysteryImage) =>
  <div style=imageBoxStyle>
    <img
      style=imageStyle
      src={Mystery.mysteryImageToFullPath(mysteryImage)}
    />
  </div>;