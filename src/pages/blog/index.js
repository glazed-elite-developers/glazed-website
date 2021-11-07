import React, { Fragment } from 'react'
import { graphql, Link } from 'gatsby'
import { css } from 'emotion'
import Img from 'gatsby-image'
import capitalize from 'capitalize'

import Layout from 're/Layout'
import PageLayout from 're/PageLayout'
import PageContent from 're/PageContent'
import Heading from 're/Heading'
import { Colors, Breakpoints } from 're/Theme'

const pageLayoutStyles = css`
  background-color: #${Colors.whiteTurquoise};
`

const pageContentStyles = css`
  align-items: center;
  padding-top: 0 !important;

  ul {
    display: flex;
    flex-direction: column;
    max-width: 70rem;
    padding-bottom: 2rem;

    li {
      display: flex;
      margin: 2rem 0;
      position: relative;

      a {
        color: #${Colors.glazedBlueDarkest};
        transition: color 200ms ease-in-out;
        position: relative;

        &:hover,
        &:focus {
          color: #${Colors.glazedBlueLighter};
        }
      }

      h3 {
        line-height: 1.5;
        padding-bottom: 0.5rem;
      }

      h5 {
        font-family: 'Muli';
        font-weight: 500;
        padding-bottom: 0.5rem;
        line-height: 1.8;
      }

      &::before {
        content: '';
        padding-right: 0.5rem;
        position: absolute;
        top: -20px;
        left: -20px;
        width: 160px;
        height: 160px;
        border: 1px solid #${Colors.glazedBlue};
        opacity: 0.1;
      }

      // Blog Post Info
      > div:first-of-type {
        flex: 1 1 65%;
        padding-bottom: 0.5rem;
        padding-right: 2rem;

        span:first-of-type {
          padding-right: 0.5rem;
        }
      }

      > div:last-of-type {
        flex: 1 0 35%;
        display: none;

        @media ${Breakpoints.phoneLandscape} {
          display: block;
        }
      }
    }
  }
`

// TODO:
// Code component
// Fix Mobile

const BlogHome = ({ data }) => {
  const posts = data.allMdx.edges

  return (
    <Layout>
      <PageLayout className={pageLayoutStyles} useDarkNavBarLinks useFloatingNavBar>
        <PageContent className={pageContentStyles}>
          <ul>
            {posts.map(({ node }) => (
              <li key={node.id}>
                <div>
                  <Link to={node.slug}>
                    <Heading level={2}>{node.frontmatter.title}</Heading>
                  </Link>
                  <Heading level={4}>{node.frontmatter.description}</Heading>
                  <span>{node.frontmatter.date}</span>
                  {node.frontmatter.tags.map((tag, index) => (
                    <Fragment key={index}>
                      <span>{capitalize.words(tag)}</span>
                      {index < node.frontmatter.tags.length - 1 && ', '}
                    </Fragment>
                  ))}
                </div>
                <div>{node.frontmatter.image && <Img fluid={node.frontmatter.image.childImageSharp.fluid} />}</div>
              </li>
            ))}
          </ul>
        </PageContent>
      </PageLayout>
    </Layout>
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
            image {
              childImageSharp {
                fluid(maxWidth: 800) {
                  ...GatsbyImageSharpFluid_withWebp_noBase64
                }
              }
            }
          }
        }
      }
    }
  }
`
