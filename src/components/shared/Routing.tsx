import { navigate as gatsbyNavigate } from 'gatsby'

// Function to create a random key
export function createKey(): string {
  return Math.random().toString().substr(2, 6)
}

// Safe event creation for compatibility with older browsers
export function safeMakeEvent(eventName: string): Event {
  if (typeof Event === 'function') {
    return new Event(eventName)
  } else {
    const event = document.createEvent('Event')
    event.initEvent(eventName, true, true)
    return event
  }
}

// Navigate function with optional state and replace behavior
export function navigate(
  state: unknown | undefined,
  replace: boolean = false,
  path: string
): void {
  const nextState = state
    ? {
        key: createKey(),
        state,
      }
    : {}
  gatsbyNavigate(path, {
    replace,
    state: nextState,
  })
}

// Function to get the full path, including search and hash
export function getFullPath(location: Location): string {
  const { pathname, search, hash } = location
  const pathWithSearch = search ? `${pathname}?${search}` : pathname
  return hash ? `${pathWithSearch}${hash}` : pathWithSearch
}

// Export the key length constant
export const keyLength = 6
