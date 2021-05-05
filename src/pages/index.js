import React, { useEffect } from 'react'
import HomePage from 're/pages/index/Index'

const Home = () => {
  const hasPlayedAnimation = typeof window !== 'undefined' ? window.sessionStorage.getItem('indexLanding') : false

  useEffect(() => {
    let timeout
    if (!hasPlayedAnimation) {
      timeout = setTimeout(() => {
        window.sessionStorage.setItem('hasPlayed:indexLanding', true)
      }, 2000)
    }

    return () => clearTimeout(timeout)
  })

  return <HomePage />
}

export default Home
