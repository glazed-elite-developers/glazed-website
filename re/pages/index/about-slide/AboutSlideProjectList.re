module LineProjectElement = {
  module Styles = {
    open Css;
    open Theme;

    let row =
      style([
        paddingLeft(`rem(0.9375)),
        display(`flex),
        flexDirection(row),
        color(hex(Colors.almostWhite)),
        opacity(0.8),
        media(Breakpoints.tabletPortrait, [padding2(~v=rem(0.625), ~h=rem(1.875))]),
        media(Breakpoints.tabletLandscape, [padding2(~v=rem(1.), ~h=rem(1.875))]),
      ]);
    let rowLeft =
      style([
        opacity(0.3),
        fontSize(`rem(0.625)),
        media(Breakpoints.tabletPortrait, [fontSize(rem(0.625))]),
        media(Breakpoints.tabletLandscape, [fontSize(rem(0.75))]),
      ]);
    let rowRight =
      style([
        paddingLeft(rem(0.9375)),
        fontSize(rem(0.75)),
        media(
          Breakpoints.tabletPortrait,
          [paddingLeft(rem(2.0625)), fontSize(rem(1.)), fontWeight(`num(700))],
        ),
        media(
          Breakpoints.tabletLandscape,
          [paddingLeft(rem(2.0625)), fontSize(rem(1.125)), fontWeight(`num(700))],
        ),
      ]);
  };

  [@react.component]
  let make = (~children) => {
    <div className=Styles.row>
      <div className=Styles.rowLeft> {"<li>" |> ReasonReact.string} </div>
      <div className=Styles.rowRight> children </div>
    </div>;
  };
};

let kindsOfProjects = [|
  "Technically complex",
  "Highly customised and detailed",
  "Innovative and using recent technologies",
  "Critically impact on businesses or people's lives",
|];

module Styles = {
  open Css;
  open Theme;

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
      backgroundColor(hex(Colors.glazedBabyBlueText)),
      lineHeight(`rem(1.875)),
      paddingBottom(rem(1.25)),
      media(Breakpoints.tabletPortrait, [paddingBottom(rem(3.75))]),
      media(
        Breakpoints.desktop,
        [
          gridRow(1, 3),
          gridColumn(2, 3),
          alignSelf(`flexEnd),
          height(pct(80.)),
          padding4(~top=`zero, ~right=rem(5.), ~bottom=rem(10.), ~left=`zero),
        ],
      ),
    ]);

  let heading =
    style([
      padding4(~top=`rem(1.25), ~left=`rem(3.5), ~bottom=`rem(0.625), ~right=`zero),
      fontSize(`rem(0.625)),
      color(hex(Colors.almostWhite)),
      opacity(0.3),
      media(
        Breakpoints.tabletPortrait,
        [padding3(~top=`rem(3.75), ~h=rem(5.), ~bottom=`rem(0.625)), fontSize(rem(0.75))],
      ),
      media(
        Breakpoints.tabletLandscape,
        [padding3(~top=rem(5.), ~bottom=rem(4.), ~h=rem(5.)), fontSize(rem(0.8125))],
      ),
    ]);
};

[@react.component]
let make = () => {
  <div className=Styles.wrapper>
    <Heading level=Heading.H6 className=Styles.heading>
      {"Our kind of projects:" |> ReasonReact.string}
    </Heading>
    {React.array(
       Array.mapi(
         (index, element) =>
           <LineProjectElement key={Belt.Int.toString(index)}>
             {ReasonReact.string(element)}
           </LineProjectElement>,
         kindsOfProjects,
       ),
     )}
  </div>;
};
