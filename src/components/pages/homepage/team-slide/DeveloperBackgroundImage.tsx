import React, { ReactNode, memo } from 'react'
import { cx, css } from '@emotion/css'
import GatsbyBackgroundImage from 'gatsby-background-image'
import { getImage, IGatsbyImageData } from 'gatsby-plugin-image'
import { convertToBgImage } from 'gbimage-bridge'

export const Styles = {
  wrapper: css`
    position: relative;
  `,
  backgroundImage: css`
    position: absolute;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
  `,
}

interface DeveloperBackgroundImageProps {
  className?: string
  gatsbyBackgroundImageClassName?: string
  image: IGatsbyImageData
  children?: ReactNode
  style?: React.CSSProperties
}

const DeveloperBackgroundImage: React.FC<DeveloperBackgroundImageProps> = ({
  image: developerPhoto,
  className,
  gatsbyBackgroundImageClassName,
  children,
  style,
}) => {
  const baseStyle: React.CSSProperties = {
    backgroundPosition: 'top center',
    marginTop: '10%',
    position: 'absolute',
    backgroundSize: 'auto 100%',
  }
  const combinedStyle = style ? { ...baseStyle, ...style } : baseStyle

  return (
    <div className={cx(Styles.wrapper, className)}>
      <GatsbyBackgroundImage
        {...convertToBgImage(developerPhoto)}
        style={combinedStyle}
        className={cx(Styles.backgroundImage, gatsbyBackgroundImageClassName)}
      >
        {children}
      </GatsbyBackgroundImage>
    </div>
  )
}

export default memo(DeveloperBackgroundImage)
