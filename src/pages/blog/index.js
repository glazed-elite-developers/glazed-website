import React from 'react'
import { StaticQuery, graphql } from 'gatsby'

import Layout from 're/Layout'
import PageLayout from 're/PageLayout'
import Blog from 're/Blog'

const BlogPage = () => (
  <Layout>
    <PageLayout>
      <StaticQuery
        query={graphql`
          query AllMarkdownRemark {
            allMarkdownRemark {
              edges {
                node {
                  tableOfContents(pathToSlugField: "frontmatter.path")
                  frontmatter {
                    path
                    title
                    date
                  }
                  id
                  excerpt
                }
              }
            }
          }
        `}
        render={data => {
          const posts = data.allMarkdownRemark.edges.map(edge => edge.node)
          return <Blog posts={posts} />
        }}
      />
    </PageLayout>
  </Layout>
)

export default BlogPage
