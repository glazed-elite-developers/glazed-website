import React, { useEffect } from 'react'
import HomePage from '@components/pages/homepage'
import '@helpers/typings'

const Home = () => {
  const hasPlayedAnimation =
    typeof window !== 'undefined'
      ? window.sessionStorage.getItem('indexLanding')
      : false

  useEffect(() => {
    let timeout: NodeJS.Timeout
    if (!hasPlayedAnimation) {
      timeout = setTimeout(() => {
        window.sessionStorage.setItem('hasPlayed:indexLanding', 'true')
      }, 2000)
    }

    return () => clearTimeout(timeout)
  })

  return <HomePage />
}

export default Home
