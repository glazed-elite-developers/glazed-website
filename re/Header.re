open React;
open Utils.React;

[@bs.module "static/images/logo-glazed.svg"] external logo: SVG.asset = "default";
[@bs.module "static/images/logo-glazed-outline.svg"] external logoOutline: SVG.asset = "default";

module Styles = {
  open Css;

  module Variables = {
    let height = px(117);
  };

  let nav =
    style([
      display(`flex),
      alignItems(`center),
      pointerEvents(`none),
      padding2(~v=rem(1.25), ~h=rem(1.25)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [padding2(~v=rem(2.1875), ~h=rem(4.6875)), height(Variables.height)],
      ),
    ]);
  let logoWrapper =
    style([
      display(`flex),
      flex3(~grow=0., ~shrink=0., ~basis=`auto),
      width(px(122)),
      pointerEvents(`auto),
    ]);
  let logo = style([height(rem(2.1875))]);
  let navBarLinks =
    style([
      display(`none),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.000000001)),
      fontFamily(`custom(Theme.Fonts.heading)),
      fontSize(`rem(0.75)),
      fontWeight(`num(700)),
      lineHeight(`rem(0.875)),
      media(Theme.Breakpoints.tabletLandscape, [display(`flex)]),
    ]);
};

[@react.component]
let make =
  memo(
    (
      ~innerRef=?,
      ~className=?,
      ~style=?,
      ~componentAtTheRight=?,
      ~onNavBarLinkClick: option((ReactEvent.Synthetic.t, string) => unit)=?,
      ~useDarkNavBarLinks: bool=false,
      ~currentPageIndex=0,
      ~onResize=?,
    ) => {
    let logoToUse = useDarkNavBarLinks ? logo : logoOutline;
    let onLogoClick =
      useMemo1(
        () => {
          switch (onNavBarLinkClick) {
          | None => None
          | Some(handler) => Some(event => handler(event, "/#hey"))
          }
        },
        [|onNavBarLinkClick|],
      );

    <ResizeMonitorContainer
      componentTag="nav"
      ?innerRef
      className=?{combineClassNames([Some(Styles.nav), className])}
      ?style
      ?onResize>
      <Gatsby.Link _to="/#hey" className=Styles.logoWrapper onClick=?onLogoClick>
        <SVG className=Styles.logo asset=logoToUse />
      </Gatsby.Link>
      <NavBarLinks
        className=Styles.navBarLinks
        useDarkNavBarLinks
        currentPageIndex
        ?onNavBarLinkClick
      />
      {switch (componentAtTheRight) {
       | None => React.null
       | Some(componentAtTheRight') => componentAtTheRight'
       }}
    </ResizeMonitorContainer>;
  });

let default = make;
