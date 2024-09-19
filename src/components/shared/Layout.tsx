import React from 'react'
import { css } from '@emotion/css'
import { graphql, useStaticQuery } from 'gatsby'
import { useLocation } from '@reach/router'
import { Helmet } from 'react-helmet'
import LogoWithBackgroundJpg from 'static/images/logo_with_background.jpg'
import GlobalStyles from '../../styles/GlobalStyles'

const styles = {
  wrapper: css`
    display: flex;
    flex-direction: column;
    position: relative;
    height: 100%;
    flex: 1 1 0.00000001rem;
  `,
  header: css`
    position: fixed;
    top: 0;
    right: 0;
    left: 0;
  `,
}

const query = graphql`
  query SiteTitleQuery {
    site {
      siteMetadata {
        title
        siteURL
      }
    }
  }
`

const defaultDescription =
  'Glazed is a team of elite web and mobile developers that partner with the world’s leading companies.'

const baseMetaTags = [
  { name: 'keywords', content: 'reasonml, bucklescript, react' },
]

interface Props {
  title?: string
  description?: string
  children?: React.ReactNode
}

const Layout: React.FC<Props> = ({
  title: titleOverride,
  description: descriptionOpt,
  children,
}) => {
  const description = descriptionOpt || defaultDescription
  const { site } = useStaticQuery(query) as any
  const siteURL = site.siteMetadata.siteURL
  const defaultTitle = site.siteMetadata.title
  const location = useLocation()
  const title = titleOverride || defaultTitle

  const metaTags = [
    ...baseMetaTags,
    { name: 'description', content: description },
    { name: 'og:title', content: title },
    { name: 'og:description', content: description },
    { name: 'og:image', content: `${siteURL}${LogoWithBackgroundJpg}` },
    { name: 'og:url', content: `${siteURL}${location.pathname}` },
    { name: 'og:site_name', content: defaultTitle },
    { name: 'twitter:card', content: 'summary_large_image' },
    { name: 'twitter:image:alt', content: 'Glazed logo.' },
  ]

  return (
    <>
      <Helmet title={title} meta={metaTags}>
        <html lang="en" />
        <link href={`${siteURL}${location.pathname}`} rel="canonical" />
      </Helmet>
      <GlobalStyles />
      {children}
    </>
  )
}

export default Layout
