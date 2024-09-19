import React, { FC } from 'react'
import { Helmet } from 'react-helmet'
import { StaticQuery, graphql } from 'gatsby'
import defaultLogo from '@static/images/logo-glazed-small.png'

interface SEOProps {
  description?: string
  lang?: string
  meta?: Array<
    { name: string; content: string } | { property: string; content: string }
  >
  title: string
  image?: string
  imageAlt?: string
  pathname: string
  postData?: {
    author: string
    date: string
  }
}

const SEO: FC<SEOProps> = ({
  description,
  lang = 'en',
  meta = [],
  title,
  image,
  imageAlt,
  pathname,
  postData,
}) => {
  return (
    <StaticQuery
      query={SEOQuery}
      render={(data) => {
        const metaDescription =
          description || data.site.siteMetadata.description
        const metaImage = `${data.site.siteMetadata.siteURL}${
          image || defaultLogo
        }`
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
            alternateName: title,
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
            property: 'og:image',
            content: metaImage,
          },
          {
            property: 'og:image:secure_url',
            content: metaImage,
          },
          {
            property: 'twitter:image',
            content: metaImage,
          },
          {
            name: 'twitter:card',
            content: 'summary_large_image',
          },
        ].concat(meta)

        return (
          <Helmet
            htmlAttributes={{
              lang,
            }}
            meta={seoMeta}
          >
            <script type="application/ld+json">
              {JSON.stringify(schemaOrgJSONLD)}
            </script>
          </Helmet>
        )
      }}
    />
  )
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
