let str = React.string;
type tags =
  | H1
  | H2
  | P;

module Tag = {
  module Styles = {
    open Css;
    open Theme;

    let h1 = style([color(hex(Colors.glazedBlueLighter))]);
    let h2 =
      style([
        color(hex(Colors.glazedBlueLighter)),
        fontFamily(Fonts.inputSecondary),
        fontSize(rem(0.75)),
        opacity(0.2),
      ]);
    let p = style([color(hex(Colors.glazedBlueLighter))]);
  };

  [@react.component]
  let make = (~tag, ~html) => {
    let className =
      switch (tag) {
      | H1 => Styles.h1
      | H2 => Styles.h2
      | P => Styles.p
      };

    <span className> {html |> str} </span>;
  };
};

module TextStyles = {
  open Css;
  open Theme;

  let h1 = style([]);
  let h2 =
    style([
      color(hex(Colors.glazedBlueDarker)),
      fontFamily(Fonts.primary),
      fontSize(rem(2.25)),
      lineHeight(rem(2.7)),
    ]);
  let p =
    style([
      color(hex(Colors.glazedBlueLighter)),
      fontFamily(Fonts.primary),
      fontSize(rem(0.88)),
      opacity(0.8),
      lineHeight(rem(1.5)),
    ]);
};

[@react.component]
let make = (~tag: tags, ~children) => {
  switch (tag) {
  | H1 =>
    <h1 className=TextStyles.h1>
      <Tag tag=H1 html="<h1>" />
      children
      <Tag tag=H1 html="</h1>" />
    </h1>
  | H2 =>
    <h2 className=TextStyles.h2>
      <Tag tag=H2 html="<h2>" />
      children
      <Tag tag=H2 html="</h2>" />
    </h2>
  | P => <p> <Tag tag=P html="<p>" /> children <Tag tag=P html="</p>" /> </p>
  };
};

let default = make;