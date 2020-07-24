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
      filipe: file(relativePath: { eq: "team/filipe.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      nuno: file(relativePath: { eq: "team/nuno.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      ismael: file(relativePath: { eq: "team/ismael.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      miguel: file(relativePath: { eq: "team/miguel.png" }) {
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
      figo: file(relativePath: { eq: "team/figo.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      pedro: file(relativePath: { eq: "team/pedro.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      raspa: file(relativePath: { eq: "team/raspa.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      goncalo: file(relativePath: { eq: "team/goncalo.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      jose: file(relativePath: { eq: "team/jose.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      cristiano: file(relativePath: { eq: "team/cristiano.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      joao: file(relativePath: { eq: "team/joao.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      maria: file(relativePath: { eq: "team/maria.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      rick: file(relativePath: { eq: "team/rick.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      torres: file(relativePath: { eq: "team/torres.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      nelson: file(relativePath: { eq: "team/nelson.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      daniela: file(relativePath: { eq: "team/daniela.png" }) {
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
      ~backgroundSize="auto 100%",
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
