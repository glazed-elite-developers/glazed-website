declare module '*.png' {
  const value: string
  export default value
}

declare module '*.jpg' {
  const value: string
  export default value
}

declare module '*.eot' {
  const value: string
  export default value
}

declare module '*.woff2' {
  const value: string
  export default value
}

declare module '*.woff' {
  const value: string
  export default value
}

declare module '*.ttf' {
  const value: string
  export default value
}

declare module '*.svg' {
  import * as React from 'react'
  export const ReactComponent: React.FC<React.SVGProps<SVGSVGElement>>
  const asset: {
    viewBox: string
    url: string
  }
  export default asset
}
