import createMailgunClient from 'mailgun-js'
import dotenv from 'dotenv'

// Gatsby logic to populate environment variables.
dotenv.config({
  path: `.env.${process.env.NODE_ENV}`,
})

// Email validation regex
const EMAIL_REGEX =
  /^(([^<>()\\[\]\\.,;:\s@"]+(\.[^<>()\\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/

// Mailgun client initialization
const mailgunClient = createMailgunClient({
  apiKey: process.env.MAILGUN_API_KEY!,
  domain: process.env.MAILGUN_DOMAIN!,
})

// Response headers
const headers = {
  'Access-Control-Allow-Origin': '*',
  'Access-Control-Allow-Headers': 'Content-Type',
}

interface RequestBody {
  name: string
  email: string
  subject: string
  message: string
  techstack: string
  role: string
}

export async function handler(
  event: { body: string; httpMethod: string },
  context: any,
  callback: any
): Promise<{ headers: typeof headers; statusCode: number; body: string }> {
  try {
    console.log(event.body)
    const { name, email, subject, message, techstack, role }: RequestBody =
      JSON.parse(event.body)
    const messageToSend = `Name: ${name}\nShort description: ${message}\nTechstack: ${techstack}\nRole: ${role}`

    if (
      event.httpMethod === 'POST' &&
      name.length > 0 &&
      EMAIL_REGEX.test(email) &&
      subject.length > 0 &&
      message.length > 0
    ) {
      const mailOptions = {
        from: `${name} <${email}>`,
        to: process.env.CONTACT_EMAIL_ADDRESS!,
        replyTo: email,
        subject: `${subject}`,
        text: `${messageToSend}`,
      }

      console.log('Mailgun mailOptions: ', mailOptions)
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
    console.log('failed to send email: ', error)
    const typedError = error as Error
    return {
      headers,
      statusCode: 400,
      body: JSON.stringify({
        error: typedError.name,
        message: typedError.message,
      }),
    }
  }
}
