open Utils.React;

module Styles = {
  open Css;

  let image =
    style([
      boxShadow(
        Shadow.box(
          ~y=px(50),
          ~blur=px(60),
          rgba(0, 0, 0, 0.1),
        ),
      ),
      media(Theme.Breakpoints.tabletLandscape, [paddingTop(rem(6.875))]),
    ]);
};

[@react.component]
let make =
    (~image: option(Gatsby.fluidImage)=?, ~className=?, ~imageClassName=?) => {
  <CaseStudySection ?className>
    <Gatsby.Image
      className=?{combineClassNames([Some(Styles.image), imageClassName])}
      fluid=?image
    />
  </CaseStudySection>;
};

let default = make;