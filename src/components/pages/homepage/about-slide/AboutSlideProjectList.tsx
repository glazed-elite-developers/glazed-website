import { css } from '@emotion/css'
import Heading, { HeadingLevel } from '@components/shared/Heading'
import { Breakpoints, Colors } from '@styles/Theme'
import React, { FC, ReactNode } from 'react'

const Styles = {
  row: css`
    padding-left: 0.9375rem;
    display: flex;
    flex-direction: row;
    color: ${Colors.almostWhite};
    opacity: 0.8;

    @media (min-width: ${Breakpoints.tabletPortrait}) {
      padding: 0.625rem 1.875rem;
    }

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 1rem 1.875rem;
    }
  `,
  rowLeft: css`
    opacity: 0.3;
    font-size: 0.625rem;

    @media (min-width: ${Breakpoints.tabletPortrait}) {
      font-size: 0.625rem;
    }

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: 0.75rem;
    }
  `,
  rowRight: css`
    padding-left: 0.9375rem;
    font-size: 0.75rem;

    @media (min-width: ${Breakpoints.tabletPortrait}) {
      padding-left: 2.0625rem;
      font-size: 1rem;
      font-weight: 700;
    }

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding-left: 2.0625rem;
      font-size: 1.125rem;
      font-weight: 700;
    }
  `,
}

const LineProjectElement: FC<{
  children: ReactNode
}> = ({ children }) => (
  <div className={Styles.row}>
    <div className={Styles.rowLeft}>{'<li>'}</div>
    <div className={Styles.rowRight}>{children}</div>
  </div>
)

const WrapperStyles = {
  wrapper: css`
    display: flex;
    flex-direction: column;
    flex: 1 1 0.00000001rem;
    background-color: ${Colors.glazedBabyBlueText};
    line-height: 1.875rem;
    padding-bottom: 1.25rem;

    @media (min-width: ${Breakpoints.tabletPortrait}) {
      padding-bottom: 3.75rem;
    }

    @media (min-width: ${Breakpoints.desktop}) {
      grid-row: 1 / 3;
      grid-column: 2 / 3;
      align-self: flex-end;
      height: 80%;
      padding: 0 5rem 10rem 0;
    }
  `,
  heading: css`
    padding: 1.25rem 0 0.625rem 3.5rem;
    font-size: 0.625rem;
    color: ${Colors.almostWhite};
    opacity: 0.3;

    @media (min-width: ${Breakpoints.tabletPortrait}) {
      padding: 3.75rem 5rem 0.625rem;
      font-size: 0.75rem;
    }

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 5rem 5rem 4rem;
      font-size: 0.8125rem;
    }
  `,
}

const kindsOfProjects = [
  'Technically complex',
  'Highly customised and detailed',
  'Innovative and using recent technologies',
  "Critically impact on businesses or people's lives",
]

const AboutSlideProjectList: React.FC = () => {
  return (
    <div className={WrapperStyles.wrapper}>
      <Heading level={HeadingLevel.H6} className={WrapperStyles.heading}>
        Our kind of projects:
      </Heading>
      {kindsOfProjects.map((project, index) => (
        <LineProjectElement key={index}>{project}</LineProjectElement>
      ))}
    </div>
  )
}

export default AboutSlideProjectList
