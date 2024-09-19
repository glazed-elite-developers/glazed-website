import React, { ReactNode, useMemo, useRef, useEffect } from 'react'
import { css } from '@emotion/css'
import { Link, useLocation } from '@reach/router'
import useOpenPageModal from './hooks/useOpenPageModal'
import Button from './Button'
import Header from './Header'
import MobileFooter from './MobileFooter'
import JobOfferModal from './JobOfferModal'
import SayHelloModal from './SayHelloModal'
import FloatingHeader from './FloatingHeader'
import { useModalsAPI } from './modals/ModalsController'
import { Fonts } from '../../styles/Theme'
import { cx } from '@emotion/css'
import { Modal } from './modals/StatelessModalController'

const Styles = {
  wrapper: css`
    display: flex;
    flex-direction: column;
    position: relative;
    background-color: #ffffff;
    flex: 1 1 0.00000001rem;
  `,
  header: css`
    position: fixed;
    top: 0;
    right: 14px;
    left: 0;
    z-index: 1;
  `,
  padFloatingNav: css`
    padding-top: 75px;

    @media (min-width: 768px) {
      padding-top: 117px;
    }
  `,
  sayHelloButton: (useDarkNavBarLinks: boolean) => css`
    display: none;
    padding: 0.875rem 1.75rem;
    color: ${useDarkNavBarLinks ? '#2e2e2e' : '#ffffff'};
    font-size: 0.75rem;
    font-family: ${Fonts.heading};
    pointer-events: auto;

    @media (min-width: 768px) {
      display: block;
    }
  `,
  mobileCloseButtonWrapper: css`
    flex: 0 0 auto;
  `,
  mobileCloseButton: css`
    padding: 0.625rem;
    margin: 0 0.9375rem;
    background: none;
    color: #ffffff;
    font-family: ${Fonts.heading};
    font-size: 0.625rem;
  `,
}

interface PageWrapperProps {
  children: ReactNode
  className?: string
  headerClassName?: string
  headerStyle?: React.CSSProperties
  useDarkNavBarLinks?: boolean
  useFloatingNavBar?: boolean
  currentPageIndex?: number
  onHeaderResize?: () => void
}

const PageLayout: React.FC<PageWrapperProps> = ({
  children,
  className,
  headerClassName,
  headerStyle,
  useDarkNavBarLinks = false,
  useFloatingNavBar = false,
  currentPageIndex = 0,
  onHeaderResize,
}) => {
  const { openModal, modalUrl } = useOpenPageModal('say-hello')
  const openedModalRef = useRef<Modal | undefined>(undefined)
  const modalsAPI = useModalsAPI()
  const location = useLocation()
  const selectedModal = new URLSearchParams(location.search).get('modal')

  const headerComponentAtTheRight = useMemo(
    () => (
      <Link
        to={modalUrl}
        onClick={openModal}
        state={{ state: { preventDefaultScrollBehavior: true } }}
      >
        <Button
          type="Secondary"
          className={Styles.sayHelloButton(useDarkNavBarLinks)}
        >
          {'> say hello'}
        </Button>
      </Link>
    ),
    [modalUrl, openModal, useDarkNavBarLinks]
  )

  const footerComponentAtTheRight = useMemo(
    () => (
      <Link
        to={modalUrl}
        className={Styles.mobileCloseButtonWrapper}
        onClick={openModal}
      >
        <Button type="Secondary" className={Styles.mobileCloseButton}>
          {'> say hello'}
        </Button>
      </Link>
    ),
    [modalUrl, openModal]
  )

  useEffect(() => {
    if (openedModalRef.current) {
      modalsAPI.closeModal(openedModalRef.current)
    }

    if (selectedModal) {
      switch (selectedModal) {
        case 'job-offer':
          openedModalRef.current = modalsAPI.openModal((propsForModal) => (
            <JobOfferModal {...propsForModal} />
          ))
          break
        case 'say-hello':
          openedModalRef.current = modalsAPI.openModal((propsForModal) => (
            <SayHelloModal {...propsForModal} />
          ))
          break
        default:
          return
      }
    }
  }, [selectedModal])

  const headerComponent = useFloatingNavBar ? (
    <FloatingHeader
      className={cx([Styles.header, headerClassName])}
      componentAtTheRight={headerComponentAtTheRight}
      useDarkNavBarLinks={useDarkNavBarLinks}
      currentPageIndex={currentPageIndex}
    />
  ) : (
    <Header
      className={cx([Styles.header, headerClassName])}
      style={headerStyle}
      onResize={onHeaderResize}
      componentAtTheRight={headerComponentAtTheRight}
      useDarkNavBarLinks={useDarkNavBarLinks}
      currentPageIndex={currentPageIndex}
    />
  )

  return (
    <div
      className={cx([
        Styles.wrapper,
        className,
        useFloatingNavBar ? Styles.padFloatingNav : '',
      ])}
    >
      {headerComponent}
      {children}
      <MobileFooter
        currentPageIndex={currentPageIndex}
        componentAtTheRight={footerComponentAtTheRight}
      />
    </div>
  )
}

export default PageLayout
