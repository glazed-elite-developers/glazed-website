type background =
  | BrightBg
  | BlueBg
  | ImageBg;

type buttonType =
  | Primary
  | Secondary
  | Tertiary;

let backgrounds = {"BrightBg": 0, "BlueBg": 1, "ImageBg": 2};

module Styles = {
  open Css;

  let base = style([padding2(~h=rem(3.0), ~v=rem(0.875))]);
  let common = style([border(px(1), `none, `transparent)]);
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
      backgroundColor(hex(Theme.Colors.glazedBlueDarker)),
      // boxShadow(),
      color(hex(Theme.Colors.almostWhite)),
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
      style([
        color(hex(Theme.Colors.almostWhite)),
        border(px(1), `solid, hex(Theme.Colors.almostWhite)),
      ])
    | ImageBg =>
      style([
        color(hex(Theme.Colors.almostWhite)),
        border(px(1), `solid, hex(Theme.Colors.glazedBlueDarker)),
      ])
    };

  let secondary = (bg, isDisabled) =>
    merge([
      style([
        color(hex(Theme.Colors.darkGreyDarker)),
        opacity(isDisabled ? 0.4 : 1.0),
        padding2(~h=rem(3.0), ~v=rem(0.875)),
        border(px(1), `solid, hex(Theme.Colors.glazedBlueDarker)),
        backgroundColor(`transparent),
      ]),
      secondaryForBg(bg),
    ]);

  let tertiary = _isDisabled =>
    style([
      color(hex(Theme.Colors.glazedBabyBlue)),
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
      ~_type: option(buttonType)=?,
      ~bgColor=BrightBg,
      ~isDisabled=false,
      ~className=?,
      ~onClick=?,
    ) => {
  let ownStyles =
    switch (_type) {
    | None => Styles.base
    | Some(unwrappedType) =>
      switch (unwrappedType) {
      | Primary => Styles.primary(isDisabled)
      | Secondary => Styles.secondary(bgColor, isDisabled)
      | Tertiary => Styles.tertiary(isDisabled)
      }
    };
  let onClickHandler =
    switch (onClick) {
    | None => (_ => ())
    | Some(handler) => isDisabled ? (_ => ()) : handler
    };

  <button
    className={Utils.React.combineOptionalStyles(
      ~baseStyles=Css.merge([Styles.common, ownStyles]),
      ~className?,
    )}
    onClick=onClickHandler>
    children
  </button>;
};

let default = make;