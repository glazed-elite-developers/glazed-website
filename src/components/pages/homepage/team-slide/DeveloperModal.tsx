import React, { FC, SyntheticEvent, useCallback } from 'react'
import { graphql, Link, useStaticQuery } from 'gatsby'
import SVG from '../../../shared/SVG'
import Button from '../../../shared/Button'
import BaseModal from '../../../shared/modals/BaseModal'
import LogoGlazedOutlineSvg from 'static/images/logo-glazed-outline.svg'
import DeveloperBackgroundImage from './DeveloperBackgroundImage'
import Heading, { HeadingLevel } from '@components/shared/Heading'
import MobileFooterLayout from '@components/shared/MobileFooterLayout'
import { BaseModalProps } from '@components/shared/modals'
import { useLocation } from '@reach/router'
import { navigate } from '@components/shared/Routing'
import * as Styles from './DeveloperModal.styles'
import { getImage } from 'gatsby-plugin-image'
import { Developer } from './squares'

const teamSlideLink = '/#team'

const CloseButton: FC<{ close: (event: SyntheticEvent) => void }> = ({
  close,
}) => (
  <Link
    to={teamSlideLink}
    className={Styles.closeButtonWrapper}
    onClick={close}
  >
    <Button className={Styles.closeButton}>{'< back team'}</Button>
  </Link>
)

const MobileFooter: FC<{ close: (event: SyntheticEvent) => void }> = ({
  close,
}) => (
  <MobileFooterLayout className={Styles.mobileFooter}>
    <Link to={teamSlideLink} onClick={close}>
      <Button className={Styles.mobileCloseButton}>{'< back team'}</Button>
    </Link>
  </MobileFooterLayout>
)

const photoOverlay = graphql`
  {
    overlay: file(relativePath: { eq: "team/overlay.png" }) {
      childImageSharp {
        gatsbyImageData(placeholder: NONE, layout: FULL_WIDTH)
      }
    }
  }
`

type DeveloperModalProps = BaseModalProps & {
  developer: Developer
}

const DeveloperModal: FC<DeveloperModalProps> = ({
  developer,
  onClose,
  onExited = () => {},
  ...props
}) => {
  const location = useLocation()
  const exit = useCallback(
    (element: HTMLElement) => {
      onExited(element)
      const match = new URLSearchParams(location.search).get('modal')
      if (match !== 'team') return
      navigate({ preventDefaultScrollBehavior: true }, true, teamSlideLink)
    },
    [onExited, location]
  )
  const queryResult = useStaticQuery(photoOverlay)
  const developerPhoto = getImage(developer.photo)
  const developerPhotoOverlay = getImage(queryResult.overlay)

  const handleCloseButtonClick = useCallback(
    (event: SyntheticEvent) => {
      event.preventDefault()
      onClose()
    },
    [onClose]
  )

  return (
    <BaseModal
      onClose={onClose}
      className={Styles.contentWrapper}
      scrollContainerClassName={Styles.wrapper}
      contentClassName={Styles.content}
      onExited={exit}
      {...props}
    >
      {developerPhoto && (
        <DeveloperBackgroundImage
          image={developerPhoto}
          className={Styles.developerBackgroundImage}
        />
      )}
      {developerPhotoOverlay && (
        <DeveloperBackgroundImage
          image={developerPhotoOverlay}
          className={Styles.overlayImage}
        />
      )}
      <Heading level={HeadingLevel.H1} className={Styles.heading}>
        {developer.name.split(' ').map((name, index) => (
          <div key={index}>{name}</div>
        ))}
      </Heading>
      <div className={Styles.descriptions}>
        <Heading level={HeadingLevel.H3} className={Styles.shortDescription}>
          {developer.shortDescription}
        </Heading>
        <p className={Styles.description}>{developer.description}</p>
      </div>
      <div className={Styles.skillsAndLinkedIn}>
        <a
          className={Styles.linkedinLink}
          href={developer.linkedInUrl}
          rel="nofollow"
          target="_blank"
        >
          &gt; LinkedIn
        </a>
        <p className={Styles.skills}>{`{ ${developer.skills.join(' ')} }`}</p>
        <p className={Styles.desktopSkills}>
          {`{\n${developer.skills.map((skill) => `// ${skill}\n`).join('')}}`}
        </p>
      </div>
      <div className={Styles.logoWrapper}>
        <SVG className={Styles.logo} asset={LogoGlazedOutlineSvg} />
      </div>
      <CloseButton close={handleCloseButtonClick} />
      <MobileFooter close={handleCloseButtonClick} />
    </BaseModal>
  )
}

export default DeveloperModal
