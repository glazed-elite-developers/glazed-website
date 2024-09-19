import React, { FC, useMemo } from 'react'
import { useStaticQuery, graphql } from 'gatsby'
import { GatsbyImage, getImage } from 'gatsby-plugin-image'
import { css } from '@emotion/css'
import { Colors } from '../../styles/Theme'

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
      color: ${Colors.darkGrey};
    }
  }
`

interface ImageProps {
  src: string
  alt: string
  caption?: string
}

const BlogImage: FC<ImageProps> = ({ src, alt, caption }) => {
  const data = useStaticQuery(graphql`
    query getAllImages {
      allFile(filter: { internal: { mediaType: { regex: "/image/" } } }) {
        nodes {
          relativePath
          childImageSharp {
            gatsbyImageData(width: 1800, placeholder: NONE, layout: CONSTRAINED)
          }
        }
      }
    }
  `)
  const image = useMemo(
    () =>
      getImage(
        data.allFile.nodes.find(({ relativePath }: any) => src === relativePath)
      ),
    [data, src]
  )

  return (
    image && (
      <figure className={figureStyles}>
        <GatsbyImage image={image} alt={alt} />
        <figcaption>{caption}</figcaption>
      </figure>
    )
  )
}

export default BlogImage
