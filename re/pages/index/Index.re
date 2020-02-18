let str = React.string;

module Styles = {
  open Css;

  let wrapper =
    style([
      padding(`zero),
      backgroundColor(hex(Theme.Colors.glazedBlue)),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
      media(Theme.Breakpoints.tabletLandscape, [padding(`zero)]),
    ]);
};

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  <PageContent className=Styles.wrapper>
    <IndexLandingSlide />
    <IndexCaseStudiesSlide />
    <IndexAboutSlide />
  </PageContent>;
};

let default = make;