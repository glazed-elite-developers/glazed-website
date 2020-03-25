module Styles = {
  open Css;

  module Variables = {
    let height = rem(3.75);
  }

  let wrapper =
    style([
      position(`fixed),
      bottom(`zero),
      left(`zero),
      right(`zero),
      backgroundColor(hex(Theme.Colors.glazedBlueMidnight)),
      media(Theme.Breakpoints.tabletLandscape, [display(`none)]),
    ]);
  let navBarLinks =
    style([
      display(`flex),
      alignItems(`center),
      height(Variables.height),
      padding2(~v=rem(0.), ~h=rem(1.)),
      fontFamily(Theme.Fonts.heading),
      fontSize(rem(0.75)),
      opacity(0.8),
    ]);
};

[@react.component]
let make = (~useDarkNavBarLinks: bool, ~currentPageIndex) => {
  <footer className=Styles.wrapper>
    <NavBarLinks
      className=Styles.navBarLinks
      useDarkNavBarLinks
      currentPageIndex
    />
  </footer>;
};

let default = make;