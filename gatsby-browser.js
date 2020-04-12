import React from 'react'
import { css, cache } from 'emotion'
import { CacheProvider } from '@emotion/core'
import { MediaContextProvider } from 'src/components/mediaContext'
import ScrollContainer from 're/shared/scroll-container/ScrollContainer'

const styles = {
  wrapper: css`
    height: 100%;
  `,
  content: css`
    height: 100%;
  `,
}

export const wrapRootElement = ({ element }) => {
  return (
    <CacheProvider value={cache}>
      <MediaContextProvider>
        <ScrollContainer className={styles.wrapper} contentClassName={styles.content}>
          {element}
        </ScrollContainer>
      </MediaContextProvider>
    </CacheProvider>
  )
}
