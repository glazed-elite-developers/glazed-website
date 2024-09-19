import { useState, useCallback, useMemo } from 'react'

const recursivelyPopulateDirtyFields = (
  dirty = {} as any,
  eventMetadata: any
): any => {
  const { fieldName, nestedFormEvent } = eventMetadata
  const nextDirtyValue =
    nestedFormEvent !== undefined
      ? recursivelyPopulateDirtyFields(dirty[fieldName], nestedFormEvent)
      : true

  return {
    ...dirty,
    [eventMetadata.fieldName]: nextDirtyValue,
  }
}

const useDirtyValues = (stateHook: any = useState({}), baseOnChange?: any) => {
  const [dirtyValues, setDirtyValues] = stateHook
  const onChange = useCallback(
    (eventMetadata, ...args) => {
      setDirtyValues((dirty: any) =>
        recursivelyPopulateDirtyFields(dirty, eventMetadata)
      )
      baseOnChange?.(eventMetadata, ...args)
    },
    [baseOnChange, setDirtyValues]
  )
  const isDirty = useMemo(
    () => Object.keys(dirtyValues).length > 0,
    [dirtyValues]
  )

  return {
    isDirty,
    dirtyValues,
    setDirtyValues,
    onChange,
  }
}

export default useDirtyValues
