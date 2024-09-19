import * as React from 'react'
import { css } from '@emotion/css'
import BackgroundImage from 'gatsby-background-image'
import { PageContent } from './PageContent'
import { Breakpoints, Colors, Fonts } from '../../styles/Theme'

const Styles = {
  developer: css`
    color: ${Colors.white};
    padding: ${1}rem;
    padding-top: ${10.9375}rem;
    position: relative;
    height: 100%;
    background-color: ${'blue'};
    background-repeat: no-repeat;
    &::before {
      background-position: left ${40}%, top ${0}rem;
    }
  `,

  name: css`
    font-size: 1rem;
    font-family: ${Fonts.heading};
    position: relative;
    &::after {
      content: '';
      position: absolute;
      top: ${-4}rem;
      left: ${-1}rem;
      width: ${8.125}rem;
      height: ${8.125}rem;
      border: ${1}px solid ${'69C0FE'};
      opacity: 0.5;
    }
    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: ${2}rem;
      &::after {
        width: ${16.125}rem;
        height: ${16.125}rem;
      }
    }
  `,

  descriptionWrapper: css`
    display: flex;
    flex-direction: column;
  `,

  description: css`
    font-size: ${0.875}rem;
    font-family: ${Fonts.text};
    color: ${Colors.grey};
    order: 2;
    padding-top: ${1}rem;
    @media (min-width: ${Breakpoints.tabletLandscape}) {
      order: 1;
      max-width: ${31.375}rem;
      font-size: ${1.5}rem;
      line-height: ${3}rem;
      padding-top: ${1}rem;
    }
  `,

  headline: css`
    font-size: ${1}rem;
    font-family: ${Fonts.text};
    font-weight: 700;
    padding-top: ${6.1875}rem;
    max-width: ${407}px;
    order: 1;
    @media (min-width: ${Breakpoints.tabletLandscape}) {
      order: 2;
      padding-top: ${4.5}rem;
      padding-left: ${6.9375}rem;
      font-size: ${2}rem;
      &::before {
        content: '// ';
      }
    }
  `,
}

interface TeamDetailProps {
  developer: {
    name: string
    description: string
    headline: string
  }
  image: any // Replace `any` with the appropriate type for the image prop
}

const TeamDetail: React.FC<TeamDetailProps> = ({ developer, image }) => {
  return (
    <PageContent>
      <BackgroundImage fluid={image} className={Styles.developer}>
        <div className={Styles.name}>
          {developer.name.split(' ').map((namePart, index) => (
            <div key={index}>{namePart}</div>
          ))}
        </div>
        <div className={Styles.descriptionWrapper}>
          <div className={Styles.description}>{developer.description}</div>
          <div className={Styles.headline}>{developer.headline}</div>
        </div>
      </BackgroundImage>
    </PageContent>
  )
}

export default TeamDetail
