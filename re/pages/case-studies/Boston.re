open CaseStudyPageTemplate;

module Styles = {
  open Css;

  let adHocComponent = style([textAlign(`center)]);
};

let pageImagesQuery = [%raw
  {|Gatsby.graphql`
     query {
       headerImage: file(relativePath: { eq: "case-studies/boston-hero.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 1200, maxHeight: 820) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       bigImage: file(relativePath: { eq: "case-studies/boston-1.png" }) {
         childImageSharp {
           fluid(maxWidth: 800) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       image: file(relativePath: { eq: "case-studies/boston-2.png" }) {
         childImageSharp {
           fluid(maxWidth: 600) {
             ...GatsbyImageSharpFluid
           }
         }
       }
       nextCaseImage: file(relativePath: { eq: "case-studies/lvmh.jpg" }) {
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
  let image = Gatsby.getImageFluid(queryResult, "image");
  let nextCaseImage = Gatsby.getImageFluid(queryResult, "nextCaseImage");
  let content: content = {
    hero: {
      image: headerImage,
      title: "Boston Hospital",
      area: "HealthTech - IoT",
      text: "A bespoke iOS application to display the position of the physician inside the hospital.",
    },
    brief: {
      techs: [|
        {name: "TensorFlow", icon: TechIcons.twitter},
        {name: "iOS", icon: TechIcons.twitter},
        {name: "BLE", icon: TechIcons.twitter},
        {name: "iBeacons", icon: TechIcons.twitter},
      |],
      year: "2019",
      brief: "We've developed a technological solution for physicians to provide live updates to their patients concerning their next appointment, including dynamically rescheduling appointments - all using positional tracking, beacons and machine learning capabilities.",
    },
    content: [|
      TextAndImage(
        {j|
        It's easy to triangulate locations while outdoors, but as soon as we get walls into the mix, the situation changes. This project's main challenge resided in being able to provide the accurate positioning of physicians within the hospital.
            The project's full scope can be broken down into the following main tasks:
            1. Calculate the physician position within the hospital
            2. Manipulate live data points
            3. Deliver results back to the patients
            4. Trigger changes if significant thresholds were reached
        |j},
        bigImage,
      ),
      Custom(
        <Heading level=Heading.H3 className=Styles.adHocComponent>
          {React.string(
             "Technological solution for live updates using positional tracking, beacons and machine learning capabilities.",
           )}
        </Heading>,
      ),
      TextAndImage(
        {j|
        To capture the most accurate position possible we've used iBeacons connected to a native iOS application through Bluetooth.
        Bluetooth low energy (BLE) beacons are a cost-effective way for apps to obtain the device's position while indoors where other methods like GPS are not available. Beacons emit a signal, and apps can roughly estimate how far a user is from them, judging by the strength of that signal; this makes it possible to triangulate the user position from several signals.
        That position estimate is very rough though, since physical objects and electronic devices can interfere with transmitted signals.
        |j},
        image,
      ),
    |],
    nextCase: {
      image: nextCaseImage,
      title: "LVMH",
      area: "Fashion - Chatbots",
      link: "/case-studies/lvmh",
    },
  };

  <CaseStudyPageTemplate content />;
};

let default = make;
