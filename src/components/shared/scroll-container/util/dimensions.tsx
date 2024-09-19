export type scrollPosition = {
  scrollTop: number
  scrollLeft: number
  scrollWidth: number
  scrollHeight: number
}

export type boundingRect = {
  top: number
  right: number
  bottom: number
  left: number
  width: number
  height: number
}

/**
 * Default scroll position.
 */
export const defaultScrollPosition: scrollPosition = {
  scrollTop: 0,
  scrollLeft: 0,
  scrollWidth: 0,
  scrollHeight: 0,
}

/**
 * Default scroll container bounding react values.
 */
export const defaultBoundingRect: boundingRect = {
  top: 0,
  right: 0,
  bottom: 0,
  left: 0,
  width: 0,
  height: 0,
}

/**
 * Serializes the scroll position values.
 *
 * @param {DOMElement} scrollContainer - Scroll container DOM element.
 *
 * @returns {Object} Scroll position values.
 */
export const serializeScrollPosition = ({
  scrollTop,
  scrollLeft,
  scrollWidth,
  scrollHeight,
}: HTMLElement) => ({
  scrollTop,
  scrollLeft,
  scrollWidth,
  scrollHeight,
})

/**
 * Serializes the scroll container dimensions.
 *
 * @param {DOMRect} boundingRect - DOMRect instance.
 *
 * @returns {Object} Scroll container dimensions.
 */
export const serializeBoundingRect = ({
  top,
  right,
  bottom,
  left,
  width,
  height,
}: DOMRect) => ({
  top,
  right,
  bottom,
  left,
  width,
  height,
})
