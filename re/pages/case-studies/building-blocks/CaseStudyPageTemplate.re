open React;

module Styles = {
  open Css;
  open Theme;

  let pageLayout =
    style([
      flex3(~grow=1., ~shrink=0., ~basis=`auto),
      backgroundColor(hex(Colors.whiteTurquoise)),
      media(Theme.Breakpoints.tabletLandscape, [paddingTop(rem(6.875))]),
    ]);
};

let breakpointsWithDarkNavBar = Belt.Set.String.fromArray([|"tabletLandscape", "desktop"|]);

let techs: array(CaseStudyBrief.tech) = [|
  {name: "react", icon: TechIcons.twitter},
  {name: "angular", icon: TechIcons.twitter},
  {name: "ios", icon: TechIcons.twitter},
|];

let useShouldUseDarkNavbarLinks = () => {
  let scrollValues: ScrollConnectors.scrollValues = ScrollConnectors.useClosestScrollValues();
  let {scrollTop}: ScrollContext.scrollPosition = scrollValues.position;
  let breakpoint = React.useContext(MediaContext.context);
  useMemo2(
    () => {
      switch (breakpoint) {
      | "tabletLandscape"
      | "desktop" => true
      | _ => scrollTop > 305.
      }
    },
    (scrollTop, breakpoint),
  );
};

type dynamicContentComponents =
  | BigImage(option(Gatsby.fluidImage))
  | TextAndImage(string, option(Gatsby.fluidImage))
  | QuoteCard(string, CaseStudyQuoteCard.author)
  | Custom(React.element);

type hero = {
  image: option(Gatsby.fluidImage),
  title: string,
  area: string,
  text: string,
};

type brief = {
  techs: array(CaseStudyBrief.tech),
  year: string,
  brief: string,
};

type nextCase = {
  image: option(Gatsby.fluidImage),
  title: string,
  area: string,
  link: string,
};

type content = {
  hero,
  brief,
  content: array(dynamicContentComponents),
  nextCase,
};

[@react.component]
let make = (~content) => {
  let shouldUseDarkNavbarLinks = useShouldUseDarkNavbarLinks();
  <Layout>
    <PageLayout className=Styles.pageLayout useDarkNavBarLinks=shouldUseDarkNavbarLinks>
      <CaseStudyHeader
        image=?{content.hero.image}
        title={content.hero.title}
        area={content.hero.area}
        text={content.hero.text}
      />
      <CaseStudyBrief
        techs={content.brief.techs}
        year={content.brief.year}
        brief={content.brief.brief}
      />
      {React.array(
         Belt.Array.mapWithIndex(
           content.content,
           (index, contentComponent) => {
             let key = Belt.Int.toString(index);

             switch (contentComponent) {
             | BigImage(image) => <CaseStudyBigImage key ?image />
             | TextAndImage(text, image) => <CaseStudyTextAndImage key text ?image />
             | QuoteCard(quote, author) => <CaseStudyQuoteCard key quote author />
             | Custom(component) => cloneElement(component, ReactDOMRe.props(~key, ()))
             };
           },
         ),
       )}
      <CaseStudyNextCase
        image=?{content.nextCase.image}
        title={content.nextCase.title}
        area={content.nextCase.area}
        link={content.nextCase.link}
      />
    </PageLayout>
  </Layout>;
};

let default = make;
