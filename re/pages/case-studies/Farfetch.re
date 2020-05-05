open CaseStudyPageTemplate;

module Styles = {
  open Css;

  let adHocComponent = style([textAlign(`center)]);
};

let pageImagesQuery = [%raw
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

[@react.component]
let make = () => {
  let queryResult = Gatsby.useStaticQuery(pageImagesQuery);
  let headerImage = Gatsby.getImageFluid(queryResult, "headerImage");
  let bigImage = Gatsby.getImageFluid(queryResult, "headerImage");
  let joseNevesAvatarImage = Gatsby.getImageFluid(queryResult, "joseNeves");

  // Replace the page contents here:
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
This project, called black-and-white, was the main strategic move the company made after being valued at $1b dollars and the first clients to use it was Manolo Blahnik and Rihanna.",
    },
    // We can declare a dynamic list of components here. There are 3 components types currently available: BigImage, TextAndImage and QuoteCard:
    content: [|
      BigImage(bigImage),
      TextAndImage(
        "We built the storefront using isomorphic React and webpack, which allowed to build a component-based single-page application that is search-engine optimised, and that only servers the content needed for each context, with a fast and light first-load which is great for mobile. Our codebase was split across several micro services, with a very scalable architecture, easy to deploy using docker.",
        bigImage,
      ),
      QuoteCard(
        "Glazed built a multi-tenant fashion eCommerce store, with a large feature set:  Product Collections, Seasons, Campaigns, Search, Browsing, Filtering, Product Recommendation algorithm, Shopping Bag, Favourites, Social interaction, Campaigns, Discounts, Newsletter, Analytics, Boutiques listing.
All was integrated with Farfetch internal processes which provided Operations, Payments, Shipping, Billing, Returns and Support.",
        {
          name: {j|José Neves|j},
          title: "Farfetch CEO",
          avatarImage: joseNevesAvatarImage,
        },
      ),
      // We can also use custom components if we need something ad hoc:
      Custom(
        <Heading level=Heading.H1 className=Styles.adHocComponent>
          {React.string("This is a custom component")}
        </Heading>,
      ),
      TextAndImage(
        "The storefront is using isomorphic ( because SEO was vital for the type of search that the company wanted to achieve and performance optimization via caching and mobile-specific code chunks) 
React and webpack (using since ‘15), which allowed building a component-based single-page application that is search-engine optimised, and that only serves the content needed for each context, with a fast and light first-load which is great for mobile. Our codebase was split across several microservices, with a very scalable architecture, easy to deploy using docker.",
        bigImage,
      ),
    |],
    nextCase: {
      image: bigImage,
      title: "Switch",
      area: "Fashion - Ecommerce",
      link: "/",
    },
  };

  <CaseStudyPageTemplate content />;
};

let default = make;
