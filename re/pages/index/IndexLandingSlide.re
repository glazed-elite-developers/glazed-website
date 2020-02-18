module Styles = {
  open Css;

  let wrapper =
    style([
      padding2(~h=rem(2.0625), ~v=rem(8.0625)),
      display(`flex),
      flexDirection(`column),
      justifyContent(`center),
      alignItems(`center),
      position(`relative),
    ]);
  let content =
    style([
      display(`flex),
      flexDirection(`column),
      width(pct(100.)),
      media(Theme.Breakpoints.tabletLandscape, [maxWidth(rem(44.))]),
    ]);
  let htmlText =
    style([
      color(hex(Theme.Colors.white)),
      fontSize(rem(0.85)),
      lineHeight(rem(1.5)),
      maxWidth(rem(14.)),
      alignSelf(`flexEnd),
      paddingRight(rem(0.75)),
      opacity(0.8),
    ]);
  let socialNetworks =
    style([
      display(`none),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          display(`flex),
          position(`absolute),
          padding(rem(4.375)),
          bottom(`zero),
          left(`zero),
          margin2(~h=`zero, ~v=rem(-0.9375)),
        ],
      ),
    ]);
  let socialIcon = style([margin(rem(0.9375))]);
  let mainHeading =
    style([
      display(`flex),
      flexDirection(`column),
      fontSize(rem(1.5)),
      lineHeight(rem(2.125)),
      color(hex(Theme.Colors.white)),
      maxWidth(rem(12.1875)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          fontSize(rem(2.25)),
          lineHeight(rem(2.75)),
          maxWidth(rem(24.)),
        ],
      ),
    ]);
  let commentedText =
    style([
      opacity(0.5),
      fontSize(rem(0.75)),
      media(Theme.Breakpoints.tabletLandscape, [fontSize(rem(0.875))]),
    ]);
  let exploreCasesButton =
    style([
      margin3(~top=rem(0.625), ~h=`zero, ~bottom=rem(0.75)),
      alignSelf(`flexStart),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          height(rem(3.125)),
          margin3(~top=rem(0.93755), ~h=`zero, ~bottom=rem(0.75)),
        ],
      ),
    ]);

  let quote =
    style([
      marginTop(rem(5.)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          maxWidth(rem(70.)),
          marginTop(rem(20.)),
          marginBottom(rem(5.)),
        ],
      ),
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
  <FullPageSlide
    className=Styles.wrapper
    backgroundImageUrl="/images/home/slide-1-background.jpg">
    <div className=Styles.content>
      <Heading level=Heading.H1 className=Styles.mainHeading>
        <span className=Styles.commentedText>
          {React.string("// Some projects")}
        </span>
        {React.string("require elite mobile and web developers")}
      </Heading>
      <Gatsby.Link className="" _to="case-studies">
        <Button isPrimary=true className=Styles.exploreCasesButton>
          {React.string("> explore cases")}
        </Button>
      </Gatsby.Link>
      <HTMLText tag=HTMLText.P className=Styles.htmlText>
        {React.string(
           "a team of highly specialized developers that takes on the most demanding web and mobile development projects",
         )}
      </HTMLText>
    </div>
    <div className=Styles.socialNetworks>
      <SocialIconDark
        className=Styles.socialIcon
        icon=SocialIconDark.Twitter
      />
      <SocialIconDark
        className=Styles.socialIcon
        icon=SocialIconDark.Facebook
      />
      <SocialIconDark
        className=Styles.socialIcon
        icon=SocialIconDark.Linkedin
      />
      <SocialIconDark className=Styles.socialIcon icon=SocialIconDark.Github />
    </div>
  </FullPageSlide>;
};

let default = make;