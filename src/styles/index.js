import React from 'react'
import { Global, css } from '@emotion/core'
import ResetCSS from './reset'

const GlobalStyles = () => (
  <>
    <ResetCSS />
    <Global
      styles={css`
        html {
          font-size: 16px;
        }

        html,
        body,
        #___gatsby,
        #gatsby-focus-wrapper {
          height: 100%;
          display: flex;
          flex-direction: column;
        }
      `}
    />
  </>
)

export default GlobalStyles
