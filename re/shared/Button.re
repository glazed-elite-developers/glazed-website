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
  let common = style([border(px(1), `none, `transparent), background(`none)]);
  let primary = isDisabled =>
    style([
      opacity(isDisabled ? 0.4 : 1.0),
      transition(~duration=1000, "box-shadow"),
      backgroundColor(hex(Theme.Colors.glazedBlueDarkerish)),
      color(hex(Theme.Colors.almostWhite)),
      fontFamily(Theme.Fonts.heading),
      fontSize(rem(0.75)),
      lineHeight(rem(0.75)),
      padding2(~h=rem(3.0), ~v=rem(0.875)),
      ...!isDisabled
           ? [
             hover([
               boxShadow(Shadow.box(~y=px(10), ~blur=px(20), rgba(0, 0, 0, 0.15))),
               transition(~duration=1000, "box-shadow"),
             ]),
           ]
           : [],
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
        border(px(1), `solid, hex(Theme.Colors.glazedBlueDarkerish)),
      ])
    };

  let secondary = (bg, isDisabled) =>
    merge([
      style([
        color(hex(Theme.Colors.darkGreyDarker)),
        opacity(isDisabled ? 0.4 : 1.0),
        padding2(~h=rem(3.0), ~v=rem(0.875)),
        border(px(1), `solid, hex(Theme.Colors.glazedBlueDarkerish)),
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
      ~type_=?,
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
    className=?{
      Utils.React.combineClassNames([Some(Css.merge([Styles.common, ownStyles])), className])
    }
    onClick=onClickHandler
    ?type_>
    children
  </button>;
};

let default = make;
