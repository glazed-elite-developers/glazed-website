import React, {
  ChangeEvent,
  ChangeEventHandler,
  FC,
  FocusEventHandler,
  ReactNode,
  useCallback,
} from 'react'
import InputWrapper from './InputWrapper'
import * as CommonInputStyles from './CommonInputStyles'

interface InputProps {
  className?: string
  labelWrapperClassName?: string
  labelClassName?: string
  errorClassName?: string
  name?: string
  label?: ReactNode
  placeholder?: string
  disabled?: boolean
  error?: string
  value?: string
  onChange?: (nextValue: string, event: ChangeEvent<HTMLInputElement>) => void
  onFocus?: FocusEventHandler<HTMLInputElement>
  onBlur?: FocusEventHandler<HTMLInputElement>
}

const Input: FC<InputProps> = ({
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
  const onChange: ChangeEventHandler<HTMLInputElement> = useCallback(
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
      <input
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

export default Input
