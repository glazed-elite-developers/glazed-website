import React, { useEffect, useMemo, useRef, useCallback, FC, memo } from 'react'
import { useThree, useLoader } from '@react-three/fiber'
import * as THREE from 'three'
import { gsap, Power2 } from 'gsap'
import debounce from 'lodash.debounce'
import dispImg from '@static/images/disp1.jpg'
import { IGatsbyImageData } from 'gatsby-plugin-image'

const vertexShader = `
varying vec2 vUv;
void main() {
  vUv = uv;
  gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}
`

const fragmentShader = `
uniform float progress;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D displacement;
uniform vec4 resolution;
uniform float intensity;
varying vec2 vUv;

void main() {
  vec2 newUV = (vUv - vec2(0.5)) * resolution.zw + vec2(0.5);
  vec4 d1 = texture2D(texture1, newUV);
  vec4 d2 = texture2D(texture2, newUV);

  float displace1 = (d1.r + d1.g + d1.b) * 0.33;
  float displace2 = (d2.r + d2.g + d2.b) * 0.33;

  vec4 t1 = texture2D(texture1, vec2(newUV.x, newUV.y + progress * (displace2 * intensity)));
  vec4 t2 = texture2D(texture2, vec2(newUV.x, newUV.y + (1.0 - progress) * (displace1 * intensity)));

  gl_FragColor = mix(t1, t2, progress);
}
`

interface GlitchImagesProps {
  imageSources: Array<string>
  current: number
}

const GlitchImages: FC<GlitchImagesProps> = ({ imageSources, current }) => {
  const duration = 1
  const easing = 'easeInOut'

  // Load textures
  const textures = useLoader(THREE.TextureLoader, imageSources)
  const displacementTexture = useLoader(THREE.TextureLoader, dispImg)

  // Access three.js context
  const { size, camera } = useThree()
  const aspect =
    camera instanceof THREE.PerspectiveCamera
      ? camera.aspect
      : size.width / size.height

  // Refs
  const material = useRef<THREE.ShaderMaterial>(null)
  const resolution = useRef(new THREE.Vector4())

  // Shader uniforms
  const uniforms = useMemo(
    () => ({
      progress: { type: 'f', value: 0 },
      border: { type: 'f', value: 0 },
      intensity: { type: 'f', value: 0.3 },
      scaleX: { type: 'f', value: 40 },
      scaleY: { type: 'f', value: 40 },
      transition: { type: 'f', value: 40 },
      swipe: { type: 'f', value: 0 },
      width: { type: 'f', value: 0 },
      radius: { type: 'f', value: 0 },
      texture1: { type: 'f', value: textures[current] },
      texture2: { type: 'f', value: textures[current + 1] },
      displacement: { type: 'f', value: displacementTexture },
      resolution: { type: 'v4', value: resolution.current },
    }),
    []
  )

  // Next animation function with debounce
  const next = useCallback(
    debounce(() => {
      const nextTexture = textures[current]
      if (material.current) {
        material.current.uniforms.texture2.value = nextTexture
        gsap.to(material.current.uniforms.progress, {
          value: 1,
          ease: Power2[easing],
          duration,
          onComplete: () => {
            if (material.current) {
              material.current.uniforms.texture1.value = nextTexture
              material.current.uniforms.progress.value = 0
            }
          },
        })
      }
    }, 200),
    [current, easing, textures]
  )

  // Resize handler
  const resize = useCallback(() => {
    const width = size.width
    const height = size.height
    const imageAspect =
      textures[current].image.height / textures[current].image.width

    let a1: number, a2: number
    if (height / width > imageAspect) {
      a1 = (width / height) * imageAspect
      a2 = 1
    } else {
      a1 = 1
      a2 = height / width / imageAspect
    }

    resolution.current.set(width, height, a1, a2)

    if (material.current) {
      material.current.uniforms.resolution.value.set(width, height, a1, a2)
    }
  }, [size, textures])

  useEffect(() => {
    next()
  }, [current, next])

  useEffect(() => {
    resize()
  }, [resize, size])

  return (
    <mesh>
      <shaderMaterial
        ref={material}
        uniforms={uniforms}
        vertexShader={vertexShader}
        fragmentShader={fragmentShader}
        side={THREE.DoubleSide}
      />
      <planeGeometry args={[aspect, 1, 2, 2]} />
    </mesh>
  )
}

export default memo(GlitchImages)
