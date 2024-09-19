import React from 'react'
import { css } from '@emotion/css'
import { Colors, Breakpoints, Fonts } from '@styles/Theme'
import Layout from '@components/shared/Layout'
import PageLayout from '@components/shared/PageLayout'
import Heading, { HeadingLevel } from '@components/shared/Heading'

const styles = {
  content: css`
    position: relative;
    padding: 4.1875rem 1.25rem 8.1875rem 1.25rem;
    display: flex;
    flex-direction: column;
    justify-content: flex-end;
    flex: 1 0 auto;
    background-color: ${Colors.almostAlmostWhite};

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      justify-content: flex-start;
      padding: 12.25rem 2.5rem 6.25rem 4.75rem;
    }
  `,
  heading: css`
    position: relative;
    padding: 1.875rem 0 5.625rem 0.9375rem;
    font-size: 4.125rem;
    color: ${Colors.glazedBabyBlueText};

    &:before {
      content: '';
      display: block;
      position: absolute;
      top: 0;
      left: 0;
      width: 130px;
      height: 130px;
      border: 1px solid ${Colors.glazedBabyBlueDarker};
      opacity: 0.1;

      @media (min-width: ${Breakpoints.tabletLandscape}) {
        width: 258px;
        height: 258px;
      }
    }

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 5.625rem 0 6.875rem 0.9375rem;
      width: auto;
      font-size: 9rem;
    }
  `,
  descriptions: css`
    display: flex;
    flex-direction: column;
    padding: 0 3.125rem 0 0.9375rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      max-width: 37.5rem;
    }
  `,
  shortDescription: css`
    line-height: 2;
    font-size: 0.875rem;
    font-family: ${Fonts.text};
    color: ${Colors.grey};
    padding-bottom: 0.625rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      order: 2;
      flex: 1 0 auto;
      display: flex;
      align-items: center;
      justify-content: flex-end;
      padding-left: 6.25rem;
      font-size: 2rem;
      line-height: 1.5;
    }
  `,
}

const NotFound: React.FC = () => {
  return (
    <Layout>
      <PageLayout className={styles.content} useDarkNavBarLinks={true}>
        <Heading level={HeadingLevel.H1} className={styles.heading}>
          404
        </Heading>
        <div className={styles.descriptions}>
          <Heading level={HeadingLevel.H3} className={styles.shortDescription}>
            You just hit a route that doesn't exist... The sadness.
          </Heading>
        </div>
      </PageLayout>
    </Layout>
  )
}

export default NotFound
