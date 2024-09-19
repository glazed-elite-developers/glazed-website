import { css } from '@emotion/css'
import { Colors, Breakpoints, Fonts } from '@styles/Theme'
import { StyleVariables as HeaderStyleVariables } from './Header'

export const wrapper = css`
  background-color: ${Colors.almostAlmostWhite};
`

export const contentWrapper = css`
  align-items: stretch;
`

export const scrollContainer = css`
  display: flex;
  flex-direction: column;
  flex: 1 1 0.0000001rem;
`

export const content = css`
  display: flex;
  flex-direction: column;
  flex: 1 0 auto;
`

export const header = css`
  position: absolute;
  top: 0;
  right: 0;
  left: 0;
`

export const closeButtonWrapper = css`
  display: none;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: flex;
    pointer-events: auto;
  }
`

export const closeButton = css`
  opacity: 0.3;
  padding: 0;

  svg {
    fill: ${Colors.darkGrey};
    stroke: ${Colors.darkGrey};
  }
`

export const contacts = css`
  display: flex;
  flex-direction: column;
  flex: 1 1 auto;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    flex-direction: row;
    padding-top: ${HeaderStyleVariables.height};
  }
`

export const map = css`
  position: relative;
  display: flex;
  flex: 0 0 12.5rem;
  background-color: #dddddd;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    flex: 1 1 0.000000001rem;
    padding-top: ${HeaderStyleVariables.height};
  }
`

export const mapImage = css`
  position: absolute;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
`

export const mapPin = css`
  position: absolute;
  bottom: 5rem;
  left: 23%;
  height: 30px;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    bottom: 30%;
    left: 51%;
    height: 50px;
  }
`

export const form = css`
  position: relative;
  display: flex;
  flex-direction: column;
  padding: 2.8125rem 1.25rem 5.625rem;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    justify-content: center;
    padding: 3.75rem 3.75rem 3.75rem 5rem;
    flex: 0 1 50%;
  }

  @media (min-width: ${Breakpoints.desktop}) {
    flex: 0 1 40%;
  }
`

export const heading = css`
  font-size: 1.125rem;
  color: ${Colors.darkGreyDarker};
  opacity: 0.9;

  &::before {
    content: '// ';
  }

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    font-size: 2rem;

    &::before {
      display: none;
    }
  }
`

export const hidden = css`
  opacity: 0;
  visibility: hidden;
  transition: visibility 0ms 500ms, opacity 500ms;
`

export const visible = css`
  visibility: visible;
  transition: opacity 100ms;
`

export const formMessage = css`
  display: inline;
  padding: 0.3125rem 0 0.625rem;
  font-size: 0.75rem;
  line-height: 2;
  color: ${Colors.darkGrey};
  opacity: 0.6;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: flex;
    flex-direction: column;
    padding: 1.5625rem 0 2.8126rem;
    font-size: 0.875rem;
    opacity: 1;
  }
`

export const formSuccessMessage = css`
  text-align: center;
`

export const formMessageHidden = css`
  ${formMessage};
  ${hidden};

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    opacity: 0;
  }
`

export const fillFormMessage = css`
  display: inline;
  padding-right: 0.3125rem;
`

export const sendEmailParagraph = css`
  display: inline;
  color: ${Colors.grey};
`

export const link = css`
  color: ${Colors.glazedBlueDarkish};
`

export const socialNetworks = css`
  display: none;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    position: absolute;
    top: 0;
    right: 4.6875rem;
    margin: -0.9375rem;
    display: flex;
  }
`

export const socialIconLink = css`
  display: flex;
  margin: 0.9375rem;
`

export const socialIcon = css`
  opacity: 0.4;

  svg {
    fill: ${Colors.darkGrey};
  }
`

export const addressDetails = css`
  position: absolute;
  top: 1.25rem;
  right: 1.25rem;
  width: 12.875rem;
  height: 12.875rem;
  padding: 1.5625rem 2.5rem 1.5625rem 1.25rem;
  background-color: ${Colors.white};
  font-size: 0.75rem;
  font-family: ${Fonts.heading};
  line-height: 1.75;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    top: 3.125rem;
    right: 3.125rem;
    width: 18.125rem;
    height: 18.125rem;
    padding: 3.125rem 2.5rem 3.4375rem 2.5rem;
    font-size: 0.84375rem;
  }
`

export const address = css`
  white-space: pre-line;
  color: ${Colors.darkGrey};
`

export const postalCode = css`
  padding: 1.5625rem 0 0.9375rem;
  color: ${Colors.grey};

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    padding: 1.875rem 0 2.5rem;
  }
`

export const openInMapsLink = css`
  ${link};
  font-size: 0.75rem;
`

export const jobOfferForm = css`
  ${visible};

  @media (min-width: ${Breakpoints.desktop}) {
    max-width: 28.125rem;
  }
`

export const mobileCloseButton = css`
  padding: 1.25rem;
  background: none;
  color: ${Colors.almostWhite};
  font-family: ${Fonts.heading};
  font-size: 0.625rem;
`
