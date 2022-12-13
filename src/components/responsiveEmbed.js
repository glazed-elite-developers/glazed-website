import React from 'react'
import { css } from 'emotion'

const embedContainerStyles = css`
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
`

export default function ResponsiveEmbed({ src }) {
  return (
    <>
      <div className={embedContainerStyles}>
        <iframe src={src} frameBorder="0" allowFullScreen></iframe>
      </div>
    </>
  )
}
