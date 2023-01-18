const { graphql } = require('graphql')
const path = require('path')

exports.onCreateWebpackConfig = ({ actions }) => {
  actions.setWebpackConfig({
    resolve: {
      alias: {
        re: path.resolve(__dirname, 'lib/es6/re'),
        static: path.resolve(__dirname, 'static'),
        src: path.resolve(__dirname, 'src'),
      },
    },
  })
}

exports.createPages = async ({ graphql, actions: { createPage } }) => {
  const results = await graphql(
    `
      {
        allContentfulBlogpost {
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
