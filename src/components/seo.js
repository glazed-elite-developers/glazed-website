import React from 'react'
import PropTypes from 'prop-types'
import Helmet from 'react-helmet'
import { StaticQuery, graphql } from 'gatsby'

import defaultLogo from '../../static/images/logo-glazed-small.png'

function SEO({ description, lang, meta, title, image, imageAlt, pathname, postData }) {
  return (
    <StaticQuery
      query={SEOQuery}
      render={data => {
        const metaDescription = description || data.site.siteMetadata.description
        const metaImage = `${data.site.siteMetadata.siteURL}${image || defaultLogo}`
        const metaUrl = `${data.site.siteMetadata.siteURL}${pathname}`

        const schemaOrgJSONLD = [
          {
            '@context': 'http://schema.org',
            '@type': 'WebSite',
            url: metaUrl,
            name: title,
            alternateName: `${data.site.siteMetadata.title} ${data.site.siteMetadata.description}`,
          },
        ]

        if (postData) {
          schemaOrgJSONLD.push({
            '@context': 'http://schema.org',
            '@type': 'BlogPosting',
            url: metaUrl,
            name: title,
            headline: title,
            image: {
              '@type': 'ImageObject',
              url: metaImage,
            },
            metaDescription,
          })

          meta.push({
            property: 'article:author',
            content: postData.author,
          })

          meta.push({
            property: 'article:published_time',
            content: postData.date,
          })
        }

        const seoMeta = [
          {
            property: 'og:title',
            content: title,
          },
          {
            property: 'og:description',
            content: metaDescription,
          },
          {
            property: 'og:type',
            content: 'website',
          },
          {
            property: 'og:site_name',
            content: data.site.siteMetadata.title,
          },
          {
            property: 'og:url',
            content: metaUrl,
          },
          {
            name: 'twitter:card',
            content: 'summary',
          },
          {
            name: 'twitter:site',
            content: data.site.siteMetadata.siteURL,
          },
          // TODO: Use Post Author
          {
            name: 'twitter:creator',
            content: data.site.siteMetadata.author,
          },
          {
            name: 'twitter:title',
            content: title,
          },
          {
            name: 'twitter:description',
            content: metaDescription,
          },
          {
            name: 'image',
            content: metaImage,
          },
          {
            property: `og:image`,
            content: metaImage,
          },
          {
            property: `og:image:secure_url`,
            content: metaImage,
          },
          {
            property: 'twitter:image',
            content: metaImage,
          },
          {
            name: `twitter:card`,
            content: `summary_large_image`,
          },
        ].concat(meta)

        return (
          <Helmet
            htmlAttributes={{
              lang,
            }}
            // title={title}
            // titleTemplate={`%s | ${data.site.siteMetadata.title}`}
            meta={seoMeta}
          >
            <script type="application/ld+json">{JSON.stringify(schemaOrgJSONLD)}</script>
          </Helmet>
        )
      }}
    />
  )
}

SEO.defaultProps = {
  lang: 'en',
  meta: [],
  keywords: [],
  isPost: false,
}

SEO.propTypes = {
  description: PropTypes.string,
  lang: PropTypes.string,
  meta: PropTypes.array,
  keywords: PropTypes.arrayOf(PropTypes.string),
  title: PropTypes.string,
  image: PropTypes.string,
  imageAlt: PropTypes.string,
  pathname: PropTypes.string,
  postData: PropTypes.object,
}

export default SEO

const SEOQuery = graphql`
  query DefaultSEOQuery {
    site {
      siteMetadata {
        title
        description
        author
        siteURL
      }
    }
  }
`
