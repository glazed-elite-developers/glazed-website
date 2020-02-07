type background =
  | BrightBg
  | BlueBg
  | ImageBg;

let backgrounds = {"BrightBg": 0, "BlueBg": 1, "ImageBg": 2};

module Styles = {
  open Css;

  let base = style([padding2(~h=rem(3.0), ~v=rem(0.875))]);

  let primary = isDisabled =>
    style([
      opacity(isDisabled ? 0.4 : 1.0),
      transition(~duration=300, "box-shadow"),
      hover([
        boxShadow(
          Shadow.box(
            ~y=px(20),
            ~blur=px(20),
            // ~x=px(0),
            // ~spread=px(0),
            // ~inset=false,
            rgba(0, 0, 0, 0.24),
          ),
        ),
        // boxShadow(0 20px 20px 0 rgba(0, 0, 0, 0.24);
      ]),
      backgroundColor(hex("2962F6")),
      // boxShadow(),
      color(hex("FFFFFF")),
      fontFamily(Theme.Fonts.heading),
      fontSize(rem(0.75)),
      lineHeight(rem(0.75)),
      // letterSpacing: 0.2px;
      padding2(~h=rem(3.0), ~v=rem(0.875)),
    ]);

  let secondaryForBg = bg =>
    switch (bg) {
    | BrightBg => style([])
    | BlueBg =>
      style([color(hex("FEFFFE")), border(px(1), `solid, hex("FFFFFF"))])
    | ImageBg =>
      style([color(hex("FEFFFE")), border(px(1), `solid, hex("2962F6"))])
    };

  let secondary = (bg, isDisabled) =>
    merge([
      style([
        color(hex("26313D")),
        opacity(isDisabled ? 0.4 : 1.0),
        padding2(~h=rem(3.0), ~v=rem(0.875)),
        // border: 1px solid #2962F6
        border(px(1), `solid, hex("2962F6")),
        backgroundColor(`transparent)
      ]),
      secondaryForBg(bg),
    ]);

  let tertiary = isDisabled =>
    style([
      color(hex("53D3FF")),
      borderWidth(px(0)),
      // opacity(0.1),
      fontFamily(Theme.Fonts.heading),
      fontSize(rem(0.75)),
      lineHeight(rem(1.5)),
      textAlign(`left),
      padding2(~h=rem(3.0), ~v=rem(0.875)),
    ]);
};

[@react.component]
let make =
    (
      ~children,
      ~isPrimary=false,
      ~isSecondary=false,
      ~isTertiary=false,
      ~bgColor=BrightBg,
      ~isDisabled=false,
      ~onClick,
    ) => {
  let className =
    isPrimary
      ? Styles.primary(isDisabled)
      : isTertiary
          ? Styles.tertiary(isDisabled)
          : isSecondary ? Styles.secondary(bgColor, isDisabled) : Styles.base;

  <button className onClick={isDisabled ? _ => () : onClick}>
    children
  </button>;
};

let default = make;