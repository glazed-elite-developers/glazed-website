open Utils.React;

module Styles = {
  open Css;
  open Theme;

  let wrapper =
    style([
      padding4(
        ~top=rem(4.1875),
        ~bottom=rem(4.1875),
        ~left=rem(1.25),
        ~right=rem(2.5),
      ),
      height(`auto),
      flex3(~grow=1., ~shrink=0., ~basis=`auto),
      backgroundColor(hex(Colors.glazedBlueDarker)),
      media(
        Breakpoints.tabletLandscape,
        [padding2(~v=rem(6.25), ~h=rem(4.75))],
      ),
    ]);
  let heading =
    style([
      opacity(0.9),
      fontSize(`rem(1.125)),
      lineHeight(`rem(1.75)),
      media(
        Theme.Breakpoints.tabletPortrait,
        [fontSize(rem(2.)), lineHeight(rem(3.)), width(px(183))],
      ),
    ]);
  let grid = style([display(`flex), flexWrap(`wrap)]);
  let square =
    style([
      flex3(~grow=0., ~shrink=0., ~basis=pct(50.)),
      media(
        Breakpoints.tabletPortrait,
        [flex3(~grow=0., ~shrink=0., ~basis=pct(33.3333333))],
      ),
      media(
        Breakpoints.tabletLandscape,
        [flex3(~grow=0., ~shrink=0., ~basis=pct(25.))],
      ),
      media(
        Breakpoints.desktop,
        [flex3(~grow=0., ~shrink=0., ~basis=pct(20.))],
      ),
    ]);
  let squareContent =
    style([
      padding(rem(0.9375)),
      display(`flex),
      flexDirection(`column),
      media(
        Theme.Breakpoints.tabletLandscape,
        [padding2(~h=rem(1.875), ~v=rem(2.1875))],
      ),
    ]);
  let squareWithBorder =
    style([
      border(px(1), `solid, rgba(105, 192, 254, 0.1)),
    ])
  let headingSquare =
    style([
      color(hex(Colors.almostWhite)),
      padding3(~top=pct(30.), ~bottom=`zero, ~h=`rem(0.9375)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [padding3(~top=pct(30.), ~bottom=`zero, ~h=`rem(1.4375))],
      ),
    ]);
  let link =
    style([
      fontFamily(Fonts.heading),
      fontSize(`rem(0.75)),
      color(hex(Colors.glazedBabyBlue)),
      textDecoration(`none),
    ]);
  let developerSquare =
    style([
      color(hex(Colors.almostWhite)),
      backgroundColor(hex(Colors.glazedBlueDarkest)),
      before([
        contentRule(""),
        position(`absolute),
        top(`zero),
        right(`zero),
        bottom(`zero),
        left(`zero),
        opacity(0.),
        backgroundColor(hex(Colors.glazedBlueDarkish)),
        transition(~duration=300, "opacity"),
      ]),
      hover([before([opacity(1.)])]),
    ]);
  let developerSquareContent =
    style([
      display(`flex),
      flexDirection(`column),
      justifyContent(`flexEnd),
      flex3(~grow=1., ~shrink=1., ~basis=rem(0.000000001)),
      color(hex(Colors.almostWhite)),
      opacity(0.8),
      transition(~duration=300, "opacity"),
      zIndex(0),
      hover([opacity(1.)]),
    ]);
  let developerBackgroundImageWrapper =
    style([
      position(`absolute),
      top(`zero),
      right(`zero),
      bottom(`zero),
      left(`zero),
      opacity(0.4),
      transition(~duration=300, "opacity"),
      hover([opacity(0.6)]),
    ]);
  let developerBackgroundImage =
    style([top(`zero), right(`zero), bottom(`zero), left(`zero)]);
  let developerName =
    style([
      fontSize(rem(0.875)),
      paddingBottom(rem(0.875)),
      whiteSpace(`preLine),
    ]);
  let developerSkills =
    style([fontSize(rem(0.625)), fontFamily(Fonts.heading)]);
  let sendApplication =
    style([
      paddingTop(rem(1.)),
      flex3(~grow=1., ~shrink=1., ~basis=rem(0.000000001)),
      color(hex(Colors.almostWhite)),
      fontSize(rem(1.)),
      lineHeight(`abs(1.5)),
      media(Theme.Breakpoints.tabletLandscape, [fontSize(rem(1.6))]),
    ]);
  let motto =
    style([
      paddingTop(rem(1.)),
      color(hex(Colors.almostWhite)),
      fontSize(rem(1.)),
      lineHeight(`abs(1.5)),
      opacity(0.7),
      media(Theme.Breakpoints.tabletLandscape, [fontSize(rem(1.6))]),
    ]);
};

module TeamSlideSquare = {
  [@react.component]
  let make = (~children: React.element, ~contentClassName=?) => {
    <Square
      className=Styles.square
      contentClassName={combineOptionalStyles(
        ~baseStyles=Styles.squareContent,
        ~className=?contentClassName,
      )}>
      children
    </Square>;
  };
};

module TitleSquare = {
  [@react.component]
  let make = (~title: string) => {
    <TeamSlideSquare contentClassName=Css.merge([Styles.headingSquare, Styles.squareWithBorder])>
      <Heading level=Heading.H1 className=Styles.heading>
        {React.string(title)}
      </Heading>
    </TeamSlideSquare>;
  };
};

module MottoSquare = {
  [@react.component]
  let make = (~motto: string) => {
    <TeamSlideSquare contentClassName=Styles.squareWithBorder>
      <Heading level=Heading.H2 className=Styles.motto>
        {React.string(motto)}
      </Heading>
    </TeamSlideSquare>;
  };
};

module SendApplicationSquare = {
  [@react.component]
  let make = () => {
    <TeamSlideSquare contentClassName=Styles.squareWithBorder>
      <Heading level=Heading.H2 className=Styles.sendApplication>
        {React.string("<Your name could be here />")}
      </Heading>
      <Gatsby.Link _to="#" className=Styles.link replace=true>
        {React.string("> explore case")}
      </Gatsby.Link>
    </TeamSlideSquare>;
  };
};

module DeveloperSquare = {
  [@react.component]
  let make = (~developer: IndexTeamSlideSquares.developer) => {
    <TeamSlideSquare contentClassName=Styles.developerSquare>
      <div className=Styles.developerBackgroundImageWrapper>
        <DeveloperBackgroundImage
          developerPhotoKey={developer.photoKey}
          className=Styles.developerBackgroundImage
        />
      </div>
      <div className=Styles.developerSquareContent>
        <Heading level=Heading.H6 className=Styles.developerName>
          {React.string(Js.String.replace(" ", "\n", developer.name))}
        </Heading>
        <p className=Styles.developerSkills>
          {React.string(
             "{ "
             ++ Array.fold_left(
                  (result, skill) => {j|$(result) // $(skill)|j},
                  "",
                  developer.skills,
                )
             ++ " }",
           )}
        </p>
      </div>
    </TeamSlideSquare>;
  };
};

[@react.component]
let make = (~innerRef=?) => {
  <FullPageSlide className=Styles.wrapper ?innerRef>
    <div className=Styles.grid>
      {React.array(
         Array.mapi(
           (index, square) =>
             switch (square) {
             | IndexTeamSlideSquares.TitleSquare(title) =>
               <TitleSquare key={Belt.Int.toString(index)} title />
             | IndexTeamSlideSquares.MottoSquare(motto) =>
               <MottoSquare key={Belt.Int.toString(index)} motto />
             | IndexTeamSlideSquares.SendApplicationSquare =>
               <SendApplicationSquare key={Belt.Int.toString(index)} />
             | IndexTeamSlideSquares.DeveloperSquare(developer) =>
               <DeveloperSquare key={Belt.Int.toString(index)} developer />
             },
           IndexTeamSlideSquares.squares,
         ),
       )}
    </div>
  </FullPageSlide>;
};

let default = make;