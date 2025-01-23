import React, {
  memo,
  useState,
  FC,
  useMemo,
  useCallback,
  SyntheticEvent,
} from 'react'
import { graphql, useStaticQuery } from 'gatsby'
import { cx } from '@emotion/css'
import FullPageSlide from '@components/shared/FullPageSlide'
import MaskContainer from '@components/shared/MaskContainer'
import GlitchImages from '@components/shared/GlitchImages'
import Square from '@components/shared/Square'
import Heading, { HeadingLevel } from '@components/shared/Heading'
import GlitchCanvas from '@components/shared/GlitchCanvas'
import CaseStudiesSlideSquare from '../CaseStudiesSlideSquare'
import CaseStudySquare, { CaseStudy } from '../CaseStudySquare'
import * as Styles from './styles'

export const query = graphql`
  query {
    allHygraphCaseStudy {
      nodes {
        name
        slug
        category
        heroImage {
          url
        }
      }
    }
  }
`

type CaseStudiesQueryResult = {
  allHygraphCaseStudy: {
    nodes: Array<CaseStudy>
  }
}

interface CaseStudiesProps {
  innerRef?: React.RefObject<HTMLDivElement>
  id?: string
  onResize?: () => void
}

const CaseStudies: FC<CaseStudiesProps> = ({ innerRef, id, onResize }) => {
  const result = useStaticQuery<CaseStudiesQueryResult>(query)
  const caseStudies = result.allHygraphCaseStudy.nodes
  const backgroundImageSources = useMemo(
    () =>
      caseStudies
        .map((entry) => entry.heroImage?.url)
        .filter(Boolean) as Array<string>,
    [caseStudies]
  )
  const [selectedCaseStudyIndex, baseSelectCaseStudyIndex] = useState(0)
  const selectCaseStudyIndex = useCallback(
    (index: number, event: SyntheticEvent) => {
      baseSelectCaseStudyIndex(index)
      event.preventDefault()
    },
    [baseSelectCaseStudyIndex]
  )

  return (
    <FullPageSlide
      className={Styles.wrapper}
      id={id}
      innerRef={innerRef}
      onResize={onResize}
    >
      <MaskContainer
        className={Styles.backgroundImage}
        maskClassName={Styles.maskContainer}
      >
        <GlitchCanvas>
          <GlitchImages
            imageSources={backgroundImageSources}
            current={selectedCaseStudyIndex}
          />
        </GlitchCanvas>
      </MaskContainer>
      <div className={Styles.grid}>
        <div className={Styles.backgroundGrid}>
          <div className={Styles.dimmedBackgroundSquareRow}>
            <Square className={Styles.squareWithBorder} />
          </div>
          <div className={Styles.backgroundSquareRow}>
            {caseStudies.map((_, index) => (
              <Square key={index} className={Styles.squareWithBorder} />
            ))}
          </div>
          <div
            className={cx(
              Styles.dimmedBackgroundSquareRow,
              Styles.onlyInMobile
            )}
          >
            <Square
              className={Styles.square}
              contentClassName={Styles.fakeSquareContent}
            />
            <Square className={Styles.squareWithBorder} />
          </div>
        </div>
        <div className={Styles.grid}>
          <div className={Styles.squareRow}>
            <CaseStudiesSlideSquare
              className={Styles.square}
              contentClassName={Styles.headingSquareContent}
            >
              <Heading level={HeadingLevel.H1} className={Styles.heading}>
                // case studies
              </Heading>
            </CaseStudiesSlideSquare>
          </div>
          <div className={Styles.squareRow}>
            {caseStudies.map((caseStudy, index) => (
              <CaseStudySquare
                key={index}
                caseStudy={caseStudy}
                index={index}
                className={Styles.square}
                contentWrapperClassName={Styles.squareContent}
                isSelected={caseStudy === caseStudies[selectedCaseStudyIndex]}
                onMouseEnter={
                  caseStudy !== caseStudies[selectedCaseStudyIndex]
                    ? (event: SyntheticEvent) =>
                        selectCaseStudyIndex(index, event)
                    : undefined
                }
              />
            ))}
          </div>
          <div className={cx(Styles.squareRow, Styles.onlyInMobile)}>
            <CaseStudiesSlideSquare
              className={Styles.square}
              contentClassName={Styles.fakeSquareContent}
            />
            <CaseStudiesSlideSquare className={Styles.square} />
          </div>
        </div>
      </div>
    </FullPageSlide>
  )
}

export default memo(CaseStudies)
