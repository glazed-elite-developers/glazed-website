[@bs.module "static/images/icon_back_arrow.svg"] external backArrowIcon: SVG.asset = "default";

module Styles = {
  open Css;
  open Theme;

  let wrapper =
    style([
      position(`relative),
      paddingTop(rem(4.0625)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [padding3(~top=rem(3.75), ~bottom=`zero, ~h=rem(5.625))],
      ),
    ]);
  let imageContainer =
    style([
      height(rem(17.5)),
      media(Theme.Breakpoints.tabletLandscape, [height(rem(34.375))]),
    ]);
  let image =
    style([
      height(rem(17.5)),
      media(Theme.Breakpoints.tabletLandscape, [height(rem(34.375))]),
    ]);
  let mask = style([backgroundColor(rgba(150, 150, 150, 0.))]);
  let nextProjectCard =
    style([
      position(`absolute),
      display(`flex),
      flexDirection(`column),
      top(`zero),
      left(rem(1.25)),
      width(rem(14.375)),
      height(rem(14.375)),
      padding(rem(1.875)),
      color(hex(Colors.white)),
      backgroundColor(hex(Colors.glazedBabyBlueText)),
      zIndex(0),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          left(rem(11.25)),
          padding2(~h=rem(2.5), ~v=rem(5.)),
          height(rem(20.625)),
          width(rem(25.625)),
          height(rem(25.625)),
        ],
      ),
    ]);
  let nextProjectLabel =
    style([
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.000000001)),
      fontSize(rem(0.625)),
      color(hex(Colors.almostWhite)),
      opacity(0.5),
    ]);
  let heading =
    style([
      fontSize(rem(1.5)),
      media(Theme.Breakpoints.tabletLandscape, [fontSize(rem(3.))]),
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
  let nextButtonWraper =
    style([
      color(hex(Colors.almostWhite)),
      fontSize(rem(0.75)),
      opacity(0.7),
      lineHeight(`abs(2.)),
      media(Theme.Breakpoints.tabletLandscape, [fontSize(rem(1.))]),
    ]);
  let nextButton =
    style([
      padding3(~h=`zero, ~bottom=rem(1.875), ~top=`zero),
      transform(rotate(deg(180.))),
      Css.SVG.fill(hex(Colors.white)),
      Css.SVG.stroke(hex(Colors.white)),
    ]);
};

module ArrowButton = {
  [@react.component]
  let make = (~link) => {
    <Gatsby.Link className=Styles.nextButtonWraper _to=link>
      <Button className=Styles.nextButton> <SVG asset=backArrowIcon height="12" /> </Button>
    </Gatsby.Link>;
  };
};

[@react.component]
let make = (~image: option(Gatsby.fluidImage)=?, ~title: string, ~area: string, ~link: string) => {
  <div className=Styles.wrapper>
    <MaskContainer className=Styles.imageContainer maskClassName=Styles.mask>
      <Gatsby.Image className=Styles.image fluid=?image />
    </MaskContainer>
    <div className=Styles.nextProjectCard>
      <Heading level=Heading.H6 className=Styles.nextProjectLabel>
        {React.string(title)}
      </Heading>
      <Heading level=Heading.H1 className=Styles.heading> {React.string(title)} </Heading>
      <p className=Styles.area> {React.string(area)} </p>
      <ArrowButton link />
    </div>
  </div>;
};

let default = make;
