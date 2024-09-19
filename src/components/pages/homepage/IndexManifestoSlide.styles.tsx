import { css } from '@emotion/css'
import { Breakpoints, Colors } from '@styles/Theme'

export const wrapper = css`
  position: relative;
  display: flex;
  flex-direction: column;
  padding: 4.1875rem 2.5rem 6rem;
  transform: translateZ(0);

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    padding: 13.5625rem 4.75rem 0;
  }
`

export const section = css`
  position: relative;
`

export const contentWrapper = css`
  display: flex;
  flex-direction: column;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    flex-direction: row;
    flex: 1 1 auto;
  }
`

export const funPart = css`
  display: flex;
  height: 5.5rem;
  position: absolute;
  right: 0;
  bottom: 0;
  left: 2.5rem;
  background-color: ${Colors.glazedBabyBlueText};

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    position: static;
    height: auto;
    margin: 0 -4.75rem 0 0;
    flex: 0 1 40%;
  }
`

export const image = css`
  flex: 1 1 0.0000001rem;
  display: flex;
  opacity: 0.3;
`

export const content = css`
  @media (min-width: ${Breakpoints.tabletPortrait}) {
    display: flex;
    flex: 1 1 auto;
  }
`

export const displayTitle = css`
  &::after {
    content: '';
    position: absolute;
    top: -2rem;
    left: -1.25rem;
    width: 8.125rem;
    height: 8.125rem;
    border: 1px solid rgba(159, 168, 179, 0.1);
  }
  padding-bottom: 1.25rem;

  @media (min-width: ${Breakpoints.tabletPortrait}) {
    &::after {
      display: none;
    }
    padding-left: 1.25rem;
    padding-bottom: 6.25rem;
  }
`

export const verticalLine = css`
  content: '';
  position: fixed;
  top: 0;
  bottom: 0;
  margin-left: -1.25rem;
  border: 1px solid rgba(159, 168, 179, 0.1);
`

export const block = css`
  &:not(:last-child) {
    margin-bottom: 1.25rem;
  }

  @media (min-width: ${Breakpoints.tabletPortrait}) {
    position: relative;
    flex: 1 1 33%;
    padding: 0 1.25rem;
    &::before {
      ${verticalLine}
    }
    display: flex;
    flex-direction: column;
    &:last-child::after {
      content: '';
      position: fixed;
      top: 0;
      bottom: 0;
      margin-left: 1.25rem;
      align-self: flex-end;
      border: 1px solid rgba(159, 168, 179, 0.1);
    }
  }
`

export const pre = css`
  display: none;
  color: #2560f2;
  font-size: 0.75rem;
  padding-bottom: 1.125rem;

  @media (min-width: ${Breakpoints.tabletPortrait}) {
    display: block;
  }
`

export const title = css`
  padding-bottom: 0.625rem;
  color: ${Colors.darkGreyDarker};
  line-height: 1.5rem;

  @media (min-width: ${Breakpoints.tabletPortrait}) {
    color: ${Colors.grey};
    padding-bottom: 1.125rem;
  }
`

export const strong = css`
  @media (min-width: ${Breakpoints.tabletPortrait}) {
    color: ${Colors.darkGreyDarker};
  }
`

export const paragraph = css`
  font-weight: 400;
  font-size: 0.75rem;
  letter-spacing: -0.025rem;
  line-height: 1.5rem;
  color: ${Colors.darkGrey};
  opacity: 0.8;

  @media (min-width: ${Breakpoints.tabletPortrait}) {
    font-size: 0.875rem;
    line-height: 2.125rem;
  }
`
