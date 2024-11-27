import React from 'react'
import { css, cx } from '@emotion/css'
import { Breakpoints, Colors } from '@styles/Theme'
import FixedRatioContainer from '@components/shared/FixedRatioContainer'
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
  content: css`
    width: 100%;
    height: 100%;
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
  video: css`
    @media (min-width: ${Breakpoints.tabletLandscape}) {
      flex: 6 1 0.0000001rem;
    }
  `,
}

interface CaseStudyTextAndVideoProps {
  className?: string
  text: string
  videoSrc: string
}

const CaseStudyTextAndVideo: React.FC<CaseStudyTextAndVideoProps> = ({
  className,
  text,
  videoSrc,
}) => {
  return (
    <CaseStudySection className={cx([Styles.wrapper, className])}>
      <FixedRatioContainer
        className={Styles.video}
        contentClassName={Styles.content}
        stretchDirection="Horizontal"
        width={16}
        height={9}
      >
        <iframe height="100%" src={videoSrc} width="100%" />
      </FixedRatioContainer>
      <div className={Styles.textWrapper}>
        <p className={Styles.text}>{text}</p>
      </div>
    </CaseStudySection>
  )
}

export default CaseStudyTextAndVideo
