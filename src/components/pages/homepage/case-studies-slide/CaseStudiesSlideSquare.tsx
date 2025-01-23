import React, { ReactNode, SyntheticEvent, memo } from 'react'
import { cx, css } from '@emotion/css'
import { Breakpoints, Colors } from '@styles/Theme'
import Square from '@components/shared/Square'

export const Styles = {
  squareContent: css`
    display: flex;
    flex-direction: column;
  `,

  leftBlueSquareStyles: css`
    &::before {
      content: '';
      display: block;
      position: absolute;
      bottom: 1px;
      left: 1px;
      width: 5px;
      height: 5px;
      background-color: ${Colors.glazedBlueDarkerish};
      opacity: 0.8;
    }
  `,

  content: (withCornerDot: boolean) => css`
    display: flex;
    flex-direction: column;
    flex: 1 1 0.000001rem;
    padding: 0.625rem 0.9375rem 0.9375rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 1.25rem 1.875rem 1.875rem;
    }

    ${withCornerDot &&
    css`
      &::before {
        content: '';
        display: block;
        position: absolute;
        bottom: 1px;
        left: 1px;
        width: 5px;
        height: 5px;
        background-color: ${Colors.glazedBlueDarkerish};
        opacity: 0.8;
      }
    `}
  `,

  hidden: css`
    visibility: hidden;
    opacity: 0;
    transition: visibility 0ms 400ms, opacity 400ms;
  `,

  visible: css`
    visibility: visible;
    opacity: 1;
    transition: opacity 150ms;
  `,

  contentWhenSelected: css`
    position: absolute;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
    background-color: rgba(41, 98, 246, 0.8);
    border: 1px solid ${Colors.glazedBabyBlueDarker};
  `,
}

interface CaseStudiesSlideSquareProps {
  className?: string
  children?: ReactNode
  contentWrapperClassName?: string
  contentClassName?: string
  contentWhenSelected?: ReactNode
  isSelected?: boolean
  onMouseEnter?: (event: SyntheticEvent) => void
}

const CaseStudiesSlideSquare: React.FC<CaseStudiesSlideSquareProps> = ({
  children,
  className,
  contentWrapperClassName,
  contentClassName,
  contentWhenSelected,
  isSelected = false,
  onMouseEnter,
}) => {
  const hasContentWhenSelected = !!contentWhenSelected
  const contentWrapperClass = cx([
    Styles.squareContent,
    contentWrapperClassName,
  ])
  const contentClass = cx([
    isSelected
      ? cx(Styles.content(hasContentWhenSelected), Styles.hidden)
      : cx(Styles.content(hasContentWhenSelected), Styles.visible),
    contentClassName,
  ])
  const contentWhenSelectedClass = cx([
    Styles.content(false),
    isSelected
      ? cx(Styles.contentWhenSelected, Styles.visible)
      : cx(Styles.contentWhenSelected, Styles.hidden),
  ])

  return (
    <Square
      className={className}
      contentClassName={contentWrapperClass}
      onMouseEnter={onMouseEnter}
    >
      {children && <div className={contentClass}>{children}</div>}
      {contentWhenSelected && (
        <div className={contentWhenSelectedClass}>{contentWhenSelected}</div>
      )}
    </Square>
  )
}

export default memo(CaseStudiesSlideSquare)
