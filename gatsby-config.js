const { createProxyMiddleware } = require('http-proxy-middleware')

module.exports = {
  siteMetadata: {
    title: 'Glazed • Elite Developers',
    author: 'Glazed Solutions Lda.',
    description: 'Glazed is a team of elite web and mobile developers that partner with the world’s leading companies.',
    siteURL: process.env.SITE_URL || 'https://glazed.dev',
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
    `gatsby-plugin-preload-fonts`,
    {
      resolve: `gatsby-plugin-manifest`,
      options: {
        name: 'Glazed • Elite Developers',
        short_name: 'Glazed',
        start_url: '/',
        background_color: '#2560F2',
        theme_color: '#2560F2',
        display: 'minimal-ui',
        icon: `static/images/logo-glazed-small.png`,
      },
    },
    {
      resolve: `gatsby-plugin-mdx`,
      options: {
        defaultLayouts: {
          default: require.resolve(`./src/components/blogLayout.js`),
        },
      },
    },
    'gatsby-plugin-mdx-frontmatter',
    'gatsby-plugin-svg-sprite',
    'gatsby-bucklescript-output-linker',
    {
      resolve: `gatsby-plugin-google-analytics`,
      options: {
        trackingId: process.env.GA_TRACKING_ID,
      },
    },
    'gatsby-plugin-remove-serviceworker',
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
