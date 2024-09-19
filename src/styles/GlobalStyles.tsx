import React from 'react'
import { css, Global } from '@emotion/react'
import ResetCSS from './ResetCSS'
import Fonts from './Fonts'

const GlobalStyles = () => (
  <>
    <ResetCSS />
    <Global
      styles={css`
        @font-face {
          font-family: 'Muli';
          font-style: normal;
          font-weight: 400;
          src: url('${Fonts.MuliRegularEot}'); /* IE9 Compat Modes */
          src: local(''),
            url('${Fonts.MuliRegularEot}.eot?#iefix')
              format('embedded-opentype'),
            /* IE6-IE8 */ url('${Fonts.MuliRegularWoff2}') format('woff2'),
            /* Super Modern Browsers */ url('${Fonts.MuliRegularWoff}')
              format('woff'),
            /* Modern Browsers */ url('${Fonts.MuliRegularTtf}')
              format('truetype');
        }

        @font-face {
          font-family: 'Muli';
          font-style: normal;
          font-weight: 700;
          src: url('${Fonts.MuliBoldEot}'); /* IE9 Compat Modes */
          src: local(''),
            url('${Fonts.MuliBoldEot}.eot?#iefix') format('embedded-opentype'),
            /* IE6-IE8 */ url('${Fonts.MuliBoldWoff2}') format('woff2'),
            /* Super Modern Browsers */ url('${Fonts.MuliBoldWoff}')
              format('woff'),
            /* Modern Browsers */ url('${Fonts.MuliBoldTtf}') format('truetype')
        }

        @font-face {
          font-family: 'ZonaProBold';
          font-style: normal;
          font-weight: 700;
          src: url('${Fonts.ZonaProBoldEot}'); /* IE9 Compat Modes */
          src: local(''),
            url('${Fonts.ZonaProBoldEot}.eot?#iefix')
              format('embedded-opentype'),
            /* IE6-IE8 */ url('${Fonts.ZonaProBoldWoff2}') format('woff2'),
            /* Super Modern Browsers */ url('${Fonts.ZonaProBoldWoff}')
              format('woff'),
            /* Modern Browsers */ url('${Fonts.ZonaProBoldTtf}')
              format('truetype')
        }

        html,
        body,
        #___gatsby,
        #gatsby-focus-wrapper {
          height: 100%;
          display: flex;
          flex-direction: column;
        }

        #___gatsby {
          font-size: 16px;
          font-family: 'Muli', 'ZonaProBold', sans-serif;
          line-height: 1.5;
        }

        a {
          text-decoration: none;
        }

        a:focus {
          outline: none;
        }
      `}
    />
  </>
)

export default GlobalStyles
