import React, { FC, ReactNode, memo } from 'react'
import { css, cx } from '@emotion/css'
import { Breakpoints, Colors, Fonts } from '@styles/Theme'
import CaseStudySection from './CaseStudySection'
import SVG, { SVGProps } from '@components/shared/SVG'
import Heading, { HeadingLevel } from '@components/shared/Heading'

export const Styles = {
  wrapper: css`
    display: flex;
    flex-wrap: wrap;
    padding: 2.5rem 1.25rem 0;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 6.25rem 11.25rem 2.25rem;
    }
  `,
  section: css`
    display: flex;
    flex-direction: column;
    padding-bottom: 1.875rem;
    line-height: 2;
  `,
  sectionTitle: css`
    padding-bottom: 0.9375rem;
    font-size: 0.625rem;
    color: ${Colors.darkGrey};
    opacity: 0.4;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: 0.8125rem;
      padding-bottom: 1.25rem;
    }
  `,
  techsSection: css`
    flex: 0 0 100%;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding-left: 3.125rem;
      flex: 0 0 30%;
    }
  `,
  briefSection: css`
    flex: 0 0 70%;
    padding-right: 1.5625rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      flex: 1 0 0.0000001rem;
    }
  `,
  yearSection: css`
    @media (min-width: ${Breakpoints.tabletLandscape}) {
      flex: 0 0 17%;
      align-items: flex-end;
    }
  `,
  techs: css`
    display: flex;
    flex-wrap: wrap;
    margin: 0 -0.875rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      flex-direction: column;
      margin: -0.25rem 0;
    }
  `,
  techBadge: css`
    display: flex;
    align-items: center;
    font-size: 0.875rem;
    font-family: ${Fonts.heading};
    padding: 0 0.875rem;
    color: ${Colors.darkGrey};
    opacity: 0.7;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 0.75rem 0;
    }
  `,
  techIcon: css`
    height: 14px;
    margin-right: 0.3125rem;
    fill: ${Colors.darkGrey};

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      margin-right: 0.625rem;
    }
  `,
  brief: css`
    font-size: 1rem;
    color: ${Colors.darkGrey};

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: 1.5rem;
    }
  `,
  year: css`
    font-size: 0.875rem;
    color: ${Colors.darkGrey};

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: 1.125rem;
    }
  `,
}

interface CaseStudyBriefSectionProps {
  title: string
  children: ReactNode
  className?: string
}

const CaseStudyBriefSection: FC<CaseStudyBriefSectionProps> = ({
  title,
  children,
  className,
}) => {
  const combinedClassName = cx(Styles.section, className)

  return (
    <div className={combinedClassName}>
      <Heading level={HeadingLevel.H6} className={Styles.sectionTitle}>
        {title}
      </Heading>
      {children}
    </div>
  )
}

interface Tech {
  icon: SVGProps['asset']
  name: string
}

interface CaseStudyBriefTechBadgeProps {
  tech: Tech
}

const CaseStudyBriefTechBadge: FC<CaseStudyBriefTechBadgeProps> = ({
  tech,
}) => (
  <div className={Styles.techBadge}>
    <SVG className={Styles.techIcon} asset={tech.icon} />
    {tech.name}
  </div>
)

interface CaseStudyBriefProps {
  techs: Tech[]
  year: string
  brief: string
}

const CaseStudyBrief: FC<CaseStudyBriefProps> = ({ techs, year, brief }) => {
  return (
    <CaseStudySection className={Styles.wrapper}>
      <CaseStudyBriefSection
        title="// Technologies"
        className={Styles.techsSection}
      >
        <div className={Styles.techs}>
          {techs.map((tech) => (
            <CaseStudyBriefTechBadge tech={tech} key={tech.name} />
          ))}
        </div>
      </CaseStudyBriefSection>

      <CaseStudyBriefSection
        title="// The Brief"
        className={Styles.briefSection}
      >
        <p className={Styles.brief}>{brief}</p>
      </CaseStudyBriefSection>

      {year && (
        <CaseStudyBriefSection title="// Year" className={Styles.yearSection}>
          <p className={Styles.year}>{year}</p>
        </CaseStudyBriefSection>
      )}
    </CaseStudySection>
  )
}

export default memo(CaseStudyBrief)
