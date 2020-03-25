open Utils.React;

module Styles = {
  open Css;

  let wrapper =
    style([
      position(`relative),
      before([contentRule(""), display(`block), paddingTop(pct(100.))]),
    ]);
  let content =
    style([
      position(`absolute),
      top(`zero),
      right(`zero),
      bottom(`zero),
      left(`zero),
    ]);
};

[@react.component]
let make = (~children=?, ~className=?, ~contentClassName=?, ~onMouseEnter=?) => {
  <div
    className={combineOptionalStyles(~baseStyles=Styles.wrapper, ~className?)}
    ?onMouseEnter>
    <div
      className={combineOptionalStyles(
        ~baseStyles=Styles.content,
        ~className=?contentClassName,
      )}>
      {switch (children) {
       | None => React.null
       | Some(children') => children'
       }}
    </div>
  </div>;
};