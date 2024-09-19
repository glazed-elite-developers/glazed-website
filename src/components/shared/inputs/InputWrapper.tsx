import React, { FC, ReactNode } from 'react'
import { cx } from '@emotion/css'
import * as CommonInputStyles from './CommonInputStyles'

interface InputWrapperProps {
  className?: string
  labelWrapperClassName?: string
  labelClassName?: string
  errorClassName?: string
  label?: ReactNode
  error?: ReactNode
  children?: ReactNode
}

const InputWrapper: FC<InputWrapperProps> = ({
  className,
  labelWrapperClassName,
  labelClassName,
  errorClassName,
  label,
  error,
  children,
}) => {
  const combinedClassName = cx([CommonInputStyles.wrapper, className])
  const combinedLabelWrapperClassName = cx([
    CommonInputStyles.labelWrapper,
    labelWrapperClassName,
  ])
  const combinedLabelClassName = cx([CommonInputStyles.label, labelClassName])
  const combinedErrorClassName = cx([
    CommonInputStyles.error,
    errorClassName,
    Boolean(error) && CommonInputStyles.errorVisible,
  ])

  return (
    <label className={combinedClassName}>
      <div className={combinedLabelWrapperClassName}>
        <div className={combinedLabelClassName}>{label}</div>
        <div className={combinedErrorClassName}>{error && <p>{error}</p>}</div>
      </div>
      {children}
    </label>
  )
}

export default InputWrapper
