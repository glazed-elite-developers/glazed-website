import React from 'react'
import { cx, css } from '@emotion/css'
import { Breakpoints, Colors } from '@styles/Theme'
import { GatsbyImage, GatsbyImageProps } from 'gatsby-plugin-image'
import CaseStudySection from './CaseStudySection'

const Styles = {
  wrapper: css`
    display: flex;
    flex-direction: column;
    padding: 0;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      flex-direction: row-reverse;
      padding: 6.25rem 0;
    }
  `,
  textWrapper: css`
    display: flex;
    align-items: center;
    justify-content: center;
    padding: 2.5rem 1.25rem;
    font-size: 0.875rem;
    color: ${Colors.darkGrey};
    line-height: 2;
    white-space: pre-line;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 1.875rem 5.625rem 0 6.25rem;
      flex: 4 1 0.0000001rem;
      font-size: 1.2rem;
    }
  `,
  text: css`
    max-width: 37.5rem;
  `,
  image: css`
    display: flex;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      flex: 6 1 0.0000001rem;
    }
  `,
}

interface CaseStudyTextAndImageProps {
  className?: string
  text: string
  image?: GatsbyImageProps['image']
}

const CaseStudyTextAndImage: React.FC<CaseStudyTextAndImageProps> = ({
  className,
  text,
  image,
}) => {
  return (
    <CaseStudySection className={cx([Styles.wrapper, className])}>
      {image && (
        <div className={Styles.image}>
          <GatsbyImage
            className={Styles.image}
            image={image}
            imgStyle={{ objectFit: 'contain' }}
            alt={text}
          />
        </div>
      )}
      <div className={Styles.textWrapper}>
        <p className={Styles.text}>{text}</p>
      </div>
    </CaseStudySection>
  )
}

export default CaseStudyTextAndImage
