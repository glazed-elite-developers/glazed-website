module Styles = {
  open Css;

  module Variables = {
    let height = rem(3.75);
  };

  let wrapper =
    style([backgroundColor(hex(Theme.Colors.glazedBlueMidnight)), height(Variables.height)]);
};

[@react.component]
let make = (~className=?, ~children) => {
  <footer className=?{Utils.React.combineClassNames([Some(Styles.wrapper), className])}>
    children
  </footer>;
};

let default = make;
