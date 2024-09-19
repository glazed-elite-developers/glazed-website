import React, { useRef, useEffect, Suspense, ReactNode } from 'react'
import { Canvas, useThree, useFrame } from '@react-three/fiber' // Updated import
import { useInView } from 'react-intersection-observer'
import { useStaticQuery, graphql } from 'gatsby'
import {
  GatsbyImage,
  GatsbyImageProps,
  getImage,
  ImageDataLike,
} from 'gatsby-plugin-image'
import * as THREE from 'three'

interface CameraProps {
  forwardRef: React.RefObject<any>
  position?: [number, number, number]
}

const Camera: React.FC<CameraProps> = ({ forwardRef, ...props }) => {
  const { size, set, camera } = useThree()

  useEffect(() => {
    if (forwardRef.current) {
      set({ camera: forwardRef.current })
    }
  }, [forwardRef, set])

  const aspect =
    camera instanceof THREE.PerspectiveCamera ? size.width / size.height : 1

  return (
    <perspectiveCamera
      {...props}
      ref={forwardRef}
      fov={2 * (180 / Math.PI) * Math.atan(1 / (2 * 2))}
      aspect={aspect}
      near={0.001}
      far={1000}
      onUpdate={(self: THREE.PerspectiveCamera) =>
        self.updateProjectionMatrix()
      }
    />
  )
}

const DisableRender: React.FC = () => useFrame(() => null, 1000)

const fallbackImageQuery = graphql`
  {
    LVMH: file(relativePath: { eq: "case-studies/lvmh-hero.jpg" }) {
      childImageSharp {
        gatsbyImageData(placeholder: NONE, layout: FULL_WIDTH)
      }
    }
  }
`

interface GlitchCanvasProps {
  children: ReactNode
}

interface StaticQueryData {
  LVMH: ImageDataLike | null
}

const GlitchCanvas: React.FC<GlitchCanvasProps> = ({ children }) => {
  const data = useStaticQuery<StaticQueryData>(fallbackImageQuery)
  const fallbackImage = getImage(data.LVMH)
  const cameraRef = useRef<THREE.PerspectiveCamera>(null)
  const cameraPosition: [number, number, number] = [0, 0, 2]

  const { ref, inView } = useInView()

  return (
    <div ref={ref} style={{ width: '100%', height: '100%' }}>
      <Suspense
        fallback={
          fallbackImage && (
            <GatsbyImage
              image={fallbackImage}
              alt="LVMH headquarters"
              style={{
                position: 'absolute',
                top: 0,
                left: 0,
                right: 0,
                bottom: 0,
              }}
            />
          )
        }
      >
        <Canvas
          dpr={(typeof window !== 'undefined' && window.devicePixelRatio) || 1}
        >
          {!inView && <DisableRender />}
          <ambientLight />
          <Camera forwardRef={cameraRef} position={cameraPosition} />
          {children}
        </Canvas>
      </Suspense>
    </div>
  )
}

export default GlitchCanvas
