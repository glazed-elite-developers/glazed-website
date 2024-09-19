import { css } from '@emotion/css'
import { Breakpoints, Colors } from '@styles/Theme'
import { StyleVariables as MobileFooterStyleVariables } from '@components/shared/MobileFooter'

const footerHeight = MobileFooterStyleVariables.height
const paddingBottom = `${footerHeight[1] + 1.25}rem`

export const wrapper = css`
  position: relative;
  display: flex;
  flex-direction: column;
  justify-content: flex-end;
  padding: 4.1875rem 2.5rem ${paddingBottom} 1.25rem;
  overflow: hidden;
  color: ${Colors.almostWhite};

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    align-items: center;
    padding: 6.25rem 7.25rem 1.875rem 4.75rem;
    justify-content: center;
  }

  @media (min-width: ${Breakpoints.desktop}) {
    padding: 6.25rem 16.875rem 1.875rem 8.75rem;
  }
`

export const maskContainer = css`
  background-color: rgba(34, 39, 63, 0.8);
`

export const backgroundImage = css`
  position: absolute;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
`

export const grid = css`
  position: relative;
  width: 100%;
  max-width: 31.25rem;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    max-width: 75rem;
  }

  padding: 1px 0 0 1px;
`

export const backgroundGrid = css`
  position: absolute;
  top: 1px;
  right: 0;
  bottom: 0;
  left: 1px;
`

export const squareRow = css`
  display: flex;
  flex-wrap: wrap;
`

export const backgroundSquareRow = css`
  ${squareRow};
  opacity: 0.7;
`

export const dimmedBackgroundSquareRow = css`
  ${squareRow};
  opacity: 0.3;
`

export const onlyInMobile = css`
  display: none;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: flex;
  }
`

export const square = css`
  margin: -1px 0 0 -1px;
  flex: 0 0 50%;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    flex: 0 0 25%;
  }
`

export const squareContent = css`
  padding: 1px 0 0 1px;
`

export const squareWithBorder = css`
  ${square};
  opacity: 0.7;
  border: 1px solid ${Colors.darkGrey};
`

export const headingSquareContent = css`
  ${squareContent};
  padding: 0 0.9375rem;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    padding: 0 1.4375rem;
  }

  justify-content: center;
`

export const fakeSquareContent = css`
  border-color: transparent;
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
