import React, { useEffect, useState } from 'react'
import styled from '@emotion/styled'
import { keyframes } from '@emotion/core'

import { Breakpoints } from 're/Theme'

const characters = [
  'a',
  'b',
  'c',
  'd',
  'e',
  'f',
  'g',
  'h',
  'i',
  'j',
  'k',
  'l',
  'm',
  'n',
  'o',
  'p',
  'q',
  'r',
  's',
  't',
  'u',
  'v',
  'x',
  'y',
  'x',
  '#',
  '%',
  '&',
  '-',
  '+',
  '_',
  '?',
  '/',
  '\\',
  '=',
]

const reveal = keyframes`
  100% {
    opacity: 1;
    transform: translateY(0);
  }
`

const Span = styled.span`
  flex-shrink: 0;
  width: ${props => (props.isSpace ? '0.5rem' : 'auto')};
  opacity: 0;
  transform: translateY(100%);
  will-change: opacity, transform;
  animation: ${reveal};
  animation-duration: 500ms;
  animation-timing-function: ease-in-out;
  animation-delay: ${props => props.animationDelay}ms;
  animation-fill-mode: forwards;

  @media ${Breakpoints.tabletLandscape} {
    width: ${props => (props.isSpace ? 'rem' : 'auto')};
  }
`

const GlitchChar = React.memo(({ className, animationDelay, isSpace, text }) => (
  <Span className={className} animationDelay={animationDelay} isSpace={isSpace}>
    {text}
  </Span>
))

const GlitchText = ({ text, className, baseDelay = 0, itemDelay = 0, duration = 100, iterationCount = 20 }) => {
  const getRandomInteger = (min, max) => {
    return Math.floor(Math.random() * (max - min + 1)) + min
  }

  const randomCharacter = characters => {
    return characters[getRandomInteger(0, characters.length - 1)]
  }

  const getFullRandomString = string => {
    return Array.from(Array(string.length).keys()).map((_, index) => {
      return string[index] === ' ' ? ' ' : randomCharacter(characters)
    })
  }

  const getNextCharacter = (iterations, index) => {
    return iterations > 10 ? randomCharacter(characters) : text[index]
  }

  const getRandomString = (charArray, iterations) => {
    return charArray.map((_, index) => {
      if (charArray[index] === ' ') {
        return ' '
      }

      const modulo = iterations % 5

      switch (modulo) {
        case 0:
          return index % 5 === 0 ? getNextCharacter(iterations, index) : charArray[index]
        case 1:
          return index % 5 === 1 ? getNextCharacter(iterations, index) : charArray[index]
        case 2:
          return index % 5 === 2 ? getNextCharacter(iterations, index) : charArray[index]
        case 3:
          return index % 5 === 3 ? getNextCharacter(iterations, index) : charArray[index]
        case 4:
          return index % 5 === 4 ? getNextCharacter(iterations, index) : charArray[index]
      }
    })
  }

  const [hidden, setHidden] = useState(baseDelay > 0)
  const [iterations, setIterations] = useState(iterationCount - 1)
  const [glitchText, setGlitchText] = useState(getFullRandomString(text))

  useEffect(() => {
    let timeout
    if (hidden) {
      timeout = setTimeout(() => {
        setHidden(false)
      }, baseDelay)
    }

    return () => clearTimeout(timeout)
  }, [])

  useEffect(() => {
    let timeout

    if (!hidden) {
      if (iterations > 1) {
        setGlitchText(getRandomString(glitchText, iterations))
      } else if (iterations === 0) {
        setGlitchText(text.split(''))
      }

      if (iterations >= 0) {
        timeout = setTimeout(() => setIterations(iterations - 1), duration)
      }
    }
    return () => clearTimeout(timeout)
  }, [iterations, hidden])

  return glitchText.map((elem, index) => {
    return hidden ? null : (
      <GlitchChar
        key={`${text[index]}${index}`}
        className={className}
        animationDelay={itemDelay * index}
        isSpace={glitchText[index] === ' '}
        text={glitchText[index]}
      />
    )
  })
}

export default GlitchText
