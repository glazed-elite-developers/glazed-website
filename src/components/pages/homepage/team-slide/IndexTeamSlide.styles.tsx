import { css } from '@emotion/css'
import { Breakpoints, Colors, Fonts } from '@styles/Theme'

export const wrapper = css`
  padding: 4.1875rem 1.25rem 4.1875rem;
  height: auto;
  flex: 1 0 auto;
  background-color: ${Colors.glazedBabyBlueText};

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    padding: 6.25rem 4.75rem;
  }
`

export const heading = css`
  opacity: 0.9;
  font-size: 1.125rem;
  line-height: 1.75rem;

  @media (min-width: ${Breakpoints.tabletPortrait}) {
    font-size: 2rem;
    line-height: 3rem;
    width: 183px;
  }
`

export const grid = css`
  display: flex;
  flex-wrap: wrap;
`

export const square = css`
  flex: 0 0 50%;

  @media (min-width: ${Breakpoints.tabletPortrait}) {
    flex: 0 0 33.3333333%;
  }

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    flex: 0 0 25%;
  }

  @media (min-width: ${Breakpoints.desktop}) {
    flex: 0 0 20%;
  }
`

export const squareContent = css`
  padding: 0.9375rem;
  display: flex;
  flex-direction: column;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    padding: 2.1875rem 1.875rem;
  }
`

export const squareWithBorder = css`
  border: 1px solid rgba(105, 192, 254, 0.1);
`

export const headingSquare = css`
  color: ${Colors.almostWhite};
  padding: 30% 0.9375rem 0;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    padding: 30% 1.4375rem 0;
  }
`

export const link = css`
  font-family: ${Fonts.heading};
  font-size: 0.75rem;
  color: ${Colors.glazedBabyBlue};
`

export const developerSquare = css`
  padding: 0;
  flex-direction: row;
  color: ${Colors.almostWhite};
  background-color: ${Colors.glazedBlueDarkestish};

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    padding: 0;
  }
`

export const developerSquareLink = css`
  padding: 0.9375rem;
  display: flex;
  flex-direction: column;
  flex: 1 1 0;

  &:before {
    content: '';
    position: absolute;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
    opacity: 0;
    background-color: ${Colors.glazedBlueDark};

    transition: opacity 300ms;
  }

  &:hover:before,
  &:focus:before,
  &:active:before {
    opacity: 1;
  }

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    padding: 2.1875rem 1.875rem;
  }
`

export const developerSquareContent = css`
  display: flex;
  flex-direction: column;
  justify-content: flex-end;
  flex: 1 1 0;
  color: ${Colors.almostWhite};
  opacity: 0.8;
  transition: opacity 300ms;
  z-index: 0;

  &:hover,
  &:focus {
    opacity: 1;
  }
`

export const developerBackgroundImageWrapper = css`
  position: absolute;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
  opacity: 0.4;
  transition: opacity 300ms;

  &:hover {
    opacity: 0.6;
  }
`

export const developerBackgroundImage = css`
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
`

export const developerName = css`
  font-size: 0.875rem;
  padding-bottom: 0.875rem;
  white-space: pre-line;
`

export const developerSkills = css`
  font-size: 0.625rem;
  font-family: ${Fonts.heading};
`

export const sendApplication = css`
  flex: 1 1 0;
  color: ${Colors.almostWhite};
  font-size: 1rem;
  line-height: 1.5;

  @media (max-width: ${Breakpoints.phone}) {
    padding-top: 1rem;
  }

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    font-size: 1.6rem;
  }
`

export const motto = css`
  color: ${Colors.almostWhite};
  font-size: 1rem;
  line-height: 1.5;
  opacity: 0.7;

  @media (max-width: ${Breakpoints.phone}) {
    padding-top: 1rem;
  }

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    font-size: 1.6rem;
  }
`
