import { css } from '@emotion/css'
import { Breakpoints, Colors, Fonts } from '@styles/Theme'

var cubeOuterEdge = 37.5
var cubeContentProjectionLength = 8.125

export const mobile = css`
  display: inherit;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: none;
  }
`

export const tabletLandscape = css`
  display: none;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: inherit;
  }
`

export const wrapper = css`
  padding: 8.0625rem 2.0625rem;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  position: relative;
  overflow: hidden;
`

export const content = css`
  position: relative;
  display: flex;
  flex-direction: column;
  width: 100%;
  max-width: 100%;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    flex-direction: row;
    width: ${cubeOuterEdge + 2 * cubeContentProjectionLength}rem;
    height: ${cubeOuterEdge}rem;
  }
`

export const cube = css`
  display: none;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: block;
    position: absolute;
    top: calc(50% - 250px);
    left: calc(50% - 250px);
  }
`

export const logoWrapper = css`
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
`

export const logo = css`
  height: 5rem;
`

export const pulse = css`
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  width: 1px;
  height: 1px;
  border-radius: 50%;
`

export const imageForeground = css`
  position: absolute;
  width: 100%;
  height: 100%;
  top: 0;
  left: 0;
  pointer-events: none;
  background-color: ${Colors.white};
`

export const backgroundImage = css`
  position: absolute;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
`

export const animatedMask = css`
  position: absolute;
  width: 100%;
  height: 100%;
  top: 0;
  left: 0;
  pointer-events: none;
  opacity: 0.65;
  background-color: ${Colors.glazedBlueMidnight};
`

export const htmlText = css`
  color: ${Colors.almostWhite};
  font-size: 0.85rem;
  line-height: 1.5rem;
  padding: 0.625rem 0;
  max-width: 13rem;
  top: 1.25rem;
  right: 0;
  align-self: flex-end;
  margin-right: -0.9375rem;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    position: absolute;
    padding: 0;
    align-self: initial;
    margin-right: 0;
  }
`

export const socialNetworks = css`
  display: none;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: flex;
    position: absolute;
    padding: 4.375rem;
    bottom: 0;
    left: 0;
    margin: -0.9375rem 0;
  }
`

export const socialIconLink = css`
  display: flex;
  margin: 0.9375rem;
`

export const socialIcon = css`
  opacity: 0.4;
  fill: ${Colors.white};
`

export const mainHeading = css`
  display: flex;
  flex-wrap: wrap;
  font-size: 1.5rem;
  line-height: 2.125rem;
  color: ${Colors.almostWhite};
  height: 4.25rem;
  max-width: 16rem;
  overflow-y: hidden;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    font-size: 2.25rem;
    line-height: 2.75rem;
    height: 5.5rem;
    max-width: 24rem;
  }
`

export const commentedText = css`
  font-weight: 700;
  margin-bottom: 0.25rem;
  color: ${Colors.grey};
  opacity: 0.5;
  font-family: ${Fonts.text};
  font-size: 0.75rem;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    font-size: 0.875rem;
  }
`

export const exploreCasesButtonWrapper = css`
  align-self: flex-start;
  margin: 1rem 0 1.125rem;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    margin: 0.9375rem 0 0;
  }
`

export const exploreCasesButton = css`
  align-self: flex-start;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    height: 3.125rem;
  }
`

export const quote = css`
  margin-top: 5rem;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    max-width: 70rem;
    margin-top: 20rem;
    margin-bottom: 5rem;
  }
`

export const techStackIcons = css`
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
  position: absolute;
  bottom: 0;
  right: 0;
  left: 0;
  opacity: 0.7;
  width: 6.25rem;
  margin-left: -1.25rem;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    flex: 0 0 3.125rem;
    width: auto;
    flex-wrap: initial;
    margin-left: 0;
    bottom: 5.625rem;
  }
`

export const techStackIcon = css`
  flex: 0 0 33.333333%;
  margin: 0.625rem 0;
  fill: ${Colors.lightGrey};
  transform: translateZ(0);
  position: relative;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    flex: 0 0 3.125rem;
  }
`

export const clients = css`
  display: flex;
  position: absolute;
  flex-direction: column;
  right: 0;
  bottom: -9rem;
  left: 2.375rem;
  opacity: 0.7;
  max-width: 16rem;
  max-height: 7rem;
  overflow: hidden;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    bottom: -7.5rem;
    left: 7.875rem;
    max-width: 28rem;
    max-height: none;
  }
`

export const clientsSpan = css`
  color: ${Colors.grey};
  font-size: 0.75rem;
  line-height: 24px;
`

export const clientsImages = css`
  margin-top: 0.375rem;
  display: flex;
  flex-wrap: wrap;
  justify-content: space-around;
`

export const clientImage = css`
  width: auto;
  height: 14px;
  object-fit: contain;
  margin-bottom: 1rem;
  flex: 0 1 50%;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    flex: 0 1 33%;
  }
`

export const headingWrapper = css`
  display: flex;
  flex-direction: column;
  justify-content: center;
  z-index: 0;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    margin-left: 2.5rem;
  }
`

export const skillComments = css`
  position: absolute;
  bottom: 3.75rem;
  right: 0;
  display: none;
  padding-top: 5rem;
  color: ${Colors.almostWhite};
  line-height: 2.4;
  font-family: ${Fonts.heading};
  font-size: 0.6875rem;
  font-weight: 700;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: block;
  }
`
