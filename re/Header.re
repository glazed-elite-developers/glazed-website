[@bs.module]
external logo: string = "../../../static/images/logo-glazed-outline.svg";

module Styles = {
  open Css;

  let header =
    style([
      display(`flex),
      alignItems(`center),
      pointerEvents(`none),
      padding2(~v=rem(2.1875), ~h=rem(4.6875)),
    ]);
  let logoWrapper = style([flex3(~grow=0., ~shrink=0., ~basis=`auto), paddingRight(rem(1.25))]);
};

[@react.component]
// let make = (~siteTitle) => {
  // <header className=Styles.header>
  //   <div className=Styles.content>
  //     <h1 className=Styles.h1>
  //       <SocialIconBright icon=SocialIconBright.Twitter />
  //       <SocialIconBright icon=SocialIconBright.Facebook />
  //       <SocialIconBright icon=SocialIconBright.Linkedin />
  //       <SocialIconBright icon=SocialIconBright.Github />
  //       <ComponentFromJS startAt={10} message="Yolo" />
  //       <Gatsby.Link _to="/" className=Styles.link>
  //         {siteTitle |> ReasonReact.string}
  //       </Gatsby.Link>
  //     </h1>
  //     <nav className=Styles.nav>
  //       <Gatsby.Link _to="/blog" className=Styles.link>
  //         {"Blog" |> ReasonReact.string}
  //       </Gatsby.Link>
  //     </nav>
  //   </div>
let make = (~className, ~useDarkNavBarLinks: bool) => {
  <header className={Css.merge([Styles.header, className])}>
    <div className=Styles.logoWrapper> <img src=logo /> </div>
    <NavBarLinks useDarkNavBarLinks />
  </header>;
};

let default = make;