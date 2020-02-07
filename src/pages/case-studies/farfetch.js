import React, { useEffect, useState } from 'react'
import Layout from 'src/components/layout'
import CaseStudiesHeader from 're/CaseStudies/CaseStudiesHeader'
import { useStaticQuery, graphql } from 'gatsby'
import debounce from 'lodash.debounce'

const DEBOUNCE_PERIOD = 50;

const FarfetchCaseStudy = () => {
  const data = useStaticQuery(graphql`
    query {
      headerImg: file(relativePath: { eq: "farfetch-header.jpg" }) {
        childImageSharp {
          fluid(maxWidth: 1200, maxHeight: 820) {
            ...GatsbyImageSharpFluid
          }
        }
      }
    }
  `)

  const [useDarkNavBarLinks, setUseDarkNavBarLinks] = useState((window.innerWidth || document.documentElement.clientWidth) > 1024);

  const changeNavWhenOnDesktop = debounce(
    () => {
      const windowWidth =
        window.innerWidth || document.documentElement.clientWidth

      // TODO: Interpolate with variable from Theme
      if (windowWidth >= 1024 && !useDarkNavBarLinks) {
        setUseDarkNavBarLinks(true)
      } else if (windowWidth < 1024 && useDarkNavBarLinks) {
        setUseDarkNavBarLinks(false)
      }
    },
    DEBOUNCE_PERIOD,
    {
      leading: true,
      trailing: false,
    }
  )

  useEffect(() => {
    window.addEventListener('resize', changeNavWhenOnDesktop)
    return () => window.removeEventListener('mouseup', changeNavWhenOnDesktop)
  })

  return (
    <Layout useDarkNavBarLinks={useDarkNavBarLinks}>
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
