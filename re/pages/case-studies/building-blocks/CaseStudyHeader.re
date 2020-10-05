module Styles = {
  open Css;
  open Theme;

  let wrapper =
    style([
      position(`relative),
      overflow(`hidden),
      padding4(~top=rem(7.1875), ~left=rem(1.25), ~bottom=`zero, ~right=`zero),
      media(
        Theme.Breakpoints.tabletLandscape,
        [padding4(~top=rem(14.375), ~left=rem(11.25), ~bottom=`zero, ~right=`zero)],
      ),
    ]);
  let imageContainer =
    style([
      position(`absolute),
      top(`zero),
      left(`zero),
      height(rem(17.5)),
      width(pct(100.)),
      zIndex(0),
      media(Theme.Breakpoints.tabletLandscape, [left(rem(3.125)), height(rem(34.375))]),
    ]);
  let image =
    style([
      height(rem(17.5)),
      media(Theme.Breakpoints.tabletLandscape, [height(rem(34.375))]),
    ]);
  let mask = style([backgroundColor(rgba(150, 150, 150, 0.))]);
  let titleCard =
    style([
      position(`relative),
      display(`flex),
      flexDirection(`column),
      width(rem(14.375)),
      height(rem(14.375)),
      padding(rem(1.875)),
      color(hex(Colors.white)),
      backgroundColor(hex(Colors.glazedBabyBlueText)),
      zIndex(0),
      media(
        Theme.Breakpoints.tabletPortrait,
        [
          justifyContent(`flexEnd),
          width(rem(17.5)),
          height(rem(17.5)),
        ],
      ),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          padding2(~h=rem(2.5), ~v=rem(2.5)),
          width(rem(21.875)),
          height(rem(21.875)),
        ],
      ),
      media(
        Theme.Breakpoints.desktop,
        [
          padding2(~h=rem(2.5), ~v=rem(5.)),
          width(rem(25.625)),
          height(rem(25.625)),
        ],
      ),
    ]);
  let heading =
    style([
      fontSize(rem(1.5)),
      lineHeight(`abs(1.25)),
      media(Theme.Breakpoints.desktop, [fontSize(rem(3.)), lineHeight(`abs(1.25))]),
    ]);
  let area =
    style([
      padding4(~top=rem(0.9375), ~left=`zero, ~bottom=rem(0.625), ~right=`zero),
      color(hex(Colors.almostWhite)),
      fontSize(rem(0.75)),
      opacity(0.3),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          padding4(~top=rem(1.875), ~left=`zero, ~bottom=rem(1.25), ~right=`zero),
          fontSize(rem(0.875)),
        ],
      ),
    ]);
  let text =
    style([
      color(hex(Colors.almostWhite)),
      fontSize(rem(0.75)),
      opacity(0.7),
      lineHeight(`abs(2.)),
      media(Theme.Breakpoints.tabletLandscape, [fontSize(rem(1.))]),
    ]);
};

[@react.component]
let make = (~image: option(Gatsby.fluidImage)=?, ~title: string, ~area: string, ~text: string) => {
  <div className=Styles.wrapper>
    <MaskContainer className=Styles.imageContainer maskClassName=Styles.mask>
      <Gatsby.Image className=Styles.image fluid=?image loading="eager" />
    </MaskContainer>
    <div className=Styles.titleCard>
      <Heading level=Heading.H1 className=Styles.heading> {React.string(title)} </Heading>
      <p className=Styles.area> {React.string(area)} </p>
      <p className=Styles.text> {React.string(text)} </p>
    </div>
  </div>;
};

let default = make;
