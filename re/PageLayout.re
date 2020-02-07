module Styles = {
  open Css;

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      position(`relative),
      height(pct(100.)),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
    ]);
  let header = style([position(`absolute), top(`zero)]);
};

[@react.component]
let make = (~children, ~useDarkNavBarLinks) => {
  <div className=Styles.wrapper>
    <Header className=Styles.header useDarkNavBarLinks currentPageIndex=0 />
    children
    <MobileFooter useDarkNavBarLinks currentPageIndex=0 />
  </div>;
};

let default = make;