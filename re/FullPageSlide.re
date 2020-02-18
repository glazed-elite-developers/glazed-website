module Styles = {
  open Css;

  let wrapper =
    style([
      height(pct(100.)),
      minHeight(pct(100.)),
      backgroundSize(`cover),
    ]);
};

[@react.component]
let make = (~className=?, ~children, ~backgroundImageUrl=?) => {
  let inlineStyle =
    switch (backgroundImageUrl) {
    | None => ReactDOMRe.Style.make()
    | Some(url) =>
      ReactDOMRe.Style.make(~backgroundImage={j|url('$(url)')|j}, ())
    };

  <section
    className={Utils.React.combineOptionalStyles(
      ~baseStyles=Styles.wrapper,
      ~className?,
    )}
    style=inlineStyle>
    children
  </section>;
};

let default = make;