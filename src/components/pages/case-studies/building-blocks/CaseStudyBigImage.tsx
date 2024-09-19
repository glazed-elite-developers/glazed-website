import React from 'react'
import { css, cx } from '@emotion/css'
import { Breakpoints } from '@styles/Theme'
import CaseStudySection from './CaseStudySection'
import { GatsbyImage, IGatsbyImageData } from 'gatsby-plugin-image'

export const Styles = {
  section: css`
    padding: 2.5rem 0;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 6.875rem 11.25rem 5rem;
    }
  `,
  image: css`
    box-shadow: 0 50px 60px rgba(0, 0, 0, 0.1);
  `,
}

interface CaseStudyBigImageProps {
  image?: IGatsbyImageData
  className?: string
  imageClassName?: string
}

const CaseStudyBigImage: React.FC<CaseStudyBigImageProps> = ({
  image,
  className,
  imageClassName,
}) => {
  return (
    <CaseStudySection className={cx([Styles.section, className])}>
      <div className={cx([Styles.image, imageClassName])}>
        {image && (
          <GatsbyImage
            image={image}
            imgStyle={{ objectFit: 'contain' }}
            alt="Case study hero image"
          />
        )}
      </div>
    </CaseStudySection>
  )
}

export default CaseStudyBigImage
