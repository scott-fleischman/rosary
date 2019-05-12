let style =
  ReactDOMRe.Style.make(~width="62px", ~height="62px", ~padding="16px", ());

[@react.component]
let make = (~onClick) => {
  <input type_="image" onClick style src="img/icons/refresh.png" />;
};