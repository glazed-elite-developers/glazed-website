import React, { FC, ReactNode, Ref } from 'react'
import { css, cx } from '@emotion/css'

export const Styles = {
  wrapper: css`
    position: relative;
    overflow: hidden;
  `,

  heightRegulator: css`
    position: relative;
    overflow: hidden;
  `,

  stretchHorizontally: css`
    width: 100%;
  `,

  stretchVertically: css`
    height: 100%;
  `,

  ratioPlaceholder: css`
    display: block;
  `,

  container: css`
    position: absolute;
    top: 50%;
    left: 50%;
    width: 100%;
    transform: translate3d(-50%, -50%, 0);
  `,
}

// Function to get the image source
export function getImgSrc(width: number, height: number): string {
  return `data:image/svg+xml,%3Csvg viewBox='0 0 ${width} ${height}' preserveAspectRatio='xMidYMid meet' xmlns='http://www.w3.org/2000/svg'/%3E`
}

// ImagePlaceholder component
interface ImagePlaceholderProps {
  innerRef?: Ref<HTMLImageElement>
  stretchDirection: 'Horizontal' | 'Vertical'
  width: number
  height: number
  className?: string
}

const ImagePlaceholder: FC<ImagePlaceholderProps> = ({
  innerRef,
  stretchDirection,
  width,
  height,
  className,
}) => {
  const src = getImgSrc(width, height)
  const widthValue = stretchDirection === 'Horizontal' ? '100%' : undefined
  const heightValue = stretchDirection === 'Vertical' ? '100%' : undefined
  const imgClassName = cx([Styles.ratioPlaceholder, className])

  return (
    <img
      role="presentation"
      alt="placeholder"
      src={src}
      ref={innerRef}
      className={imgClassName}
      width={widthValue}
      height={heightValue}
    />
  )
}

// FixedRatioContainer component
interface FixedRatioContainerProps {
  className?: string
  heightRegulatorClassName?: string
  imagePlaceholderClassName?: string
  contentClassName?: string
  stretchDirection: 'Horizontal' | 'Vertical'
  placeholderRef?: Ref<HTMLImageElement>
  width: number
  height: number
  children: ReactNode
}

const FixedRatioContainer: FC<FixedRatioContainerProps> = ({
  className,
  heightRegulatorClassName,
  imagePlaceholderClassName,
  contentClassName,
  stretchDirection,
  placeholderRef,
  width,
  height,
  children,
}) => {
  const stretchClass =
    stretchDirection === 'Horizontal'
      ? Styles.stretchHorizontally
      : Styles.stretchVertically
  const heightRegulatorClass = cx([
    heightRegulatorClassName,
    Styles.heightRegulator,
    stretchClass,
  ])
  const wrapperClassName = cx([Styles.wrapper, className])
  const contentClass = cx([Styles.container, contentClassName])

  return (
    <div className={wrapperClassName}>
      <div className={heightRegulatorClass}>
        <ImagePlaceholder
          stretchDirection={stretchDirection}
          width={width}
          height={height}
          innerRef={placeholderRef}
          className={imagePlaceholderClassName}
        />
        <div className={contentClass}>{children}</div>
      </div>
    </div>
  )
}

export default FixedRatioContainer
