open Utils.React;

module Styles = {
  open Css;

  let wrapper = style([position(`relative)]);
  let mask =
    style([
      position(`absolute),
      width(pct(100.)),
      height(pct(100.)),
      top(`zero),
      left(`zero),
      backgroundColor(rgba(255, 255, 255, 0.35)),
    ]);
};

[@react.component]
let make = (~className=?, ~maskClassName=?, ~children) => {
  <div className=?{combineClassNames([Some(Styles.wrapper), className])}>
    children
    <div
      className=?{combineClassNames([Some(Styles.mask), maskClassName])}
    />
  </div>;
};

let default = make;