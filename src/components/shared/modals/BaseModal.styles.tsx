import { css } from '@emotion/css'
import { Colors } from '@styles/Theme'
import { transparentize } from 'polished'

const Styles = {
  wrapper: css`
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    z-index: 1;
    display: flex;
    flex-direction: column;
    overflow: hidden;
    transform: translateZ(0);
  `,

  scrollContainer: css`
    height: 100%;
    display: flex;
    flex-direction: column;
    background-color: ${transparentize(0.5, Colors.black)};
    overflow: auto;
  `,

  scrollContent: css`
    display: flex;
    flex: 1 0 auto;
    justify-content: center;
    align-items: center;
  `,

  wrapperBeforeAppearingAnimation: css`
    opacity: 0;
  `,

  contentBeforeAppearingAnimation: css`
    opacity: 0;
    transform: translate3d(0, 1rem, 0);
  `,

  wrapperVisible: css`
    opacity: 1;
    transition: opacity 300ms;
  `,

  contentVisible: css`
    opacity: 1;
    transform: translate3d(0, 0, 0);
    transition: opacity 300ms, transform 300ms;
  `,

  wrapperLeaving: css`
    opacity: 0;
    transition: opacity 300ms;
  `,

  contentLeaving: css`
    opacity: 0;
    transform: translate3d(0, 1rem, 0);
    transition: opacity 300ms, transform 300ms;
  `,
}

export default Styles
