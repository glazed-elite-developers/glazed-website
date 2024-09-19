import React from 'react'
import { css, cx } from '@emotion/css'
import { Breakpoints, Fonts } from '../../styles/Theme'

// Styles
export const Styles = {
  wrapper: css`
    display: flex;
    background-color: #fafbff;
    margin: 0rem 1rem;
    flex: 1 0 33%;
    flex-direction: column;
    justify-content: center;
    align-items: center;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      flex-direction: row;
      max-width: 64rem;
      margin: auto;
    }
  `,
  quote: css`
    order: 1;
    margin: 3.125rem 3.75rem 1.12rem;
    font-family: ${Fonts.text};
    font-size: 1rem;
    color: #9fa8b3;
    font-weight: 400;
    letter-spacing: 0.03rem;
    line-height: 2.125rem;
    text-align: center;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      order: 2;
      font-size: 1.5rem;
      line-height: 3.125rem;
      margin: 10rem 9.625rem 8.8125rem 0;
    }
  `,
  img: css`
    width: 50px;
    height: 50px;
    border-radius: 25px;
  `,
  quoter: css`
    display: flex;
    order: 2;
    flex-direction: column;
    justify-content: center;
    align-items: center;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      order: 1;
      flex: 1 0 15%;
      align-items: flex-start;
      margin-left: 9.625rem;
    }
  `,
  name: css`
    font-size: 0.6875rem;
    font-weight: 700;
    color: #26313d;
    margin-top: 1rem;
  `,
  position: css`
    font-size: 0.6875rem;
    font-weight: 700;
    color: #9fa8b3;
    margin-top: 0.6rem;
    margin-bottom: 1.875rem;
  `,
}

// Quote component props interface
interface QuoteProps {
  className?: string
  quote: string
  imageSrc: string
  name: string
  position: string
}

const Quote: React.FC<QuoteProps> = ({
  className,
  quote,
  imageSrc,
  name,
  position,
}) => {
  return (
    <div className={cx(Styles.wrapper, className)}>
      <p className={Styles.quote}>{quote}</p>
      <div className={Styles.quoter}>
        <img className={Styles.img} src={imageSrc} alt={`${name}'s avatar`} />
        <p className={Styles.name}>{name}</p>
        <p className={Styles.position}>{position}</p>
      </div>
    </div>
  )
}

export default Quote
