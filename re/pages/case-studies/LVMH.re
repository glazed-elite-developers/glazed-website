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
       headerImage: file(relativePath: { eq: "case-studies/lvmh.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 820) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       bigImage: file(relativePath: { eq: "case-studies/lvmh.jpg" }) {
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
  let bigImage = Gatsby.getImageFluid(queryResult, "headerImage");
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
        {name: "Node.js", icon: TechIcons.twitter},
        {name: "Google Assistant", icon: TechIcons.twitter},
        {name: "Alexa Skills", icon: TechIcons.twitter},
        {name: "IBM Watson Assistant", icon: TechIcons.twitter},
        {name: "Dialogflow", icon: TechIcons.twitter},
        {name: "Elixir", icon: TechIcons.twitter},
        {name: "React", icon: TechIcons.twitter},
      |],
      year: "2020",
      brief: {j|The goal was to leverage conversational technologies and NLU (Natural Language Understanding) to provide customers with valuable, engaging and personalised experiences available 24/7 through the messaging and voice channels they already use.|j},
    },
    content: [|
      TextAndImage(
        {j|We focused on getting off the ground quickly, by integrating with the best available 3rd party services for our core needs, including the NLU and Dialogue handling, where we started by integrating with IBM Watson. We also started by developing the connector for Facebook Messenger, which was the most used and complete service at the time, to validate our design approach and develop our first chatbots. As we learned more about the technology and as our requirements for new projects evolved, we ended up building our own dialogue engine. This allowed us to push the boundaries on this front, delivering new features to our customers and responding quickly to feature requests. An example was when we were asked to integrate a live chat with human handover seamlessly into our chatbot experience for a project. Ownership of the dialogue engine allowed us to extend it to fully support this feature, including companion features, quickly and effectively without compromising on our UX, which would otherwise have been impossible.
.|j},
        bigImage,
      ),
      Custom(
        <Heading level=Heading.H2 className=Styles.inPageHeading>
          {React.string(
             {j|We built a modular chatbot platform following a driver-based approach for the main components|j},
           )}
        </Heading>,
      ),
      BigImage(bigImage),
      TextAndImage(
        {j|Each project that we did the baseline for each project’s NLU understanding was better than the last and that all projects were constantly evolving and improving from an always growing shared pool of examples obtained from not only training but also real chats. A smart variable replacement system also allowed us to more easily reuse examples for multiple projects with similar needs but different contexts (e.g. booking an appointment on a hairdresser or on a cosmetics store).|j},
        bigImage,
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
