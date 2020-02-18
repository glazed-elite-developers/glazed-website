import React, { useState, useEffect, createContext, useCallback } from 'react'
import Theme from 're/theme'

export const MediaContext = createContext(null)

const matchMediaQueries = Object.entries(Theme.Breakpoints)
  .filter(([name]) => {
    return !name.includes('Value')
  })
  .map(([name, value]) => ({
    name,
    query: window.matchMedia(value),
  }))

export const MediaContextProvider = ({ children }) => {
  let [currentBreakpoint, setCurrentBreakpoint] = useState('phone')

  const handleWindowResize = useCallback(() => {
    for (const { name, query } of matchMediaQueries) {
      if (query.matches) {
        console.log({ current: name })
        setCurrentBreakpoint(name)
      }
    }
  })

  useEffect(() => {
    for (const { query } of matchMediaQueries) {
      query.addListener(handleWindowResize)
    }

    return () => {
      for (const { query } of matchMediaQueries) {
        query.removeListener(handleWindowResize)
      }
    }
  }, [])

  return (
    <MediaContext.Provider value={currentBreakpoint}>
      {children}
    </MediaContext.Provider>
  )
}

export const MediaContextConsumer = MediaContext.Consumer

export default { MediaContext, MediaContextProvider, MediaContextConsumer }
