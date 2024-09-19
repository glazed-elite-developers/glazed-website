export const cancelAnimationTimeout = (frame: any) =>
  cancelAnimationFrame(frame.id)

/**
 * Recursively calls requestAnimationFrame until a specified delay has been met or exceeded.
 * When the delay time has been reached the function you're timing out will be called.
 *
 * Credit: Joe Lambert (https://gist.github.com/joelambert/1002116#file-requesttimeout-js).
 *
 * @param {Function} callback - Timeout callback.
 * @param {Integer} delay - Timeout value in milliseconds.
 *
 * @returns {Object} Frame data.
 */
export const requestAnimationTimeout = (callback: any, delay: any) => {
  const start = Date.now()

  const timeout = () => {
    const delta = Date.now() - start

    if (delta >= delay) {
      callback.call()
    } else {
      frame.id = requestAnimationFrame(timeout)
    }
  }

  const frame = {
    id: requestAnimationFrame(timeout),
  }

  return frame
}
