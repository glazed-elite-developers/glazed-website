export const compose =
  (...functions: any) =>
  (args: any) =>
    functions.reduceRight((arg: any, fn: any) => fn(arg), args)

export function identity<Value>(value: Value): Value {
  return value
}

export function compact<Result>(value: Result): Result {
  return JSON.parse(JSON.stringify(value))
}

/**
 * Picks the given properties from the given object.
 * @param obj
 * @param props
 * @returns Object with the picked properties.
 */
export function pick<Type>(
  obj: Type,
  properties: Array<keyof Type>
): Partial<Type> {
  return Object.assign({}, ...properties.map((prop) => ({ [prop]: obj[prop] })))
}
