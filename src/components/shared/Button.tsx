import { css, cx } from '@emotion/css'
import React, { ButtonHTMLAttributes, FC, MouseEvent, ReactNode } from 'react'
import { Colors, Fonts } from '@styles/Theme'

export enum Backgrounds {
  BrightBg = 0,
  BlueBg = 1,
  ImageBg = 2,
}

const secondaryForBg = (bg: Backgrounds) => {
  switch (bg) {
    case Backgrounds.BrightBg:
      return ''
    case Backgrounds.BlueBg:
      return css`
        color: ${Colors.almostWhite};
        border: 1px solid ${Colors.almostWhite};
      `
    case Backgrounds.ImageBg:
      return css`
        color: ${Colors.almostWhite};
        border: 1px solid ${Colors.glazedBlueDarkerish};
      `
  }
}

// Base and common styles
const Styles = {
  base: css`
    padding: 0.875rem 3rem;
  `,

  common: css`
    border: 1px none transparent;
    background: none;
  `,
  primary: (isDisabled: boolean) => css`
    opacity: ${isDisabled ? 0.4 : 1};
    transition: box-shadow 1s;
    background-color: ${Colors.glazedBlueDarkerish};
    color: ${Colors.almostWhite};
    font-family: ${Fonts.heading};
    font-size: 0.75rem;
    line-height: 0.75rem;
    padding: 0.875rem 3rem;
    ${!isDisabled &&
    `
    &:hover {
      box-shadow: 0 10px 20px rgba(0, 0, 0, 0.15);
      transition: box-shadow 1s;
    }
  `}
  `,

  secondary: (bg: Backgrounds, isDisabled: boolean) => css`
    color: ${Colors.darkGreyDarker};
    opacity: ${isDisabled ? 0.4 : 1};
    padding: 0.875rem 3rem;
    border: 1px solid ${Colors.glazedBlueDarkerish};
    background-color: transparent;
    ${secondaryForBg(bg)}
  `,

  // Tertiary button styles
  tertiary: (isDisabled: boolean) => css`
    color: ${Colors.glazedBabyBlue};
    border-width: 0;
    font-family: ${Fonts.heading};
    font-size: 0.75rem;
    line-height: 1.5rem;
    text-align: left;
    padding: 0.875rem 3rem;
  `,
}

interface ButtonProps {
  type?: 'Primary' | 'Secondary' | 'Tertiary'
  bgColor?: Backgrounds
  isDisabled?: boolean
  className?: string
  onClick?: (event: MouseEvent<HTMLButtonElement>) => void
  type_?: ButtonHTMLAttributes<HTMLButtonElement>['type']
  children: ReactNode
}

const Button: FC<ButtonProps> = ({
  type,
  bgColor = Backgrounds.BrightBg,
  isDisabled = false,
  className,
  onClick,
  type_,
  children,
}) => {
  let ownStyles = Styles.base

  // Determine button style based on type
  switch (type) {
    case 'Primary':
      ownStyles = Styles.primary(isDisabled)
      break
    case 'Secondary':
      ownStyles = Styles.secondary(bgColor, isDisabled)
      break
    case 'Tertiary':
      ownStyles = Styles.tertiary(isDisabled)
      break
  }

  const onClickHandler = isDisabled ? () => {} : onClick || (() => {})
  const buttonClassName = cx([Styles.common, ownStyles, className])

  return (
    <button
      className={buttonClassName}
      onClick={onClickHandler}
      type={type_}
      disabled={isDisabled}
    >
      {children}
    </button>
  )
}

export default Button
