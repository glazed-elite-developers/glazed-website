import React, { useEffect, useMemo } from 'react'
import { useThree, useLoader, useResource } from 'react-three-fiber'
import * as THREE from 'three'
import { TimelineMax, Power2 } from 'gsap'
import debounce from 'lodash.debounce'

import lvmh from '../../static/images/case-studies/lvmh-hero.jpg'
import farfetch from '../../static/images/case-studies/farfetch-hero.jpg'
import mercadao from '../../static/images/case-studies/mercadao-hero.jpg'
import boston from '../../static/images/case-studies/boston-hero.jpg'
import dispImg from '../../static/images/disp1.jpg'

const vertex =
  'varying vec2 vUv;void main() {vUv = uv;gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );}'

const fragment = `
uniform float progress;
uniform float width;
uniform float scaleX;
uniform float scaleY;
uniform float transition;
uniform float radius;
uniform float intensity;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D displacement;
uniform vec4 resolution;
varying vec2 vUv;

void main()	{
  vec2 newUV = (vUv - vec2(0.5))*resolution.zw + vec2(0.5);

    vec4 d1 = texture2D(texture1, newUV);
    vec4 d2 = texture2D(texture2, newUV);

    float displace1 = (d1.r + d1.g + d1.b)*0.33;
    float displace2 = (d2.r + d2.g + d2.b)*0.33;

    vec4 t1 = texture2D(texture1, vec2(newUV.x, newUV.y + progress * (displace2 * intensity)));
    vec4 t2 = texture2D(texture2, vec2(newUV.x, newUV.y + (1.0 - progress) * (displace1 * intensity)));

    gl_FragColor = mix(t1, t2, progress);

}
`

const GlitchImages = React.memo(({ current }) => {
  const images = [lvmh, farfetch, mercadao, boston]
  const duration = 1
  const easing = 'easeInOut'
  const textures = useLoader(THREE.TextureLoader, images)
  const displacementTexture = useLoader(THREE.TextureLoader, dispImg)

  const { size, camera } = useThree()
  const material = useResource()
  const resolution = useResource(new THREE.Vector4())

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
      resolution: { type: 'v4', value: resolution },
    }),
    []
  )

  const next = debounce(
    () => {
      const nextTexture = textures[current]
      uniforms.texture2.value = nextTexture
      const tl = new TimelineMax()
      tl.to(uniforms.progress, duration, {
        value: 1,
        ease: Power2[easing],
        onComplete: () => {
          uniforms.texture1.value = nextTexture
          uniforms.progress.value = 0
        },
      })
    },
    200,
    { leading: false, trailing: true }
  )

  const resize = () => {
    const width = size.width
    const height = size.height

    // image cover
    const imageAspect = textures[current].image.height / textures[current].image.width
    let a1
    let a2
    if (height / width > imageAspect) {
      a1 = (width / height) * imageAspect
      a2 = 1
    } else {
      a1 = 1
      a2 = height / width / imageAspect
    }

    resolution.x = width
    resolution.y = height
    resolution.z = a1
    resolution.w = a2

    if (material.current) {
      material.current.uniforms.resolution.value.x = width
      material.current.uniforms.resolution.value.y = height
      material.current.uniforms.resolution.value.z = a1
      material.current.uniforms.resolution.value.w = a2
    }
  }

  useEffect(() => {
    next()
  }, [current])

  useEffect(() => {
    resize()
  }, [size])

  return (
    <mesh>
      <shaderMaterial
        ref={material}
        extensions={{
          derivatives: '#extension GL_OES_standard_derivatives : enable',
        }}
        side={THREE.DoubleSide}
        uniforms={uniforms}
        vertexShader={vertex}
        fragmentShader={fragment}
      />
      <planeGeometry material={material.current} args={[camera.aspect, 1, 2, 2]} />
    </mesh>
  )
})

export default GlitchImages
