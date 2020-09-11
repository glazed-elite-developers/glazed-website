open Utils.React;

module Styles = {
  open Css;

  let section =
    style([
      padding2(~h=`zero, ~v=rem(2.5)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [padding3(~h=rem(11.25), ~top=rem(6.875), ~bottom=rem(5.))],
      ),
    ]);
  let wrapper = style([boxShadow(Shadow.box(~y=px(50), ~blur=px(60), rgba(0, 0, 0, 0.1)))]);
  let content = style([width(pct(100.)), height(pct(100.))]);
};

[@react.component]
let make = (~src: string, ~className=?) => {
  <CaseStudySection className=?{combineClassNames([Some(Styles.section), className])}>
    <FixedRatioContainer
      className=Styles.wrapper
      contentClassName=Styles.content
      width=16
      height=9
      stretchDirection=FixedRatioContainer.Horizontal>
      <iframe src width="100%" height="100%" />
    </FixedRatioContainer>
  </CaseStudySection>;
};

let default = make;
