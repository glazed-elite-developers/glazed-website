open Utils.React;

module Styles = {
  open Css;

  module Variables = {
    let height = rem(3.75);
  };

  let wrapper =
    style([
      position(`fixed),
      bottom(`zero),
      left(`zero),
      right(`zero),
      display(`flex),
      alignItems(`center),
      whiteSpace(`nowrap),
      media(Theme.Breakpoints.tabletLandscape, [display(`none)]),
    ]);
  let navBarLinks =
    style([
      display(`flex),
      alignItems(`center),
      height(Variables.height),
      padding4(
        ~top=rem(0.),
        ~bottom=rem(0.),
        ~left=rem(1.),
        ~right=rem(0.),
      ),
      fontFamily(Theme.Fonts.heading),
      fontSize(rem(0.625)),
      opacity(0.8),
    ]);
};

[@react.component]
let make =
    (
      ~className=?,
      ~navBarLinksClassName=?,
      ~currentPageIndex=0,
      ~componentAtTheRight=?,
    ) => {
  <MobileFooterLayout
    className=?{combineClassNames([Some(Styles.wrapper), className])}>
    <NavBarLinks
      className=?{
        combineClassNames([Some(Styles.navBarLinks), navBarLinksClassName])
      }
      currentPageIndex
    />
    {switch (componentAtTheRight) {
     | None => React.null
     | Some(componentAtTheRight') => componentAtTheRight'
     }}
  </MobileFooterLayout>;
};

let default = make;