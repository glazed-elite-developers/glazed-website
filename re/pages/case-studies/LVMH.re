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
};

let pageImagesQuery = [%raw
  {|Gatsby.graphql`
     query {
       headerImage: file(relativePath: { eq: "case-studies/lvmh-hero.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 820) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       bigImage: file(relativePath: { eq: "case-studies/LVMH001.jpeg" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       productImage: file(relativePath: { eq: "case-studies/LVMH002.jpeg" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 800) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       productImage2: file(relativePath: { eq: "case-studies/LVMH003.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       productImage3: file(relativePath: { eq: "case-studies/LVMH004.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 800) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       productImage4: file(relativePath: { eq: "case-studies/LVMH005.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       nextCaseImage: file(relativePath: { eq: "case-studies/farfetch-header.jpg" }) {
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
  let productImage3 = Gatsby.getImageFluid(queryResult, "productImage3");
  let productImage4 = Gatsby.getImageFluid(queryResult, "productImage4");
  let nextCaseImage = Gatsby.getImageFluid(queryResult, "nextCaseImage");
  let content: content = {
    hero: {
      image: headerImage,
      title: "LVMH",
      area: "Fashion - Chatbots",
      text: {j|Moët Hennessy Louis Vuitton is a French multinational corporation and conglomerate specializing in luxury goods.|j},
    },
    brief: {
      techs: [|
        {name: "Google Assistant", icon: TechIcons.generic},
        {name: "Alexa Skills", icon: TechIcons.generic},
        {name: "IBM Watson Assistant", icon: TechIcons.generic},
        {name: "Dialogflow", icon: TechIcons.generic},
        {name: "Elixir", icon: TechIcons.generic},
      |],
      year: "2016 - 2020",
      brief: {j|Develop a conversational solution to engage and create personalised experiences for customers.|j},
    },
    content: [|
    BigImage(productImage2),
      TextAndImage(
        {j|We wanted to hit the floor running, as such, we looked for the best third party services that would be able to aid us with NLU (Natural Language Understanding) and dialogue handling to provide customers with valuable, engaging and bespoke experiences.

      At the time, Facebook Messenger was the most used and complete service, and since we wanted to validate our design approach this was a good option to develop our first chatbots. As we learned more about the technology and the requirements evolved, we ended up building our own dialogue engine.
      |j},
        bigImage,
      ),
      Custom(
        <Heading level=Heading.H3 className=Styles.inPageHeading>
          {React.string(
              {j|The project’s NLU understanding was constantly improving from an always growing shared pool of examples obtained from not only training but also real chats.|j},
           )}
        </Heading>,
      ),
      TextAndImage(
        {j| 
        Ownership of the dialogue engine allowed us to extend it to fully support live chat with the seamless human handover, including companion features, quickly and effectively without compromising on our UX, which would otherwise have been impossible. Plus, we developed tools to facilitate NLU training, reusability, deployment and become service agnostic.        
      
        From here we started focusing more on service use cases, handling user data gathering and GDPR compliance, improving flows to act as the first line of customer triage and also to cope with customer centres out of hours schedules. 
        |j},
        productImage,
      ),
      TextAndImage(
        {j|
        
        Over time we’ve grown our channel support to Facebook Messenger, WhatsApp, WeChat, Google Assistant, Alexa, Web Pages (chat widget) and Slack. 
        
        We also integrated with multiple third-party services like Salesforce, added human handover with live chat, booking appointments and even image recognition based product recommendation services.

        |j},
        productImage4,
      ),
      BigVideo("https://player.vimeo.com/video/455530260?autoplay=1&muted=1"),
    |],
    nextCase: {
      image: nextCaseImage,
      title: "Farfetch",
      area: "Fashion - Ecommerce",
      link: "/case-studies/farfetch",
    },
  };

  <CaseStudyPageTemplate content />;
};

let default = make;
