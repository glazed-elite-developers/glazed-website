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
       bigImage: file(relativePath: { eq: "case-studies/lvmh-1.png" }) {
         childImageSharp {
           fluid(maxWidth: 600, maxHeight: 420) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       solutionImage: file(relativePath: { eq: "case-studies/lvmh-2.png" }) {
         childImageSharp {
           fluid(maxWidth: 600, maxHeight: 420) {
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
  let solutionImage = Gatsby.getImageFluid(queryResult, "solutionImage");
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
        {name: "Google Assistant", icon: TechIcons.twitter},
        {name: "Alexa Skills", icon: TechIcons.twitter},
        {name: "IBM Watson Assistant", icon: TechIcons.twitter},
        {name: "Dialogflow", icon: TechIcons.twitter},
        {name: "Elixir", icon: TechIcons.twitter},
      |],
      year: "2016 - 2020",
      brief: {j|Develop a conversational solution to engage and create personalised experiences for customers.|j},
    },
    content: [|
      TextAndImage(
        {j|We wanted to hit the floor running, as such, we looked for the best 3rd party services that would be able to aids with NLU (Natural Language Understanding) and dialogue handling to provide customers with valuable, engaging and bespoke experiences.

At the time, Facebook Messenger was the most used and complete service, and since we wanted to validate our design approach this was a good option to develop our first chatbots. As we learned more about the technology and the requirements evolved, we ended up building our own dialogue engine. 

Over time we started focusing more on customer service use cases as it represented the higher value for our customers. This include: 
  • Integrating live chat support and handover
  • Improve flows for acting as the first line of customer service/triage or cope with customer centre’s out of hours schedules
  • Handle user data gathering and GDPR compliance 

.|j},
        bigImage,
      ),
      Custom(
        <Heading level=Heading.H3 className=Styles.inPageHeading>
          {React.string(
              {j|With each project the baseline for the project’s NLU understanding was better than the last, and all projects were constantly improving from an always growing shared pool of examples obtained from not only training but also real chats.|j},
           )}
        </Heading>,
      ),
      TextAndImage(
        {j| Ownership of the dialogue engine allowed us to extend it to fully support live chat with seamless human handover, including companion features, quickly and effectively without compromising on our UX, which would otherwise have been impossible.  
        
        Over time, we’ve grown our channel support to include: 
        • Facebook Messenger
        • WhatsApp
        • WeChat
        • Google Assistant
        • Alexa
        • Web Pages (chat widget)
        • Slack
        
        And we also integrated with multiple third-party services, including:
        • Salesforce
        • Human handover & live chat
        • Appointment booking services
        • Image recognition based product recommendation services
        |j},
        solutionImage,
      ),
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
