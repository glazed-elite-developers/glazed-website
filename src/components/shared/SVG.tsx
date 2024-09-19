import React, { FC } from 'react'

export interface SVGProps {
  className?: string
  height?: string | number
  asset: {
    viewBox: string
    url: string
  }
}

const SVG: FC<SVGProps> = ({ className, height, asset }) => {
  return (
    <svg viewBox={asset.viewBox} className={className} height={height}>
      <use xlinkHref={asset.url} />
    </svg>
  )
}

export default SVG
