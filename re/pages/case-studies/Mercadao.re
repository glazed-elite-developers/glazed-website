open CaseStudyPageTemplate;

module Styles = {
  open Css;

  let inPageHeading =
    style([
      textAlign(`center),
      maxWidth(rem(64.)),
      padding2(~h=rem(1.875), ~v=`zero),
      margin(`auto),
      color(hex(Theme.Colors.grey)),
    ]);

  let adHocComponent = style([textAlign(`center)]);
};

let pageImagesQuery = [%raw
  {|Gatsby.graphql`
     query {
       headerImage: file(relativePath: { eq: "case-studies/mercadao-hero.jpg" }) {
         childImageSharp {
            fluid(maxWidth: 2400) {
             ...GatsbyImageSharpFluid_withWebp_noBase64
           }
         }
       }
       bigImage: file(relativePath: { eq: "case-studies/mercadao-big.png" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid_withWebp_noBase64
           }
         }
       }
       productImage1: file(relativePath: { eq: "case-studies/mercadao-01.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid_withWebp_noBase64
           }
         }
       }
       productImage2: file(relativePath: { eq: "case-studies/mercadao-02.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid_withWebp_noBase64
           }
         }
       }
       productImage3: file(relativePath: { eq: "case-studies/mercadao-03.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid_withWebp_noBase64
           }
         }
       }
       goncaloSoares: file(relativePath: { eq: "case-studies/goncalo-soares-da-costa.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 120) {
             ...GatsbyImageSharpFluid_withWebp_noBase64
           }
         }
       }
       nextCaseImage: file(relativePath: { eq: "case-studies/boston-hero.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid_withWebp_noBase64
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
  let productImage1 = Gatsby.getImageFluid(queryResult, "productImage1");
  let productImage2 = Gatsby.getImageFluid(queryResult, "productImage2");
  let productImage3 = Gatsby.getImageFluid(queryResult, "productImage3");
  let quoteAvatarImage = Gatsby.getImageFluid(queryResult, "goncaloSoares");
  let nextCaseImage = Gatsby.getImageFluid(queryResult, "nextCaseImage");
  let content: content = {
    hero: {
      image: headerImage,
      title: {j|Mercadão|j},
      area: "Marketplace - Ecommerce",
      text: {j|Mercadão is the first on-demand marketplace in Portugal, introducing 2-hour deliveries from a variety of retailers.|j},
    },
    brief: {
      techs: [|
        {name: "react", icon: TechIcons.generic},
        {name: "docker", icon: TechIcons.generic},
        {name: "node", icon: TechIcons.generic},
        {name: "aws", icon: TechIcons.generic},
      |],
      year: "2020",
      brief: "Provide an overall performance upgrade to their service, integrate a new payment's journey and improve the website response.",
    },
    content: [|
      TextAndImage(
        {j|
          As one of the top online food and essential goods retailers in Portugal, Mercadão saw a rapid increase in usage as the Pandemic evolved.

          This unforeseen growth brought new scalability challenges that Glazed tackled by revamping the existing infrastructure, implementing auto-scaling strategies, as well as disaster protection and recovery policies.

          Many tasks, such as an in-depth analysis and improvement of the query execution times, had been performed while keeping the platform up and running, allowing the customers to continue their shopping experience uninterrupted.
|j},
        bigImage,
      ),
      Custom(
        <Heading level=Heading.H3 className=Styles.inPageHeading>
          {React.string(
              {j|Ever since we teamed-up with Mercadão, we've tackled top priorities without undermining the shopper's experience.|j},
           )}
        </Heading>,
      ),
      TextAndImage(
        {j|
        The Click & Collect service, which allows customers to shop online and choose a specific pick-up store, mitigated some of the Pandemic's strain on the delivery logistics.

        For that reason, we've created an API for third party usage, empowering the partner brands with Mercadão's catalogue of advanced features such as:
        • Failover mechanisms spread over multiple availability zones
        • Improved service quality and response time backed by automatic CPU based machine scaling
        • Integrated the payments journey with SIBS, including the MBway mobile service

|j},
        productImage3,
      ),
      QuoteCard(
      {j|
      Top-notch development at Glazed allowed Mercadão to leverage on massive demand growth with confidence.
      Plus: they're great people to work with.
      |j},

      {name: {j|Gonçalo Soares da Costa|j}, title: {j|Mercadão CEO|j}, avatarImage: quoteAvatarImage},
      ),
       TextAndImage(
        {j|
        In less than a year working with Mercadão, we can confidently state that business processes are now faster, more reliable, and overall infrastructure resource consumption has decreased.

        All those changes have translated into a smoother user experience, an increase of MAU's and since January 2020, there has been a daily delivery increase of more than 20x.

        All-in-all, our combined effort created one of the top players in the Portuguese online retail maket.

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

  <CaseStudyPageTemplate
    pageTitle={j|Glazed • Mercadão|j}
    pageDescription={j|Mercadão is the first on-demand marketplace in Portugal, introducing 2-hour deliveries from a variety of retailers.|j}
    content
  />;
};

let default = make;
