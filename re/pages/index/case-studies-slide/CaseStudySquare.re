type caseStudy = {
  name: string,
  area: string,
  backgroundImageUrl: string,
  link: string,
};

module Styles = {
  open Css;
  open Theme;

  let number =
    style([
      fontFamily(Fonts.heading),
      fontSize(`rem(0.5)),
      opacity(0.3),
      color(hex(Colors.almostWhite)),
      media(Theme.Breakpoints.tabletLandscape, [fontSize(`rem(0.625))]),
    ]);
  let smallProjectName =
    style([
      display(`flex),
      alignItems(`flexEnd),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.000001)),
      fontSize(`rem(0.75)),
      opacity(0.7),
      color(hex(Colors.almostWhite)),
      media(Theme.Breakpoints.tabletLandscape, [fontSize(`rem(1.125))]),
    ]);
  let bigProjectName =
    style([
      fontSize(`rem(1.125)),
      color(hex(Colors.almostWhite)),
      opacity(0.9),
      media(Theme.Breakpoints.tabletLandscape, [fontSize(`rem(2.))]),
    ]);
  let projectArea =
    style([
      color(white),
      fontSize(px(14)),
      fontWeight(`normal),
      letterSpacing(pxFloat(0.31)),
      lineHeight(px(34)),
      marginLeft(px(30)),
    ]);
  let link =
    style([
      fontFamily(Fonts.heading),
      fontSize(`rem(0.75)),
      color(hex(Colors.glazedBabyBlue)),
    ]);
  let centeredContentWhenSelected =
    style([
      display(`flex),
      flexDirection(`column),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.000001)),
      justifyContent(`center),
    ]);
  let area =
    style([
      display(`none),
      paddingTop(`rem(0.625)),
      fontSize(`rem(0.8125)),
      lineHeight(`abs(1.5)),
      opacity(0.5),
      color(hex(Colors.almostWhite)),
      media(Theme.Breakpoints.tabletLandscape, [display(`block)]),
    ]);
};

[@react.component]
let make =
    (
      ~caseStudy: caseStudy,
      ~index: int,
      ~className=?,
      ~contentWrapperClassName=?,
      ~contentClassName=?,
      ~isSelected,
      ~onMouseEnter=?,
    ) => {
  <CaseStudiesSlideSquare
    ?className
    ?contentWrapperClassName
    ?contentClassName
    isSelected
    ?onMouseEnter
    contentWhenSelected={
      <React.Fragment>
        <p className=Styles.number> {"// 0" ++ Belt.Int.toString(index + 1) |> React.string} </p>
        <div className=Styles.centeredContentWhenSelected>
          <Heading level=Heading.H2 className=Styles.bigProjectName>
            {React.string(caseStudy.name)}
          </Heading>
          <p className=Styles.area> {React.string(caseStudy.area)} </p>
        </div>
        <Gatsby.Link _to={caseStudy.link} className=Styles.link>
          {React.string("> explore case")}
        </Gatsby.Link>
      </React.Fragment>
    }>
    <p className=Styles.number> {"// 0" ++ Belt.Int.toString(index + 1) |> React.string} </p>
    <Heading level=Heading.H4 className=Styles.smallProjectName>
      {React.string(caseStudy.name)}
    </Heading>
  </CaseStudiesSlideSquare>;
};
