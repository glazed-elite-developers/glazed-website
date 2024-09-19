import { css } from '@emotion/css'

const Styles = {
  wrapper: css`
    /* Hints the browser to isolate the content in a new layer without creating a new stacking
    context. 'will-change: transform;' of other transform based hints would create new contexts. */
    will-change: opacity;
    overflow: auto;

    /* Needed for smooth scrolling in iOS devices. */
    -webkit-overflow-scrolling: touch;

    @media print {
      overflow: visible;
    }
  `,
  content: css`
    /* Same as before, but we need to have this both in the scroll container and in a wrapper for
    the scrollable content to successfully prevent repaints while scrolling. */
    will-change: opacity;
  `,
  lockScroll: css`
    /* Locks the scroll on the scroll container. */
    overflow: hidden;

    /* Needed for the scroll to be properly locked in iOS. */
    -webkit-overflow-scrolling: auto;
  `,
}

export default Styles
