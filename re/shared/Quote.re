[@bs.module] external image: string = "assets/examples/bunny.jpg";

let str = React.string;

module Styles = {
  open Css;

  let wrapper =
    style([
      display(`flex),
      backgroundColor(hex("FAFBFF")),
      margin2(~h=rem(1.), ~v=rem(0.)),
      flex3(~grow=1., ~shrink=0., ~basis=pct(33.)),
      flexDirection(`column),
      justifyContent(`center),
      alignItems(`center),
      media(
        Theme.Breakpoints.tabletLandscape,
        [flexDirection(`row), maxWidth(rem(64.0)), margin(`auto)],
      ),
    ]);

  let quote =
    style([
      order(1),
      margin3(~h=rem(3.75), ~bottom=rem(1.12), ~top=rem(3.125)),
      fontFamily(Theme.Fonts.text),
      fontSize(rem(1.)),
      color(hex("9FA8B3")),
      fontWeight(`num(400)),
      letterSpacing(rem(0.03)),
      lineHeight(rem(2.125)),
      textAlign(`center),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          order(2),
          fontSize(rem(1.5)),
          lineHeight(rem(3.125)),
          margin4(~top=rem(10.), ~right=rem(9.625), ~bottom=rem(8.8125), ~left=rem(0.)),
        ],
      ),
    ]);

  let img = style([width(px(50)), height(px(50)), borderRadius(px(25))]);

  let quoter =
    style([
      display(`flex),
      order(2),
      flexDirection(`column),
      justifyContent(`center),
      alignItems(`center),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          order(1),
          flex3(~grow=1.0, ~shrink=0.0, ~basis=`percent(15.)),
          alignItems(`flexStart),
          marginLeft(rem(9.625)),
        ],
      ),
    ]);

  let name =
    style([
      fontSize(rem(0.6875)),
      fontWeight(`num(700)),
      color(hex("26313D")),
      marginTop(rem(1.)),
    ]);

  let position =
    style([
      fontSize(rem(0.6875)),
      fontWeight(`num(700)),
      color(hex("9FA8B3")),
      marginTop(rem(0.6)),
      marginBottom(rem(1.875)),
    ]);
};

[@react.component]
let make = (~className=?, ~quote, ~imageSrc, ~name, ~position) => {
  <div className=?{Utils.React.combineClassNames([Some(Styles.wrapper), className])}>
    <p className=Styles.quote> {quote |> str} </p>
    <div className=Styles.quoter>
      <img src=imageSrc className=Styles.img />
      <p className=Styles.name> {name |> str} </p>
      <p className=Styles.position> {position |> str} </p>
    </div>
  </div>;
};

let default = make;
