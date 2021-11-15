import React, { Fragment } from 'react'
import { css } from 'emotion'
import styled from '@emotion/styled'
import { MDXProvider } from '@mdx-js/react'
import capitalize from 'capitalize'
import { Link } from 'gatsby'

import Layout from 're/Layout'
import PageLayout from 're/PageLayout'
import PageContent from 're/PageContent'
import Heading from 're/Heading'
import { Colors, Breakpoints } from 're/Theme'
import SVG from 're/shared/SVG'
import SEO from '../components/seo'
import Code from '../components/code'

import glazedLogo from '../../static/images/logo-glazed-small.svg'
import GatsbyImage from 'gatsby-image'

const pageLayoutStyles = css`
  background-color: #${Colors.whiteTurquoise};
`

const pageContentStyles = css`
  padding-top: 0 !important;

  > article {
    display: flex;
    flex-direction: column;
    align-items: center;
    width: 100%;

    pre {
      max-width: 39.5rem;
      width: 100%;
      overflow-x: auto;
      margin-bottom: 1rem;
      background-color: #${Colors.almostAlmostWhite};
      padding: 1rem;
    }

    footer {
      display: flex;
      flex-direction: column;
      padding-top: 0.5rem;
      padding-bottom: 6rem;

      @media ${Breakpoints.tabletLandscape} {
        padding-bottom: 3rem;
      }

      div {
        display: flex;
        align-items: center;
        margin-bottom: 1.25rem;

        svg {
          width: 5rem;
        }

        hr {
          height: 0;
          margin-top: 0;
          margin-bottom: 0;

          &:first-of-type {
            margin-right: 1rem;
          }

          &:last-of-type {
            margin-left: 1rem;
          }
        }
      }

      p {
        margin-bottom: 1rem;
      }

      > a {
        &:after {
          display: none;
        }

        &:visited {
          color: #${Colors.glazedBlueDarker};
        }
      }
    }
  }
`

const GlobalBlogStylesContainer = styled.div`
  display: flex;
  flex-direction: column;
  align-items: center;
  width: 100%;

  a {
    color: #${Colors.glazedBlueDarker};
    transition: color 200ms ease-in-out;
    position: relative;

    &:after {
      content: '';
      position: absolute;
      transition: color 200ms ease-in-out;
      bottom: 1px;
      left: 0;
      right: 0;
      height: 1px;
      background-color: #${Colors.glazedBlueDarker};
    }

    &:visited {
      color: #${Colors.glazedBlueMidnight};

      &:after {
        background-color: #${Colors.glazedBlueMidnight};
      }
    }

    &:hover,
    &:focus {
      color: #${Colors.glazedBlueLighter};

      &:after {
        background-color: #${Colors.glazedBlueLighter};
      }
    }
  }

  h1,
  h2,
  h3,
  h4,
  h5,
  h6 {
    padding: 1rem 0;
    width: 100%;
    padding-right: 0.5rem;
    max-width: 37.5rem;

    color: #${Colors.darkGrey};
  }

  p,
  li {
    line-height: 1.8;
    font-size: 1.125rem;
    text-align: left;
    color: #${Colors.darkGrey};
  }

  p,
  ul,
  ol,
  blockquote {
    padding-bottom: 1rem;
    max-width: 37.5rem;
    width: 100%;
    text-align: justify;
  }

  li {
    padding-bottom: 0.5rem;
    padding-left: 0.5rem;

    &::before {
      padding-right: 0.5rem;
    }
  }

  ol {
    counter-reset: ol-counter;

    li {
      counter-increment: ol-counter;

      &::before {
        content: '' counter(ol-counter) '.';
        color: #${Colors.glazedBlue};
      }
    }
  }

  ul li::before {
    content: '•';
    color: #${Colors.glazedBlue};
  }

  hr {
    margin-bottom: 2rem;
    max-width: 37.5rem;
    width: 100%;
    border: solid 1px #${Colors.glazedBlueDarkest};
  }
`

const Title = styled(Heading)`
  width: 100%;
  padding-bottom: 0.75rem;
  max-width: 37.5rem;
  color: #${Colors.darkGreyDarker};
`

const Frontmatter = styled.div`
  width: 100%;
  max-width: 39.5rem;
  display: flex;
  flex-direction: column;
`

const AuthorContainer = styled.div`
  display: flex;
`

const ImageContainer = styled.div`
  width: 5rem;
  height: 4rem;
  overflow: hidden;
  border-radius: 50%;
  margin-right: 0.5rem;
`

const PostInfo = styled.div`
  display: flex;
  flex-direction: column;
  justify-content: center;

  a {
    color: #${Colors.darkGreyDarker};
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

export default function BlogPageLayout({
  children,
  location,
  data: {
    mdx: { frontmatter },
    authorPhoto,
  },
}) {
  const authorName = authorPhoto.childImageSharp.fluid.src.substring(
    authorPhoto.childImageSharp.fluid.src.lastIndexOf('/') + 1,
    authorPhoto.childImageSharp.fluid.src.lastIndexOf('.')
  )

  console.log({ img: frontmatter.image })

  return (
    <>
      <SEO
        title={frontmatter.title}
        description={frontmatter.description}
        image={frontmatter.image.publicURL}
        pathname={location.pathname}
        postData={{
          author: authorName,
          date: frontmatter.date,
        }}
      />
      <Layout title={`Glazed • ${frontmatter.title}`} description={frontmatter.description}>
        <PageLayout className={pageLayoutStyles} useDarkNavBarLinks useFloatingNavBar>
          <PageContent className={pageContentStyles}>
            <article>
              <Frontmatter>
                <Title level={0}>{frontmatter.title}</Title>

                <AuthorContainer>
                  <a href={`/?modal=team&unit=${authorName}`} target="_blank">
                    <ImageContainer>
                      <GatsbyImage
                        objectFit="cover"
                        objectPosition="50% 50%"
                        fluid={authorPhoto.childImageSharp.fluid}
                      />
                    </ImageContainer>
                  </a>
                  <PostInfo>
                    <a href={`/?modal=team&unit=${authorName}`} target="_blank">
                      {frontmatter.author}
                    </a>
                    <FormattedDate>
                      {new Date(frontmatter.date).toLocaleDateString('en-US', {
                        year: 'numeric',
                        month: 'long',
                        day: 'numeric',
                      })}
                    </FormattedDate>
                    <Tags>
                      {frontmatter.tags.map((tag, index) => (
                        <Fragment key={tag}>
                          <span>{capitalize.words(tag)}</span>
                          {index < frontmatter.tags.length - 1 && ', '}
                        </Fragment>
                      ))}
                    </Tags>
                  </PostInfo>
                </AuthorContainer>
              </Frontmatter>
              <MDXProvider
                components={{
                  // // Map HTML element tag to React component
                  h1: props => <Heading level={1} {...props} />,
                  h2: props => <Heading level={2} {...props} />,
                  h3: props => <Heading level={3} {...props} />,
                  h4: props => <Heading level={4} {...props} />,
                  h5: props => <Heading level={5} {...props} />,
                  h6: props => <Heading level={6} {...props} />,
                  code: props => <Code {...props} />,
                }}
              >
                <GlobalBlogStylesContainer>
                  {children}
                  <footer>
                    <div>
                      <hr />
                      <SVG asset={glazedLogo} />
                      <hr />
                    </div>
                    <p>
                      Thanks for reading, if you enjoyed our content you can you can stay up to date by following us on{' '}
                      <a href="https://twitter.com/glazedSolutions" target="_blank" rel="noopener">
                        Twitter
                      </a>
                      ,{' '}
                      <a href="https://www.facebook.com/glazedEliteDevelopers" target="_blank" rel="noopener">
                        Facebook
                      </a>{' '}
                      and{' '}
                      <a href="https://www.linkedin.com/company/glazed-solutions/" target="_blank" rel="noopener">
                        LinkedIn
                      </a>{' '}
                      👋
                    </p>
                    <Link to="/blog">{'//'}&nbsp; back to blog</Link>
                  </footer>
                </GlobalBlogStylesContainer>
              </MDXProvider>
            </article>
          </PageContent>
        </PageLayout>
      </Layout>
    </>
  )
}
