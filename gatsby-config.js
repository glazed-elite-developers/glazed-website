const { createProxyMiddleware } = require('http-proxy-middleware')

module.exports = {
  siteMetadata: {
    title: 'Glazed - Elite Developers',
    author: 'Glazed Solutions Lda.',
    siteURL: process.env.SITE_URL || '',
  },
  plugins: [
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
    `gatsby-transformer-sharp`,
    `gatsby-plugin-sharp`,
    {
      resolve: `gatsby-plugin-manifest`,
      options: {
        name: 'Glazed - Elite Developers',
        short_name: 'Glazed',
        start_url: '/',
        background_color: '#2560F2',
        theme_color: '#2560F2',
        display: 'minimal-ui',
        icon: 'src/images/logo-glazed-small.png',
      },
    },
    'gatsby-transformer-remark',
    'gatsby-plugin-offline',
    'gatsby-plugin-svg-sprite',
    'gatsby-bucklescript-output-linker',
    {
      resolve: `gatsby-plugin-google-analytics`,
      options: {
        trackingId: process.env.GA_TRACKING_ID,
      },
    },
  ],
  // For avoiding CORS while developing Netlify Functions locally.
  // Read more: https://www.gatsbyjs.org/docs/api-proxy/#advanced-proxying
  developMiddleware: app => {
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
