module Styles = {
  open Css;

  let wrapper =
    style([
      position(`relative),
      before([contentRule(`text("")), display(`block), paddingTop(pct(100.))]),
    ]);
  let content =
    style([position(`absolute), top(`zero), right(`zero), bottom(`zero), left(`zero)]);
};

[@react.component]
let make = (~children=?, ~className=?, ~contentClassName=?, ~onMouseEnter=?) => {
  <div
    className=?{Utils.React.combineClassNames([Some(Styles.wrapper), className])} ?onMouseEnter>
    <div className=?{Utils.React.combineClassNames([Some(Styles.content), contentClassName])}>
      {switch (children) {
       | None => React.null
       | Some(children') => children'
       }}
    </div>
  </div>;
};

let default = make;
