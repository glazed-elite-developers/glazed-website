module Styles = {
  open Css;

  let wrapper =
    style([
      height(pct(100.)),
      padding3(~top=rem(6.25), ~h=rem(4.75), ~bottom=`zero)
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