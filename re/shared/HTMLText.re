let str = React.string;
type tags =
  | H1
  | H2
  | P;

let tags = {"h1": 0, "h2": 1, "p": 2};

module Tag = {
  module Styles = {
    open Css;
    open Theme;

    let h1 = style([position(`absolute), color(hex(Colors.glazedBlueLighter))]);

    let h2 =
      style([
        position(`absolute),
        color(hex(Colors.glazedBlueLighter)),
        fontFamily(Fonts.text),
        fontWeight(`num(700)),
        fontSize(rem(0.75)),
        opacity(0.2),
      ]);

    let p = style([position(`absolute), color(hex(Colors.glazedBlueLighter))]);
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

  let h1 = style([position(`relative)]);

  let h2 =
    style([
      position(`relative),
      color(hex(Colors.glazedBlueDarkerish)),
      fontFamily(Fonts.heading),
      fontSize(rem(2.25)),
      lineHeight(rem(2.7)),
    ]);

  let p =
    style([
      position(`relative),
      color(hex(Colors.glazedBlueLighter)),
      fontFamily(Fonts.heading),
      fontSize(rem(0.88)),
      opacity(0.8),
      lineHeight(rem(1.5)),
    ]);
};

module TextContent = {
  [@react.component]
  let make = (~children, ~inline=?) => {
    let className =
      switch (inline) {
      | None => Css.(style([paddingLeft(rem(1.56)), display(`inlineBlock)]))
      | Some () => Css.(style([paddingLeft(rem(1.56))]))
      };

    <span className> children </span>;
  };
};

[@react.component]
let make = (~tag: tags, ~className, ~children) => {
  switch (tag) {
  | H1 =>
    <h1 className={Css.merge([TextStyles.h1, className])}>
      <Tag tag=H1 html="<h1>" />
      <TextContent> children </TextContent>
      <Tag tag=H1 html="</h1>" />
    </h1>
  | H2 =>
    <h2 className={Css.merge([TextStyles.h2, className])}>
      <Tag tag=H2 html="<h2>" />
      <TextContent> children <Tag tag=H2 html="</h2>" /> </TextContent>
    </h2>
  | P =>
    <p className>
      <Tag tag=P html="<p> " />
      <TextContent inline=()> children </TextContent>
      <Tag tag=P html=" </p>" />
    </p>
  };
};

let default = make;
