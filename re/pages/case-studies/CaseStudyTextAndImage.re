open Utils.React;

module Styles = {
  open Css;
  open Theme;

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      padding2(~h=`zero, ~v=rem(2.5)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [flexDirection(`rowReverse), padding2(~h=`zero, ~v=rem(6.25))],
      ),
    ]);
  let textWrapper =
    style([
      display(`flex),
      alignItems(`center),
      justifyContent(`center),
      padding2(~h=rem(1.25), ~v=rem(2.5)),
      fontSize(rem(0.875)),
      color(hex(Colors.grey)),
      lineHeight(`abs(2.)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          padding4(
            ~top=rem(1.875),
            ~right=rem(5.625),
            ~bottom=`zero,
            ~left=rem(6.25),
          ),
          flex3(~grow=4., ~shrink=1., ~basis=rem(0.0000001)),
          fontSize(rem(1.)),
        ],
      ),
    ]);
  let text = style([maxWidth(rem(37.5))]);
  let image =
    style([
      media(
        Theme.Breakpoints.tabletLandscape,
        [flex3(~grow=6., ~shrink=1., ~basis=rem(0.0000001))],
      ),
    ]);
};

[@react.component]
let make = (~className=?, ~text: string, ~image: option(Gatsby.fluidImage)=?) => {
  <CaseStudySection
    className=?{combineClassNames([Some(Styles.wrapper), className])}>
    <Gatsby.Image className=Styles.image fluid=?image />
    <div className=Styles.textWrapper>
      <p className=Styles.text> {React.string(text)} </p>
    </div>
  </CaseStudySection>;
};

let default = make;