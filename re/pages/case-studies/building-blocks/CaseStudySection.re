open Utils.React;

module Styles = {
  open Css;

  let wrapper =
    style([
      padding2(~h=rem(1.25), ~v=rem(2.5)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [padding2(~h=rem(11.25), ~v=rem(6.25))],
      ),
    ]);
};

[@react.component]
let make = (~className=?, ~children) => {
  <section className=?{combineClassNames([Some(Styles.wrapper), className])}>
    children
  </section>;
};

let default = make;