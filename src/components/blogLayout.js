import React from 'react'
import { css } from 'emotion'
import { MDXProvider } from '@mdx-js/react'
import capitalize from 'capitalize'

import Layout from 're/Layout'
import PageLayout from 're/PageLayout'
import PageContent from 're/PageContent'
import Heading from 're/Heading'
import { useHeaderPosition } from 're/pages/case-studies/building-blocks/CaseStudyPageTemplate'
import { Colors } from 're/Theme'

const contentStyles = css`
  margin-top: 3rem;

  .frontmatter {
    max-width: 40rem;
    margin: 0 auto;

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
    padding-bottom: 0.5rem;
    max-width: 40rem;
    margin: 0 auto;
  }

  p,
  ul,
  ol,
  blockquote {
    padding-bottom: 1rem;
    max-width: 40rem;
    margin: 0 auto;
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
    margin-bottom: 1rem;
    max-width: 40rem;
    border: solid 1px #${Colors.glazedBlueMidnight};
  }
`

export default function BlogPageLayout({ children, pageContext: { frontmatter } }) {
  console.log({ useHeaderPosition })
  return (
    <>
      <Layout title={`Glazed • ${frontmatter.title}`}>
        <PageLayout useDarkNavBarLinks>
          <PageContent className={contentStyles}>
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
              </MDXProvider>
            </article>
          </PageContent>
        </PageLayout>
      </Layout>
    </>
  )
}
