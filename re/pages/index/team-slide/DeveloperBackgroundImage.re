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
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      filipe: file(relativePath: { eq: "team/filipe.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      nuno: file(relativePath: { eq: "team/nuno.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      ismael: file(relativePath: { eq: "team/ismael.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      miguel: file(relativePath: { eq: "team/miguel.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      diogo: file(relativePath: { eq: "team/diogo.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      figo: file(relativePath: { eq: "team/figo.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      pedro: file(relativePath: { eq: "team/pedro.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      raspa: file(relativePath: { eq: "team/raspa.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      goncalo: file(relativePath: { eq: "team/goncalo.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      jose: file(relativePath: { eq: "team/jose.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      cristiano: file(relativePath: { eq: "team/cristiano.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      joao: file(relativePath: { eq: "team/joao.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      maria: file(relativePath: { eq: "team/maria.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      rick: file(relativePath: { eq: "team/rick.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      torres: file(relativePath: { eq: "team/torres.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      nelson: file(relativePath: { eq: "team/nelson.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      daniela: file(relativePath: { eq: "team/daniela.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
          }
        }
      }
      overlay: file(relativePath: { eq: "team/overlay.png" }) {
        childImageSharp {
          fluid(maxWidth: 1000) {
            ...GatsbyImageSharpFluid_noBase64
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
