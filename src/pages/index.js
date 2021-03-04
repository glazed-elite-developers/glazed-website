import React, { useEffect, useContext, useState } from 'react'
import { AnimationContext, AnimationContextProvider } from '../components/animationContext'
import HomePage from 're/pages/index/Index'

const Home = () => {
  const animationContext = useContext(AnimationContext)
  const [hasAnimated, setHasAnimated] = useState(animationContext?.indexLanding || false)

  useEffect(() => {
    const timeout = setTimeout(() => {
      setHasAnimated(true)
    }, 6000)

    return () => clearTimeout(timeout)
  })

  return (
    <AnimationContextProvider group="indexLanding" value={hasAnimated}>
      <HomePage />
    </AnimationContextProvider>
  )
}

export default Home
