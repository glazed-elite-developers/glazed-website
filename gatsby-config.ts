import { GatsbyConfig } from 'gatsby'
import { config } from 'dotenv'
import { createProxyMiddleware } from 'http-proxy-middleware'

// Load respective .env file.
config({ path: `.env.${process.env.NODE_ENV}` })

const gatsbyConfig: GatsbyConfig = {
  siteMetadata: {
    title: 'Glazed Solutions | Expert Web and Mobile Development Services',
    author: 'Glazed Solutions Lda.',
    description:
      'Glazed Solutions specializes in delivering top-tier web and mobile development projects. Our team of expert developers creates innovative, scalable, and customized solutions for businesses of all sizes.',
    siteURL: process.env.SITE_URL || 'https://glazed.dev',
  },
  plugins: [
    'gatsby-plugin-tsconfig-paths',
    'gatsby-plugin-react-helmet',
    {
      resolve: `gatsby-source-filesystem`,
      options: {
        name: `images`,
        path: `${__dirname}/static/images`,
      },
    },
    {
      resolve: `gatsby-source-filesystem`,
      options: {
        name: `pages`,
        path: `${__dirname}/src/pages`,
      },
    },
    {
      resolve: 'gatsby-v5-source-hygraph',
      options: {
        endpoint:
          'https://eu-west-2.cdn.hygraph.com/content/cm167sjl1025r07w73tf4c3tr/master',
        locales: ['en'],
        fragmentsPath: '.hygraph-fragments',
      },
    },
    `gatsby-plugin-image`,
    `gatsby-plugin-sharp`,
    `gatsby-transformer-sharp`,
    `gatsby-plugin-preload-fonts`,
    {
      resolve: `gatsby-plugin-manifest`,
      options: {
        name: 'Glazed Solutions | Expert Web and Mobile Development Services',
        short_name: 'Glazed',
        start_url: '/',
        background_color: '#2560F2',
        theme_color: '#2560F2',
        display: 'minimal-ui',
        icon: `static/images/logo-glazed-small.png`,
      },
    },
    'gatsby-plugin-mdx',
    'gatsby-plugin-mdx-frontmatter',
    'gatsby-plugin-slug',
    'gatsby-plugin-svg-sprites',
    {
      resolve: `gatsby-plugin-google-gtag`,
      options: {
        trackingIds: [process.env.GA_TRACKING_ID],
        gtagConfig: {
          cookie_domain:
            process.env.NODE_ENV === 'development' ? 'none' : undefined,
        },
      },
    },
    'gatsby-plugin-remove-serviceworker',
  ],
  // For avoiding CORS while developing Netlify Functions locally.
  // Read more: https://www.gatsbyjs.org/docs/api-proxy/#advanced-proxying
  developMiddleware: (app) => {
    app.use(
      '/.netlify/functions/',
      createProxyMiddleware({
        target: `http://localhost:9000`,
        pathRewrite: {
          '/.netlify/functions/': '',
        },
      })
    )
  },
}

export default gatsbyConfig
