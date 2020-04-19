import React from 'react'
import { css, cache } from 'emotion'
import { CacheProvider } from '@emotion/core'
import { MediaContextProvider } from 'src/components/mediaContext'
import ScrollContainer from 're/shared/scroll-container/ScrollContainer'
import ModalsController from 're/shared/modals/ModalsController'

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
        <ModalsController>
          <ScrollContainer className={styles.wrapper} contentClassName={styles.content}>
            {element}
          </ScrollContainer>
        </ModalsController>
      </MediaContextProvider>
    </CacheProvider>
  )
}
