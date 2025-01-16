import React, { FC, ReactElement, ReactNode } from 'react'
import { css } from '@emotion/css'
import CaseStudyQuoteCard, { Author } from './CaseStudyQuoteCard'
import CaseStudyTextAndImage from './CaseStudyTextAndImage'
import CaseStudyTextAndVideo from './CaseStudyTextAndVideo'
import { Breakpoints, Colors } from '@styles/Theme'
import PageLayout from '@components/shared/PageLayout'
import Layout from '@components/shared/Layout'
import IconTwitterSvg from '@static/images/icon_twitter.svg'
import CaseStudyHeader from './CaseStudyHeader'
import CaseStudyBrief from './CaseStudyBrief'
import CaseStudyBigImage from './CaseStudyBigImage'
import CaseStudyBigVideo from './CaseStudyBigVideo'
import CaseStudyNextCase from './CaseStudyNextCase'
import { SVGProps } from '@components/shared/SVG'
import { GatsbyImageProps } from 'gatsby-plugin-image'
import Heading, { HeadingLevel } from '@components/shared/Heading'

const Styles = {
  pageLayout: css`
    flex: 1 0 auto;
    background-color: ${Colors.whiteTurquoise};
  `,
  pageContent: css`
    position: relative;
    z-index: 0;
    transform: translateZ(0);
  `,
  header: css`
    position: fixed;
    background-color: ${Colors.whiteTurquoise};
    transition: all 200ms ease-out;
    transform: translateY(-100%);
  `,
  headerWithShadow: css`
    box-shadow: 0 7px 15px rgba(0, 0, 0, 0.04);
  `,
  inPageHeading: css`
    text-align: center;
    max-width: 64rem;
    padding: 1.875rem;
    margin: auto;
    color: ${Colors.grey};

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 1.875rem 0 1.875rem;
    }
  `,
}

const techs = [
  {
    name: 'react',
    icon: IconTwitterSvg,
  },
  {
    name: 'angular',
    icon: IconTwitterSvg,
  },
  {
    name: 'ios',
    icon: IconTwitterSvg,
  },
]

type Content =
  | {
      type: 'BigImage'
      image?: GatsbyImageProps['image']
    }
  | {
      type: 'TextAndImage'
      text: string
      image?: GatsbyImageProps['image']
    }
  | {
      type: 'TextAndVideo'
      text: string
      videoSrc: string
    }
  | {
      type: 'QuoteCard'
      author: Author
      quote: string
    }
  | {
      type: 'BigVideo'
      url: string
    }
  | {
      type: 'HighlightedText'
      text: string
    }

export interface CaseStudyPageContent {
  hero: {
    title: string
    area: string
    text: string
    image?: GatsbyImageProps['image']
  }
  brief: {
    techs: {
      name: string
      icon: SVGProps['asset']
    }[]
    year: string
    brief: string
  }
  content: Array<Content>
  nextCase: {
    title: string
    area: string
    link: string
    image?: GatsbyImageProps['image']
  }
}

interface CaseStudyPageTemplateProps {
  content: CaseStudyPageContent
  pageTitle: string
  pageDescription: string
}

const CaseStudyPageTemplate: FC<CaseStudyPageTemplateProps> = ({
  content,
  pageTitle,
  pageDescription,
}) => {
  const heroData = {
    title: content.hero.title,
    area: content.hero.area,
    text: content.hero.text,
    image: content.hero.image,
  }

  const nextCaseData = {
    title: content.nextCase.title,
    area: content.nextCase.area,
    link: content.nextCase.link,
    image: content.nextCase.image,
  }

  return (
    <Layout title={pageTitle} description={pageDescription}>
      <PageLayout
        className={Styles.pageLayout}
        useDarkNavBarLinks={true}
        useFloatingNavBar={true}
        currentPageIndex={1}
      >
        <div className={Styles.pageContent}>
          <CaseStudyHeader {...heroData} />
          <CaseStudyBrief
            techs={content.brief.techs}
            year={content.brief.year}
            brief={content.brief.brief}
          />
          {content.content.map((contentElement, index) => {
            const key = String(index)
            switch (contentElement.type) {
              case 'BigImage':
                return <CaseStudyBigImage key={key} {...contentElement} />
              case 'TextAndImage':
                return <CaseStudyTextAndImage key={key} {...contentElement} />
              case 'QuoteCard':
                return <CaseStudyQuoteCard key={key} {...contentElement} />
              case 'BigVideo':
                return <CaseStudyBigVideo key={key} src={contentElement.url} />
              case 'TextAndVideo':
                return <CaseStudyTextAndVideo key={key} {...contentElement} />
              case 'HighlightedText':
                return (
                  <Heading
                    key={key}
                    level={HeadingLevel.H3}
                    className={Styles.inPageHeading}
                  >
                    {contentElement.text}
                  </Heading>
                )
              default:
                return null
            }
          })}
          <CaseStudyNextCase {...nextCaseData} />
        </div>
      </PageLayout>
    </Layout>
  )
}

export default CaseStudyPageTemplate
