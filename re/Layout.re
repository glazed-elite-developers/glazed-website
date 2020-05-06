module GlobalStyles = {
  [@react.component] [@bs.module "src/styles"] external make: unit => React.element = "default";
};

module Styles = {
  open Css;

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      position(`relative),
      height(pct(100.)),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
    ]);
  let header = style([position(`fixed), top(`zero), right(`zero), left(`zero)]);
};

// @TODO: refactor following this idea: https://stackoverflow.com/questions/55122752/reusable-gatsby-image-component-with-dynamic-image-sources
let query = [%raw
  {|Gatsby.graphql`
    query SiteTitleQuery {
      site {
        siteMetadata {
          title
        }
      }
    }
  `|}
];

let metaTags: array(Helmet.metaTag) = [|
  {"name": "description", "content": "Static site built with Gatsbyjs, ReasonML, and React."},
  {"name": "keywords", "content": "reasonml, bucklescript, react"},
|];

[@react.component]
let make =
  React.memo((~children) => {
    let queryResult = Gatsby.useStaticQuery(query);
    <>
      <Helmet title={queryResult##site##siteMetadata##title} meta=metaTags>
        <html lang="en" />
        <link
          href="https://fonts.googleapis.com/css?family=Muli:400,700&display=swap"
          rel="stylesheet"
        />
      </Helmet>
      <GlobalStyles />
      children
    </>;
  });

let default = make;
