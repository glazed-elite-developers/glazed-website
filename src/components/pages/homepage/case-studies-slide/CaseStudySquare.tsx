import React, { memo, SyntheticEvent } from 'react'
import { Link } from 'gatsby'
import { css, cx } from '@emotion/css'
import { Colors, Breakpoints, Fonts } from '@styles/Theme'
import CaseStudiesSlideSquare from './CaseStudiesSlideSquare'
import Heading, { HeadingLevel } from '@components/shared/Heading'
import { IGatsbyImageData } from 'gatsby-plugin-image'

export const Styles = {
  number: css`
    font-family: ${Fonts.heading};
    font-size: 0.5rem;
    opacity: 0.3;
    color: ${Colors.almostWhite};

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: 0.625rem;
    }
  `,

  smallProjectName: css`
    display: flex;
    align-items: flex-end;
    flex: 1 1 0.000001rem;
    font-size: 0.75rem;
    opacity: 0.7;
    color: ${Colors.almostWhite};

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: 1.125rem;
    }
  `,

  bigProjectName: css`
    font-size: 1.125rem;
    color: ${Colors.almostWhite};
    opacity: 0.9;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: 2rem;
    }
  `,

  projectArea: css`
    color: white;
    font-size: 14px;
    font-weight: normal;
    letter-spacing: 0.31px;
    line-height: 34px;
    margin-left: 30px;
  `,

  link: css`
    font-family: ${Fonts.heading};
    font-size: 0.75rem;
    color: ${Colors.glazedBabyBlue};
  `,

  centeredContentWhenSelected: css`
    display: flex;
    flex-direction: column;
    flex: 1 1 0.000001rem;
    justify-content: center;
  `,

  area: css`
    display: none;
    padding-top: 0.625rem;
    font-size: 0.8125rem;
    line-height: 1.5rem;
    opacity: 0.5;
    color: ${Colors.almostWhite};

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      display: block;
    }
  `,
}

export type CaseStudy = {
  name: string
  slug: string
  category: string
  heroImage?: {
    url: string
  }
}

interface CaseStudySquareProps {
  caseStudy: CaseStudy
  index: number
  className?: string
  contentWrapperClassName?: string
  contentClassName?: string
  isSelected?: boolean
  onMouseEnter?: (event: SyntheticEvent) => void
}

const CaseStudySquare: React.FC<CaseStudySquareProps> = ({
  caseStudy,
  index,
  className,
  contentWrapperClassName,
  contentClassName,
  isSelected,
  onMouseEnter,
}) => {
  return (
    <CaseStudiesSlideSquare
      className={cx(className)}
      contentWrapperClassName={cx(contentWrapperClassName)}
      contentClassName={cx(contentClassName)}
      isSelected={isSelected}
      onMouseEnter={onMouseEnter}
      contentWhenSelected={
        <>
          <p className={Styles.number}>// 0{index + 1}</p>
          <div className={Styles.centeredContentWhenSelected}>
            <Heading level={HeadingLevel.H3} className={Styles.bigProjectName}>
              {caseStudy.name}
            </Heading>
            <p className={Styles.area}>{caseStudy.category}</p>
          </div>
          <Link to={`/case-studies/${caseStudy.slug}`} className={Styles.link}>
            &gt; explore case
          </Link>
        </>
      }
    >
      <p className={Styles.number}>// 0{index + 1}</p>
      <Heading level={HeadingLevel.H5} className={Styles.smallProjectName}>
        {caseStudy.name}
      </Heading>
    </CaseStudiesSlideSquare>
  )
}

export default memo(CaseStudySquare)
