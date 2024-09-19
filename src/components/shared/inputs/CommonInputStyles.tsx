import { css } from '@emotion/css'
import { Breakpoints, Colors, Fonts } from '@styles/Theme'

export const wrapper = css`
  display: flex;
  flex-direction: column;
`

export const labelWrapper = css`
  display: flex;
  align-items: center;
  justify-content: space-between;
`

export const label = css`
  color: #9fa8b3;
  font-size: 0.625rem;
  font-weight: 700;
  line-height: 23px;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    font-size: 0.6875rem;
  }
`

export const error = css`
  font-size: 0.6875rem;
  font-family: ${Fonts.heading};
  color: ${Colors.orange};
  opacity: 0;
  visibility: hidden;
  transition: visibility 0.5s, opacity 0.5s;
`

export const errorVisible = css`
  opacity: 1;
  visibility: visible;
  transition: opacity 0.1s;
`

export const input = css`
  background-color: #f4f6fb;
  transition: border-width 300ms;
  border-width: 0;
  color: #9fa8b3;
  display: block;
  font-family: ${Fonts.heading};
  line-height: 1.44rem;
  margin-top: 0.625rem;
  padding: 0.93rem 1.25rem;
  font-size: 0.75rem;
  border-bottom-width: 1px;
  border-color: transparent;
  border-radius: 0;
  resize: none;

  @media (min-width: ${Breakpoints.tabletLandscape}) {
    font-size: 0.93rem;
  }

  &:hover {
    border-color: #2962f6;
    border-bottom-width: 1px;
  }
`
