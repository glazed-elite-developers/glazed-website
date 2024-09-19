import React from 'react'
import { css, cx } from '@emotion/css'
import CaseStudySection from './CaseStudySection'
import { Breakpoints } from '@styles/Theme'
import FixedRatioContainer from '@components/shared/FixedRatioContainer'

export const Styles = {
  section: css`
    padding: 2.5rem 0;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 6.875rem 11.25rem 5rem;
    }
  `,
  wrapper: css`
    box-shadow: 0 50px 60px rgba(0, 0, 0, 0.1);
  `,
  content: css`
    width: 100%;
    height: 100%;
  `,
}

interface CaseStudyBigVideoProps {
  src: string
  className?: string
}

const CaseStudyBigVideo: React.FC<CaseStudyBigVideoProps> = ({
  src,
  className,
}) => {
  return (
    <CaseStudySection className={cx([Styles.section, className])}>
      <FixedRatioContainer
        className={Styles.wrapper}
        contentClassName={Styles.content}
        stretchDirection="Horizontal"
        width={16}
        height={9}
      >
        <iframe
          width="100%"
          height="100%"
          src={src}
          frameBorder="0"
          allowFullScreen
        />
      </FixedRatioContainer>
    </CaseStudySection>
  )
}

export default CaseStudyBigVideo
