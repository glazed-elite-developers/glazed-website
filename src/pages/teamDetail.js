import React from 'react'
import TeamDetail from 're/TeamDetail'
import Layout from 're/Layout'
import PageLayout from 're/PageLayout'
import { useStaticQuery, graphql } from 'gatsby'

const developer = {
  name: 'Diogo Nunes',
  description:
    // eslint-disable-next-line max-len
    'Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi u',
  headline: 'has a vast experience and deep knowledge on all things on iOS',
  photo: 'images/team/CarlosMatias.png',
}

const IndexPage = () => {
  const data = useStaticQuery(graphql`
    query {
      developerImage: file(relativePath: { eq: "team/CarlosMatias.png" }) {
        childImageSharp {
          fluid(maxWidth: 1200) {
            ...GatsbyImageSharpFluid
          }
        }
      }
    }
  `)

  return (
    <Layout>
      <PageLayout useDarkNavBarLinks>
        <TeamDetail developer={developer} image={data.developerImage.childImageSharp.fluid} />
      </PageLayout>
    </Layout>
  )
}

export default IndexPage
