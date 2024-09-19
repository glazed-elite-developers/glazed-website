import React, { FC, useMemo } from 'react'
import { graphql, useStaticQuery, Link } from 'gatsby'
import Button from '@components/shared/Button'
import Cube from './Cube'
import HTMLText, { Tags } from '@components/shared/HTMLText'
import Animate from '@components/shared/Animate'
import { GatsbyImage, getImage } from 'gatsby-plugin-image'
import Heading, { HeadingLevel } from '@components/shared/Heading'
import GlitchText from '@components/shared/GlitchText'

import * as Styles from './IndexLandingSlide.styles'

// Client logos.
import ASOSLogo from '@static/images/clients/ASOS.png'
import BostonChildrensHospitalLogo from '@static/images/clients/BostonChildrensHospital.png'
import fentyLogo from '@static/images/clients/fenty.png'
import BulgariLogo from '@static/images/clients/Bulgari.png'
import Louis_VuittonLogo from '@static/images/clients/Louis_Vuitton.png'
import ralph_and_russoLogo from '@static/images/clients/ralph_and_russo.png'
import sephoraLogo from '@static/images/clients/sephora.png'
import WeChangersLogo from '@static/images/clients/WeChangers.png'
import BloombergLogo from '@static/images/clients/Bloomberg.png'

// Tech icons.
import Icon_angular_shield from '@static/images/icon_angular_shield.svg'
import Icon_android from '@static/images/icon_android.svg'
import Icon_ruby from '@static/images/icon_ruby.svg'
import Icon_apple from '@static/images/icon_apple.svg'
import Icon_react from '@static/images/icon_react.svg'
import Icon_nodejs from '@static/images/icon_nodejs.svg'

// Social icons.
import Icon_twitter from '@static/images/icon_twitter.svg'
import Icon_facebook from '@static/images/icon_facebook.svg'
import Icon_linkedin from '@static/images/icon_linkedin.svg'
import Icon_github from '@static/images/icon_github.svg'
import SVG from '@components/shared/SVG'

import OfficeJpg from '@static/images/home/office.jpg'
import FullPageSlide from '@components/shared/FullPageSlide'
import usePlatform from '@components/shared/hooks/usePlatform'

const clients = [
  ASOSLogo,
  BostonChildrensHospitalLogo,
  fentyLogo,
  BulgariLogo,
  Louis_VuittonLogo,
  ralph_and_russoLogo,
  sephoraLogo,
  WeChangersLogo,
  BloombergLogo,
]

const techIcons = [
  Icon_angular_shield,
  Icon_android,
  Icon_ruby,
  Icon_apple,
  Icon_react,
  Icon_nodejs,
]

const imageQuery = graphql`
  {
    backgroundImage: file(relativePath: { eq: "home/office.jpg" }) {
      childImageSharp {
        gatsbyImageData(quality: 100, layout: FULL_WIDTH)
      }
    }
  }
`

interface Props {
  id?: string
  innerRef?: React.RefObject<HTMLDivElement>
  onResize?: () => void
  hasMounted: boolean
}

const IndexLandingSlide: FC<Props> = ({
  id,
  innerRef,
  hasMounted,
  onResize,
}) => {
  const platform = usePlatform()
  const queryResult = useStaticQuery(imageQuery)
  const backgroundImage = getImage(queryResult?.backgroundImage)
  const hasPlayedAnimation = useMemo(
    () =>
      platform
        ? false
        : sessionStorage.getItem('hasPlayed:indexLanding') === 'true',
    [platform]
  )

  return (
    <FullPageSlide
      id={id}
      innerRef={innerRef}
      onResize={onResize}
      className={Styles.wrapper}
    >
      <div className={Styles.backgroundImage}>
        {hasMounted ? (
          hasPlayedAnimation && backgroundImage ? (
            <GatsbyImage
              className={Styles.backgroundImage}
              style={{ position: 'absolute' }}
              image={backgroundImage}
              alt="Glazed office."
              loading="eager"
            />
          ) : (
            <img
              style={{
                height: '100%',
                width: '100%',
                objectFit: 'cover',
              }}
              src={OfficeJpg}
            />
          )
        ) : null}
        <Animate
          isIn={hasMounted}
          animationGroup="indexLanding"
          animation="scaleDownY"
          baseDelay={1250}
          duration={1500}
          transformOrigin="top center"
        >
          <div className={`${Styles.imageForeground} ${Styles.mobile}`} />
        </Animate>
        <Animate
          isIn={hasMounted}
          animationGroup="indexLanding"
          animation="scaleUpY"
          baseDelay={2000}
          duration={1500}
          transformOrigin="bottom center"
        >
          <div className={`${Styles.animatedMask} ${Styles.mobile}`} />
        </Animate>
        <Animate
          isIn={hasMounted}
          animationGroup="indexLanding"
          animation="scaleDownX"
          baseDelay={1250}
          duration={1500}
          transformOrigin="center right"
        >
          <div
            className={`${Styles.imageForeground} ${Styles.tabletLandscape}`}
          />
        </Animate>
        <Animate
          isIn={hasMounted}
          animationGroup="indexLanding"
          animation="scaleUpX"
          baseDelay={2000}
          duration={1500}
          transformOrigin="center left"
        >
          <div className={`${Styles.animatedMask} ${Styles.tabletLandscape}`} />
        </Animate>
      </div>
      <Animate
        isIn={hasMounted}
        animationGroup="indexLanding"
        animation="fadeOut"
        baseDelay={1250}
        duration={200}
      >
        <Animate
          isIn={hasMounted}
          animationGroup="indexLanding"
          animation="pulse"
          baseDelay={100}
          duration={625}
          iterationCount={2}
          timingFunction="cubic-bezier(0, 0.75, 0, 1)"
        >
          <div className={Styles.pulse} />
        </Animate>
        <div className={Styles.logoWrapper}>{/* SVG logo code */}</div>
      </Animate>
      <Animate
        isIn={hasMounted}
        animationGroup="indexLanding"
        animation="scaleUp"
        baseDelay={1250}
        duration={1500}
      >
        <Cube className={Styles.cube} />
      </Animate>
      <div className={Styles.content}>
        <div className={Styles.headingWrapper}>
          <Animate
            isIn={hasMounted}
            animationGroup="indexLanding"
            animation="fadeIn"
            baseDelay={2250}
            duration={1500}
            timingFunction="ease-in"
          >
            <span className={Styles.commentedText}>// Some projects</span>
          </Animate>
          <Heading level={HeadingLevel.H1} className={Styles.mainHeading}>
            {hasPlayedAnimation ? (
              'require elite mobile and web developers'
            ) : (
              <GlitchText
                text="require elite mobile and web developers"
                baseDelay={2500}
                itemDelay={25}
                duration={120}
                iterationCount={35}
              />
            )}
          </Heading>
          <div className={Styles.exploreCasesButtonWrapper}>
            <Link to="/#case-studies">
              <Animate
                isIn={hasMounted}
                animationGroup="indexLanding"
                animation="fadeIn"
                baseDelay={2750}
                duration={1000}
                timingFunction="ease-in"
              >
                <Button type="Primary" className={Styles.exploreCasesButton}>
                  &gt; explore cases
                </Button>
              </Animate>
            </Link>
          </div>
        </div>
        <Animate
          isIn={hasMounted}
          animationGroup="indexLanding"
          animation="fadeIn"
          baseDelay={3000}
          duration={750}
          timingFunction="ease-in"
        >
          <HTMLText tag={Tags.p} className={Styles.htmlText}>
            a team of highly specialized developers that takes on the most
            demanding web and mobile development projects
          </HTMLText>
        </Animate>
        <Animate
          isIn={hasMounted}
          animationGroup="indexLanding"
          animation="fadeIn"
          baseDelay={3500}
          duration={750}
          timingFunction="ease-in"
        >
          <pre className={Styles.skillComments}>
            {`
 {
 // machine learning
 // backend
 // frontend
 // android
 // iOS
 // APIs
 ... }
 `}
          </pre>
        </Animate>
        <div className={Styles.techStackIcons}>
          <Animate
            isIn={hasMounted}
            animationGroup="indexLanding"
            animation="slideUpFadeIn"
            baseDelay={3500}
            itemDelay={200}
            duration={1500}
          >
            {techIcons.map((icon, index) => (
              <SVG
                key={index}
                className={Styles.techStackIcon}
                height="16"
                asset={icon}
              />
            ))}
          </Animate>
        </div>
        <div className={Styles.clients}>
          <Animate
            isIn={hasMounted}
            animationGroup="indexLanding"
            animation="fadeIn"
            baseDelay={3750}
            itemDelay={200}
            duration={1500}
            timingFunction="ease-in"
          >
            <span className={Styles.clientsSpan}>clients like:</span>
          </Animate>
          <div className={Styles.clientsImages}>
            <Animate
              isIn={hasMounted}
              animationGroup="indexLanding"
              animation="slideUpFadeIn"
              baseDelay={2750}
              itemDelay={200}
              duration={1000}
            >
              {clients.map((src, index) => (
                <img key={index} className={Styles.clientImage} src={src} />
              ))}
            </Animate>
          </div>
        </div>
      </div>
      <div className={Styles.socialNetworks}>
        <Animate
          isIn={hasMounted}
          animationGroup="indexLanding"
          animation="slideUpFadeIn"
          baseDelay={2000}
          itemDelay={200}
          duration={1000}
        >
          <a
            className={Styles.socialIconLink}
            href="https://twitter.com/glazedSolutions"
            rel="nofollow"
            target="_blank"
          >
            <SVG
              className={Styles.socialIcon}
              height="16"
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
              height="16"
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
              height="16"
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
              height="16"
              asset={Icon_github}
            />
          </a>
        </Animate>
      </div>
    </FullPageSlide>
  )
}

export default IndexLandingSlide
