import React from 'react'
import { useStaticQuery, graphql } from 'gatsby'
import Img from 'gatsby-image'
import { css } from 'emotion'

const figureStyles = css`
  padding: 1rem 0;

  figcaption {
    padding-top: 0.5rem;
    font-size: 0.725rem;
    text-align: center;
  }
`

export default function Image({ src, alt, caption }) {
  const { allImageSharp } = useStaticQuery(graphql`
    query {
      allImageSharp {
        edges {
          node {
            id
            fluid(maxWidth: 1800) {
              ...GatsbyImageSharpFluid_noBase64
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
