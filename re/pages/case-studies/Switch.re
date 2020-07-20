open CaseStudyPageTemplate;

module Styles = {
  open Css;

  let adHocComponent = style([textAlign(`center)]);
};

let pageImagesQuery = [%raw
  {|Gatsby.graphql`
     query {
       headerImage: file(relativePath: { eq: "case-studies/switch-hero.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 820) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       bigImage: file(relativePath: { eq: "case-studies/switch-3.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 800) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       nextCaseImage: file(relativePath: { eq: "case-studies/boston-hero.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 820) {
             ...GatsbyImageSharpFluid
           }
         }
       }
     }
  `|}
];

[@react.component]
let make = () => {
  let queryResult = Gatsby.useStaticQuery(pageImagesQuery);
  let headerImage = Gatsby.getImageFluid(queryResult, "headerImage");
  let bigImage = Gatsby.getImageFluid(queryResult, "bigImage");
  let nextCaseImage = Gatsby.getImageFluid(queryResult, "nextCaseImage");

  // Replace the page contents here:
  let content: content = {
    hero: {
      image: headerImage,
      title: "Switch",
      area: "FinTech - Payments",
      text: "Switch provides the technical infrastructure for transaction orchestration across the entire payments value chain.",
    },
    brief: {
      techs: [|
        {name: "elixir", icon: TechIcons.twitter},
        {name: "python", icon: TechIcons.twitter},
        {name: "react", icon: TechIcons.twitter},
      |],
      year: "2020",
      brief: "Glazed worked with Switch to conceive and implement the 2nd and current version of its technological offer, moving from a credit cards only solution to its current unified payment API.
Glazed integrated more than 20 payment methods and entities across the world, with diverse specifications.",
    },
    // We can declare a dynamic list of components here. There are 3 components types currently availablBigImage, TextAndImage and QuoteCard:
    content: [|
      TextAndImage(
        {j|We developed the core architecture, that unites all the distinct payment method flows under a single integration, and allows having several providers per payment method, for cost optimisation and redundancy.
          We created REST and real-time APIs, using Python and Elixir, and developed integration libraries for Ruby, Python, Elixir, Node, iOS, Android and client-side JS.
          Glazed developed Switch’s website, merchant dashboard, documentation page and support platform.
          Glazed also handled Switch’s PCI certification, developing bank-grade security, fraud protection and data handling processes. We implemented automatic tests, continuous integration, high-availability, redundancy and scalability.|j},
        bigImage,
      ),
    |],
    nextCase: {
      image: nextCaseImage,
      title: "Boston Children's Hospital",
      area: "HealthTech - IoT",
      link: "/case-studies/boston",
    },
  };

  <CaseStudyPageTemplate content />;
};

let default = make;