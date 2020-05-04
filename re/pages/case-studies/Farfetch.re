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

let backgroundImageQuery = [%raw
  {|Gatsby.graphql`
     query {
       headerImage: file(relativePath: { eq: "farfetch-header.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 820) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       bigImage: file(relativePath: { eq: "farfetch-header.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       joseNeves: file(relativePath: { eq: "farfetch-header.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 120) {
             ...GatsbyImageSharpFluid
           }
         }
       }
     }
  `|}
];

let breakpointsWithDarkNavBar =
  Belt.Set.String.fromArray([|"tabletLandscape", "desktop"|]);

let techs: array(CaseStudyBrief.tech) = [|
  {name: "react", icon: TechIcons.twitter},
  {name: "angular", icon: TechIcons.twitter},
  {name: "ios", icon: TechIcons.twitter},
|];

let genericText = "We built the storefront using isomorphic React and webpack, which allowed to build a component-based single-page application that is search-engine optimised, and that only servers the content needed for each context, with a fast and light first-load which is great for mobile. Our codebase was split across several micro services, with a very scalable architecture, easy to deploy using docker.";

let joseNevesQuote = "This project, called black-and-white, was the main strategic move the company made after being valued at $1b dollars. The first clients to use it were Manolo Blahnik and Rihanna.";

let useShouldUseDarkNavbarLinks = () => {
  let scrollValues: ScrollConnectors.scrollValues =
    ScrollConnectors.useClosestScrollValues();
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

[@react.component]
let make = () => {
  let shouldUseDarkNavbarLinks = useShouldUseDarkNavbarLinks();
  let queryResult = Gatsby.useStaticQuery(backgroundImageQuery);
  let headerImage = Gatsby.getImageFluid(queryResult, "headerImage");
  let bigImage = Gatsby.getImageFluid(queryResult, "headerImage");
  let joseNevesAvatarImage = Gatsby.getImageFluid(queryResult, "joseNeves");
  let quoteAuthor: CaseStudyQuoteCard.author = {
    name: {j|José Neves|j},
    title: "Farfetch CEO",
    avatarImage: joseNevesAvatarImage,
  };

  <Layout>
    <PageLayout
      className=Styles.pageLayout useDarkNavBarLinks=shouldUseDarkNavbarLinks>
      <CaseStudyHeader
        image=?headerImage
        title="Farfetch"
        area="Fashion - Ecommerce"
        text="An international fashion website that sells products from 400 independent boutiques around the world."
      />
      <CaseStudyBrief
        techs
        year="2019"
        brief="Farfetch asked us to create a white label version of the their main e-commerce site for big brands that want to sell on their own website."
      />
      <CaseStudyBigImage image=?bigImage />
      <CaseStudyTextAndImage text=genericText image=?bigImage />
      <CaseStudyQuoteCard quote=joseNevesQuote author=quoteAuthor />
      <CaseStudyNextCase
        image=?bigImage
        title="Switch"
        area="Fasion - Ecommerce"
        link="/"
      />
    </PageLayout>
  </Layout>;
};

let default = make;