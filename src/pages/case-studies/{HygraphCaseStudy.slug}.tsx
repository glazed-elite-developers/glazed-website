import React, { useMemo } from 'react'
import { graphql } from 'gatsby'
import CaseStudyPageTemplate, {
  CaseStudyPageContent,
} from '@components/pages/case-studies/building-blocks/CaseStudyPageTemplate'

import LogoGlazedSmallSvg from 'static/images/logo-glazed-small.svg'
import { getImage, ImageDataLike } from 'gatsby-plugin-image'
import { CaseStudy } from '@components/pages/homepage/case-studies-slide/CaseStudySquare'

interface CaseStudyPageProps {
  data: {
    allHygraphCaseStudy: {
      nodes: Array<Omit<CaseStudy, 'heroImage'> & { heroImage: ImageDataLike }>
    }
    hygraphCaseStudy: {
      id: string
      name: string
      slug: string
      heroImage: ImageDataLike
      category: string
      shortDescription: string
      technologies?: Array<string>
      brief: string
      year: string
      content: Array<
        | {
            type: 'Hygraph_BigImageSection'
            image: ImageDataLike
          }
        | {
            type: 'Hygraph_BigVideoSection'
            embeddedVideoUrl: string
          }
        | {
            type: 'Hygraph_HighlightedTextSection'
            text: string
          }
        | {
            type: 'Hygraph_QuoteCardSection'
            quote: string
            quoteAuthor: {
              name: string
              title: string
              photo: ImageDataLike
            }
          }
        | {
            type: 'Hygraph_TextAndImageSection'
            text: string
            image: ImageDataLike
          }
        | {
            type: 'Hygraph_TextAndVideoSection'
            text: string
            embeddedVideoUrl: string
          }
      >
    }
  }
}

export default function CaseStudyPage(props: CaseStudyPageProps) {
  const caseStudy = props.data.hygraphCaseStudy
  const caseStudies = props.data.allHygraphCaseStudy.nodes
  const nextCaseStudyIndex =
    (caseStudies.findIndex((entry) => entry.slug === caseStudy.slug) + 1) %
    caseStudies.length
  const nextCaseStudy = caseStudies[nextCaseStudyIndex]
  const content: CaseStudyPageContent = useMemo(
    () => ({
      hero: {
        title: caseStudy.name,
        area: caseStudy.category,
        text: caseStudy.shortDescription,
        image: getImage(caseStudy.heroImage),
      },
      brief: {
        brief: caseStudy.brief,
        techs:
          caseStudy.technologies?.map((technology) => ({
            name: technology,
            icon: LogoGlazedSmallSvg,
          })) ?? [],
        year: caseStudy.year,
      },
      content: caseStudy.content
        .map<CaseStudyPageContent['content']['0']>((section) => {
          switch (section.type) {
            case 'Hygraph_BigImageSection':
              return { type: 'BigImage', image: getImage(section.image) }
            case 'Hygraph_BigVideoSection':
              return { type: 'BigVideo', url: section.embeddedVideoUrl }
            case 'Hygraph_HighlightedTextSection':
              return { type: 'HighlightedText', text: section.text }
            case 'Hygraph_TextAndImageSection':
              return {
                type: 'TextAndImage',
                text: section.text,
                image: getImage(section.image),
              }
            case 'Hygraph_TextAndVideoSection':
              return {
                type: 'TextAndVideo',
                text: section.text,
                videoSrc: section.embeddedVideoUrl,
              }
            case 'Hygraph_QuoteCardSection':
              return {
                type: 'QuoteCard',
                quote: section.quote,
                author: {
                  name: section.quoteAuthor.name,
                  title: section.quoteAuthor.title,
                  avatarImage: getImage(section.quoteAuthor.photo),
                },
              }
          }
        })
        .filter(Boolean),
      nextCase: {
        title: nextCaseStudy.name,
        area: nextCaseStudy.category,
        link: `/case-studies/${nextCaseStudy.slug}`,
        image: getImage(nextCaseStudy.heroImage),
      },
    }),
    [caseStudy]
  )
  return (
    <CaseStudyPageTemplate
      content={content}
      pageTitle={`Glazed • ${caseStudy.name}`}
      pageDescription={caseStudy.shortDescription}
    />
  )
}

export const query = graphql`
  query ($slug: String) {
    allHygraphCaseStudy {
      nodes {
        name
        slug
        category
        heroImage {
          gatsbyImageData(placeholder: NONE, layout: FULL_WIDTH)
        }
      }
    }
    hygraphCaseStudy(slug: { eq: $slug }) {
      id
      name
      slug
      heroImage {
        gatsbyImageData(placeholder: NONE, layout: FULL_WIDTH)
      }
      category
      shortDescription
      technologies
      brief
      year
      content {
        type: __typename
        ... on Hygraph_BigImageSection {
          stage
          id
          image {
            gatsbyImageData(placeholder: NONE, layout: FULL_WIDTH)
          }
        }
        ... on Hygraph_BigVideoSection {
          stage
          id
          embeddedVideoUrl
        }
        ... on Hygraph_HighlightedTextSection {
          stage
          id
          text
        }
        ... on Hygraph_QuoteCardSection {
          stage
          id
          quote
          quoteAuthor {
            ... on Hygraph_QuoteAuthor {
              name
              title
              photo {
                gatsbyImageData(placeholder: NONE, layout: FULL_WIDTH)
              }
            }
          }
        }
        ... on Hygraph_TextAndImageSection {
          stage
          id
          text
          image {
            gatsbyImageData(placeholder: NONE, layout: FULL_WIDTH)
          }
        }
        ... on Hygraph_TextAndVideoSection {
          stage
          id
          text
          embeddedVideoUrl
        }
      }
    }
  }
`
