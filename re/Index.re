let str = React.string;

module Styles = {
  open Css;

  let wrapper =
    style([
      padding(`zero),
      backgroundColor(hex(Theme.Colors.glazedBlue)),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
      media(Theme.Breakpoints.tabletLandscape, [padding(`zero)]),
    ]);
  let socialNetworks =
    style([
      display(`none),
      media(Theme.Breakpoints.tabletLandscape, [display(`flex)]),
    ]);
};

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  <PageContent className=Styles.wrapper>
    <FullPageSlide backgroundImageUrl="/images/home/slide-1-background.jpg">
      <ColorSamples />
      <div className=Styles.socialNetworks>
        <SocialIconDark icon=SocialIconDark.Twitter />
        <SocialIconDark icon=SocialIconDark.Facebook />
        <SocialIconDark icon=SocialIconDark.Linkedin />
        <SocialIconDark icon=SocialIconDark.Github />
      </div>
    </FullPageSlide>
  </PageContent>;
};

let default = make;