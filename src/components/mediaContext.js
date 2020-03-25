import React, { useState, useEffect, createContext, useCallback } from 'react'
import { Breakpoints } from 're/Theme'

export const MediaContext = createContext(null)

const matchMediaQueries = Object.entries(Breakpoints)
  .filter(([name]) => {
    return !name.includes('Value')
  })
  .map(([name, value]) => ({
    name,
    query: window.matchMedia(value),
  }))

export const MediaContextProvider = ({ children }) => {
  const [currentBreakpoint, setCurrentBreakpoint] = useState('phone')

  const handleWindowResize = useCallback(() => {
    for (const { name, query } of matchMediaQueries) {
      if (query.matches) {
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

  return <MediaContext.Provider value={currentBreakpoint}>{children}</MediaContext.Provider>
}

export const MediaContextConsumer = MediaContext.Consumer

export default { MediaContext, MediaContextProvider, MediaContextConsumer }
