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
  let header = style([position(`fixed), top(`zero), right(`zero), left(`zero)]);
};

[@react.component]
let make = (~children, ~useDarkNavBarLinks=false, ~currentPageIndex=0) => {
  <div className=Styles.wrapper>
    children
    <Header className=Styles.header useDarkNavBarLinks currentPageIndex />
    <MobileFooter currentPageIndex />
  </div>;
};

let default = make;