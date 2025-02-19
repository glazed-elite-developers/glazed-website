import React, { FC, SyntheticEvent, useCallback, useState } from 'react'
import { cx } from '@emotion/css'
import { Link, graphql, useStaticQuery } from 'gatsby'
import { useLocation } from '@reach/router'
import BackgroundImage from 'gatsby-background-image'
import * as Styles from './SayHelloModal.styles'
import Header from './Header'
import MobileFooter from './MobileFooter'
import Button from './Button'
import { BaseModal, BaseModalProps } from './modals'
import ScrollContainer from './scroll-container'
import { navigate } from './Routing'
import SVG from './SVG'
import ContactForm from './ContactForm'
import Heading, { HeadingLevel } from './Heading'
import Icon_github from '@static/images/icon_github.svg'
import Icon_twitter from '@static/images/icon_twitter.svg'
import Icon_facebook from '@static/images/icon_facebook.svg'
import Icon_linkedin from '@static/images/icon_linkedin.svg'
import Icon_back_arrow from '@static/images/icon_back_arrow.svg'
import LogoGlazedSmall from '@static/images/logo-glazed-small.svg'
import { getResponsiveBackgroundImageFluid } from '@helpers/gatsby'

const emailSubject = 'Glazed Mail'

const backgroundImageQuery = graphql`
  query {
    map_mobile: file(relativePath: { eq: "map_mobile.png" }) {
      childImageSharp {
        gatsbyImageData(width: 1024, placeholder: NONE, layout: CONSTRAINED)
      }
    }
    map_desktop: file(relativePath: { eq: "map.png" }) {
      childImageSharp {
        gatsbyImageData(width: 2000, placeholder: NONE, layout: CONSTRAINED)
      }
    }
  }
`

interface CloseButtonProps {
  backToUrl: string
  close: (event: SyntheticEvent) => void
}

const CloseButton: FC<CloseButtonProps> = ({ backToUrl, close }) => (
  <Link to={backToUrl} className={Styles.closeButtonWrapper} onClick={close}>
    <Button className={Styles.closeButton}>
      <SVG height="12" asset={Icon_back_arrow} />
    </Button>
  </Link>
)

const SayHelloModal: FC<BaseModalProps> = ({
  onClose,
  onExited = () => {},
  ...props
}) => {
  const location = useLocation()
  const backToUrl = new URLSearchParams(location.search).get('backTo') || '/'
  const handleExited = useCallback(
    (element: HTMLElement) => {
      onExited(element)
      const modal = new URLSearchParams(location.search).get('modal')
      if (modal === 'say-hello') {
        navigate({ preventDefaultScrollBehavior: true }, undefined, backToUrl)
      }
    },
    [onExited, backToUrl, location]
  )
  const handleCloseButtonClick = useCallback(
    (event: SyntheticEvent) => {
      event.preventDefault()
      onClose()
    },
    [onClose]
  )
  const onNavBarLinkClick = useCallback(
    () => (link: string) => {
      navigate(undefined, undefined, link)
    },
    []
  )

  const [submissionStatus, setSubmissionStatus] = useState<
    'Pristine' | 'Pending' | 'Success' | 'Failed'
  >('Pristine')

  const onSubmit = useCallback(
    (values: any) => {
      setSubmissionStatus('Pending')
      const payload: Record<string, string> = {
        ...values,
        subject: emailSubject,
      }

      fetch('/.netlify/functions/sendEmail', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(payload),
      })
        .then((response) => {
          if (response.status < 200 || response.status >= 300) {
            throw new Error(response.statusText)
          }
          return response.json()
        })
        .then(() => setSubmissionStatus('Success'))
        .catch(() => setSubmissionStatus('Failed'))
    },
    [setSubmissionStatus]
  )

  const onChange = useCallback(() => {
    if (submissionStatus !== 'Pristine') {
      setSubmissionStatus('Pristine')
    }
  }, [submissionStatus, setSubmissionStatus])

  const [formMessageClass, contactFormClass, headingText] =
    submissionStatus === 'Success'
      ? [
          Styles.formMessageHidden,
          cx([Styles.contactForm, Styles.hidden]),
          "we'll get in touch soon!",
        ]
      : [Styles.formMessage, Styles.contactForm, 'say hello']

  const queryResult = useStaticQuery(backgroundImageQuery)
  const fluidMapImage = getResponsiveBackgroundImageFluid(queryResult, [
    ['map_mobile', undefined],
    ['map_desktop', '(min-width: 1024px)'],
  ])

  return (
    <BaseModal
      className={Styles.contentWrapper}
      contentClassName={Styles.content}
      scrollContainerClassName={Styles.wrapper}
      onExited={handleExited}
      onClose={onClose}
      {...props}
    >
      <ScrollContainer
        className={Styles.scrollContainer}
        contentClassName={Styles.scrollContainer}
      >
        <div className={Styles.contacts}>
          <div className={Styles.map}>
            <BackgroundImage
              fluid={fluidMapImage}
              className={Styles.mapImage}
              style={{ position: 'absolute' }}
              alt="Glazed on the map."
            />
            <SVG className={Styles.mapPin} asset={LogoGlazedSmall} />
            <div className={Styles.addressDetails}>
              <p className={Styles.address}>
                Rua Mouzinho de Albuquerque{'\n'}nº 744, 3º andar
              </p>
              <p className={Styles.postalCode}>4450-203 Matosinhos, PT</p>
              <a
                className={Styles.openInMapsLink}
                href="https://goo.gl/maps/V6Q8fQyzHStX6wGx7"
                rel="nofollow"
                target="_blank"
              >
                {'>'} open in google maps
              </a>
            </div>
          </div>
          <div className={Styles.form}>
            <div className={Styles.socialNetworks}>
              <a
                className={Styles.socialIconLink}
                href="https://twitter.com/glazedSolutions"
                rel="nofollow"
                target="_blank"
              >
                <SVG
                  className={Styles.socialIcon}
                  height="14"
                  asset={Icon_twitter}
                />
              </a>
              <a
                className={Styles.socialIconLink}
                href="https://www.facebook.com/glazedEliteDevelopers/"
                rel="nofollow"
                target="_blank"
              >
                <SVG
                  className={Styles.socialIcon}
                  height="14"
                  asset={Icon_facebook}
                />
              </a>
              <a
                className={Styles.socialIconLink}
                href="https://www.linkedin.com/company/glazed-solutions/"
                rel="nofollow"
                target="_blank"
              >
                <SVG
                  className={Styles.socialIcon}
                  height="14"
                  asset={Icon_linkedin}
                />
              </a>
              <a
                className={Styles.socialIconLink}
                href="https://github.com/glazed-elite-developers"
                rel="nofollow"
                target="_blank"
              >
                <SVG
                  className={Styles.socialIcon}
                  height="14"
                  asset={Icon_github}
                />
              </a>
            </div>
            <Heading level={HeadingLevel.H3} className={Styles.heading}>
              {headingText}
            </Heading>
            <div className={formMessageClass}>
              <p className={Styles.fillFormMessage}>
                Fill the form, or, if you prefer,
              </p>
              <p className={Styles.sendEmailParagraph}>
                {'<a>'}
                <a
                  className={Styles.link}
                  href="mailto:info@glazedsolutions.com"
                >
                  send us an email
                </a>
                {'</a>'}
              </p>
            </div>
            <ContactForm
              className={contactFormClass}
              onSubmit={onSubmit}
              onChange={onChange}
              submissionStatus={submissionStatus}
            />
          </div>
        </div>
      </ScrollContainer>
      <Header
        className={Styles.header}
        componentAtTheRight={
          <CloseButton backToUrl={backToUrl} close={handleCloseButtonClick} />
        }
        onNavBarLinkClick={onNavBarLinkClick}
        useDarkNavBarLinks={true}
      />
      <MobileFooter
        componentAtTheRight={
          <Link to={backToUrl} onClick={handleCloseButtonClick}>
            <Button className={Styles.mobileCloseButton}>
              {'< back team'}
            </Button>
          </Link>
        }
      />
    </BaseModal>
  )
}

export default SayHelloModal
