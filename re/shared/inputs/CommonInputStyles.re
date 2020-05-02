open Css;
open Theme;

let wrapper = style([display(`flex), flexDirection(`column)]);
let labelWrapper =
  style([
    display(`flex),
    alignItems(`center),
    justifyContent(`spaceBetween),
  ]);
let label =
  style([
    color(hex("9FA8B3")),
    fontSize(rem(0.625)),
    fontWeight(`num(700)),
    lineHeight(px(23)),
  ]);
let labelInner = style([color(hex("000"))]);
let error =
  style([
    fontSize(rem(0.6875)),
    fontFamily(Theme.Fonts.heading),
    color(hex(Colors.orange)),
    opacity(0.),
    visibility(`hidden),
    transitions([
      Transition.shorthand(~duration=0, ~delay=500, "visibility"),
      Transition.shorthand(~duration=500, "opacity"),
    ]),
  ]);
let errorVisible =
  style([
    opacity(1.),
    visibility(`visible),
    transitions([Transition.shorthand(~duration=100, "opacity")]),
  ]);
let input =
  style([
    backgroundColor(hex("F4F6FB")),
    transition(~duration=300, "borderWidth"),
    borderWidth(px(0)),
    color(hex("9FA8B3")),
    display(`block),
    fontFamily(Theme.Fonts.heading),
    fontSize(rem(0.69)),
    lineHeight(rem(1.44)),
    marginTop(rem(0.625)),
    padding2(~h=rem(1.25), ~v=rem(0.93)),
    fontSize(rem(0.93)),
    borderBottomWidth(px(1)),
    borderColor(`transparent),
    resize(`none),
    hover([borderColor(hex("2962F6")), borderBottomWidth(px(1))]),
  ]);