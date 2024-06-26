import React, { useState } from 'react'
import HTMLText, { tags } from 're/shared/HTMLText'
import Input from 're/shared/inputs/Input'
import Button, { backgrounds } from 're/shared/Button'
import Layout from 're/Layout'
import PageLayout from 're/PageLayout'
import { Colors } from 're/Theme'

const withBG = color => ({ backgroundColor: `#${color}`, padding: '10px' })
// const blueBG = { backgroundColor: `#${Colors.blueDarker}`};

const tints = {}

const ShowcasePage = () => {
  const [value, setVal] = useState('')

  return (
    <Layout>
      <PageLayout useDarkNavBarLinks>
        <h1>NOT FOUND</h1>
        <p>You just hit a route that doesn&#39;t exist... the sadness.</p>
        <HTMLText tag={tags.h1}>This is H1 text</HTMLText>
        <HTMLText tag={tags.h2}>Trusted by the world’s leading brands</HTMLText>
        <HTMLText tag={tags.p}>This is P text</HTMLText>

        <div style={{ backgroundColor: 'white', padding: '10px' }}>
          <Input label="your name" placeholder="Name" tint={tints.Light} value={value} onChange={setVal} />
        </div>

        <div style={withBG(Colors.blueDarker)}>
          <Input label="your email" placeholder="Email" tint={tints.Dark} value={value} onChange={setVal} />
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

        <div>
          <div style={withBG('fff')}>
            <Button isPrimary>> send</Button>
          </div>

          <div style={withBG('fff')}>
            <Button isSecondary bgColor={backgrounds.BrightBg}>
              > send
            </Button>
            <br />
            <br />
            <Button isSecondary bgColor={backgrounds.BrightBg} isDisabled>
              > send
            </Button>
          </div>

          <div style={withBG(Colors.glazedBlue)}>
            <Button isSecondary bgColor={backgrounds.BlueBg}>
              > send
            </Button>
            <br />
            <br />
            <Button isSecondary bgColor={backgrounds.BlueBg} isDisabled>
              > send
            </Button>
          </div>

          <div style={withBG(Colors.darkGreyDarker)}>
            <Button isSecondary bgColor={backgrounds.ImageBg}>
              > send
            </Button>
            <br />
            <br />
            <Button isSecondary bgColor={backgrounds.ImageBg} isDisabled>
              > send
            </Button>
          </div>

          <div style={withBG('fff')}>
            <Button isTertiary>> send</Button>
          </div>
        </div>
      </PageLayout>
    </Layout>
  )
}

// Uncomment to enable.
// export default ShowcasePage
export default () => null
