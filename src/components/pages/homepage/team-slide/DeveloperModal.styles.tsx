import { css } from '@emotion/css';
import { Breakpoints, Colors, Fonts } from '@styles/Theme';

export const wrapper = css`
  background-color: ${Colors.glazedBlueDark};
`;

export const contentWrapper = css`
  align-items: stretch;
`;

export const content = css`
  position: relative;
  padding: 4.1875rem 1.25rem 4.1875rem 1.25rem;
  display: flex;
  flex-direction: column;
  justify-content: flex-end;
  flex: 1 0 auto;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    justify-content: flex-start;
    padding: 6.25rem 2.5rem 6.25rem 4.75rem;
  }
`;

export const backgroundImage = css`
  position: absolute;
  top: 0;
  right: 0;
  bottom: 0;
  width: 100%;
  max-width: 90%;
  z-index: 0;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    max-width: 64rem;
    left: unset;
  }
`;

export const developerBackgroundImage = css`
  ${backgroundImage}
  opacity: 0.6;
`;

export const overlayImage = css`
  ${backgroundImage}
  opacity: 0.1;
`;

export const logoWrapper = css`
  position: absolute;
  top: 0;
  left: 0;
  padding: 1.25rem;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: none;
  }
`;

export const logo = css`
  height: 2.1875rem;
`;

export const closeButtonWrapper = css`
  display: none;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: flex;
    position: absolute;
    top: 0;
    right: 0;
  }
`;

export const closeButton = css`
  padding: 0;
  flex: 1 1 auto;
  width: 8.5rem;
  height: 8.5rem;
  background-color: ${Colors.glazedBlueDarker};
  font-family: ${Fonts.heading};
  font-size: 0.625rem;
  opacity: 0.6;
  color: ${Colors.white};
`;

export const heading = css`
  position: relative;
  padding: 1.875rem 0 5.625rem 0.9375rem;
  font-size: 1.125rem;
  color: ${Colors.almostWhite};

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
    padding: 5.625rem 0 1.875rem 0.9375rem;
    width: auto;
    font-size: 1.8rem;
  }
`;

export const descriptions = css`
  display: flex;
  flex-direction: column;
  padding: 0 3.125rem 0 0.9375rem;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    max-width: 37.5rem;
    flex: 1 0 auto;
  }
`;

export const shortDescription = css`
  line-height: 2;
  font-size: 0.875rem;
  font-family: ${Fonts.text};
  color: ${Colors.almostWhite};
  padding-bottom: 0.625rem;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    order: 2;
    flex: 1 0 auto;
    display: flex;
    align-items: center;
    justify-content: flex-end;
    padding-left: 6.25rem;
    font-size: 1.6rem;
    line-height: 1.5;
  }
`;

export const description = css`
  line-height: 2;
  font-size: 0.75rem;
  color: ${Colors.white};
  opacity: 0.7;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    order: 1;
    font-size: 1.2rem;
  }
`;

export const skillsAndLinkedIn = css`
  display: flex;
  flex-direction: row-reverse;
  align-items: center;
  justify-content: space-between;
  padding: 1.875rem 0 1.875rem 0.9375rem;
  font-size: 0.625rem;
  z-index: 0;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    padding: 0;
  }
`;

export const skills = css`
  color: ${Colors.almostWhite};
  opacity: 0.4;
  font-family: ${Fonts.heading};

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: none;
  }
`;

export const desktopSkills = css`
  display: none;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: block;
    position: absolute;
    top: 50%;
    right: 2.5rem;
    min-width: 9.375rem;
    transform: translateY(-50%);
    color: ${Colors.almostWhite};
    white-space: pre-line;
    font-size: 1rem;
    line-height: 2;
    opacity: 0.6;
  }
`;

export const linkedinLink = css`
  font-family: ${Fonts.heading};
  color: ${Colors.glazedBabyBlue};

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    font-size: 0.75rem;
    min-width: 9.375rem;
  }
`;

export const mobileFooter = css`
  position: absolute;
  bottom: 0;
  left: 0;
  right: 0;
  background-color: ${Colors.glazedBlueDarkestish};
  display: flex;
  align-items: center;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    display: none;
  }
`;

export const mobileCloseButton = css`
  padding: 1.25rem;
  background: none;
  color: ${Colors.almostWhite};
  font-family: ${Fonts.heading};
  font-size: 0.625rem;
`;
