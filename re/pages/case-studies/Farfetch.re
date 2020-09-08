open CaseStudyPageTemplate;

module Styles = {
  open Css;

  let adHocComponent = style([textAlign(`center)]);
};

let pageImagesQuery = [%raw
  {|Gatsby.graphql`
     query {
       headerImage: file(relativePath: { eq: "case-studies/farfetch-hero.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 820) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       bigImage: file(relativePath: { eq: "case-studies/farfetch-1.png" }) {
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
        "There are many ways to optimise the conversion funnel – the path that invites the customers into the store – and finally converting to a sale, hence, a responsive design, converged in performance and search engine & app store optimisation is vital to getting users in with the less amount of friction possible.

        Since SEO was a vital requirement for the type of search the company wanted to achieve, the storefronts are using isomorphic React and webpack (since 2015). This allowed us to do performance optimization via caching and mobile-specific code chunks, and a component-based single-page application that is search-engine optimised that only serves the content needed for each context, with a fast and light first-load which is great for mobile. The codebase was split across several microservices, with a very scalable architecture and easily deployed using docker.",
        bigImage,
      ),
      QuoteCard(
        "Culture really trumps everything else.",
        {name: {j|José Neves|j}, title: "Farfetch CEO", avatarImage: joseNevesAvatarImage},
      ),
      BigVideo("https://player.vimeo.com/video/336812660?title=0&byline=0&portrait=0"),
      TextAndVideo("Text example", "https://player.vimeo.com/video/336812660?title=0&byline=0&portrait=0"),
      TextAndImage(
        {j|
        As a result, Glazed created a custom eCommerce CMS, where each tenant could change the look and content of the storefront in real-time.

        The multi-tenant fashion eCommerce store that could host a large feature including Product Collections, Seasons, Campaigns, Search, Browsing, Filtering, Product Recommendation algorithm, Shopping Bag, Favourites, Social interaction, Campaigns, Discounts, Newsletter, Analytics and Boutiques listing.

        All of them integrated with Farfetch internal processes which provided Operations, Payments, Shipping, Billing, Returns and Support. 	
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
