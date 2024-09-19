import React, {
  ChangeEvent,
  ChangeEventHandler,
  FocusEvent,
  ReactNode,
  useCallback,
} from 'react'
import InputWrapper from './InputWrapper'
import * as CommonInputStyles from './CommonInputStyles'

interface TextAreaProps {
  className?: string
  labelWrapperClassName?: string
  labelClassName?: string
  errorClassName?: string
  name?: string
  label?: ReactNode
  placeholder?: string
  disabled?: boolean
  error?: ReactNode
  value?: string
  onChange?: (
    nextValue: string,
    event: ChangeEvent<HTMLTextAreaElement>
  ) => void
  onFocus?: (event: FocusEvent<HTMLTextAreaElement>) => void
  onBlur?: (event: FocusEvent<HTMLTextAreaElement>) => void
}

const TextArea: React.FC<TextAreaProps> = ({
  className,
  labelWrapperClassName,
  labelClassName,
  errorClassName,
  name,
  label,
  placeholder,
  disabled = false,
  error,
  value,
  onChange: baseOnChange,
  onFocus,
  onBlur,
}) => {
  const onChange: ChangeEventHandler<HTMLTextAreaElement> = useCallback(
    (event) => baseOnChange?.(event.target.value, event),
    [baseOnChange]
  )

  return (
    <InputWrapper
      label={label}
      className={className}
      labelWrapperClassName={labelWrapperClassName}
      labelClassName={labelClassName}
      errorClassName={errorClassName}
      error={error}
    >
      <textarea
        className={CommonInputStyles.input}
        disabled={disabled}
        name={name}
        placeholder={placeholder}
        value={value}
        onChange={onChange}
        onFocus={onFocus}
        onBlur={onBlur}
      />
    </InputWrapper>
  )
}

export default TextArea
