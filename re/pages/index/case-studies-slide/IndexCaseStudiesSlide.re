module Styles = {
  open Css;
  open Theme;

  let wrapper = {
    let footerHeight = MobileFooter.Styles.Variables.height;
    let paddingBottom =
      switch (footerHeight) {
      | `rem(value) => `rem(value +. 1.25)
      };

    style([
      position(`relative),
      display(`flex),
      flexDirection(`column),
      justifyContent(`flexEnd),
      // minHeight(rem(37.5)),
      padding4(~top=rem(4.1875), ~right=rem(2.5), ~left=rem(1.25), ~bottom=paddingBottom),
      overflow(`hidden),
      color(hex(Colors.almostWhite)),
      // media(Breakpoints.tabletPortrait, [minHeight(rem(56.25))]),
      media(
        Breakpoints.tabletLandscape,
        [
          alignItems(`center),
          padding4(~top=rem(6.25), ~right=rem(7.25), ~bottom=rem(1.875), ~left=rem(4.75)),
          justifyContent(`center),
        ],
      ),
      media(
        Breakpoints.desktop,
        [
          // minHeight(rem(62.5)),
          padding4(~top=rem(6.25), ~right=rem(16.875), ~bottom=rem(1.875), ~left=rem(8.75)),
        ],
      ),
    ]);
  };
  let maskContainer = style([backgroundColor(rgba(34, 39, 63, 0.8))]);
  let backgroundImage =
    style([position(`absolute), top(`zero), right(`zero), bottom(`zero), left(`zero)]);
  let grid =
    style([
      position(`relative),
      width(pct(100.)),
      maxWidth(`rem(31.25)),
      media(Breakpoints.tabletLandscape, [maxWidth(`rem(75.))]),
      padding4(~top=`px(1), ~right=`zero, ~bottom=`zero, ~left=`px(1)),
    ]);
  let backgroundGrid =
    style([position(`absolute), top(`px(1)), right(`zero), bottom(`zero), left(`px(1))]);
  let contentGrid = style([width(pct(100.))]);
  let squareRow = style([display(`flex), flexWrap(`wrap)]);
  let backgroundSquareRow = merge([squareRow, style([opacity(0.7)])]);
  let dimmedBackgroundSquareRow = merge([squareRow, style([opacity(0.3)])]);
  let onlyInMobile =
    style([display(`none), media(Breakpoints.tabletLandscape, [display(`flex)])]);
  let square =
    style([
      margin4(~top=`px(-1), ~right=`zero, ~bottom=`zero, ~left=`px(-1)),
      flex3(~grow=0., ~shrink=0., ~basis=pct(50.)),
      media(Breakpoints.tabletLandscape, [flex3(~grow=0., ~shrink=0., ~basis=pct(25.))]),
    ]);
  let squareContent =
    style([padding4(~top=`px(1), ~right=`zero, ~bottom=`zero, ~left=`px(1))]);
  let squareWithBorder =
    merge([square, style([opacity(0.7), border(px(1), `solid, hex(Colors.darkGrey))])]);
  let headingSquareContent =
    Css.merge([
      squareContent,
      style([
        padding2(~v=`zero, ~h=`rem(0.9375)),
        justifyContent(`center),
        media(Breakpoints.tabletLandscape, [padding2(~v=`zero, ~h=`rem(1.4375))]),
      ]),
    ]);

  let fakeSquareContent = merge([style([borderColor(`transparent)])]);
  let heading =
    style([
      opacity(0.9),
      fontSize(`rem(1.125)),
      lineHeight(`rem(1.75)),
      media(
        Breakpoints.tabletPortrait,
        [fontSize(rem(2.)), lineHeight(rem(3.)), width(px(183))],
      ),
    ]);
};

let caseStudies: array(CaseStudySquare.caseStudy) = [|
  {
    index: 0,
    name: "LVMH",
    area: "Fashion - Chatbots",
    backgroundImageKey: "LVMH",
    link: "/case-studies/lvmh",
  },
  {
    index: 1,
    name: "Farfetch",
    area: "Fashion - Ecommerce",
    backgroundImageKey: "Farfetch",
    link: "/case-studies/farfetch",
  },
  {
    index: 2,
    name: {j|Mercadão|j},
    area: "Retail - Marketplace",
    backgroundImageKey: "Mercadao",
    link: "/case-studies/mercadao",
  },
  {
    index: 3,
    name: "Boston Hospital",
    area: "HealthTech - IoT",
    backgroundImageKey: "Boston",
    link: "/case-studies/boston",
  },
|];

[@react.component]
let make =
  React.memo((~innerRef=?, ~id=?, ~onResize) => {
    let (selectedCaseStudy, selectCaseStudy) = React.useState(() => caseStudies[0]);

    <FullPageSlide className=Styles.wrapper ?id ?innerRef onResize>
      <MaskContainer className=Styles.backgroundImage maskClassName=Styles.maskContainer>
        <GlitchCanvas>
          <GlitchImages
            current=selectedCaseStudy.index
          />
        </GlitchCanvas>
      </MaskContainer>
      <div className=Styles.grid>
        <div className=Styles.backgroundGrid>
          <div className=Styles.dimmedBackgroundSquareRow>
            <Square className=Styles.squareWithBorder />
          </div>
          <div className=Styles.backgroundSquareRow>
            {caseStudies
             |> Array.mapi((index, _) =>
                  <Square key={Belt.Int.toString(index)} className=Styles.squareWithBorder />
                )
             |> React.array}
          </div>
          <div className={Css.merge([Styles.dimmedBackgroundSquareRow, Styles.onlyInMobile])}>
            <Square className=Styles.square contentClassName=Styles.fakeSquareContent />
            <Square className=Styles.squareWithBorder />
          </div>
        </div>
        <div className=Styles.contentGrid>
          <div className=Styles.squareRow>
            <CaseStudiesSlideSquare
              className=Styles.square contentClassName=Styles.headingSquareContent>
              <Heading level=Heading.H1 className=Styles.heading>
                {React.string("// case studies")}
              </Heading>
            </CaseStudiesSlideSquare>
          </div>
          <div className=Styles.squareRow>
            {caseStudies
             |> Array.mapi((index, caseStudy) =>
                  <CaseStudySquare
                    key={Belt.Int.toString(index)}
                    caseStudy
                    index
                    className=Styles.square
                    contentWrapperClassName=Styles.squareContent
                    isSelected={caseStudy === selectedCaseStudy}
                    onMouseEnter={_ => selectCaseStudy(_ => caseStudy)}
                  />
                )
             |> React.array}
          </div>
          <div className={Css.merge([Styles.squareRow, Styles.onlyInMobile])}>
            <CaseStudiesSlideSquare
              className=Styles.square
              contentClassName=Styles.fakeSquareContent
            />
            <CaseStudiesSlideSquare className=Styles.square />
          </div>
        </div>
      </div>
    </FullPageSlide>;
  });

let default = make;
