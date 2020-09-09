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
       bigImage: file(relativePath: { eq: "case-studies/farfetch-01.png" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       productImage2: file(relativePath: { eq: "case-studies/farfetch-02.png" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 800) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       productImage3: file(relativePath: { eq: "case-studies/farfetch-03.png" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 800) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       productImage4: file(relativePath: { eq: "case-studies/farfetch-04.png" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 800) {
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
  let productImage2 = Gatsby.getImageFluid(queryResult, "productImage2");
  let productImage3 = Gatsby.getImageFluid(queryResult, "productImage3");
  let productImage4 = Gatsby.getImageFluid(queryResult, "productImage4");
  let nextCaseImage = Gatsby.getImageFluid(queryResult, "nextCaseImage");
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
        {name: "react", icon: TechIcons.react},
        {name: "angular", icon: TechIcons.angular},
        {name: "ios", icon: TechIcons.apple},
      |],
      year: "2019",
      brief: "Farfetch asked Glazed to create a white label version of their main e-commerce site for big brands that want to sell on their own website.
      This project, called black-and-white, was the main strategic move the company made after being valued at $1b dollars and the first clients to use it were Manolo Blahnik and Rihanna.",
    },
    content: [|
      BigImage(productImage3),
      TextAndImage(
        {j|
        There are many ways to optimise the conversion funnel, yet the bottom line is to invite customers into the store and convert a sale with the minimum amount of friction possible.

Therefore, a responsive design solution, converged in performance with search engine and app store optimisation was vital. 

Since SEO was an essential requirement for the type of search the company wanted to achieve, we implemented an isomorphic React storefront with webpack. This allowed us to do performance optimization via caching and mobile-specific code chunks, and a component-based single-page application that is search-engine optimised that only serves the content needed for each context, with a fast and light first-load which is great for mobile. 

Considering the codebase was split across several microservices with a very scalable architecture it allowed us to easily deploy via docker. 
        |j},
        productImage4,
      ),
      QuoteCard(
        "Culture really trumps everything else.",
        {
          name: {j|José Neves|j},
          title: "Farfetch CEO",
          avatarImage: joseNevesAvatarImage,
        },
      ),
      BigVideo("https://player.vimeo.com/video/336812660?title=0&byline=0&portrait=0"),
      TextAndVideo("Text example", "https://player.vimeo.com/video/336812660?title=0&byline=0&portrait=0"),
      TextAndImage(
        {j|
        As a result, Glazed created a custom eCommerce CMS, where each tenant could change the look and content of the storefront in real-time.

        The multi-tenant fashion eCommerce store that could host a large feature including Product Collections, Seasons, Campaigns, Search, Browsing, Filtering, Product Recommendation algorithm, Shopping Bag, Favourites, Social interaction, Campaigns, Discounts, Newsletter, Analytics and Boutiques listing.

        All of them integrated with Farfetch internal processes which provided Operations, Payments, Shipping, Billing, Returns and Support.
        |j},
        productImage2,
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
