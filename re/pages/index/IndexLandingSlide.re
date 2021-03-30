[@bs.module "static/images/logo-glazed-g.svg"] external logo: SVG.asset = "default";

// Tech icons.
[@bs.module "static/images/icon_angular_shield.svg"] external angularIcon: SVG.asset = "default";
[@bs.module "static/images/icon_android.svg"] external androidIcon: SVG.asset = "default";
[@bs.module "static/images/icon_ruby.svg"] external rubyIcon: SVG.asset = "default";
[@bs.module "static/images/icon_apple.svg"] external appleIcon: SVG.asset = "default";
[@bs.module "static/images/icon_react.svg"] external reactIcon: SVG.asset = "default";
[@bs.module "static/images/icon_nodejs.svg"] external nodeJSIcon: SVG.asset = "default";

// Social icons.
[@bs.module "static/images/icon_twitter.svg"] external twitterIcon: SVG.asset = "default";
[@bs.module "static/images/icon_facebook.svg"] external facebookIcon: SVG.asset = "default";
[@bs.module "static/images/icon_linkedin.svg"] external linkedInIcon: SVG.asset = "default";
[@bs.module "static/images/icon_github.svg"] external githubIcon: SVG.asset = "default";

// Hero Image
[@bs.module "static/images/home/office.jpg"] external office: string = "default";

// Client Images
[@bs.module "static/images/clients/ASOS.png"] external asos: string = "default";
[@bs.module "static/images/clients/BostonChildrensHospital.png"] external bostonHospital: string = "default";
[@bs.module "static/images/clients/fenty.png"] external fenty: string = "default";
[@bs.module "static/images/clients/Bulgari.png"] external bulgari: string = "default";
[@bs.module "static/images/clients/Louis_Vuitton.png"] external lvmh: string = "default";
[@bs.module "static/images/clients/ralph_and_russo.png"] external ralphAndRusso: string = "default";
[@bs.module "static/images/clients/sephora.png"] external sephora: string = "default";
[@bs.module "static/images/clients/WeChangers.png"] external weChangers: string = "default";
[@bs.module "static/images/clients/Bloomberg.png"] external bloomberg: string = "default";

// Variables.
let techIcons = [|angularIcon, androidIcon, rubyIcon, appleIcon, reactIcon, nodeJSIcon|];
let socialIcons = [|twitterIcon, facebookIcon, linkedInIcon, githubIcon|];
let clients = [|asos, bostonHospital, fenty, bulgari, lvmh, ralphAndRusso, sephora, weChangers, bloomberg|]
let cubeOuterEdge = 37.5;
let cubeContentProjectionLength = 8.125;

open Utils.Env;

module Styles = {
  open Css;

  let mobile = style([
    display(`inherit_),
    media(
      Theme.Breakpoints.tabletLandscape,
      [display(`none)],
    ),
  ]);
  let tabletLandscape = style([
    display(`none),
    media(
      Theme.Breakpoints.tabletLandscape,
      [display(`inherit_)],
    ),
  ]);

  let wrapper =
    style([
      padding2(~h=rem(2.0625), ~v=rem(8.0625)),
      display(`flex),
      flexDirection(`column),
      justifyContent(`center),
      alignItems(`center),
      position(`relative),
      overflow(`hidden)
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
  let cube = style([
    display(`none),
    media(
        Theme.Breakpoints.tabletLandscape,
        [
          display(`block),
          position(`absolute),
          top(Calc.(-)(pct(50.), px(250))),
          left(Calc.(-)(pct(50.), px(250)))
        ],
      ),
  ])
  let logoWrapper = style([
    position(`absolute),
    top(`percent(50.)),
    left(`percent(50.)),
    transform(`translate(`percent(-50.), `percent(-50.))),
  ]);
  let logo = style([height(rem(5.))]);
  let pulse = style([
    position(`absolute),
    top(`percent(50.)),
    left(`percent(50.)),
    transform(`translate(`percent(-50.), `percent(-50.))),
    width(`px(1)),
    height(`px(1)),
    borderRadius(`percent(50.))
  ]);
  let imageForeground = style([
      position(`absolute),
      width(pct(100.)),
      height(pct(100.)),
      top(`zero),
      left(`zero),
      pointerEvents(`none),
      backgroundColor(hex(Theme.Colors.white))
  ]);
  let backgroundImage =
    style([position(`absolute), top(`zero), right(`zero), bottom(`zero), left(`zero)]);
  let animatedMask = style([
     position(`absolute),
      width(pct(100.)),
      height(pct(100.)),
      top(`zero),
      left(`zero),
      pointerEvents(`none),
      opacity(0.65),
      backgroundColor(hex(Theme.Colors.glazedBlueMidnight))
  ])
  let htmlText =
    style([
      color(hex(Theme.Colors.almostWhite)),
      fontSize(rem(0.85)),
      lineHeight(rem(1.5)),
      padding2(~v=rem(0.625), ~h=`zero),
      maxWidth(rem(13.)),
      top(`rem(1.25)),
      right(`zero),
      alignSelf(`flexEnd),
      marginRight(`rem(-0.9375)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [position(`absolute), padding(`zero), alignSelf(`initial), marginRight(`zero)],
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
  let socialIcon = style([opacity(0.4), Css.SVG.fill(hex(Theme.Colors.white))]);
  let mainHeading =
    style([
      display(`flex),
      flexWrap(`wrap),
      fontSize(rem(1.5)),
      lineHeight(rem(2.125)),
      color(hex(Theme.Colors.almostWhite)),
      height(`rem(4.25)),
      maxWidth(rem(16.)),
      overflowY(`hidden),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          fontSize(rem(2.25)),
          lineHeight(rem(2.75)),
          height(`rem(5.5)),
          maxWidth(rem(24.))
        ],
      ),
    ]);
  let commentedText =
    style([
      fontWeight(`num(700)),
      marginBottom(`rem(0.25)),
      color(hex(Theme.Colors.grey)),
      opacity(0.5),
      fontFamily(`custom(Theme.Fonts.text)),
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
        [maxWidth(rem(70.)), marginTop(rem(20.)), marginBottom(rem(5.))],
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
  let clients =
    style([
      display(`flex),
      position(`absolute),
      flexDirection(`column),
      right(`zero),
      bottom(`rem(-9.)),
      left(`rem(2.375)),
      opacity(0.7),
      maxWidth(`rem(16.)),
      maxHeight(`rem(7.)),
      overflow(`hidden),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          bottom(`rem(-7.5)),
          left(`rem(7.875)),
          maxWidth(`rem(28.)),
          maxHeight(`none)
        ],
      ),
    ]);
  let clientsSpan = style([
    color(hex(Theme.Colors.grey)),
    fontSize(rem(0.75)),
    lineHeight(px(24))
  ]);
  let clientsImages = style([
      marginTop(`rem(0.375)),
      display(`flex),
      flexWrap(`wrap),
      justifyContent(`spaceAround)
  ]);
  let clientImage =
    style([
      width(`auto),
      height(px(14)),
      objectFit(`contain),
      marginBottom(`rem(1.)),
      flex3(~grow=0., ~shrink=1., ~basis=pct(50.)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [flex3(~grow=0., ~shrink=1., ~basis=pct(33.))]
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
      fontFamily(`custom(Theme.Fonts.heading)),
      fontSize(`rem(0.6875)),
      fontWeight(`num(700)),
      media(Theme.Breakpoints.tabletLandscape, [display(`block)]),
    ]);
};

let imageQuery = [%raw
  {|Gatsby.graphql`
    query {
      backgroundImage: file(relativePath: { eq: "home/office.jpg" }) {
        childImageSharp {
          fluid(maxWidth: 4032, quality: 100) {
            ...GatsbyImageSharpFluid_withWebp
          }
        }
      }
    }
  `|}
];

[@react.component]
let make =
  React.memo((~id=?, ~innerRef=?, ~onResize, ~hasMounted) => {
    let queryResult = Gatsby.useStaticQuery(imageQuery);
    let backgroundImage = Gatsby.getImageFluid(queryResult, "backgroundImage");

    let hasPlayedAnimation =
    switch (Utils.Env.getPlatform()) {
      | Browser =>
        switch (Dom.Storage.(sessionStorage |> getItem("hasPlayed:indexLanding"))) {
          | Some("true") => true
          | _ => false
          };
      | _ => false
    };

    <FullPageSlide ?id ?innerRef className=Styles.wrapper onResize>
      <div className=Styles.backgroundImage>
        {hasMounted ?
          hasPlayedAnimation ?
            <Gatsby.Image
              className=Styles.backgroundImage
              fluid=?backgroundImage
              style={ReactDOMRe.Style.make(~position="absolute", ())}
              loading="eager"
            /> :
            // Gatsby image replacement stutters the page load
            <img
              src=office
              style={ReactDOMRe.Style.make(~width="100%", ~height="100%", ~objectFit="cover", ())}
            /> :
            React.null
        }
        <Animate
          isIn=hasMounted
          animationGroup="indexLanding"
          animation="scaleDownY"
          baseDelay=1250
          duration=1500
          transformOrigin="top center"
        >
          <div className=?{Utils.React.combineClassNames([Some(Styles.imageForeground), Some(Styles.mobile)])} />
        </Animate>
        <Animate
          isIn=hasMounted
          animationGroup="indexLanding"
          animation="scaleUpY"
          baseDelay=2000
          duration=1500
          transformOrigin="bottom center"
        >
          <div className=?{Utils.React.combineClassNames([Some(Styles.animatedMask), Some(Styles.mobile)])} />
        </Animate >
        <Animate
          isIn=hasMounted
          animationGroup="indexLanding"
          animation="scaleDownX"
          baseDelay=1250
          duration=1500
          transformOrigin="center right"
        >
          <div className=?{Utils.React.combineClassNames([Some(Styles.imageForeground), Some(Styles.tabletLandscape)])} />
        </Animate>
        <Animate
          isIn=hasMounted
          animationGroup="indexLanding"
          animation="scaleUpX"
          baseDelay=2000
          duration=1500
          transformOrigin="center left"
        >
          <div className=?{Utils.React.combineClassNames([Some(Styles.animatedMask), Some(Styles.tabletLandscape)])} />
        </Animate>
      </div>
        <Animate
          isIn=hasMounted
          animationGroup="indexLanding"
          animation="fadeOut"
          baseDelay=1250
          duration=200
        >
        <Animate
          isIn=hasMounted
            animationGroup="indexLanding"
            animation="pulse"
            duration=625
            baseDelay=100
            timingFunction="cubic-bezier(0, 0.75, 0, 1)"
            iterationCount=2
          >
            <div className=Styles.pulse />
          </Animate >
          <div className=Styles.logoWrapper>
            <svg className=Styles.logo width="57px" height="68px" viewBox="0 0 57 68" version="1.1" xmlns="http://www.w3.org/2000/svg">
              <g id="Page-1" stroke="none" strokeWidth="1" fill="none" fillRule="evenodd">
                  <g id="logo-glazed" transform="translate(-1.000000, -1.000000)" fillRule="nonzero">
                      <g id="Group_33" transform="translate(0.191000, 0.099000)">
                          <polygon id="Path_144" fill="#024DD1" points="29.324 57.21 48.957 45.676 29.285 33.834 9.69 45.458"></polygon>
                          <polygon id="Path_145" fill="#0E4AA0" points="9.691 45.618 38.109 28.364 38.15 6.264 9.691 23.331"></polygon>
                          <polygon id="Path_146" fill="#537EED" points="9.691 23.326 38.15 6.26 29.328 0.901 0.81 18.084"></polygon>
                          <polygon id="Path_147" fill="#0E4AA0" points="40.155 28.567 48.955 33.834 48.955 45.676 39.071 39.726"></polygon>
                          <polygon id="Path_148" fill="#2962F6" points="20.438 29.749 29.324 35.034 29.324 45.457 20.438 40.152"></polygon>
                          <polygon id="Path_149" fill="#2962F6" points="29.324 35.034 29.324 45.457 48.957 33.833 48.957 45.675 29.324 57.21 9.691 45.457 9.691 23.326 0.861 18.019 0.861 50.947 29.324 67.967 57.787 50.92 57.787 17.987"></polygon>
                          <polygon id="Path_150" fill="#537EED" points="29.37 35.034 57.829 17.967 49.007 12.608 20.489 29.791"></polygon>
                      </g>
                  </g>
              </g>
            </svg>
          </div>
      </Animate >
      <Animate
        isIn=hasMounted
        animationGroup="indexLanding"
        animation="scaleUp"
        baseDelay=1250
        duration=1500
      >
        <Cube className=Styles.cube />
      </Animate>
        <div className=Styles.content>
          <div className=Styles.headingWrapper>
            <Animate
              isIn=hasMounted
              animationGroup="indexLanding"
              animation="fadeIn"
              timingFunction="ease-in"
              baseDelay=2250
              duration=1500
            >
              <span className=Styles.commentedText>{React.string("// Some projects")}</span>
            </Animate>
            <Heading level=Heading.H1 className=Styles.mainHeading>
              {
                hasPlayedAnimation
                  ? <>{"require elite mobile and web developers" |> ReasonReact.string}</>
                  : <GlitchText
                    animationGroup="indexLanding"
                    baseDelay=2500
                    itemDelay=25
                    iterationCount=30
                    duration=125
                    text="require elite mobile and web developers"
                  />
              }
            </Heading>
            <div className=Styles.exploreCasesButtonWrapper>
              <Gatsby.Link className="" _to="/#case-studies">
                <Animate
                  isIn=hasMounted
                  animationGroup="indexLanding"
                  animation="fadeIn"
                  timingFunction="ease-in"
                  baseDelay=2750
                  duration=1000
                >
                  <Button _type=Button.Primary className=Styles.exploreCasesButton>
                    {React.string("> explore cases")}
                  </Button>
                </Animate>
              </Gatsby.Link>
            </div>
          </div>
          <Animate
            isIn=hasMounted
            animationGroup="indexLanding"
            animation="fadeIn"
            timingFunction="ease-in"
            baseDelay=3000
            duration=750
          >
            <HTMLText tag=HTMLText.P className=Styles.htmlText>
              {React.string(
                "a team of highly specialized developers that takes on the most demanding web and mobile development projects",
              )}
            </HTMLText>
          </Animate>
          <Animate
            isIn=hasMounted
            animationGroup="indexLanding"
            animation="fadeIn"
            timingFunction="ease-in"
            baseDelay=3500
            duration=750
          >
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
          </Animate>
          <div className=Styles.techStackIcons>
            <Animate
              isIn=hasMounted
              animationGroup="indexLanding"
                animation="slideUpFadeIn"
                baseDelay=3500
                itemDelay=200
                duration=1500
              >
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
            </Animate>
          </div>
        <div className=Styles.clients>
          <Animate
            isIn=hasMounted
            animationGroup="indexLanding"
            animation="fadeIn"
            timingFunction="ease-in"
            baseDelay=3750
            itemDelay=200
            duration=1500
          >
          <span className=Styles.clientsSpan>{"clients like:" |> ReasonReact.string}</span>
          </Animate>
          <div className=Styles.clientsImages>
            <Animate
              isIn=hasMounted
              animationGroup="indexLanding"
              animation="slideUpFadeIn"
              baseDelay=2750
              itemDelay=200
              duration=1000
            >
               {React.array(
                Array.mapi(
                  (index, src) =>
                    <img
                      key={Belt.Int.toString(index)}
                      className=Styles.clientImage
                      src=src
                    />,
                  clients,
                ),
              )}
            </Animate>
          </div>
        </div>
      </div>
      <div className=Styles.socialNetworks>
        <Animate
          isIn=hasMounted
          animationGroup="indexLanding"
          animation="slideUpFadeIn"
          baseDelay=2000
          itemDelay=200
          duration=1000
        >
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
        </Animate>
      </div>
    </FullPageSlide>;
  });

let default = make;
