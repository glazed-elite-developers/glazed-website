[@bs.module "static/images/logo-glazed.svg"]
external logo: SVG.asset = "default";
[@bs.module "static/images/logo-glazed-outline.svg"]
external logoOutline: SVG.asset = "default";

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
      display(`flex),
      flex3(~grow=0., ~shrink=0., ~basis=`auto),
      paddingRight(rem(1.25)),
      pointerEvents(`auto),
    ]);
  let logo = style([height(rem(2.1875))]);
  let navBarLinks =
    style([
      display(`none),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.000000001)),
      fontFamily(Theme.Fonts.heading),
      fontSize(`rem(0.75)),
      fontWeight(`num(700)),
      lineHeight(`rem(0.875)),
      media(Theme.Breakpoints.tabletLandscape, [display(`flex)]),
    ]);
  let sayHelloButton =
    style([
      display(`none),
      padding2(~v=`rem(0.875), ~h=`rem(1.75)),
      color(hex(Theme.Colors.almostWhite)),
      fontSize(`rem(0.75)),
      fontFamily(Theme.Fonts.heading),
      pointerEvents(`auto),
      media(Theme.Breakpoints.tabletLandscape, [display(`block)]),
    ]);
};

[@react.component]
let make = (~className, ~useDarkNavBarLinks: bool, ~currentPageIndex) => {
  let logoToUse = useDarkNavBarLinks ? logo : logoOutline;

  <nav className={Css.merge([Styles.nav, className])}>
    <Gatsby.Link _to="/" className=Styles.logoWrapper>
      <SVG className=Styles.logo asset=logoToUse />
    </Gatsby.Link>
    <NavBarLinks
      className=Styles.navBarLinks
      useDarkNavBarLinks
      currentPageIndex
    />
    <Button _type=Button.Secondary className=Styles.sayHelloButton>
      {React.string("> say hello")}
    </Button>
  </nav>;
};

let default = make;