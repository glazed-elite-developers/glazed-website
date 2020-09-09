open CaseStudyPageTemplate;

module Styles = {
  open Css;

  let adHocComponent = style([textAlign(`center)]);
};

let pageImagesQuery = [%raw
  {|Gatsby.graphql`
     query {
       headerImage: file(relativePath: { eq: "case-studies/switch-hero.png" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 820) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       bigImage: file(relativePath: { eq: "case-studies/switch-1.png" }) {
         childImageSharp {
           fluid(maxWidth: 800) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       productImage: file(relativePath: { eq: "case-studies/switch-2.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 800) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       productImage2: file(relativePath: { eq: "case-studies/switch-5.png" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 800) {
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
  let productImage = Gatsby.getImageFluid(queryResult, "productImage");
  let productImage2 = Gatsby.getImageFluid(queryResult, "productImage2");
  let nextCaseImage = Gatsby.getImageFluid(queryResult, "nextCaseImage");
  let content: content = {
    hero: {
      image: headerImage,
      title: "Switch",
      area: "FinTech - Payments",
      text: "Switch Payments connects the entire payments value chain through a single software platform.",
    },
    brief: {
      techs: [|
        {name: "angular", icon: TechIcons.angular},
        {name: "nodeJS", icon: TechIcons.nodejs},
        {name: "django", icon: TechIcons.generic},
        {name: "java", icon: TechIcons.generic},
        {name: "objective c", icon: TechIcons.apple},
        {name: "php", icon: TechIcons.generic},
        {name: "docker", icon: TechIcons.generic},
      |],
      year: "2020",
      brief: {j|Switch Payments was founded by Glazed team members and spun off to become one of the world’s leading Payment companies.|j},
    },
    content: [|
      TextAndImage(
        {j|
        Glazed has a lot of experience in building MVPs and innovative products.

        From conception to seed rounds, from seed to series A, all the way up to IPOs Glazed dealt with the technical challenges startups go through.
        Building Switch put all that experience to the test.

        Switch’s founding story is also a testament to Glazed team members expertise in creating highly complex and demanding software for areas like Fintech, where stability and security are critical.
        
        Switch Payments was incubated at Glazed when its core payment abstraction evolved from processing credit cards to supporting every payment method existent in the industry.
        |j},
        productImage,
      ),
      TextAndImage(
        {j|
        Switch offers access to every payment method, POS terminal, financial institution, and third-party risk provider, as well as the most modern payment management tools to improve acceptance rates, processing fees, security, dynamic routing, reconciliation, and reporting.
        
        Different payment methods and payment providers have different usability flows, possibly going through multiple steps to collect authentication data and capture funds, requiring offline actions by the customer or redirecting to payment providers’ web pages, and having synchronous or asynchronous responses.

        Dealing with all these flows is a nightmare for merchants, and so a single abstraction and integration flow was conceived to support all of them.
        |j},
        bigImage,
      ),
      TextAndImage(
        {j|
        To make things simpler for merchants, this abstraction was then made available via REST and Real-time APIs, as well as SDKs in several frontends, backend and native mobile programming languages. We also developed Switch’s initial website and technical documentation platforms.
        
        Payments are a very critical part of any business, and their stability has a direct impact on sales, therefore it was especially important to have a performant, highly-available and resistant micro-services architecture.

        Security requirements were also at the highest level, and we had to integrate with numerous banks, financial institutions, and comply with the corresponding security requirements. This included going through the PCI DSS certifications and implementing highly secure infrastructure, communications, and software development practices.
        |j},
        productImage2,
      ),
    |],
    nextCase: {
      image: nextCaseImage,
      title: "Boston Hospital",
      area: "HealthTech - IoT",
      link: "/case-studies/boston",
    },
  };

  <CaseStudyPageTemplate content />;
};

let default = make;
