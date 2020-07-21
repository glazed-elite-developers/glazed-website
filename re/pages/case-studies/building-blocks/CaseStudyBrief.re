open Utils.React;

module Styles = {
  open Css;
  open Theme;

  let wrapper =
    style([
      display(`flex),
      flexWrap(`wrap),
      padding2(~h=rem(1.25), ~v=rem(2.5)),
      media(Theme.Breakpoints.tabletLandscape, [padding2(~h=rem(11.25), ~v=rem(6.25))]),
    ]);
  let section =
    style([
      display(`flex),
      flexDirection(`column),
      paddingBottom(rem(1.875)),
      lineHeight(`abs(2.)),
    ]);
  let sectionTitle =
    style([
      paddingBottom(rem(0.9375)),
      fontSize(rem(0.625)),
      color(hex(Colors.darkGrey)),
      opacity(0.4),
      media(Breakpoints.tabletLandscape, [fontSize(rem(0.8125)), paddingBottom(rem(1.25))]),
    ]);
  let techsSection =
    style([
      flex3(~grow=0., ~shrink=0., ~basis=pct(100.)),
      media(
        Breakpoints.tabletLandscape,
        [paddingLeft(rem(3.125)), flex3(~grow=0., ~shrink=0., ~basis=pct(30.))],
      ),
    ]);
  let briefSection =
    style([
      flex3(~grow=0., ~shrink=0., ~basis=pct(70.)),
      paddingRight(rem(1.5625)),
      media(Breakpoints.tabletLandscape, [flex3(~grow=1., ~shrink=0., ~basis=rem(0.0000001))]),
    ]);
  let yearSection =
    style([
      media(
        Breakpoints.tabletLandscape,
        [flex3(~grow=0., ~shrink=0., ~basis=pct(17.)), alignItems(`flexEnd)],
      ),
    ]);
  let techs =
    style([
      display(`flex),
      flexWrap(`wrap),
      margin2(~v=`zero, ~h=rem(-0.875)),
      media(
        Breakpoints.tabletLandscape,
        [flexDirection(`column), margin2(~v=rem(-0.25), ~h=`zero)],
      ),
    ]);
  let techBadge =
    style([
      display(`flex),
      alignItems(`center),
      fontSize(rem(0.875)),
      fontFamily(Fonts.heading),
      padding2(~v=`zero, ~h=rem(0.875)),
      color(hex(Colors.darkGrey)),
      opacity(0.7),
      media(Breakpoints.tabletLandscape, [padding2(~v=rem(0.75), ~h=`zero)]),
    ]);
  let techIcon =
    style([
      height(px(14)),
      marginRight(rem(0.3125)),
      Css.SVG.fill(hex(Theme.Colors.darkGrey)),
      media(Breakpoints.tabletLandscape, [marginRight(rem(0.625))]),
    ]);
  let brief =
    style([
      fontSize(rem(1.)),
      color(hex(Colors.darkGrey)),
      media(Breakpoints.tabletLandscape, [fontSize(rem(1.5))]),
    ]);
  let year =
    style([
      fontSize(rem(0.875)),
      color(hex(Colors.darkGrey)),
      media(Breakpoints.tabletLandscape, [fontSize(rem(1.125))]),
    ]);
};

type tech = {
  name: string,
  icon: SVG.asset,
};

module Section = {
  [@react.component]
  let make = (~title: string, ~children, ~className=?) => {
    <div className=?{combineClassNames([Some(Styles.section), className])}>
      <Heading level=Heading.H6 className=Styles.sectionTitle> {React.string(title)} </Heading>
      children
    </div>;
  };
};

module TechBadge = {
  [@react.component]
  let make = (~tech: tech) => {
    <div className=Styles.techBadge>
      <SVG className=Styles.techIcon asset={tech.icon} />
      {React.string(tech.name)}
    </div>;
  };
};

[@react.component]
let make = (~techs: array(tech), ~year: string, ~brief: string) => {
  <CaseStudySection className=Styles.wrapper>
    <Section title="// Technologies" className=Styles.techsSection>
      <div className=Styles.techs>
        {React.array(Belt.Array.map(techs, tech => <TechBadge key={tech.name} tech />))}
      </div>
    </Section>
    <Section title="// The Brief" className=Styles.briefSection>
      <p className=Styles.brief> {React.string(brief)} </p>
    </Section>
    <Section title="// Year" className=Styles.yearSection>
      <p className=Styles.year> {React.string(year)} </p>
    </Section>
  </CaseStudySection>;
};

let default = make;
