const DEFAULT_INTERVAL = 100

export const makeDelayFunction = (timeout: number) => (method: any) =>
  setTimeout(method, timeout)
const defaultDelayFunction = makeDelayFunction(DEFAULT_INTERVAL)

export const makeThrottler =
  (delayFunction = defaultDelayFunction) =>
  (decoratedMethod: any) => {
    let isScheduled = false
    let isFirstRun = true
    let memoizedValue: any

    const makeDecoratedMethodThunk =
      (...args: any) =>
      () => {
        isScheduled = false
        memoizedValue = decoratedMethod(...args)
      }

    return (...args: any) => {
      if (!isScheduled) {
        isScheduled = true
        delayFunction(makeDecoratedMethodThunk(...args))
      }

      if (isFirstRun) {
        isFirstRun = false
        memoizedValue = decoratedMethod(...args)
      }

      return memoizedValue
    }
  }

export const throttleWithRAF = makeThrottler(
  typeof window !== 'undefined'
    ? window.requestAnimationFrame
    : (defaultDelayFunction as any)
)

/*
 * Throttle.
 */
export default function throttle(
  decoratedMethod: any,
  interval = DEFAULT_INTERVAL
) {
  return makeThrottler((method) => setTimeout(method, interval))(
    decoratedMethod
  )
}
