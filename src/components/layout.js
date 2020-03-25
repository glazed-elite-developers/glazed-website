import React from 'react'
import PropTypes from 'prop-types'
import Helmet from 'react-helmet'
import { graphql, useStaticQuery } from 'gatsby'
import PageLayout from 're/PageLayout'
import GlobalStyles from 'src/styles'

const Layout = ({ children, useDarkNavBarLinks }) => {
  const data = useStaticQuery(graphql`
    query SiteTitleQuery {
      site {
        siteMetadata {
          title
        }
      }
    }
  `)
  return (
    <>
      <Helmet
        title={data.site.siteMetadata.title}
        meta={[
          {
            name: 'description',
            content: 'Static site built with Gatsbyjs, ReasonML, and React.',
          },
          { name: 'keywords', content: 'reasonml, bucklescript, react' },
        ]}
      >
        <html lang="en" />
        <link href="https://fonts.googleapis.com/css?family=Muli:400,700&display=swap" rel="stylesheet" />
      </Helmet>
      <GlobalStyles />
      <PageLayout siteTitle={data.site.siteMetadata.title} useDarkNavBarLinks={useDarkNavBarLinks}>
        {children}
      </PageLayout>
    </>
  )
}

Layout.propTypes = {
  children: PropTypes.node.isRequired,
}

export default Layout
