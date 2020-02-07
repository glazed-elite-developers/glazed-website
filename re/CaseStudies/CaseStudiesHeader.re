module Styles = {
  open Css;

  let header =
    style([
      height(rem(100.)),
      backgroundColor(hex("BBCCDD"))
    ]);
};

[@react.component]
let make = (~image: unit) => {

  <header>
    <GatsbyImage fluid=image />
  </header>;
};

let default = make;