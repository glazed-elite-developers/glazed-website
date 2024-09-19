import { ReactNode } from 'react'

export type Pristine = { status: 'pristine' }
export type Pending<OperationResult> = {
  status: 'pending'
  data?: OperationResult
}
export type Success<Result> = { status: 'success'; data: Result }
export type Error<OperationError> = { status: 'error'; error: OperationError }

export type AsyncState<OperationResult = any, OperationError = any> =
  | Pristine
  | Pending<OperationResult>
  | Success<OperationResult>
  | Error<OperationError>

export const renderError = (
  state: AsyncState<any, any>,
  mapError = (error: any) => error
) => (state.status === 'error' ? mapError(state.error) : undefined)

type RenderOptions<OperationResult, OperationError> = {
  onPristine?: () => ReactNode
  onPending?: (data?: OperationResult) => ReactNode
  onSuccess?: (data: OperationResult) => ReactNode
  onData?: (data: OperationResult) => ReactNode
  onError?: (error: OperationError) => ReactNode
}

export const renderAsyncState = <OperationResult, OperationError>(
  state: AsyncState<OperationResult, OperationError>,
  {
    onPristine = () => null,
    onPending = () => null,
    onSuccess = () => null,
    onError = () => null,
    onData = () => null,
  }: RenderOptions<OperationResult, OperationError>
) => {
  if (state.status === 'pristine') {
    return onPristine()
  } else if (state.status === 'pending' && state.data !== undefined) {
    return onData?.(state.data) ?? onPending(state.data)
  } else if (state.status === 'success') {
    return onData?.(state.data) ?? onSuccess(state.data)
  } else if (state.status === 'error') {
    return onError(state.error)
  } else {
    return null
  }
}

export const getData = <OperationResult, OperationError>(
  state: AsyncState<OperationResult, OperationError>
): OperationResult | undefined =>
  state.status === 'success'
    ? state.data
    : state.status === 'pending'
    ? state.data
    : undefined

export function compose<
  OperationAResult,
  OperationAError,
  OperationBResult,
  OperationBError
>(
  asyncStateA: AsyncState<OperationAResult, OperationAError>,
  asyncStateB: AsyncState<OperationBResult, OperationBError>
): AsyncState<
  [OperationAResult, OperationBResult],
  OperationAError | OperationBError
> {
  if (asyncStateA.status === 'success' && asyncStateB.status === 'success') {
    return { status: 'success', data: [asyncStateA.data, asyncStateB.data] }
  } else {
    const asyncStateAData = getData(asyncStateA)
    const asyncStateBData = getData(asyncStateB)

    if (asyncStateAData !== undefined && asyncStateBData !== undefined) {
      return { status: 'pending', data: [asyncStateAData, asyncStateBData] }
    } else if (
      asyncStateA.status === 'error' ||
      asyncStateB.status === 'error'
    ) {
      const error =
        asyncStateA.status === 'error'
          ? asyncStateA.error
          : (asyncStateB as Error<OperationBError>).error
      return { status: 'error', error }
    } else if (
      asyncStateA.status === 'pending' ||
      asyncStateB.status === 'pending'
    ) {
      return { status: 'pending' }
    } else {
      return { status: 'pristine' }
    }
  }
}
