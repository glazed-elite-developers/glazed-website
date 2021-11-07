import React, { useRef, useEffect, Suspense } from 'react'
import { Canvas, useThree, useFrame } from 'react-three-fiber'
import { useInView } from 'react-intersection-observer'
import BackgroundImage from 'gatsby-background-image'
import { useStaticQuery, graphql } from 'gatsby'

const Camera = ({ forwardRef, ...props }) => {
  const { size, setDefaultCamera } = useThree()

  // eslint-disable-next-line no-void
  useEffect(() => void setDefaultCamera(forwardRef.current), [])

  return (
    <perspectiveCamera
      {...props}
      ref={forwardRef}
      fov={2 * (180 / Math.PI) * Math.atan(1 / (2 * 2))}
      aspect={size.width / size.height}
      near={0.001}
      far={1000}
      onUpdate={self => self.updateProjectionMatrix()}
    />
  )
}

const DisableRender = () => useFrame(() => null, 1000)

const GlitchCanvas = ({ children }) => {
  // TODO: Move this to the parent
  const data = useStaticQuery(graphql`
    query {
      LVMH: file(relativePath: { eq: "case-studies/lvmh-hero.jpg" }) {
        childImageSharp {
          fluid(maxWidth: 1200) {
            ...GatsbyImageSharpFluid_withWebp_noBase64
          }
        }
      }
    }
  `)

  const cameraRef = useRef()
  const cameraPosition = [0, 0, 2]

  const { ref, inView } = useInView()

  return (
    <div ref={ref} style={{ width: '100%', height: '100%' }}>
      <Canvas pixelRatio={(typeof window !== 'undefined' && window.devicePixelRatio) || 1}>
        {!inView && <DisableRender />}
        <ambientLight />
        <Camera forwardRef={cameraRef} position={cameraPosition} />
        <Suspense
          fallback={
            <BackgroundImage
              fluid={data.LVMH.fluid}
              style={{
                position: 'absolute',
                top: 0,
                left: 0,
                right: 0,
                bottom: 0,
              }}
            />
          }
        >
          {children}
        </Suspense>
      </Canvas>
    </div>
  )
}

export default GlitchCanvas
