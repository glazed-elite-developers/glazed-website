import React from 'react'
import { graphql, Link } from 'gatsby'
import { css } from 'emotion'

import Layout from 're/Layout'
import PageLayout from 're/PageLayout'
import PageContent from 're/PageContent'
import Heading from 're/Heading'
import { Colors } from 're/Theme'
import capitalize from 'capitalize'

const contentClassName = css`
  ul {
    display: flex;
    flex-direction: column;
    max-width: 40rem;

    li {
      display: flex;
      padding-top: 1rem;

      &::before {
        content: '';
        border-left: solid 2px #${Colors.glazedBlue};
        padding-right: 0.5rem;
      }

      div {
        padding-bottom: 0.5rem;

        span:first-of-type {
          padding-right: 0.5rem;
        }
      }
    }
  }
`

const BlogHome = ({ data }) => {
  const posts = data.allMdx.edges
  return (
    <>
      <Layout>
        <PageLayout useDarkNavBarLinks>
          <PageContent className={contentClassName}>
            <ul>
              {posts.map(({ node }) => (
                <li key={node.slug}>
                  <div>
                    <Link to={node.slug}>
                      <Heading level={2}>{node.frontmatter.title}</Heading>
                    </Link>
                    <span>{node.frontmatter.date}</span>
                    {node.frontmatter.tags.map((tag, index) => (
                      <>
                        <span>{capitalize.words(tag)}</span>
                        {index < node.frontmatter.tags.length - 1 && ', '}
                      </>
                    ))}
                  </div>
                </li>
              ))}
            </ul>
          </PageContent>
        </PageLayout>
      </Layout>
    </>
  )
}

export default BlogHome

export const pageQuery = graphql`
  query BlogQuery {
    allMdx(sort: { fields: [frontmatter___date], order: DESC }) {
      edges {
        node {
          id
          slug
          frontmatter {
            date
            description
            tags
            title
          }
        }
      }
    }
  }
`
