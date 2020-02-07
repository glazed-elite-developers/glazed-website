import React from 'react'
import Layout from 'src/components/layout'
import CaseStudiesHeader from 're/CaseStudies/CaseStudiesHeader'
import { useStaticQuery, graphql } from 'gatsby'

const FarfetchCaseStudy = () => {
  const data = useStaticQuery(graphql`
    query {
      headerImg: file(relativePath: { eq: "farfetch-header.jpg" }) {
        childImageSharp {
          fluid(maxWidth: 1200) {
            ...GatsbyImageSharpFluid
          }
        }
      }
    }
  `)

  return (
    <Layout useDarkNavBarLinks>
      <CaseStudiesHeader
        image={data.headerImg.childImageSharp.fluid}
        title="Farfetch"
        area="Fashion - Ecommerce"
        text="An international fashion website that sells products from 400 independent boutiques around the world."
        techs={['react', 'vue']}
        year="2019"
        brief="Farfetch asked us to create a white label version of the their main e-commerce site for big brands that want to sell on their own website."
      />
    </Layout>
  )
}

export default FarfetchCaseStudy
