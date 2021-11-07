import React from 'react'
import { css } from 'emotion'
import { MDXProvider } from '@mdx-js/react'
import capitalize from 'capitalize'
import { Link } from 'gatsby'

import Layout from 're/Layout'
import PageLayout from 're/PageLayout'
import PageContent from 're/PageContent'
import Heading from 're/Heading'
import { Colors } from 're/Theme'
import SVG from 're/shared/SVG'
import SEO from '../components/seo'
import Code from '../components/code'

import glazedLogo from '../../static/images/logo-glazed-small.svg'

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
    // max-width: 70vw;
    // margin: 0 auto;

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
      margin-top: 0.5rem;

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
        margin-bottom: 4rem;

        &:after {
          display: none;
        }

        &:visited {
          color: #${Colors.glazedBlueDarker};
        }
      }
    }
  }

  .frontmatter {
    width: 100%;
    max-width: 37.5rem;

    span:first-of-type {
      padding-right: 0.5rem;
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

export default function BlogPageLayout({
  children,
  location,
  data: {
    mdx: { frontmatter },
  },
}) {
  console.log(children)
  return (
    <>
      <SEO
        title={frontmatter.title}
        description={frontmatter.description}
        image={
          frontmatter.image.childImageSharp ? frontmatter.image.childImageSharp.fluid.src : frontmatter.image.publicURL
        }
        pathname={location.pathname}
        postData={{
          // author: author.name,
          date: frontmatter.date,
        }}
      />
      <Layout title={`Glazed • ${frontmatter.title}`} description={frontmatter.description}>
        <PageLayout className={pageLayoutStyles} useDarkNavBarLinks useFloatingNavBar>
          <PageContent className={pageContentStyles}>
            <article>
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
                <Heading level={1}>{frontmatter.title}</Heading>
                <div className="frontmatter">
                  <span>{frontmatter.date}</span>
                  {frontmatter.tags.map((tag, index) => (
                    <>
                      <span>{capitalize.words(tag)}</span>
                      {index < frontmatter.tags.length - 1 && ', '}
                    </>
                  ))}
                </div>
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
                  <Link to="/blog">
                    {'// < '}
                    back to blog
                  </Link>
                </footer>
              </MDXProvider>
            </article>
          </PageContent>
        </PageLayout>
      </Layout>
    </>
  )
}
