const path = require('path')
const { graphql } = require('graphql')

exports.onCreateWebpackConfig = ({ actions }) => {
  actions.setWebpackConfig({
    resolve: {
      alias: {
        re: path.resolve(__dirname, 'lib/es6/re'),
        src: path.resolve(__dirname, 'src'),
        static: path.resolve(__dirname, 'static'),
      },
    },
  })
}

exports.createPages = async ({ graphql, actions: { createPage } }) => {
  const results = await graphql(
    `
      {
        allContentfulBlogpost(filter: { node_locale: { eq: "en-US" } }) {
          nodes {
            slug
          }
        }
      }
    `
  )
  if (results.errors) {
    console.log(results.errors)
    return
  }
  results.data.allContentfulBlogpost.nodes.forEach(node => {
    createPage({
      path: `/${node.slug}`,
      component: require.resolve('./src/components/contentfulBlogLayout.js'),
      context: {
        slug: node.slug,
      },
    })
  })
}
