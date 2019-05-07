let handleClick = _event => Js.log("clicked!");

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
let make = () =>
  <div onClick=handleClick style=imageBoxStyle>
    <img style=imageStyle src="img/sorrowful/5-crucifixion-1.jpg" />
  </div>;