module Styles = {
  open Css;
  open Theme;

  let pageLayout =
    style([
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

[@react.component]
let make = () => {
  let queryResult = Gatsby.useStaticQuery(backgroundImageQuery);
  let headerImage = Gatsby.getImageFluid(queryResult, "headerImage");
  let bigImage = Gatsby.getImageFluid(queryResult, "headerImage");
  let breakpoint = React.useContext(MediaContext.context);

  <Layout>
    <PageLayout
      className=Styles.pageLayout
      useDarkNavBarLinks={Belt.Set.String.has(
        breakpointsWithDarkNavBar,
        breakpoint,
      )}>
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
      <CaseStudyNextCase image=?bigImage title="Switch" area="Fasion - Ecommerce" link="/" />
    </PageLayout>
  </Layout>;
};

let default = make;