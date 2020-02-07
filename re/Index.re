let str = React.string;

module Styles = {
  open Css;

  let wrapper =
    style([
      backgroundColor(hex(Theme.Colors.glazedBlue)),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
    ]);
};

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  <PageContent className=Styles.wrapper>
    <ColorSamples />
    // <div className=Styles.socialNetworks></div>
    <SocialIconDark icon=SocialIconDark.Twitter />
    <SocialIconDark icon=SocialIconDark.Facebook />
    <SocialIconDark icon=SocialIconDark.Linkedin />
    <SocialIconDark icon=SocialIconDark.Github />
  </PageContent>;
};

let default = make;