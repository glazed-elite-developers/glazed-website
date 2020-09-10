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
       nextCaseImage: file(relativePath: { eq: "case-studies/lvmh-hero.jpg" }) {
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
      brief: {j|
      We've developed a technological solution for physicians to provide live updates to their patients concerning their next appointment, including dynamically rescheduling appointments - all using positional tracking, beacons and machine learning capabilities.
      |j},
    },
    content: [|
      TextAndVideo({j|
        It's easy to triangulate locations while outdoors, but as soon as we get walls into the mix, the situation changes. 
        
        This project's main challenge resided in being able to provide the accurate positioning of physicians within the hospital, hence, we needed to be able to accurately calculate the physician position within the hospital. This meant to be able to manage live data points that would deliver results back to the patients and then if required, trigger changes.
        |j}, 
        "https://player.vimeo.com/video/455760404?autoplay=1&muted=1"),
         Custom(
        <Heading level=Heading.H3 className=Styles.inPageHeading>
          {React.string(
              {j|We were able to identify scheduling problems and provide staff and patients with on-time feedback.|j},
           )}
        </Heading>,
      ),
      TextAndImage(
        {j|
        To capture the most accurate position possible we've used iBeacons connected to a native iOS application through Bluetooth.
 
Bluetooth low energy (BLE) beacons are a cost-effective way for apps to obtain the device's position while indoors where other methods like GPS are not available. 

Through the strength of the signal beacons emit, apps can roughly estimate how far a user is from them and be able to triangulate the user position from several signals.
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
