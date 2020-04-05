let backgroundImageQuery = [%raw
  {|Gatsby.graphql`
    query {
      carlosMatias: file(relativePath: { eq: "team/CarlosMatias.png" }) {
        childImageSharp {
          fluid(maxWidth: 200) {
            ...GatsbyImageSharpFluid
          }
        }
      }
    }
  `|}
];

[@react.component]
let make = (~developerPhotoKey: string, ~className=?) => {
  let queryResult = Gatsby.useStaticQuery(backgroundImageQuery);
  let backgroundImage = Gatsby.getImageFluid(queryResult, developerPhotoKey);

  <Gatsby.BackgroundImage
    ?className
    fluid=backgroundImage
    style={ReactDOMRe.Style.make(~position="absolute", ())}
  />;
};