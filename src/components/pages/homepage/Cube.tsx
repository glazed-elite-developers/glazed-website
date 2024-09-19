import React from 'react'
import { css, cx } from '@emotion/css'

const cubeSize = '250px'
const cubeDimensions = '500px'
const cubePerspective = '2000px'

export const Variables = {
  rawCubeSize: 250,
  cubeSize: cubeSize,
  cubeDimensions: cubeDimensions,
  cubePerspective: cubePerspective,
}

export const Styles = {
  wrapper: css`
    perspective: ${cubePerspective};
    perspective-origin: ${cubeSize} ${cubeSize};
    width: ${cubeDimensions};
    height: ${cubeDimensions};
    filter: blur(1px);
  `,
  cube: css`
    position: absolute;
    transform-style: preserve-3d;
    transform-origin: ${cubeSize} ${cubeSize};
  `,
  cubeFace: css`
    width: ${cubeDimensions};
    height: ${cubeDimensions};
    opacity: 0.8;
    position: absolute;
    box-shadow: 0 0 5px rgba(83, 211, 255, 1);
  `,
  front: css`
    transform: translateZ(${cubeSize});
    border: 1px solid rgba(83, 211, 255, 1);
  `,
  back: css`
    transform: translateZ(-${cubeSize}) rotateY(180deg);
    border: 1px solid rgba(83, 211, 255, 0.2);
    transform-origin: 50% 50%;
  `,
  right: css`
    transform: translateX(${cubeSize}) rotateY(-270deg);
    transform-origin: 0 100%;
    border: 1px solid rgba(83, 211, 255, 1);
    border-left-style: none;
  `,
  left: css`
    transform: translateX(-${cubeSize}) rotateY(270deg);
    transform-origin: 50% 0;
    border: 1px solid rgba(83, 211, 255, 1);
    border-right-style: none;
  `,
  top: css`
    transform: translateY(-${cubeSize}) rotateX(90deg);
    transform-origin: 0 50%;
  `,
  bottom: css`
    transform: translateY(${cubeSize}) rotateX(-90deg);
    transform-origin: 100% 50%;
  `,
}

interface CubeProps {
  className?: string
}

const Cube: React.FC<CubeProps> = ({ className }) => {
  return (
    <div className={cx([Styles.wrapper, className])}>
      <div className={Styles.cube}>
        <div className={cx([Styles.cubeFace, Styles.front])}></div>
        <div className={cx([Styles.cubeFace, Styles.back])}></div>
        <div className={cx([Styles.cubeFace, Styles.bottom])}></div>
        <div className={cx([Styles.cubeFace, Styles.left])}></div>
        <div className={cx([Styles.cubeFace, Styles.left])}></div>
        <div className={cx([Styles.cubeFace, Styles.right])}></div>
      </div>
    </div>
  )
}

export default Cube
