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

  let quote= 
    style([
      marginTop(rem(5.)),
      media(
      Theme.Breakpoints.tabletLandscape,[
        maxWidth(rem(70.)),
        marginTop(rem(20.)),
        marginBottom(rem(5.)),
      ])
  ]);

    let contactFormWrapper = 
      style([
        backgroundColor(hex(Theme.Colors.glazedBlueMidnight)),
        marginBottom(rem(3.0)),
        padding(rem(1.0)),
      ]);
};

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  <PageContent className=Styles.wrapper>
    <FullPageSlide backgroundImageUrl="/images/home/slide-1-background.jpg">
      <Quote
        className=Styles.quote
        quote={"\"Bacon ipsum dolor amet bresaola swine pancetta buffalo tri-tip. Shank bresaola turkey pork belly ball tip. Bresaola brisket frankfurter, kevin buffalo bacon sausage porchetta doner hamburger short ribs. Tri-tip sirloin pork belly tongue ribeye.\""}
        imageSrc={"/images/iwilsonq.jpg"}
        name={j|Tony Barracuda|j}
        position={"CEO SweeNuus"}
        />
      <div className=Styles.socialNetworks>
        <SocialIconDark icon=SocialIconDark.Twitter />
        <SocialIconDark icon=SocialIconDark.Facebook />
        <SocialIconDark icon=SocialIconDark.Linkedin />
        <SocialIconDark icon=SocialIconDark.Github />
      </div>
      <div className=Styles.contactFormWrapper>
        <ContactForm />
      </div>
    </FullPageSlide>
  </PageContent>;
};

let default = make;