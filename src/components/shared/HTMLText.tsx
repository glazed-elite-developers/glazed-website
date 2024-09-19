import React, { ReactNode, FC } from 'react'
import { css, cx } from '@emotion/css'
import { Colors, Fonts } from '../../styles/Theme'

// Styles
export const Styles = {
  h1: css`
    position: absolute;
    color: ${Colors.glazedBlueLighter};
  `,
  h2: css`
    position: absolute;
    color: ${Colors.glazedBlueLighter};
    font-family: ${Fonts.text};
    font-weight: 700;
    font-size: 0.75rem;
    opacity: 0.2;
  `,
  p: css`
    position: absolute;
    color: ${Colors.glazedBlueLighter};
  `,
}

// Enum for tags
export enum Tags {
  h1 = 'h1',
  h2 = 'h2',
  p = 'p',
}

interface HTMLTextTagProps {
  tag: Tags
  html: string
}

// Component for HTMLText tags
const HTMLTextTag: FC<HTMLTextTagProps> = ({ tag, html }) => {
  const className = Styles[tag]
  return <span className={className}>{html}</span>
}

// Text Styles for the main elements
export const TextStyles = {
  h1: css`
    position: relative;
  `,
  h2: css`
    position: relative;
    color: ${Colors.glazedBlueDarkerish};
    font-family: ${Fonts.heading};
    font-size: 2.25rem;
    line-height: 2.7rem;
  `,
  p: css`
    position: relative;
    color: ${Colors.glazedBlueLighter};
    font-family: ${Fonts.heading};
    font-size: 0.88rem;
    opacity: 0.8;
    line-height: 1.5rem;
  `,
}

// Props interface for HTMLText content
interface HTMLTextContentProps {
  children: ReactNode
  inline?: boolean
}

// Component for HTMLText content
const HTMLTextContent: FC<HTMLTextContentProps> = ({ children, inline }) => {
  const className = inline
    ? css`
        padding-left: 1.56rem;
      `
    : css`
        padding-left: 1.56rem;
        display: inline-block;
      `
  return <span className={className}>{children}</span>
}

// Main HTMLText component
interface HTMLTextProps {
  tag: Tags
  className?: string
  children: ReactNode
}

const HTMLText: FC<HTMLTextProps> = ({ tag, className, children }) => {
  switch (tag) {
    case Tags.h1:
      return (
        <h1 className={cx(TextStyles.h1, className)}>
          <HTMLTextTag tag={Tags.h1} html="<h1>" />
          <HTMLTextContent>{children}</HTMLTextContent>
          <HTMLTextTag tag={Tags.h1} html="</h1>" />
        </h1>
      )
    case Tags.h2:
      return (
        <h2 className={cx(TextStyles.h2, className)}>
          <HTMLTextTag tag={Tags.h2} html="<h2>" />
          <HTMLTextContent>{children}</HTMLTextContent>
          <HTMLTextTag tag={Tags.h2} html="</h2>" />
        </h2>
      )
    case Tags.p:
      return (
        <p className={cx(TextStyles.p, className)}>
          <HTMLTextTag tag={Tags.p} html="<p> " />
          <HTMLTextContent inline>{children}</HTMLTextContent>
          <HTMLTextTag tag={Tags.p} html=" </p>" />
        </p>
      )
  }
}

export default HTMLText
