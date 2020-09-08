module Styles = {
  open Css;

  let wrapper = style([boxShadow(Shadow.box(~y=px(50), ~blur=px(60), rgba(0, 0, 0, 0.1)))]);
  let content = style([width(pct(100.)), height(pct(100.))]);
};

[@react.component]
let make = (~src: string, ~className=?) => {
  <CaseStudySection ?className>
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
