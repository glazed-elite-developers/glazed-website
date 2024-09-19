import React, { FC, ReactNode } from 'react'
import { cx, css } from '@emotion/css'
import { Breakpoints } from '@styles/Theme'

const Styles = {
  wrapper: css`
    padding: 2.5rem 1.25rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 5rem 11.25rem;
    }
  `,
}

interface CaseStudySectionProps {
  className?: string
  children: ReactNode
}

const CaseStudySection: FC<CaseStudySectionProps> = ({
  className,
  children,
}) => {
  return (
    <section className={cx([Styles.wrapper, className])}>{children}</section>
  )
}

export default CaseStudySection
