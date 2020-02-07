import React from 'react'
import HTMLText, { tags } from 're/shared/HTMLText'
import Layout from 'src/components/layout'

const IndexPage = () => (
  <Layout>
    <HTMLText tag={tags.h1}>This is H1 text</HTMLText>
    <HTMLText tag={tags.h2}>Trusted by the world’s leading brands</HTMLText>
    <HTMLText tag={tags.p}>This is P text</HTMLText>
  </Layout>
)

export default IndexPage
