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
       headerImage: file(relativePath: { eq: "placeholder-hero.png" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid_withWebp_noBase64
           }
         }
       }
       bigImage: file(relativePath: { eq: "placeholder.png" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid_withWebp_noBase64
           }
         }
       }
       productImage2: file(relativePath: { eq: "placeholder.png" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid_withWebp_noBase64
           }
         }
       }
       productImage4: file(relativePath: { eq: "placeholder.png" }) {
         childImageSharp {
           fluid(maxWidth: 1200) {
             ...GatsbyImageSharpFluid_withWebp_noBase64
           }
         }
       }
       joseNeves: file(relativePath: { eq: "placeholder.png" }) {
         childImageSharp {
           fluid(maxWidth: 120) {
             ...GatsbyImageSharpFluid_withWebp_noBase64
           }
         }
       }
       nextCaseImage: file(relativePath: { eq: "case-studies/lvmh-hero.jpg" }) {
         childImageSharp {
           fluid(maxWidth: 2400) {
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
  let productImage2 = Gatsby.getImageFluid(queryResult, "productImage2");
  let productImage4 = Gatsby.getImageFluid(queryResult, "productImage4");
  let nextCaseImage = Gatsby.getImageFluid(queryResult, "nextCaseImage");
  let content: content = {
    hero: {
      image: headerImage,
      title: "Pasabi",
      area: "AI Analytics",
      text: "",
    },
    brief: {
      techs: [|
        {name: "react", icon: TechIcons.generic},
        {name: "angular", icon: TechIcons.generic},
        {name: "ios", icon: TechIcons.generic},
      |],
      year: "2022",
      brief: "Enabling online marketplaces, platforms, communities and brands to make their digital platforms safer, more authentic, trusted places."
    },
    content: [|
      BigImage(bigImage),
      TextAndImage(
        {j|Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce eget elit ultricies mi malesuada sodales. Nam vitae augue eu orci auctor malesuada sit amet at elit. Maecenas eu bibendum erat. Etiam ac est purus. Proin condimentum ultrices mollis. Donec viverra tellus nec mi semper, vitae dictum turpis feugiat. Maecenas non hendrerit diam. Quisque sapien turpis, consequat et dolor sit amet, rutrum mollis libero. Suspendisse bibendum risus non feugiat pharetra. Suspendisse quis quam eu arcu sagittis pretium. Fusce ac nunc in magna accumsan consequat.|j},
        productImage4,
      ),
      Custom(
        <Heading level=Heading.H3 className=Styles.inPageHeading>
          {React.string(
              {j|Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce eget elit ultricies mi malesuada sodales. Nam vitae augue eu orci auctor malesuada sit amet at elit. Maecenas eu bibendum erat. Etiam ac est purus. Proin condimentum ultrices mollis.|j},
           )}
        </Heading>,
      ),
      TextAndImage(
        {j|Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce eget elit ultricies mi malesuada sodales. Nam vitae augue eu orci auctor malesuada sit amet at elit. Maecenas eu bibendum erat. Etiam ac est purus. Proin condimentum ultrices mollis. Donec viverra tellus nec mi semper, vitae dictum turpis feugiat. Maecenas non hendrerit diam. Quisque sapien turpis, consequat et dolor sit amet, rutrum mollis libero. Suspendisse bibendum risus non feugiat pharetra. Suspendisse quis quam eu arcu sagittis pretium. Fusce ac nunc in magna accumsan consequat.|j},
        productImage2,
      ),
    |],
    nextCase: {
      image: nextCaseImage,
      title: "LVMH",
      area: "Fashion - Chatbots",
      link: "/case-studies/lvmh",
    },
  };

  <CaseStudyPageTemplate
    pageTitle="Glazed • Pasabi"
    pageDescription="Lorem ipsum dolor sit amet, consectetur adipiscing elit."
    content
  />;
};

let default = make;
