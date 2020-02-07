[@bs.module] external logo: string = "../../../static/images/logo-glazed.svg";
[@bs.module]
external logoOutline: string =
  "../../../static/images/logo-glazed-outline.svg";

module Styles = {
  open Css;

  let nav =
    style([
      display(`flex),
      alignItems(`center),
      pointerEvents(`none),
      padding2(~v=rem(1.25), ~h=rem(1.25)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [padding2(~v=rem(2.1875), ~h=rem(4.6875))],
      ),
    ]);
  let logoWrapper =
    style([
      flex3(~grow=0., ~shrink=0., ~basis=`auto),
      paddingRight(rem(1.25)),
    ]);
  let logo = style([height(rem(2.1875))]);
  let navBarLinks =
    style([
      display(`none),
      media(
        Theme.Breakpoints.tabletLandscape,
        [display(`flex)],
      ),
    ]);
};

[@react.component]
let make = (~className, ~useDarkNavBarLinks: bool, ~currentPageIndex) => {
  let logoToUse = useDarkNavBarLinks ? logo : logoOutline;

  <nav className={Css.merge([Styles.nav, className])}>
    <div className=Styles.logoWrapper>
      <img className=Styles.logo src=logoToUse />
    </div>
    <NavBarLinks
      className=Styles.navBarLinks
      useDarkNavBarLinks
      currentPageIndex
    />
  </nav>;
};

let default = make;