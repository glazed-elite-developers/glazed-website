import FullPageSlide from '@components/shared/FullPageSlide'
import Heading, { HeadingLevel } from '@components/shared/Heading'
import HTMLText, { Tags } from '@components/shared/HTMLText'
import { css } from '@emotion/css'
import { Breakpoints, Colors } from '@styles/Theme'
import React, { memo, RefObject } from 'react'
import AboutSlideProjectList from './AboutSlideProjectList'

const wrapper = css`
  display: grid;
  grid-template-rows: auto minmax(auto, 11.25rem) 1fr;
  flex: 1 0 auto;
  padding: 4.1875rem 0 0 1.25rem;
  overflow: hidden;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    grid-template-rows: auto 1fr;
    grid-template-columns: 1fr 1fr;
    padding: 6.25rem 0 0 4.75rem;
  }

  @media (min-width: ${Breakpoints.desktop}) {
    grid-template-columns: 6fr 4fr;
  }
`

const about = css`
  display: flex;
  flex-direction: column;
  flex: 0 0 auto;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    grid-column: 1 / 3;
    padding: 0 4.75rem 4.75rem 0;
  }

  @media (min-width: ${Breakpoints.desktop}) {
    grid-column: 1 / 2;
  }
`

const heading = css`
  position: relative;
  padding: 1.875rem 0 0.625rem 0.9375rem;
  font-size: 1.125rem;
  color: ${Colors.grey};

  &::before {
    content: '';
    display: block;
    position: absolute;
    top: 0;
    left: 0;
    width: 130px;
    height: 130px;
    border: 1px solid ${Colors.glazedBabyBlueText};
    opacity: 0.1;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      width: 258px;
      height: 258px;
    }
  }

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    padding: 5.625rem 0 1.875rem 0.9375rem;
    width: auto;
    color: ${Colors.darkGrey};
    font-size: 2rem;
  }
`

const contentText = css`
  padding: 0 0.9375rem;
  opacity: 0.6;
  font-size: 0.75rem;
  line-height: 2;
  color: ${Colors.glazedGreyText};

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: block;
    font-size: 1.5rem;
  }
`

const contentTextLine = css`
  display: inline;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: block;
  }
`

const dimmedOnDesktop = css`
  @media (min-width: ${Breakpoints.tabletLandscape}) {
    opacity: 0.6;
  }
`

const htmlTextWrapper = css`
  display: flex;
  align-items: center;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: block;
    padding: 4.75rem 2.5rem 0 0;
  }

  @media (min-width: ${Breakpoints.desktop}) {
    grid-column: 1 / 2;
    padding: 4.75rem 4.75rem 0 2.5rem;
    max-width: 47.5rem;
  }
`

const htmlTag = css`
  padding: 0.625rem 0.9375rem 1.25rem 0.9375rem;
  color: ${Colors.glazedBabyBlueText};
  font-size: 1.125rem;
  line-height: 1.5;
  max-width: 21.875rem;
  text-align: left;

  @media (min-width: ${Breakpoints.tabletPortrait}) {
    max-width: 30rem;
  }

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    max-width: none;
    font-size: 2.125rem;
    padding: 0;
    align-self: flex-end;
  }
`

// Component
interface AboutSlideProps {
  innerRef?: RefObject<HTMLDivElement>
  id?: string
  onResize?: () => void
}

const AboutSlide: React.FC<AboutSlideProps> = memo(
  ({ innerRef, id, onResize }) => {
    return (
      <FullPageSlide
        className={wrapper}
        onResize={onResize}
        id={id}
        innerRef={innerRef}
      >
        <div className={about}>
          <Heading level={HeadingLevel.H1} className={heading}>
            // about us
          </Heading>
          <div className={contentText}>
            <p className={contentTextLine}>
              Every team member is highly experienced (8y avg), strives for
              excellency and has access to the colossal combined knowledge of
              the whole team.
            </p>
            <p className={`${contentTextLine} ${dimmedOnDesktop}`}>
              We act as (an extension of) your development team, in very
              flexible team sizes, adapting to your processes and with a tight
              feedback loop.
            </p>
          </div>
        </div>
        <div className={htmlTextWrapper}>
          <HTMLText tag={Tags.h2} className={htmlTag}>
            It's your code, ready to hand off or build a team around at any
            time, but we care for it as it were ours.
          </HTMLText>
        </div>
        <AboutSlideProjectList />
      </FullPageSlide>
    )
  }
)

export default AboutSlide
