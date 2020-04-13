// import React from 'react'
// import PropTypes from 'prop-types'
// import Helmet from 'react-helmet'
// import { graphql, useStaticQuery } from 'gatsby'
// import PageLayout from 're/PageLayout'
// import GlobalStyles from 'src/styles'

// const Layout = ({ children, useDarkNavBarLinks }) => {
//   const data = useStaticQuery(graphql`
//     query SiteTitleQuery {
//       site {
//         siteMetadata {
//           title
//         }
//       }
//     }
//   `)
//   return (
//     <>
//       <Helmet
//         title={data.site.siteMetadata.title}
//         meta={[
//           {
//             name: 'description',
//             content: 'Static site built with Gatsbyjs, ReasonML, and React.',
//           },
//           { name: 'keywords', content: 'reasonml, bucklescript, react' },
//         ]}
//       >
//       </Helmet>
//       <GlobalStyles />
//       <PageLayout siteTitle={data.site.siteMetadata.title} useDarkNavBarLinks={useDarkNavBarLinks}>
//         {children}
//       </PageLayout>
//     </>
//   )
// }

// Layout.propTypes = {
//   children: PropTypes.node.isRequired,
// }

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

[@react.component]
let make = (~children, ~useDarkNavBarLinks: bool) => {
  let queryResult = Gatsby.useStaticQuery(query);
  <>
    <Helmet title={queryResult##site##siteMetadata##title} content=[|
          {
            name: "description",
            content: "Static site built with Gatsbyjs, ReasonML, and React.",
          },
          { name: "keywords", content: "reasonml, bucklescript, react" },
    |]>
        // <html lang="en" />
        // <link href="https://fonts.googleapis.com/css?family=Muli:400,700&display=swap" rel="stylesheet" />
    <Helmet>
  </>
};

let default = make;