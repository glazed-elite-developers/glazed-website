import { Ref, SVGProps } from 'react'

type AllSVGProps = SVGProps<SVGSVGElement>

type ReservedProps = 'color' | 'width' | 'height' | 'fill' | 'viewBox'

export interface SVGImageProps
  extends Pick<AllSVGProps, Exclude<keyof AllSVGProps, ReservedProps>> {
  /**
   * Allows accessing the wraooer element by reference.
   */
  innerRef?: Ref<SVGElement>
  color?: string
  width?: number | string
  height?: number | string
  children?: never
}

export interface SVGImageProps
  extends Pick<AllSVGProps, Exclude<keyof AllSVGProps, ReservedProps>> {
  color?: string
  width?: number | string
  height?: number | string
  children?: never
}
