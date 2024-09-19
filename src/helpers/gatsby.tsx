import { IBackgroundImageProps } from 'gatsby-background-image'
import { getImage, ImageDataLike } from 'gatsby-plugin-image'
import { convertToBgImage } from 'gbimage-bridge'

type QueryResult = Record<string, ImageDataLike>

type ImageTuple = [string, string?]
type Images = ImageTuple[]

export function getResponsiveBackgroundImageFluid(
  result: QueryResult,
  images: Images
): IBackgroundImageProps['fluid'] {
  return images.map(([key, mediaQuery]) => {
    const image = convertToBgImage(
      getImage(result[key])
    ) as IBackgroundImageProps
    return mediaQuery !== undefined
      ? { ...image.fluid, media: mediaQuery }
      : image.fluid
  }) as IBackgroundImageProps['fluid']
}
