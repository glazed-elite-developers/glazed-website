import React from 'react'
import { Global, css } from '@emotion/core'
import ResetCSS from './reset'
import fonts from './fonts'

const GlobalStyles = () => (
  <>
    <ResetCSS />
    <Global
      styles={css`
        @font-face {
          font-family: 'Muli';
          font-style: normal;
          font-weight: 400;
          src: url('${fonts.MuliRegularEot}'); /* IE9 Compat Modes */
          src: local(''),
              url('${fonts.MuliRegularEot}.eot?#iefix') format('embedded-opentype'), /* IE6-IE8 */
              url('${fonts.MuliRegularWoff2}') format('woff2'), /* Super Modern Browsers */
              url('${fonts.MuliRegularWoff}') format('woff'), /* Modern Browsers */
              url('${fonts.MuliRegularTtf}') format('truetype'), /* Safari, Android, iOS */
              url('${fonts.MuliRegularSvg}#Muli') format('svg'); /* Legacy iOS */
        }

        @font-face {
          font-family: 'Muli';
          font-style: normal;
          font-weight: 700;
          src: url('${fonts.MuliBoldEot}'); /* IE9 Compat Modes */
          src: local(''),
              url('${fonts.MuliBoldEot}.eot?#iefix') format('embedded-opentype'), /* IE6-IE8 */
              url('${fonts.MuliBoldWoff2}') format('woff2'), /* Super Modern Browsers */
              url('${fonts.MuliBoldWoff}') format('woff'), /* Modern Browsers */
              url('${fonts.MuliBoldTtf}') format('truetype'), /* Safari, Android, iOS */
              url('${fonts.MuliBoldSvg}#Muli') format('svg'); /* Legacy iOS */
        }

        @font-face {
          font-family: 'ZonaProBold';
          font-style: normal;
          font-weight: 700;
          src: url('${fonts.ZonaProBoldEot}'); /* IE9 Compat Modes */
          src: local(''),
              url('${fonts.ZonaProBoldEot}.eot?#iefix') format('embedded-opentype'), /* IE6-IE8 */
              url('${fonts.ZonaProBoldWoff2}') format('woff2'), /* Super Modern Browsers */
              url('${fonts.ZonaProBoldWoff}') format('woff'), /* Modern Browsers */
              url('${fonts.ZonaProBoldTtf}') format('truetype'), /* Safari, Android, iOS */
              url('${fonts.ZonaProBoldSvg}#ZonaProBold') format('svg'); /* Legacy iOS */
        }

        html {
          font-size: 16px;
          font-family: 'Muli', 'ZonaProBold', sans-serif;
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
