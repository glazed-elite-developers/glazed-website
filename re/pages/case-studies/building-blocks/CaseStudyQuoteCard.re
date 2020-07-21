open Utils.React;

module Styles = {
  open Css;
  open Theme;

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      padding2(~h=rem(1.875), ~v=rem(3.125)),
      margin2(~h=rem(1.25), ~v=rem(2.5)),
      maxWidth(rem(64.)),
      backgroundColor(hex(Colors.almostAlmostWhite)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          margin2(~h=`auto, ~v=rem(2.5)),
          padding2(~h=rem(9.375), ~v=rem(8.75)),
          flexDirection(`rowReverse),
        ],
      ),
    ]);
  let author =
    style([
      display(`flex),
      flexDirection(`column),
      alignItems(`center),
      paddingTop(rem(0.625)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [alignItems(`flexStart), flex3(~grow=0., ~shrink=1., ~basis=rem(10.))],
      ),
    ]);
  let avatarImage = style([width(rem(3.125)), height(rem(3.125)), borderRadius(pct(50.))]);
  let authorName =
    style([
      padding3(~top=rem(0.625), ~bottom=rem(0.625), ~h=`zero),
      fontSize(rem(0.6875)),
      fontFamily(`custom(Fonts.heading)),
      color(hex(Colors.darkGreyDarker)),
    ]);
  let authorTitle =
    style([fontSize(rem(0.6875)), fontFamily(`custom(Fonts.heading)), color(hex(Colors.grey))]);
  let quote =
    style([
      fontSize(rem(1.)),
      lineHeight(`abs(2.)),
      color(hex(Colors.grey)),
      textAlign(`center),
      paddingBottom(rem(1.875)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          paddingBottom(`zero),
          flex3(~grow=1., ~shrink=1., ~basis=rem(0.00000001)),
          fontSize(rem(1.5)),
          textAlign(`left),
        ],
      ),
    ]);
};

type author = {
  name: string,
  title: string,
  avatarImage: option(Gatsby.fluidImage),
};

[@react.component]
let make = (~className=?, ~author: author, ~quote: string) => {
  <CaseStudySection className=?{combineClassNames([Some(Styles.wrapper), className])}>
    <p className=Styles.quote> {React.string(quote)} </p>
    <div className=Styles.author>
      <Gatsby.Image className=Styles.avatarImage fluid=?{author.avatarImage} />
      <p className=Styles.authorName> {React.string(author.name)} </p>
      <p className=Styles.authorTitle> {React.string(author.title)} </p>
    </div>
  </CaseStudySection>;
};

let default = make;
