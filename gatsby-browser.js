// import 'normalize-css'

import * as React from 'react'
import { cache } from 'emotion'
import { CacheProvider } from '@emotion/core'

export const wrapRootElement = ({ element }) => {
  return <CacheProvider value={cache}>{element}</CacheProvider>
}
