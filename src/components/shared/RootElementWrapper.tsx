import React from 'react'
import { cache } from '@emotion/css'
import { CacheProvider } from '@emotion/react'
import { MediaContextProvider } from '@components/shared/MediaContext'

interface RootElementWrapperProps {
  children: React.ReactNode
}

const RootElementWrapper: React.FC<RootElementWrapperProps> = ({
  children,
}) => {
  return (
    <CacheProvider value={cache}>
      <MediaContextProvider>{children}</MediaContextProvider>
    </CacheProvider>
  )
}

export default RootElementWrapper
