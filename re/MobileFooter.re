open Utils.React;

module Styles = {
  open Css;
  open Theme;

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
  let navBarLinksWrapper =
    style([
      position(`relative),
      overflow(`hidden),
      flex3(~grow=1., ~shrink=1., ~basis=`auto),
      after([
        contentRule(""),
        position(`absolute),
        top(`zero),
        right(`zero),
        bottom(`zero),
        left(`zero),
        boxShadow(
          Shadow.box(
            ~inset=true,
            ~blur=px(10),
            ~spread=px(10),
            hex(Colors.glazedBlueMidnight),
          ),
        ),
        pointerEvents(`none),
      ]),
    ]);
  let navBarLinksScrollerContent =
    style([flexDirection(`row), fontFamily(Theme.Fonts.heading), fontSize(rem(0.625))]);
  let navBarLinks =
    style([
      display(`flex),
      alignItems(`center),
      padding2(~v=rem(0.), ~h=rem(0.625)),
      height(Variables.height),
      opacity(0.8),
    ]);
};

[@react.component]
let make = (~className=?, ~navBarLinksClassName=?, ~currentPageIndex=0, ~componentAtTheRight=?) => {
  <MobileFooterLayout className=?{combineClassNames([Some(Styles.wrapper), className])}>
    <div className=Styles.navBarLinksWrapper>
      <ScrollContainer contentClassName=Styles.navBarLinksScrollerContent>
        <NavBarLinks
          className=?{combineClassNames([Some(Styles.navBarLinks), navBarLinksClassName])}
          currentPageIndex
        />
      </ScrollContainer>
    </div>
    {switch (componentAtTheRight) {
     | None => React.null
     | Some(componentAtTheRight') => componentAtTheRight'
     }}
  </MobileFooterLayout>;
};

let default = make;
