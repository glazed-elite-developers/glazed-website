import React, { Fragment } from 'react'
import { graphql, Link } from 'gatsby'
import { css } from 'emotion'
import Img from 'gatsby-image'
import capitalize from 'capitalize'
import styled from '@emotion/styled'

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
        font-size: 1.25rem;
        line-height: 1.5;
        padding-bottom: 0.25rem;
        color: inherit;

        @media ${Breakpoints.tabletLandscape} {
          font-size: 1.5rem;
        }
      }

      h4 {
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
        left: -10px;
        width: 160px;
        height: 160px;
        border: 1px solid #${Colors.glazedBlue};
        opacity: 0.1;

        @media ${Breakpoints.tabletLandscape} {
          left: -20px;
        }
      }

      // Blog Post Info
      > div:first-of-type {
        flex: 1 1 65%;
        padding-bottom: 0.5rem;
        padding-right: 2rem;
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

const FormattedDate = styled.span`
  font-size: 0.875rem;
  padding-top: 0.125rem;
`

const Tags = styled.span`
  font-size: 0.75rem;
  font-style: italic;
  padding-top: 0.5rem;
`

const ContentfulBlogHome = ({ data }) => {
  const posts = data.allContentfulBlogpost.edges

  return (
    <Layout>
      <PageLayout className={pageLayoutStyles} useDarkNavBarLinks useFloatingNavBar>
        <PageContent className={pageContentStyles}>
          <ul>
            {posts.map(({ node }) => (
              <li key={node.id}>
                <div>
                  <Link to={node.slug}>
                    <Heading level={2}>{node.content.childMdx.frontmatter.title}</Heading>
                  </Link>
                  <Heading level={3}>{node.content.childMdx.frontmatter.description}</Heading>
                  <div>
                    <FormattedDate>
                      {new Date(node.content.childMdx.frontmatter.date).toLocaleDateString('en-US', {
                        year: 'numeric',
                        month: 'long',
                        day: 'numeric',
                      })}
                    </FormattedDate>
                  </div>
                  <div>
                    <Tags>
                      {node.content.childMdx.frontmatter.tags.map((tag, index) => (
                        <Fragment key={tag}>
                          <span>{capitalize.words(tag)}</span>
                          {index < node.content.childMdx.frontmatter.tags.length - 1 && ', '}
                        </Fragment>
                      ))}
                    </Tags>
                  </div>
                </div>
                <div> {node.image && <Img fluid={node.image.fluid} />} </div>
              </li>
            ))}
          </ul>
        </PageContent>
      </PageLayout>
    </Layout>
  )
}

export default ContentfulBlogHome

export const pageQuery = graphql`
  query ContentfulBlogQuery {
    allContentfulBlogpost(filter: { node_locale: { eq: "en-US" } }) {
      edges {
        node {
          content {
            childMdx {
              frontmatter {
                date
                description
                title
                tags
              }
            }
          }
          slug
          image {
            fluid(maxWidth: 800) {
              ...GatsbyContentfulFluid_withWebp_noBase64
            }
            file {
              fileName
            }
          }
        }
      }
    }
  }
`
