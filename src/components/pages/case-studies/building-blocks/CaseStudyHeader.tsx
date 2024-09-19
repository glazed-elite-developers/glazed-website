import { css } from '@emotion/css'
import React from 'react'
import { Breakpoints, Colors } from '@styles/Theme'
import MaskContainer from '../../../shared/MaskContainer'
import Heading, { HeadingLevel } from '@components/shared/Heading'
import { GatsbyImage, IGatsbyImageData } from 'gatsby-plugin-image'

const Styles = {
  wrapper: css`
    position: relative;
    overflow: hidden;
    padding: 7.1875rem 0 0 1.25rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 14.375rem 0 0 11.25rem;
    }
  `,
  imageContainer: css`
    position: absolute;
    top: 0;
    left: 0;
    height: 17.5rem;
    width: 100%;
    z-index: 0;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      left: 3.125rem;
      height: 34.375rem;
    }
  `,
  image: css`
    height: 17.5rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      height: 34.375rem;
    }
  `,
  mask: css`
    background-color: rgba(150, 150, 150, 0);
  `,
  titleCard: css`
    position: relative;
    display: flex;
    flex-direction: column;
    width: 14.375rem;
    height: 14.375rem;
    padding: 1.875rem;
    color: ${Colors.white};
    background-color: ${Colors.glazedBabyBlueText};
    z-index: 0;

    @media (min-width: ${Breakpoints.tabletPortrait}) {
      justify-content: flex-end;
      width: 17.5rem;
      height: 17.5rem;
    }

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 2.5rem;
      width: 21.875rem;
      height: 21.875rem;
    }

    @media (min-width: ${Breakpoints.desktop}) {
      padding: 5rem 2.5rem;
      width: 25.625rem;
      height: 25.625rem;
    }
  `,
  heading: css`
    font-size: 1.5rem;
    line-height: 1.25;

    @media (min-width: ${Breakpoints.desktop}) {
      font-size: 3rem;
    }
  `,
  area: css`
    padding: 0.9375rem 0 0.625rem 0;
    color: ${Colors.almostWhite};
    font-size: 0.75rem;
    opacity: 0.3;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 1.875rem 0 1.25rem 0;
      font-size: 0.875rem;
    }
  `,
  text: css`
    color: ${Colors.almostWhite};
    font-size: 0.75rem;
    opacity: 0.7;
    line-height: 2;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: 1rem;
    }
  `,
}

interface CaseStudyHeaderProps {
  image?: IGatsbyImageData
  title: string
  area: string
  text: string
}

const CaseStudyHeader: React.FC<CaseStudyHeaderProps> = ({
  image,
  title,
  area,
  text,
}) => {
  return (
    <div className={Styles.wrapper}>
      <MaskContainer
        className={Styles.imageContainer}
        maskClassName={Styles.mask}
      >
        {image && (
          <GatsbyImage
            image={image}
            className={Styles.image}
            loading="eager"
            alt={title}
          />
        )}
      </MaskContainer>
      <div className={Styles.titleCard}>
        <Heading level={HeadingLevel.H1} className={Styles.heading}>
          {title}
        </Heading>
        <p className={Styles.area}>{area}</p>
        <p className={Styles.text}>{text}</p>
      </div>
    </div>
  )
}

export default CaseStudyHeader
