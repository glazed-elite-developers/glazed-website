/*
import React from 'react'
import { useStaticQuery, graphql } from 'gatsby'
import Img from 'gatsby-image'
import { css } from 'emotion'

import { Colors } from 're/Theme'

const figureStyles = css`
  padding: 1rem 0;
  max-width: 70rem;
  width: 100%;
  margin: 1rem auto 2rem;

  figcaption {
    padding-top: 0.5rem;
    font-size: 0.875rem;
    text-align: center;

    > a {
      color: #${Colors.darkGrey};
    }
  }
`

export default function Image({ src, alt, caption }) {
  // TODO: This query is probably taking too long
  const { allImageSharp } = useStaticQuery(graphql`
    query {
      allImageSharp {
        edges {
          node {
            id
            fluid(maxWidth: 1800) {
              ...GatsbyImageSharpFluid_withWebp_noBase64
            }
            parent {
              ... on File {
                id
                relativePath
              }
            }
          }
        }
      }
    }
  `)

  const image = allImageSharp.edges.find(edge => edge.node.parent.relativePath === src)

  if (!image) {
    return null
  }

  return (
    <figure className={figureStyles}>
      <Img fluid={image.node.fluid} alt={alt} />
      <figcaption>{caption}</figcaption>
    </figure>
  )
}
*/
