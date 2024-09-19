import React, { FC, ReactNode, useCallback, useMemo } from 'react'
import { cx, css } from '@emotion/css'
import { Colors, Fonts } from '@styles/Theme'
import {
  createField,
  createForm,
  createRegexValidator,
  requiredValidator,
  useController,
} from 'react-functional-form'
import { emailRegex } from '@helpers/regexes'
import Input from '@components/shared/inputs/Input'
import Button from '@components/shared/Button'
import {
  createErrorMapper,
  Errors,
  useGetPropsForFieldWithFilled,
  usePreventDefault,
} from '@helpers/form'

const Styles = {
  container: css`
    display: flex;
    flex-direction: column;
  `,
  title: css`
    color: #ffffff;
    font-size: 1.125rem;
    margin-bottom: 2rem;
  `,
  subtitle: css`
    color: #feffef;
    font-size: 0.75rem;
    opacity: 0.5;
    margin-bottom: 1rem;
  `,
  anchor: css`
    color: #2560f2;
  `,
  fields: css`
    display: flex;
    flex-direction: column;
  `,
  fieldsContainer: css`
    display: flex;
    flex-direction: column;
  `,
  fieldInnerLabel: css`
    color: ${Colors.black};
  `,
  field: css`
    padding: 0.625rem 0;
  `,
  button: css`
    margin-top: 1.25rem;
    width: 10.625rem;
  `,
  error: css`
    font-size: 0.6875rem;
    font-family: ${Fonts.heading};
    color: ${Colors.orange};
    opacity: 0;
    padding-top: 0.625rem;
    height: 1.5625rem;
    visibility: hidden;
    transition: visibility 0s 500ms, opacity 500ms;
  `,
  errorVisible: css`
    opacity: 1;
    visibility: visible;
    transition: opacity 100ms;
  `,
}

export function FieldLabel({ children }: { children: ReactNode }) {
  return (
    <>
      {'<input "'}
      <span className={Styles.fieldInnerLabel}>{children}</span>
      {'"'}
    </>
  )
}

export type ContactFormFields = {
  [fieldName: string]: {
    schema: {
      validators: ((result: unknown, value: unknown) => (string | boolean)[])[]
    }
    label: React.JSX.Element
    placeholder: string
  }
}

export const DefaultFields: ContactFormFields = {
  name: {
    schema: {
      validators: [requiredValidator],
    },
    label: <FieldLabel>your name</FieldLabel>,
    placeholder: 'Name>',
  },
  email: {
    schema: {
      validators: [createRegexValidator(emailRegex), requiredValidator],
    },
    label: <FieldLabel>your email</FieldLabel>,
    placeholder: 'Email',
  },
  message: {
    schema: {
      validators: [requiredValidator],
    },
    label: <FieldLabel>your thoughts</FieldLabel>,
    placeholder: 'Subject',
  },
}

const errorMessages: any = {
  [Errors.Required]: 'required field',
  [Errors.FailedRegex]: 'invalid email',
}

interface ContactFormProps {
  className?: string
  onSubmit?: (event: React.FormEvent<HTMLFormElement>) => void
  onChange?: (event: React.ChangeEvent<HTMLInputElement>) => void
  submissionStatus?: 'Pristine' | 'Pending' | 'Success' | 'Failed'
  fields?: ContactFormFields
}

const ContactForm: FC<ContactFormProps> = ({
  className,
  onSubmit,
  onChange,
  submissionStatus,
  fields = DefaultFields,
}) => {
  const schema = useMemo(
    () =>
      createForm(
        Object.entries(fields).map(([fieldName, fieldData]) => [
          fieldName,
          createField(fieldData.schema.validators),
        ])
      ),
    [fields]
  )
  const controlProps = useController({ schema, onChange, onSubmit })
  const mapError = useCallback(createErrorMapper(errorMessages), [])
  const getPropsForField = useGetPropsForFieldWithFilled(controlProps, mapError)

  return (
    <form
      noValidate
      onSubmit={usePreventDefault(controlProps.onSubmit)}
      className={cx(Styles.container, className)}
    >
      <div className={Styles.fieldsContainer}>
        <div className={Styles.fields}>
          {Object.keys(fields).map((fieldKey) => (
            <Input
              key={fieldKey}
              className={Styles.field}
              {...getPropsForField(fieldKey)}
              label={fields[fieldKey as keyof typeof fields]?.label}
              placeholder={fields[fieldKey as keyof typeof fields]?.placeholder}
            />
          ))}
        </div>
      </div>
      <Button
        type="Primary"
        children="> send"
        type_="submit"
        isDisabled={
          submissionStatus === 'Pending' || !controlProps.validationResult[0]
        }
        className={Styles.button}
      />
      {submissionStatus === 'Failed' ? (
        <div className={cx(Styles.error, Styles.errorVisible)}>
          An unexpected error occurred
        </div>
      ) : (
        <div className={Styles.error} />
      )}
    </form>
  )
}

export default ContactForm
