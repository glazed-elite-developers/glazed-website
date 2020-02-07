module Styles = {
  open Css;

  let wrapper = style([height(pct(100.)), minHeight(pct(100.))]);
};

[@react.component]
let make = (~className, ~children) => {
  let combinedStyles =
    switch (className) {
    | None => Styles.wrapper
    | Some(className) => Css.merge([Styles.wrapper, className])
    };

  <section
    className=combinedStyles
    style={ReactDOMRe.Style.make(
      ~backgroundImage={j|url('')|j},
      (),
    )}>
    children
  </section>;
};

let default = make;