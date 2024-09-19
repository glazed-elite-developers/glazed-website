import React, { FC } from 'react'
import { css } from '@emotion/css'

const Styles = {
  embedContainerStyles: css`
    position: relative;
    padding-bottom: 56.25%;
    height: 0;
    overflow: hidden;
    width: 100%;
    margin: 1rem 0 2rem;

    iframe,
    object,
    embed {
      position: absolute;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
    }
  `,
}

interface ResponsiveEmbedProps {
  src: string
}

const ResponsiveEmbed: FC<ResponsiveEmbedProps> = ({ src }) => {
  return (
    <div className={Styles.embedContainerStyles}>
      <iframe src={src} frameBorder="0" allowFullScreen></iframe>
    </div>
  )
}

export default ResponsiveEmbed
