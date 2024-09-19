import React, { FC, memo } from 'react'
import { css } from '@emotion/css'
import { Link } from 'gatsby'
import { Breakpoints, Colors } from '@styles/Theme'
import MaskContainer from '@components/shared/MaskContainer'
import { GatsbyImage, GatsbyImageProps } from 'gatsby-plugin-image'
import Heading, { HeadingLevel } from '@components/shared/Heading'
import Button from '@components/shared/Button'
import SVG from '@components/shared/SVG'
import IconBackArrowSvg from 'static/images/icon_back_arrow.svg'

export const Styles = {
  wrapper: css`
    position: relative;
    padding-top: 4.0625rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 3.75rem 5.625rem 0;
    }
  `,
  imageContainer: css`
    height: 17.5rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
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
  nextProjectCard: css`
    position: absolute;
    display: flex;
    flex-direction: column;
    top: 0;
    left: 1.25rem;
    width: 14.375rem;
    height: 14.375rem;
    padding: 1.875rem;
    color: ${Colors.white};
    background-color: ${Colors.glazedBabyBlueText};
    z-index: 0;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      left: 11.25rem;
      padding: 5rem 2.5rem;
      height: 25.625rem;
      width: 25.625rem;
    }
  `,
  nextProjectLabel: css`
    flex: 1 1 auto;
    font-size: 0.625rem;
    color: ${Colors.almostWhite};
    opacity: 0.5;
  `,
  heading: css`
    font-size: 1.5rem;
    line-height: 1.25;
    display: flex;
    align-items: flex-end;
    flex: 1 0 auto;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: 3rem;
      line-height: 1.25;
    }
  `,
  area: css`
    padding: 0.9375rem 0 0.625rem 0;
    flex: 1 0 auto;
    color: ${Colors.almostWhite};
    font-size: 0.75rem;
    opacity: 0.3;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 1.875rem 0 1.25rem 0;
      font-size: 0.875rem;
    }
  `,
  nextButtonWraper: css`
    color: ${Colors.almostWhite};
    font-size: 0.75rem;
    opacity: 0.7;
    line-height: 2;
    display: flex;
    align-items: flex-end;
    flex: 1 0 auto;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: 1rem;
    }
  `,
  nextButton: css`
    padding: 0 0 0.625rem;
    transform: rotate(180deg);

    svg {
      fill: ${Colors.white};
      stroke: ${Colors.white};
    }
  `,
}

interface CaseStudyNextCaseProps {
  image?: GatsbyImageProps['image']
  title: string
  area: string
  link: string
}

interface ArrowButtonProps {
  link: string
}

const ArrowButton: FC<ArrowButtonProps> = ({ link }) => {
  return (
    <Link to={link} className={Styles.nextButtonWraper}>
      <Button className={Styles.nextButton}>
        <SVG height="12" asset={IconBackArrowSvg} />
      </Button>
    </Link>
  )
}

const CaseStudyNextCase: FC<CaseStudyNextCaseProps> = ({
  image,
  title,
  area,
  link,
}) => {
  return (
    <div className={Styles.wrapper}>
      <MaskContainer
        className={Styles.imageContainer}
        maskClassName={Styles.mask}
      >
        {image && (
          <GatsbyImage image={image} className={Styles.image} alt={title} />
        )}
      </MaskContainer>
      <div className={Styles.nextProjectCard}>
        <Heading level={HeadingLevel.H6} className={Styles.nextProjectLabel}>
          {title}
        </Heading>
        <Heading level={HeadingLevel.H1} className={Styles.heading}>
          {title}
        </Heading>
        <p className={Styles.area}>{area}</p>
        <ArrowButton link={link} />
      </div>
    </div>
  )
}

export default memo(CaseStudyNextCase)
