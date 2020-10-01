[@bs.module "static/images/logo_with_background.jpg"]
external logoWithBackgrund: string = "default";

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

let query = [%raw
  {|Gatsby.graphql`
    query SiteTitleQuery {
      site {
        siteMetadata {
          title,
          siteURL
        }
      }
    }
  `|}
];

let defaultDescription = {j|Glazed is a team of elite web and mobile developers that partner with the world’s leading companies.|j};

let baseMetaTags: array(Helmet.metaTag) = [|
  {"name": "keywords", "content": "reasonml, bucklescript, react"},
|];

[@react.component]
let make =
  React.memo((~title as titleOverride=?, ~description=defaultDescription, ~children) => {
    let queryResult = Gatsby.useStaticQuery(query);
    let siteURL = queryResult##site##siteMetadata##siteURL;
    let defaultTitle = queryResult##site##siteMetadata##title;
    let location: Routing.location = Routing.useLocation();
    let title = Belt.Option.getWithDefault(titleOverride, defaultTitle);
    let meta =
      Belt.Array.concat(
        baseMetaTags,
        [|
          {"name": "description", "content": description},
          {"name": "og:title", "content": title},
          {"name": "og:description", "content": description},
          {"name": "og:image", "content": siteURL ++ logoWithBackgrund},
          {"name": "og:url", "content": siteURL ++ location.pathname},
          {"name": "og:site_name", "content": defaultTitle},
          {"name": "twitter:card", "content": "summary_large_image"},
          {"name": "twitter:image:alt", "content": "Glazed logo."},
        |],
      );

    <>
      <Helmet title meta>
        <html lang="en" />
        <link
          href="https://fonts.googleapis.com/css?family=Muli:400,700&display=swap"
          rel="stylesheet"
        />
        <link rel="canonical" href={siteURL ++ location.pathname} />
      </Helmet>
      <GlobalStyles />
      children
    </>;
  });

let default = make;
