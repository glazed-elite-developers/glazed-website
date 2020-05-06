open Utils.React;

module Styles = {
  open Css;

  let wrapper = style([position(`relative)]);
  let backgroundImage =
    style([position(`absolute), top(`zero), right(`zero), bottom(`zero), left(`zero)]);
};

let backgroundImageQuery = [%raw
  {|Gatsby.graphql`
    query {
      matias: file(relativePath: { eq: "team/matias.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      diogo: file(relativePath: { eq: "team/diogo.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      overlay: file(relativePath: { eq: "team/overlay.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
    }
  `|}
];

[@react.component]
let make =
    (
      ~developerPhotoKey: string,
      ~className=?,
      ~gatsbyBackgroundImageClassName=?,
      ~children=?,
      ~style=?,
    ) => {
  let queryResult = Gatsby.useStaticQuery(backgroundImageQuery);
  let backgroundImage = Gatsby.getImageFluid(queryResult, developerPhotoKey);
  let baseStyle =
    ReactDOMRe.Style.make(
      ~position="absolute",
      ~marginTop="10%",
      ~backgroundPosition="top center",
      (),
    );
  let backgroundImageStyle =
    switch (style) {
    | None => baseStyle
    | Some(style) => ReactDOMRe.Style.combine(baseStyle, style)
    };

  <div className=?{combineClassNames([Some(Styles.wrapper), className])}>
    <Gatsby.BackgroundImage
      className=?{
        combineClassNames([Some(Styles.backgroundImage), gatsbyBackgroundImageClassName])
      }
      ?children
      fluid=?backgroundImage
      style=backgroundImageStyle
    />
  </div>;
};
