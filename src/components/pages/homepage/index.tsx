import React, {
  useState,
  useRef,
  useCallback,
  useEffect,
  useMemo,
  FC,
  memo,
} from 'react'
import { css, keyframes } from '@emotion/css'
import { Colors, Breakpoints } from '@styles/Theme'
import Layout from '@components/shared/Layout'
import PageLayout from '@components/shared/PageLayout'
import PageContent from '@components/shared/PageContent'
import IndexLandingSlide from './IndexLandingSlide'
import IndexCaseStudiesSlide from './case-studies-slide/IndexCaseStudiesSlide'
import IndexAboutSlide from './about-slide/IndexAboutSlide'
import IndexTeamSlide from './team-slide/IndexTeamSlide'
import IndexManifestoSlide from './IndexManifestoSlide'
import {
  useClosestScrollerAPI,
  useClosestScrollValues,
} from '@components/shared/scroll-container/scrollConnectors'
import usePlatform from '@components/shared/hooks/usePlatform'
import useDidMount from '@components/shared/hooks/useDidMount'

const Styles = {
  pageLayout: css`
    max-height: 100%;
    height: 100%;
  `,
  wrapper: css`
    max-height: 100%;
    padding: 0;
    background-color: ${Colors.glazedBlue};
    flex: 1 1 0.00000001rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 0;
    }
  `,
  fadeIn: keyframes`
    100% {
      visibility: visible;
      opacity: 1;
    }
  `,
  header: (hasAnimated: boolean) => css`
    @media (min-width: ${Breakpoints.tabletLandscape}) {
      opacity: ${hasAnimated ? 1 : 0};
      visibility: ${hasAnimated ? 'visible' : 'hidden'};
      animation-name: ${Styles.fadeIn};
      animation-duration: ${hasAnimated ? '0ms' : '1500ms'};
      animation-delay: ${hasAnimated ? '0ms' : '2500ms'};
      animation-fill-mode: forwards;
      animation-timing-function: ease-out;
    }
  `,
}

const usePagePositionController = (numberOfSlides: number) => {
  const [positions, setPositions] = useState<number[]>(
    Array(numberOfSlides).fill(0)
  )
  const refs = useRef<React.RefObject<HTMLDivElement>[]>(
    Array.from({ length: numberOfSlides }, () => React.createRef())
  )
  const scrollerAPI = useClosestScrollerAPI()
  const updatePositions = useCallback(() => {
    refs.current.forEach((slideRef, index) => {
      const current = slideRef.current
      if (current) {
        const nextPosition =
          current.getBoundingClientRect().top +
          scrollerAPI.getScrollPosition().scrollTop
        setPositions((state) =>
          state.map((pos, idx) => (index === idx ? nextPosition : pos))
        )
      }
    })
  }, [scrollerAPI])

  const handleResize = useCallback(() => {
    updatePositions()
  }, [updatePositions])

  useEffect(() => {
    updatePositions()
  }, [updatePositions])

  return [positions, refs.current, handleResize] as const
}

const useCurrentSlideIndex = (positions: number[], offsetY: number) => {
  const scrollValues = useClosestScrollValues()
  return useMemo(() => {
    return positions.reduce((currentPage, position, index) => {
      return scrollValues.position.scrollTop + scrollValues.boundingRect.top >=
        position + offsetY
        ? index
        : currentPage
    }, 0)
  }, [scrollValues, positions, offsetY])
}

const pagesWithDarkNavBarLinks = new Set([2, 4])
const slideIDs = ['hey', 'case-studies', 'about', 'team', 'manifesto']

const HomePage: FC = () => {
  const platform = usePlatform()
  const hasMounted = useDidMount()
  const [positions, domSlideRefs, onResize] = usePagePositionController(5)
  const currentPageIndex = useCurrentSlideIndex(positions, -65)
  const useDarkNavBarLinks = pagesWithDarkNavBarLinks.has(currentPageIndex)
  const hasPlayedAnimation = useMemo(
    () =>
      platform
        ? false
        : sessionStorage.getItem('hasPlayed:indexLanding') === 'true',
    [platform]
  )

  return (
    <Layout>
      <PageLayout
        className={Styles.pageLayout}
        headerClassName={Styles.header(hasPlayedAnimation)}
        useDarkNavBarLinks={useDarkNavBarLinks}
        currentPageIndex={currentPageIndex}
      >
        <PageContent className={Styles.wrapper}>
          <IndexLandingSlide
            id={slideIDs[0]}
            innerRef={domSlideRefs[0]}
            onResize={onResize}
            hasMounted={hasMounted}
          />
          <IndexCaseStudiesSlide
            id={slideIDs[1]}
            innerRef={domSlideRefs[1]}
            onResize={onResize}
          />
          <IndexAboutSlide
            id={slideIDs[2]}
            innerRef={domSlideRefs[2]}
            onResize={onResize}
          />
          <IndexTeamSlide
            id={slideIDs[3]}
            innerRef={domSlideRefs[3]}
            onResize={onResize}
          />
          <IndexManifestoSlide
            id={slideIDs[4]}
            innerRef={domSlideRefs[4]}
            onResize={onResize}
          />
        </PageContent>
      </PageLayout>
    </Layout>
  )
}

export default memo(HomePage)
