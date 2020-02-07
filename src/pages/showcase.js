import React, { useState } from 'react'
import HTMLText, { tags } from 're/shared/HTMLText'
import Input, { tints } from 're/shared/Input'
import Layout from 'src/components/layout'

const IndexPage = () => {
  const [value, setVal] = useState('')

  return (
    <Layout useDarkNavBarLinks>
      <HTMLText tag={tags.h1}>This is H1 text</HTMLText>
      <HTMLText tag={tags.h2}>Trusted by the world’s leading brands</HTMLText>
      <HTMLText tag={tags.p}>This is P text</HTMLText>

      <div style={{ backgroundColor: 'white', padding: '10px' }}>
        <Input
          label="your name"
          placeholder="Name"
          tint={tints.Light}
          value={value}
          onChange={setVal}
        />
      </div>

      <div style={{ backgroundColor: 'rgb(2, 12, 47)', padding: '10px' }}>
        <Input
          label="your email"
          placeholder="Email"
          tint={tints.Dark}
          value={value}
          onChange={setVal}
        />
      </div>

      <div style={{ backgroundColor: 'rgb(2, 12, 47)', padding: '10px' }}>
        <Input
          label="your email"
          placeholder="Email"
          tint={tints.Dark}
          textArea={true}
          value={value}
          onChange={setVal}
        />
      </div>
    </Layout>
  )
}

export default IndexPage
