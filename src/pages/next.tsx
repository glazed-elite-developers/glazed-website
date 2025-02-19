import React, { useState, useCallback } from 'react'
import { css } from '@emotion/css'
import { Colors, Breakpoints } from '@styles/Theme'
import Layout from '@components/shared/Layout'
import PageLayout from '@components/shared/PageLayout'
import Heading, { HeadingLevel } from '@components/shared/Heading'
import ContactForm, {
  ContactFormFields,
  DefaultFields as DefaultContactFormFields,
  FieldLabel,
} from '@components/shared/ContactForm'

const styles = {
  fillFormMessage: css`
    display: inline;
    padding-right: 0.3125rem;
    padding-bottom: 1rem;
  `,
  sendEmailParagraph: css`
    display: inline;
    color: ${Colors.grey};
    margin-bottom: 2rem;
  `,
  link: css`
    color: ${Colors.glazedBlueDarkish};
  `,
  content: css`
    position: relative;
    padding: 4.1875rem 1.25rem 8.1875rem 1.25rem;
    display: flex;
    flex-direction: column;
    flex: 1 0 auto;
    background-color: ${Colors.almostAlmostWhite};

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      justify-content: flex-start;
      padding: 12.25rem 2.5rem 6.25rem 4.75rem;
    }
  `,
  heading: css`
    position: relative;
    padding: 1.875rem 0 5.625rem 0.9375rem;
    font-size: 4.125rem;
    color: ${Colors.glazedBabyBlueText};

    &::before {
      content: '';
      display: block;
      position: absolute;
      top: 0;
      left: 0;
      width: 130px;
      height: 130px;
      border: 1px solid ${Colors.glazedBabyBlueDarker};
      opacity: 0.8;

      @media (min-width: ${Breakpoints.tabletLandscape}) {
        width: 258px;
        height: 258px;
      }
    }

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 5.625rem 0 6.875rem 0.9375rem;
      width: auto;
      font-size: 9rem;
      &::before {
        top: -30px;
      }
    }
  `,
  pageContent: css`
    @media (min-width: ${Breakpoints.tabletLandscape}) {
      max-width: 50rem;
    }
  `,
}

type SubmissionStatus = 'Pristine' | 'Pending' | 'Success' | 'Failed'

const emailSubject = 'Glazed Application'

const FormFields: ContactFormFields = {
  ...DefaultContactFormFields,
  message: {
    ...DefaultContactFormFields.message,
    label: <FieldLabel>your project / thesis's description</FieldLabel>,
  },
}

const Next: React.FC = () => {
  const [submissionStatus, setSubmissionStatus] =
    useState<SubmissionStatus>('Pristine')

  const onSubmit = useCallback(
    (values: any) => {
      setSubmissionStatus('Pending')
      const payload: Record<string, string> = {
        ...values,
        subject: emailSubject,
      }

      fetch('/.netlify/functions/sendEmail', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(payload),
      })
        .then((response) => {
          if (response.status < 200 || response.status >= 300) {
            throw new Error(response.statusText)
          }
          return response.json()
        })
        .then(() => setSubmissionStatus('Success'))
        .catch(() => setSubmissionStatus('Failed'))
    },
    [setSubmissionStatus]
  )

  const onChange = useCallback(() => {
    if (typeof submissionStatus === 'string') {
      setSubmissionStatus('Pristine')
    }
  }, [submissionStatus])

  return (
    <Layout>
      <PageLayout className={styles.content} useDarkNavBarLinks>
        <Heading level={HeadingLevel.H1} className={styles.heading}>
          Next
        </Heading>
        <div className={styles.pageContent}>
          <p className={styles.fillFormMessage}>
            At Glazed we're committed to taking software development to next
            level. Many of our developers started by doing an internship or
            developing their thesis at Glazed, and you could be next! We will
            provide the support you need to help your project bloom.
          </p>
          <br />
          <br />
          <p className={styles.fillFormMessage}>
            Send your application by filling the form below, or, if you prefer,
          </p>
          <p className={styles.sendEmailParagraph}>
            <a className={styles.link} href="mailto:info@glazedsolutions.com">
              send us an email
            </a>
          </p>
          <br />
          <br />
          <ContactForm
            onSubmit={onSubmit}
            onChange={onChange}
            submissionStatus={submissionStatus}
            fields={FormFields}
          />
        </div>
      </PageLayout>
    </Layout>
  )
}

export default Next
