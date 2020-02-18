import React from 'react'
import PropTypes from 'prop-types'
import Helmet from 'react-helmet'
import { StaticQuery, graphql } from 'gatsby'
import { Global, css } from '@emotion/core'
import PageLayout from 're/PageLayout'
import Header from 're/Header'
import Index from 're/Index'
import GlobalStyles from 'src/styles'
import { MediaContextProvider } from './mediaContext'

const Layout = ({ children, useDarkNavBarLinks }) => (
  <StaticQuery
    query={graphql`
      query SiteTitleQuery {
        site {
          siteMetadata {
            title
          }
        }
      }
    `}
    render={data => (
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
          <link
            href="https://fonts.googleapis.com/css?family=Muli:400,700&display=swap"
            rel="stylesheet"
          />
        </Helmet>
        <GlobalStyles />

        <PageLayout
          siteTitle={data.site.siteMetadata.title}
          useDarkNavBarLinks={useDarkNavBarLinks}
        >
          {children}
        </PageLayout>
      </>
    )}
  />
)

Layout.propTypes = {
  children: PropTypes.node.isRequired,
}

export default Layout
