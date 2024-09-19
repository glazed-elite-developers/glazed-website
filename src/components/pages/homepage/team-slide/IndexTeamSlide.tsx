import React, {
  memo,
  ReactNode,
  RefObject,
  SyntheticEvent,
  useCallback,
  useEffect,
  useMemo,
  useRef,
} from 'react'
import { graphql, Link, useStaticQuery } from 'gatsby'
import { cx } from '@emotion/css'
import Square from '@components/shared/Square'
import Heading, { HeadingLevel } from '@components/shared/Heading'
import { navigate } from '@components/shared/Routing'
import DeveloperBackgroundImage from './DeveloperBackgroundImage'
import { useModalsAPI } from '@components/shared/modals'
import { useLocation } from '@reach/router'
import { Developer, buildDeveloperSquares } from './squares'
import DeveloperModal from './DeveloperModal'
import FullPageSlide from '@components/shared/FullPageSlide'
import { Modal } from '@components/shared/modals/StatelessModalController'
import useOpenPageModal from '@components/shared/hooks/useOpenPageModal'
import * as Styles from './IndexTeamSlide.styles'
import { getImage } from 'gatsby-plugin-image'

interface TeamSlideSquareProps {
  children: ReactNode
  contentClassName?: string
}

function TeamSlideSquare({ children, contentClassName }: TeamSlideSquareProps) {
  return (
    <Square
      className={Styles.square}
      contentClassName={cx([Styles.squareContent, contentClassName])}
    >
      {children}
    </Square>
  )
}

interface TitleSquareProps {
  title: string
}

function TitleSquare({ title }: TitleSquareProps) {
  return (
    <TeamSlideSquare
      contentClassName={`${Styles.headingSquare} ${Styles.squareWithBorder}`}
    >
      <Heading level={HeadingLevel.H1} className={Styles.heading}>
        {title}
      </Heading>
    </TeamSlideSquare>
  )
}

interface MottoSquareProps {
  motto: string
}

function MottoSquare({ motto }: MottoSquareProps) {
  return (
    <TeamSlideSquare contentClassName={Styles.squareWithBorder}>
      <Heading level={HeadingLevel.H2} className={Styles.motto}>
        {motto}
      </Heading>
    </TeamSlideSquare>
  )
}

function SendApplicationSquare() {
  const { openModal, modalUrl } = useOpenPageModal('job-offer')

  return (
    <TeamSlideSquare contentClassName={Styles.squareWithBorder}>
      <Heading level={HeadingLevel.H2} className={Styles.sendApplication}>
        {'<Your name could be here />'}
      </Heading>
      <Link
        to={modalUrl}
        className={Styles.link}
        onClick={openModal}
        state={{ preventDefaultScrollBehavior: true }}
      >
        {'> send application'}
      </Link>
    </TeamSlideSquare>
  )
}

const selectedDeveloperQueryStringKey = 'unit'

function developerLink(key: string) {
  return `/?modal=team&${selectedDeveloperQueryStringKey}=${key}`
}

interface DeveloperSquareProps {
  developer: Developer
}

function DeveloperSquare({ developer }: DeveloperSquareProps) {
  const link = developerLink(developer.key)
  const onClick = useCallback(
    (event: SyntheticEvent) => {
      event.preventDefault()
      navigate({ preventDefaultScrollBehavior: true }, undefined, link)
    },
    [developer]
  )
  const developerPhoto = getImage(developer.photo)

  return (
    <TeamSlideSquare contentClassName={Styles.developerSquare}>
      <Link
        to={link}
        className={Styles.developerSquareLink}
        onClick={onClick}
        replace
        state={{ preventDefaultScrollBehavior: true }}
      >
        {developerPhoto && (
          <DeveloperBackgroundImage
            image={developerPhoto}
            className={Styles.developerBackgroundImageWrapper}
            gatsbyBackgroundImageClassName={Styles.developerBackgroundImage}
            style={{
              backgroundPosition: 'top center',
              marginTop: '10%',
              backgroundSize: 'auto 250%',
            }}
          />
        )}
        <div className={Styles.developerSquareContent}>
          <Heading level={HeadingLevel.H6} className={Styles.developerName}>
            {developer.name.replace(' ', '\n')}
          </Heading>
          <p className={Styles.developerSkills}>
            {`{ ${developer.skills.join(' // ')} }`}
          </p>
        </div>
      </Link>
    </TeamSlideSquare>
  )
}

export const query = graphql`
  query {
    allHygraphDeveloper {
      nodes {
        key
        name
        description
        shortDescription
        skills
        linkedInUrl
        photo {
          gatsbyImageData(placeholder: NONE, layout: FULL_WIDTH)
        }
      }
    }
  }
`

type DevelopersQueryResult = {
  allHygraphDeveloper: {
    nodes: Array<Developer>
  }
}

type Square =
  | { type: 'TitleSquare'; content: string }
  | { type: 'DeveloperSquare'; developerKey: string }
  | { type: 'MottoSquare'; content: string }
  | { type: 'SendApplicationSquare' }

interface IndexTeamSlideProps {
  innerRef?: RefObject<HTMLDivElement>
  id?: string
  onResize?: () => void
}

const IndexTeamSlide = ({ innerRef, id, onResize }: IndexTeamSlideProps) => {
  const openedModalRef = useRef<Modal>()
  const modalsAPI = useModalsAPI()
  const location = useLocation()
  const selectedDeveloper = new URLSearchParams(location.search).get(
    selectedDeveloperQueryStringKey
  )
  const developersQueryResult = useStaticQuery<DevelopersQueryResult>(query)
  const developers = developersQueryResult.allHygraphDeveloper.nodes
  const squares = useMemo(() => buildDeveloperSquares(developers), [developers])

  useEffect(() => {
    if (openedModalRef.current !== undefined) {
      modalsAPI.closeModal(openedModalRef.current)
    }

    const developer = selectedDeveloper
      ? developers.find((developer) => developer.key === selectedDeveloper)
      : undefined

    if (developer) {
      const modal = modalsAPI.openModal((propsforModal) => (
        <DeveloperModal {...propsforModal} developer={developer} />
      ))
      openedModalRef.current = modal
    }
  }, [selectedDeveloper])

  return (
    <FullPageSlide
      innerRef={innerRef}
      id={id}
      className={Styles.wrapper}
      onResize={onResize}
    >
      <div className={Styles.grid}>
        {squares.map((square, index) => {
          switch (square.type) {
            case 'SendApplicationSquare':
              return <SendApplicationSquare key={index} />
            case 'TitleSquare':
              return <TitleSquare title={square.content} key={index} />
            case 'MottoSquare':
              return <MottoSquare motto={square.content} key={index} />
            case 'DeveloperSquare':
              const developer = developers.find(
                (developer) => developer.key === square.developerKey
              )
              return developer ? (
                <DeveloperSquare key={index} developer={developer} />
              ) : null
          }
        })}
      </div>
    </FullPageSlide>
  )
}

export default memo(IndexTeamSlide)
