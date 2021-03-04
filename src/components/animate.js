import React, { useContext } from 'react'
import { css, keyframes } from '@emotion/core'
import styled from '@emotion/styled'

const pulse = {
  baseStyles: css``,
  name: keyframes`
    0% {
      box-shadow: 0 0 0 0px rgba(0, 0, 0, 0.2);
    }

    100% {
      box-shadow: 0 0 0 80px rgba(0, 0, 0, 0);
    }
  `,
}

const scaleUp = {
  baseStyles: css`
    transform: scale(0);
    animation-timing-function: cubic-bezier(0.5, 0, 0.5, 1.5);
  `,
  name: keyframes`
    40% {
      animation-timing-function: cubic-bezier(0, 2, 0, 2);
    }

    100% {
      transform: scale(1);
    }
  `,
}

const scaleUpX = {
  baseStyles: css`
    transform: scaleX(0);
    animation-timing-function: cubic-bezier(0.5, 0, 0.5, 1.5);
  `,
  name: keyframes`
    40% {
      animation-timing-function: cubic-bezier(0, 2, 0, 2);
    }

    100% {
      transform: scaleX(1);
    }
  `,
}

const scaleDownX = {
  defaultStyles: css`
    opacity: 0;
    visibility: hidden;
  `,
  baseStyles: css`
    transform: scaleX(1);
    animation-timing-function: cubic-bezier(0.5, 0, 0.5, 1.5);
  `,
  name: keyframes`
    40% {
      animation-timing-function:cubic-bezier(0, 2, 0, 2);
    }

    100% {
      transform: scaleX(0);
    }
  `,
}

const scaleUpY = {
  baseStyles: css`
    transform: scaleY(0);
    animation-timing-function: cubic-bezier(0.5, 0, 0.5, 1.5);
  `,
  name: keyframes`
    40% {
      animation-timing-function: cubic-bezier(0, 2, 0, 2);
    }

    100% {
      transform: scaleY(1);
    }
  `,
}

const scaleDownY = {
  defaultStyles: css`
    opacity: 0;
    visibility: hidden;
  `,
  baseStyles: css`
    transform: scaleY(1);
    animation-timing-function: cubic-bezier(0.5, 0, 0.5, 1.5);
  `,
  name: keyframes`
    40% {
      animation-timing-function:cubic-bezier(0, 2, 0, 2);
    }

    100% {
      transform: scaleY(0);
    }
  `,
}

const slideUpFadeIn = {
  baseStyles: css`
    opacity: 0;
    visibility: hidden;
    transform: translateY(100%);
  `,
  name: keyframes`
    100% {
      opacity: inherit;
      visibility: visible;
      transform: translateY(0);
    }
  `,
}

const fadeIn = {
  baseStyles: css`
    opacity: 0;
    visibility: hidden;
  `,
  name: keyframes`
    100% {
      opacity: inherit;
      visibility: visible;
    }
  `,
}

const fadeOut = {
  defaultStyles: css`
    opacity: 0;
    visibility: hidden;
  `,
  baseStyles: css`
    opacity: 1;
    visibility: visible;
  `,
  name: keyframes`
    100% {
      opacity: 0;
      visibility: hidden;
    }
  `,
}

const animations = { pulse, scaleUp, scaleUpX, scaleDownX, scaleUpY, scaleDownY, slideUpFadeIn, fadeIn, fadeOut }

const Animate = ({
  animationGroup = '',
  animation,
  baseDelay = 0,
  itemDelay = 0,
  duration = 0,
  timingFunction = 'ease-out',
  fillMode = 'forwards',
  transformOrigin = 'center center',
  iterationCount = 1,
  children,
}) => {
  const hasPlayedAnimation =
    typeof window !== 'undefined' ? Boolean(window.sessionStorage.getItem(`hasPlayed:${animationGroup}`)) : false
  const hasAnimated = (!!animationGroup && hasPlayedAnimation) || false

  if (!hasAnimated) {
    return React.Children.map(children, (child, index) => {
      const Container = styled(child.type)`
        ${animations[animation].baseStyles};
        animation: ${animations[animation].name};
        animation-duration: ${props => props.duration}ms;
        animation-delay: ${props => props.delay}ms;
        animation-timing-function: ${timingFunction};
        animation-fill-mode: ${fillMode};
        animation-iteration-count: ${iterationCount};
        transform-origin: ${transformOrigin};
      `

      return <Container delay={baseDelay + itemDelay * index} duration={duration} {...child.props}></Container>
    })
  }

  return React.Children.map(children, child => {
    const Container = styled(child.type)`
      ${animations[animation].defaultStyles};
    `

    return <Container {...child.props}></Container>
  })
}

export default Animate
