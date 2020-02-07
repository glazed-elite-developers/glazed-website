[@bs.module] external logo: string = "../../../static/images/logo-glazed.svg";
[@bs.module]
external logoOutline: string =
  "../../../static/images/logo-glazed-outline.svg";

module Styles = {
  open Css;

  let header =
    style([
      display(`flex),
      alignItems(`center),
      pointerEvents(`none),
      padding2(~v=rem(2.1875), ~h=rem(4.6875)),
    ]);
  let logoWrapper =
    style([
      flex3(~grow=0., ~shrink=0., ~basis=`auto),
      paddingRight(rem(1.25)),
    ]);
  let logo = style([height(rem(2.1875))]);
};

[@react.component]
let make = (~className, ~useDarkNavBarLinks: bool, ~currentPageIndex) => {
  let logoToUse = useDarkNavBarLinks ? logo : logoOutline;

  <header className={Css.merge([Styles.header, className])}>
    <div className=Styles.logoWrapper>
      <img className=Styles.logo src=logoToUse />
    </div>
    <NavBarLinks useDarkNavBarLinks currentPageIndex />
  </header>;
};

let default = make;