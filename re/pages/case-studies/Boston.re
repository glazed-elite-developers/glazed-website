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
     }
  `|}
];

[@react.component]
let make = () => {
  let queryResult = Gatsby.useStaticQuery(pageImagesQuery);
  let headerImage = Gatsby.getImageFluid(queryResult, "headerImage");
  let bigImage = Gatsby.getImageFluid(queryResult, "bigImage");
  let image = Gatsby.getImageFluid(queryResult, "image");

  // Replace the page contents here:
  let content: content = {
    hero: {
      image: headerImage,
      title: "Boston Hospital",
      area: "HealthTech - IoT",
      text: "A bespoke iOS application from the ground up to communicate with iBeacons to correctly display the position of the physician inside the hospital.",
    },
    brief: {
      techs: [|
        {name: "TensorFlow", icon: TechIcons.twitter},
        {name: "iOS", icon: TechIcons.twitter},
        {name: "iBeacons", icon: TechIcons.twitter}
      |],
      year: "2019",
      brief: "We’ve developed a technological solution for physicians to give live updates to their patients concerning their next appointment and even appointments dynamically rescheduling – all using positional tracking, beacons and machine learning capabilities.",
    },
    // We can declare a dynamic list of components here. There are 3 components types currently availablBigImage, TextAndImage and QuoteCard:
    content: [|
      TextAndImage(
        "It’s fairly easy to triangulate geo positions of people or places in the world but as soon as we get walls into the mix that’s when we struggle. The challenge of this project occurs when we want to obtain an accurate position within a building.
Thus, when we were tasked with developing a solution that was able to capture live data from moving targets (physicians), process those inputs into meaningful data and then present back to users we broke it down to the following points:
 Fetch the physician position within the hospital
Manipulate live data points
Deliver results back to the patients
Trigger changes if significant thresholds were reached",
        bigImage,
      ),
           Custom(
        <Heading level=Heading.H2 className=Styles.adHocComponent>
          {React.string("technological solution for physicians live updates using positional tracking, beacons and machine learning capabilities.
")}
        </Heading>,
      ),
      TextAndImage(
        "To capture the most accurate position we’ve used iBeacons connecting to a native iOS application through Bluetooth. 
        Bluetooth low energy (BLE) beacons are a cost-effective way for apps to know the position of a user indoors when other methods like GPS are not available. Beacons emit a signal, and apps can very roughly estimate how far a user is from one beacon, depending on the strength of that signal; or triangulate the user position from several signals. 
        That position estimate is very rough though since physical objects and electronic devices interfere with transmitted signals.", 
        image),
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
