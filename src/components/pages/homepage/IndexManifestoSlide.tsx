import React, { FC, RefObject } from 'react'
import { graphql, useStaticQuery } from 'gatsby'
import FullPageSlide from '@components/shared/FullPageSlide'
import Heading, { HeadingLevel } from '@components/shared/Heading'
import DeveloperBackgroundImage from './team-slide/DeveloperBackgroundImage'
import * as Styles from './IndexManifestoSlide.styles'
import { getImage } from 'gatsby-plugin-image'

const photoOverlay = graphql`
  {
    overlay: file(relativePath: { eq: "team/overlay.png" }) {
      childImageSharp {
        gatsbyImageData(placeholder: NONE, layout: FULL_WIDTH)
      }
    }
  }
`

interface ManifestoContent {
  title: string
  content: string
}

const manifestoContent: ManifestoContent[] = [
  {
    title: 'love their work',
    content:
      "They love talking about technology, so they know where it is at and where it is going, and they communicate programming challenges better. They have a comprehensive toolbox, and know there are no silver bullets. And that's why they pick the right tools for specific projects.",
  },
  {
    title: 'are great people',
    content:
      "They care about who they work with, and about areas outside their speciality, understanding other's needs and limitations. They anticipate problems and propose solutions. And that's why it takes less time to ship a great product with them.",
  },
  {
    title: 'build great code',
    content:
      "Great code is simple: it is the shortest path to a solution. Because it doesn't try to solve the future, it is more adaptable to the unpredictable. Because it is easily understood, it is easy to improve upon. And that's why it takes them less time to add new features.",
  },
]

interface Props {
  innerRef?: RefObject<HTMLDivElement>
  id?: string
  onResize?: () => void
}

const IndexManifestoSlide: FC<Props> = ({ innerRef, id, onResize }) => {
  const queryResult = useStaticQuery(photoOverlay)
  const overlay = getImage(queryResult.overlay)
  return (
    <FullPageSlide
      className={Styles.wrapper}
      onResize={onResize}
      id={id}
      innerRef={innerRef}
    >
      <Heading level={HeadingLevel.H1} className={Styles.displayTitle}>
        // manifesto
      </Heading>
      <div className={Styles.contentWrapper}>
        <div className={Styles.content}>
          {manifestoContent.map((element, index) => {
            const index1 = index + 1
            return (
              <div key={String(index1)} className={Styles.block}>
                <Heading level={HeadingLevel.H5} className={Styles.pre}>
                  // 0{String(index1)}
                </Heading>
                <Heading level={HeadingLevel.H3} className={Styles.title}>
                  Great developers{' '}
                  <strong className={Styles.strong}>{element.title}</strong>
                </Heading>
                <p className={Styles.paragraph}>{element.content}</p>
              </div>
            )
          })}
        </div>
        <div className={Styles.funPart}>
          {overlay && (
            <DeveloperBackgroundImage
              image={overlay}
              className={Styles.image}
            />
          )}
        </div>
      </div>
    </FullPageSlide>
  )
}

export default IndexManifestoSlide
