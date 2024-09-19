import {
  useGetPropsForField,
  identityValidator,
  Errors as BaseErrors,
} from 'react-functional-form'
import {
  Dispatch,
  SetStateAction,
  SyntheticEvent,
  useCallback,
  useMemo,
  useState,
} from 'react'
import { AsyncState } from '../async-state'
import { emailRegex } from '../regexes'

export const Errors = {
  ...BaseErrors,
  InvalidEmail: 'InvalidEmail',
  InvalidTime: 'InvalidTime',
  InvalidLink: 'InvalidLink',
  PasswordTooShort: 'PasswordTooShort',
  PasswordsMismatch: 'PasswordsMismatch',
  EmailsMismatch: 'EmailsMismatch',
  MaxLengthExceeded: 'MaxLengthExceeded',
}

export type FormValidationError = { code: keyof typeof Errors | string }

type UseFormSubmissionOptions = {
  onChange?: any
  clearSuccessOnChange?: boolean
  stateHook?: [
    AsyncState<any, any>,
    Dispatch<SetStateAction<AsyncState<any, any>>>
  ]
}

export const useFormSubmission = (
  submit: (values: any, ...args: any) => void,
  {
    onChange: baseOnChange,
    clearSuccessOnChange = false,
    stateHook = useState<AsyncState<any, any>>({
      status: 'pristine',
    }),
  }: UseFormSubmissionOptions = {}
) => {
  const [submissionState, setSubmissionState] = stateHook
  const clearSubmissionState = useCallback(
    () => setSubmissionState({ status: 'pristine' }),
    [setSubmissionState]
  )
  const onSubmit = useCallback(
    async (values: unknown, ...args: Array<unknown>) => {
      try {
        setSubmissionState({ status: 'pending' })
        const result = await submit(values, ...args)
        setSubmissionState({ status: 'success', data: result })
      } catch (error) {
        setSubmissionState({ status: 'error', error })
      }
    },
    [submit, setSubmissionState]
  )
  const shouldClearSubmissionState =
    submissionState.status === 'error' ||
    (clearSuccessOnChange && submissionState.status === 'success')
  const onChange = useMemo(
    () =>
      shouldClearSubmissionState
        ? (...args: any) => {
            clearSubmissionState()
            baseOnChange?.(...args)
          }
        : baseOnChange,
    [shouldClearSubmissionState]
  )

  return { submissionState, onChange, onSubmit }
}

export const usePreventDefault = (onSubmit?: (event: SyntheticEvent) => void) =>
  useCallback(
    (event: SyntheticEvent) => {
      event.preventDefault()
      onSubmit?.(event)
    },
    [onSubmit]
  )

export const useGetPropsForFieldWithFilled = (
  props: any,
  mapError: any = ({ code }: { code: string }) => code
) => {
  const mapErrorByCode = useCallback(
    (code: string) => (code ? mapError({ code }) : null),
    [mapError]
  )
  const getPropsForField = useGetPropsForField(props, mapErrorByCode)
  return useCallback(
    (name: string) => {
      const propsForField = getPropsForField(name)
      return {
        ...propsForField,
        filled: props.touched[name] && !propsForField.error,
      }
    },
    [getPropsForField, props.touched]
  )
}

/**
 * Creates an error mapper function that with the default error messages for a list of
 * known errors.
 * @returns Error mapper function.
 */
export function createErrorMapper(
  messages: {
    [code: string]: string
  } = {}
) {
  return (error?: { code?: string; message?: string }): string | undefined => {
    return error && error.code
      ? messages[error?.code] ?? error?.message ?? messages[Errors.Unexpected]
      : undefined
  }
}

export const createOptionalRegexValidator =
  (regex: any, error: any = Errors.FailedRegex) =>
  (result: any, value: any) =>
    value && !regex.test(value) ? [false, error] : identityValidator(result)

export const emailValidator = createOptionalRegexValidator(
  emailRegex,
  Errors.InvalidEmail
)

export const createEmailMatchValidator =
  (emailFieldName: string = 'email') =>
  (result: any, value: any, field: any, { values }: any) =>
    value !== values[emailFieldName]
      ? [false, Errors.EmailsMismatch]
      : identityValidator(result)

export const createMaxLengthValidator =
  (maximumCharLength: number, error = Errors.MaxLengthExceeded) =>
  (result: any, value: any = '') =>
    value.length > maximumCharLength
      ? [false, error]
      : identityValidator(result)
