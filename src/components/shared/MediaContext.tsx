import React, {
  FC,
  useState,
  useEffect,
  createContext,
  useCallback,
  ReactNode,
} from 'react'
import { Breakpoints } from '../../styles/Theme'

interface MediaContextProps {
  children: ReactNode
}

export const MediaContext = createContext<string | null>(null)

const matchMediaQueries =
  typeof window !== 'undefined'
    ? Object.entries(Breakpoints)
        .filter(([name]) => !name.includes('Value'))
        .map(([name, value]) => ({
          name,
          query: window.matchMedia(value as string),
        }))
    : []

export const MediaContextProvider: FC<MediaContextProps> = ({ children }) => {
  const [currentBreakpoint, setCurrentBreakpoint] = useState<string>('phone')

  const handleWindowResize = useCallback(() => {
    for (const { name, query } of matchMediaQueries) {
      if (query.matches) {
        setCurrentBreakpoint(name)
      }
    }
  }, [])

  useEffect(() => {
    for (const { query } of matchMediaQueries) {
      query.addListener(handleWindowResize)
    }
    handleWindowResize()

    return () => {
      for (const { query } of matchMediaQueries) {
        query.removeListener(handleWindowResize)
      }
    }
  }, [handleWindowResize])

  return (
    <MediaContext.Provider value={currentBreakpoint}>
      {children}
    </MediaContext.Provider>
  )
}

export const MediaContextConsumer = MediaContext.Consumer
