import createMailgunClient from 'mailgun-js'
import dotenv from 'dotenv'

// Gatsby logic to populate environment variables.
dotenv.config({
  path: `.env.${process.env.NODE_ENV}`,
})

// eslint-disable-next-line max-len
const EMAIL_REGEX = /^(([^<>()\\[\]\\.,;:\s@"]+(\.[^<>()\\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/

const mailgunClient = createMailgunClient({
  apiKey: process.env.MAILGUN_API_KEY,
  domain: process.env.MAILGUN_DOMAIN,
})

// Response headers.
const headers = {
  'Access-Control-Allow-Origin': '*',
  'Access-Control-Allow-Headers': 'Content-Type',
}

export async function handler(event, context, callback) {
  try {
    const { name, email, subject, message } = JSON.parse(event.body)

    if (
      event.httpMethod === 'POST' &&
      name.length > 0 &&
      EMAIL_REGEX.test(email) &&
      subject.length > 0 &&
      message.length > 0
    ) {
      const mailOptions = {
        from: `${name} <${email}>`,
        to: process.env.CONTACT_EMAIL_ADDRESS,
        replyTo: email,
        subject: `${subject}`,
        text: `${message}`,
      }
      await mailgunClient.messages().send(mailOptions)

      return {
        headers,
        statusCode: 200,
        body: JSON.stringify({
          message: 'Message sent successfully',
        }),
      }
    } else {
      throw new Error('Invalid params')
    }
  } catch (error) {
    return {
      headers,
      statusCode: 400,
      body: JSON.stringify({
        error: error.name,
        message: error.message,
      }),
    }
  }
}
