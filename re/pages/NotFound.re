module Styles = {
  open Css;
  open Theme;

  let content =
    style([
      position(`relative),
      padding4(~top=rem(4.1875), ~bottom=rem(8.1875), ~left=rem(1.25), ~right=rem(1.25)),
      display(`flex),
      flexDirection(`column),
      justifyContent(`flexEnd),
      flex3(~grow=1., ~shrink=0., ~basis=`auto),
      backgroundColor(hex(Colors.almostAlmostWhite)),
      media(
        Breakpoints.tabletLandscape,
        [
          justifyContent(`flexStart),
          padding4(~top=rem(12.25), ~bottom=rem(6.25), ~left=rem(4.75), ~right=rem(2.5)),
        ],
      ),
    ]);
  let heading =
    style([
      position(`relative),
      padding4(~top=`rem(1.875), ~left=`rem(0.9375), ~bottom=`rem(5.625), ~right=`zero),
      fontSize(`rem(4.125)),
      color(hex(Colors.glazedBabyBlueText)),
      before([
        contentRule(""),
        display(`block),
        position(`absolute),
        top(`px(0)),
        left(`px(0)),
        width(px(130)),
        height(px(130)),
        border(px(1), `solid, hex(Colors.glazedBabyBlueDarker)),
        opacity(0.1),
        media(Breakpoints.tabletLandscape, [width(`px(258)), height(`px(258))]),
      ]),
      media(
        Breakpoints.tabletLandscape,
        [
          padding4(~top=`rem(5.625), ~left=`rem(0.9375), ~bottom=`rem(6.875), ~right=`zero),
          width(`auto),
          fontSize(rem(9.)),
        ],
      ),
    ]);
  let descriptions =
    style([
      display(`flex),
      flexDirection(`column),
      padding4(~left=rem(0.9375), ~right=rem(3.125), ~top=`zero, ~bottom=`zero),
      media(Theme.Breakpoints.tabletLandscape, [maxWidth(rem(37.5))]),
    ]);
  let shortDescription =
    style([
      lineHeight(`abs(2.)),
      fontSize(rem(0.875)),
      fontFamily(Theme.Fonts.text),
      color(hex(Colors.grey)),
      paddingBottom(rem(0.625)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          order(2),
          flex3(~grow=1., ~shrink=0., ~basis=`auto),
          display(`flex),
          alignItems(`center),
          justifyContent(`flexEnd),
          paddingLeft(rem(6.25)),
          fontSize(rem(2.)),
          lineHeight(`abs(1.5)),
        ],
      ),
    ]);
};

[@react.component]
let make = () => {
  <Layout>
    <PageLayout className=Styles.content useDarkNavBarLinks=true>
      <Heading level=Heading.H1 className=Styles.heading> {React.string("404")} </Heading>
      <div className=Styles.descriptions>
        <Heading level=Heading.H3 className=Styles.shortDescription>
          {React.string({j|You just hit a route that doesn't exist... The sadness.|j})}
        </Heading>
      </div>
    </PageLayout>
  </Layout>;
};

let default = make;
