import React from 'react'
import { cache } from 'emotion'
import { CacheProvider } from '@emotion/core'
import { MediaContextProvider } from 'src/components/mediaContext'

export const wrapRootElement = ({ element }) => {
  return (
    <CacheProvider value={cache}>
      <MediaContextProvider>{element}</MediaContextProvider>
    </CacheProvider>
  )
}
