import React, { createContext } from 'react'

const globalAnimationContext = {}

export const AnimationContext = createContext(globalAnimationContext)
export const AnimationContextProvider = ({ group, value, children }) => {
  globalAnimationContext[group] = value

  return <AnimationContext.Provider value={globalAnimationContext}>{children}</AnimationContext.Provider>
}
export const AnimationContextConsumer = AnimationContext.Consumer
