open CaseStudyPageTemplate;

module Styles = {
  open Css;

  let adHocComponent = style([textAlign(`center)]);
};

let pageImagesQuery = [%raw
  {|Gatsby.graphql`
     query {
       headerImage: file(relativePath: { eq: "case-studies/farfetch-header.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 820) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       bigImage: file(relativePath: { eq: "case-studies/farfetch-header.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       joseNeves: file(relativePath: { eq: "case-studies/farfetch-header.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 120) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       nextCaseImage: file(relativePath: { eq: "case-studies/switch-hero.jpg" }) {
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
  let bigImage = Gatsby.getImageFluid(queryResult, "headerImage");
  let joseNevesAvatarImage = Gatsby.getImageFluid(queryResult, "joseNeves");
  let nextCaseImage = Gatsby.getImageFluid(queryResult, "nextCaseImage");
  let content: content = {
    hero: {
      image: headerImage,
      title: "Farfetch",
      area: "Fashion - Ecommerce",
      text: "An international fashion website that sells products from 400 independent boutiques around the world.",
    },
    brief: {
      techs: [|
        {name: "react", icon: TechIcons.twitter},
        {name: "angular", icon: TechIcons.twitter},
        {name: "ios", icon: TechIcons.twitter},
      |],
      year: "2019",
      brief: "Farfetch asked Glazed to create a white label version of their main e-commerce site for big brands that want to sell on their own website.
      This project, called black-and-white, was the main strategic move the company made after being valued at $1b dollars and the first clients to use it were Manolo Blahnik and Rihanna.",
    },
    content: [|
      BigImage(bigImage),
      TextAndImage(
        "Glazed built a multi-tenant fashion eCommerce store, with a large feature set:  Product Collections, Seasons, Campaigns, Search, Browsing, Filtering, Product Recommendation algorithm, Shopping Bag, Favourites, Social interaction, Campaigns, Discounts, Newsletter, Analytics, Boutiques listing.
        All of them were integrated with Farfetch's internal processes which provided Operations, Payments, Shipping, Billing, Returns and Support.",
        bigImage,
      ),
      QuoteCard(
        "Culture really trumps everything else.",
        {name: {j|José Neves|j}, title: "Farfetch CEO", avatarImage: joseNevesAvatarImage},
      ),
      TextAndImage(
        {j|
        The storefront is using isomorphic React (because SEO was vital for the type of search that the company wanted to achieve and performance optimization via caching and mobile-specific code chunks)
        React and webpack (using since ‘15), which allowed building a component-based single-page application that is search-engine optimised, and that only serves the content needed for each context, with a fast and light first-load which is great for mobile. Our codebase was split across several microservices, with a very scalable architecture, easy to deploy using docker.
        |j},
        bigImage,
      ),
    |],
    nextCase: {
      image: nextCaseImage,
      title: "Switch",
      area: "FinTech - Payments",
      link: "/case-studies/switch",
    },
  };

  <CaseStudyPageTemplate content />;
};

let default = make;
