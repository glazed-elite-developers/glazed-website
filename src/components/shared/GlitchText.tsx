import React, { useEffect, useState } from 'react'
import styled from '@emotion/styled'
import { keyframes, css } from '@emotion/css'
import { Breakpoints } from '@styles/Theme'

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

const Styles = {
  reveal: keyframes`
    100% { opacity: 1; transform: translateY(0); }
  `,
  span: (props: { isSpace: boolean; animationDelay: number }) => css`
    flex-shrink: 0;
    width: ${props.isSpace ? '0.5rem' : 'auto'};
    opacity: 0;
    transform: translateY(100%);
    will-change: opacity, transform;
    animation: ${Styles.reveal};
    animation-duration: 500ms;
    animation-timing-function: ease-in-out;
    animation-delay: ${props.animationDelay}ms;
    animation-fill-mode: forwards;

    @media ${Breakpoints.tabletLandscape} {
      width: ${props.isSpace ? '1rem' : 'auto'};
    }
  `,
}

const Span = styled.span<{ isSpace: boolean; animationDelay: number }>`
  ${(props) => Styles.span(props)}
`

interface GlitchCharProps {
  className?: string
  animationDelay: number
  isSpace: boolean
  text: string
}

const GlitchChar: React.FC<GlitchCharProps> = React.memo(
  ({ className, animationDelay, isSpace, text }) => (
    <Span
      className={className}
      animationDelay={animationDelay}
      isSpace={isSpace}
    >
      {text}
    </Span>
  )
)

interface GlitchTextProps {
  text: string
  className?: string
  baseDelay?: number
  itemDelay?: number
  duration?: number
  iterationCount?: number
}

const GlitchText: React.FC<GlitchTextProps> = ({
  text,
  className,
  baseDelay = 0,
  itemDelay = 0,
  duration = 100,
  iterationCount = 20,
}) => {
  const getRandomInteger = (min: number, max: number): number => {
    return Math.floor(Math.random() * (max - min + 1)) + min
  }

  const randomCharacter = (chars: string[]): string => {
    return chars[getRandomInteger(0, chars.length - 1)]
  }

  const getFullRandomString = (string: string): string[] => {
    return Array.from(Array(string.length).keys()).map((_, index) => {
      return string[index] === ' ' ? ' ' : randomCharacter(characters)
    })
  }

  const getNextCharacter = (iterations: number, index: number): string => {
    return iterations > 10 ? randomCharacter(characters) : text[index]
  }

  const getRandomString = (
    charArray: string[],
    iterations: number
  ): string[] => {
    return charArray.map((_, index) => {
      if (charArray[index] === ' ') {
        return ' '
      }

      const modulo = iterations % 5

      switch (modulo) {
        case 0:
          return index % 5 === 0
            ? getNextCharacter(iterations, index)
            : charArray[index]
        case 1:
          return index % 5 === 1
            ? getNextCharacter(iterations, index)
            : charArray[index]
        case 2:
          return index % 5 === 2
            ? getNextCharacter(iterations, index)
            : charArray[index]
        case 3:
          return index % 5 === 3
            ? getNextCharacter(iterations, index)
            : charArray[index]
        case 4:
          return index % 5 === 4
            ? getNextCharacter(iterations, index)
            : charArray[index]
        default:
          return charArray[index]
      }
    })
  }

  const [hidden, setHidden] = useState(baseDelay > 0)
  const [iterations, setIterations] = useState(iterationCount - 1)
  const [glitchText, setGlitchText] = useState(getFullRandomString(text))

  useEffect(() => {
    let timeout: NodeJS.Timeout
    if (hidden) {
      timeout = setTimeout(() => {
        setHidden(false)
      }, baseDelay)
    }

    return () => clearTimeout(timeout)
  }, [])

  useEffect(() => {
    let timeout: NodeJS.Timeout

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

  return (
    <>
      {glitchText.map((elem, index) => {
        return hidden ? null : (
          <GlitchChar
            key={`${text[index]}${index}`}
            className={className}
            animationDelay={itemDelay * index}
            isSpace={glitchText[index] === ' '}
            text={glitchText[index]}
          />
        )
      })}
    </>
  )
}

export default GlitchText
