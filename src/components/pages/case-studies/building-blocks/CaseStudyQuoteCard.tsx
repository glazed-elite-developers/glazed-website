import React from 'react'
import { css, cx } from '@emotion/css'
import CaseStudySection from './CaseStudySection'
import { Breakpoints, Colors, Fonts } from '@styles/Theme'
import { GatsbyImage, GatsbyImageProps } from 'gatsby-plugin-image'

// Styles encapsulated in a Styles object
const Styles = {
  wrapper: css`
    display: flex;
    flex-direction: column;
    padding: 3.125rem 1.875rem;
    margin: 2.5rem 1.25rem;
    max-width: 64rem;
    background-color: ${Colors.almostAlmostWhite};

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      margin: 2.5rem auto;
      padding: 8.75rem 9.375rem;
      flex-direction: row-reverse;
    }
  `,

  author: css`
    display: flex;
    flex-direction: column;
    align-items: center;
    padding-top: 0.625rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      align-items: flex-start;
      flex: 0 1 10rem;
    }
  `,

  avatarImage: css`
    width: 3.125rem;
    height: 3.125rem;
    border-radius: 50%;
  `,

  authorName: css`
    padding: 0.625rem 0;
    font-size: 0.6875rem;
    font-family: ${Fonts.heading};
    color: ${Colors.darkGreyDarker};
  `,

  authorTitle: css`
    font-size: 0.6875rem;
    font-family: ${Fonts.heading};
    color: ${Colors.grey};
  `,

  quote: css`
    font-size: 1rem;
    line-height: 2;
    color: ${Colors.grey};
    text-align: center;
    padding-bottom: 1.875rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding-bottom: 0;
      flex: 1 1 0.00000001rem;
      font-size: 1.5rem;
      text-align: left;
    }
  `,
}

export interface Author {
  name: string
  title: string
  avatarImage?: GatsbyImageProps['image']
}

interface CaseStudyQuoteCardProps {
  className?: string
  author: Author
  quote: string
}

const CaseStudyQuoteCard: React.FC<CaseStudyQuoteCardProps> = ({
  className,
  author,
  quote,
}) => {
  return (
    <CaseStudySection className={cx([Styles.wrapper, className])}>
      <p className={Styles.quote}>{quote}</p>
      <div className={Styles.author}>
        {author.avatarImage && (
          <GatsbyImage
            className={Styles.avatarImage}
            image={author.avatarImage}
            alt={author.name}
          />
        )}
        <p className={Styles.authorName}>{author.name}</p>
        <p className={Styles.authorTitle}>{author.title}</p>
      </div>
    </CaseStudySection>
  )
}

export default CaseStudyQuoteCard
