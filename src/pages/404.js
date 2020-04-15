import React from 'react'
import Layout from 're/layout'
import PageLayout from 're/PageLayout'

const NotFoundPage = () => (
  <Layout>
    <PageLayout useDarkNavBarLinks>
      <h1>NOT FOUND</h1>
      <p>You just hit a route that doesn&#39;t exist... the sadness.</p>
    </PageLayout>
  </Layout>
)

export default NotFoundPage
