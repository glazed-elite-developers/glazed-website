module Styles = {
  open Css;

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
      height(pct(100.)),
      padding3(~top=rem(4.1875), ~h=rem(1.25), ~bottom=`zero),
      media(
        Theme.Breakpoints.tabletLandscape,
        [padding3(~top=rem(6.25), ~h=rem(4.75), ~bottom=`zero)],
      ),
    ]);
};

[@react.component]
let make = (~className=?, ~children) => {
  let combinedStyles =
    switch (className) {
    | None => Styles.wrapper
    | Some(className) => Css.merge([Styles.wrapper, className])
    };

  <main className=combinedStyles> children </main>;
};

let default = make;