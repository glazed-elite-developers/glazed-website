// Tech icons.
[@bs.module "static/images/icon_angular_shield.svg"]
external angularIcon: SVG.asset = "default";
[@bs.module "static/images/icon_android.svg"]
external androidIcon: SVG.asset = "default";
[@bs.module "static/images/icon_ruby.svg"]
external rubyIcon: SVG.asset = "default";
[@bs.module "static/images/icon_apple.svg"]
external appleIcon: SVG.asset = "default";
[@bs.module "static/images/icon_react.svg"]
external reactIcon: SVG.asset = "default";
[@bs.module "static/images/icon_nodejs.svg"]
external nodeJSIcon: SVG.asset = "default";

// Social icons.
[@bs.module "static/images/icon_twitter.svg"]
external twitterIcon: SVG.asset = "default";
[@bs.module "static/images/icon_facebook.svg"]
external facebookIcon: SVG.asset = "default";
[@bs.module "static/images/icon_linkedin.svg"]
external linkedInIcon: SVG.asset = "default";
[@bs.module "static/images/icon_github.svg"]
external githubIcon: SVG.asset = "default";

// Variables.
let techIcons = [|
  angularIcon,
  androidIcon,
  rubyIcon,
  appleIcon,
  reactIcon,
  nodeJSIcon,
|];
let socialIcons = [|twitterIcon, facebookIcon, linkedInIcon, githubIcon|];
let cubeOuterEdge = 37.5;
let cubeContentProjectionLength = 8.125;

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
      position(`relative),
      display(`flex),
      flexDirection(`column),
      width(pct(100.)),
      maxWidth(pct(100.)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          flexDirection(`row),
          width(`rem(cubeOuterEdge +. 2. *. cubeContentProjectionLength)),
          height(`rem(cubeOuterEdge)),
        ],
      ),
    ]);
  let backgroundCube =
    style([
      position(`absolute),
      top(pct(50.)),
      right(`rem(0.625)),
      left(`rem(0.625)),
      margin(`auto),
      transform(`translateY(pct(-50.))),
      border(px(1), `solid, hex(Theme.Colors.glazedBabyBlue)),
      boxShadow(Shadow.box(~blur=px(2), hex(Theme.Colors.glazedBabyBlue))),
      opacity(0.1),
      before([contentRule(""), display(`block), paddingTop(pct(100.))]),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          right(`rem(cubeContentProjectionLength)),
          left(`rem(cubeContentProjectionLength)),
        ],
      ),
    ]);
  let htmlText =
    style([
      color(hex(Theme.Colors.almostWhite)),
      fontSize(rem(0.85)),
      lineHeight(rem(1.5)),
      padding2(~v=rem(0.625), ~h=`zero),
      maxWidth(rem(13.)),
      opacity(0.7),
      top(`rem(1.25)),
      right(`zero),
      alignSelf(`flexEnd),
      marginRight(`rem(-0.9375)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          position(`absolute),
          padding(`zero),
          alignSelf(`initial),
          marginRight(`zero),
        ],
      ),
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
  let socialIconLink = style([display(`flex), margin(rem(0.9375))]);
  let socialIcon =
    style([opacity(0.4), Css.SVG.fill(hex(Theme.Colors.white))]);
  let mainHeading =
    style([
      display(`flex),
      flexDirection(`column),
      fontSize(rem(1.5)),
      lineHeight(rem(2.125)),
      color(hex(Theme.Colors.almostWhite)),
      maxWidth(rem(12.1875)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          fontSize(rem(2.25)),
          lineHeight(rem(2.75)),
          maxWidth(rem(24.)),
          marginTop(`rem(-1.875)),
        ],
      ),
    ]);
  let commentedText =
    style([
      opacity(0.5),
      fontFamily(Theme.Fonts.text),
      fontSize(rem(0.75)),
      media(Theme.Breakpoints.tabletLandscape, [fontSize(rem(0.875))]),
    ]);
  let exploreCasesButtonWrapper =
    style([
      alignSelf(`flexStart),
      margin3(~top=rem(1.), ~h=`zero, ~bottom=rem(1.125)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [margin3(~top=rem(0.93755), ~h=`zero, ~bottom=`zero)],
      ),
    ]);
  let exploreCasesButton =
    style([
      alignSelf(`flexStart),
      media(Theme.Breakpoints.tabletLandscape, [height(rem(3.125))]),
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
  let techStackIcons =
    style([
      display(`flex),
      flexWrap(`wrap),
      justifyContent(`center),
      position(`absolute),
      bottom(`zero),
      right(`zero),
      left(`zero),
      opacity(0.7),
      width(`rem(6.25)),
      marginLeft(`rem(-1.25)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          flex3(~grow=0., ~shrink=0., ~basis=`rem(3.125)),
          width(`auto),
          flexWrap(`initial),
          marginLeft(`zero),
          bottom(`rem(5.625)),
        ],
      ),
    ]);
  let techStackIcon =
    style([
      flex3(~grow=0., ~shrink=0., ~basis=pct(33.333333)),
      margin2(~v=`rem(0.625), ~h=`zero),
      Css.SVG.fill(hex(Theme.Colors.lightGrey)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [flex3(~grow=0., ~shrink=0., ~basis=`rem(3.125))],
      ),
    ]);
  let headingWrapper =
    style([
      display(`flex),
      flexDirection(`column),
      justifyContent(`center),
      zIndex(0),
      media(Theme.Breakpoints.tabletLandscape, [marginLeft(`rem(2.5))]),
    ]);
  let skillComments =
    style([
      position(`absolute),
      bottom(`rem(3.75)),
      right(`zero),
      display(`none),
      paddingTop(`rem(5.)),
      color(hex(Theme.Colors.almostWhite)),
      lineHeight(`abs(2.4)),
      fontFamily(Theme.Fonts.heading),
      fontSize(`rem(0.6875)),
      fontWeight(`num(700)),
      media(Theme.Breakpoints.tabletLandscape, [display(`block)]),
    ]);
};

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make =
  React.memo((~id=?, ~innerRef=?, ~onResize) => {
    <FullPageSlide
      ?id
      ?innerRef
      className=Styles.wrapper
      backgroundImageUrl="/images/home/slide-1-background.jpg"
      onResize>
      <div className=Styles.content>
        <div className=Styles.backgroundCube />
        <div className=Styles.headingWrapper>
          <Heading level=Heading.H1 className=Styles.mainHeading>
            <span className=Styles.commentedText>
              {React.string("// Some projects")}
            </span>
            {React.string("require elite mobile and web developers")}
          </Heading>
          <div className=Styles.exploreCasesButtonWrapper>
            <Gatsby.Link className="" _to="/#case-studies">
              <Button _type=Button.Primary className=Styles.exploreCasesButton>
                {React.string("> explore cases")}
              </Button>
            </Gatsby.Link>
          </div>
        </div>
        <HTMLText tag=HTMLText.P className=Styles.htmlText>
          {React.string(
             "a team of highly specialized developers that takes on the most demanding web and mobile development projects",
           )}
        </HTMLText>
        <pre className=Styles.skillComments>
          {React.string(
             {|
          {
          // machine learning
          // backend
          // frontend
          // android
          // iOS
          // APIs
          ... }
        |},
           )}
        </pre>
        <div className=Styles.techStackIcons>
          {React.array(
             Array.mapi(
               (index, icon) =>
                 <SVG
                   key={Belt.Int.toString(index)}
                   className=Styles.techStackIcon
                   asset=icon
                   height="16"
                 />,
               techIcons,
             ),
           )}
        </div>
      </div>
      <div className=Styles.socialNetworks>
        <a
          href="https://twitter.com/glazedSolutions"
          className=Styles.socialIconLink
          target="_blank"
          rel="nofollow">
          <SVG className=Styles.socialIcon asset=twitterIcon height="16" />
        </a>
        <a
          href="https://www.facebook.com/glazedEliteDevelopers/"
          className=Styles.socialIconLink
          target="_blank"
          rel="nofollow">
          <SVG className=Styles.socialIcon asset=facebookIcon height="16" />
        </a>
        <a
          href="https://www.linkedin.com/company/glazed-solutions/"
          className=Styles.socialIconLink
          target="_blank"
          rel="nofollow">
          <SVG className=Styles.socialIcon asset=linkedInIcon height="16" />
        </a>
        <a
          href="https://github.com/glazed-elite-developers"
          className=Styles.socialIconLink
          target="_blank"
          rel="nofollow">
          <SVG className=Styles.socialIcon asset=githubIcon height="16" />
        </a>
      </div>
    </FullPageSlide>
  });

let default = make;