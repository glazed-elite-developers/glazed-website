module FieldNameCompare =
  Belt.Id.MakeComparable({
    type t = string;
    let cmp = Pervasives.compare;
  });

type values('value) = Belt.Map.t(string, 'value, FieldNameCompare.identity);

type errors('error) = Belt.Map.t(string, 'error, FieldNameCompare.identity);

type touched = Belt.Map.t(string, bool, FieldNameCompare.identity);

type visited = Belt.Map.t(string, bool, FieldNameCompare.identity);

type error('error) =
  | MissingRequired
  | FailedRegex
  | Custom('error);

type formValidationResult('error) =
  | FormValid
  | FormInvalid(errors('error));

type validationResult('error) =
  | Valid
  | Invalid('error);

type validator('value, 'error) =
  (validationResult('error), 'value, values('value)) => validationResult('error);

type fieldSchema('value, 'error) = {validators: list(validator('value, 'error))};

type schema('fieldSchema) = Belt.Map.t(string, 'fieldSchema, FieldNameCompare.identity);

module type InternalMap = {
  type map('element) = Belt.Map.t(string, 'element, FieldNameCompare.identity);
};

module InternalMap = (Type: InternalMap) => {
  let make: unit => Type.map('element) = () => Belt.Map.make(~id=(module FieldNameCompare));
  let fromArray: array((string, 'element)) => Type.map('element) =
    Belt.Map.fromArray(~id=(module FieldNameCompare));
  let toArray: Type.map('element) => array((string, 'element)) = Belt.Map.toArray;
  let reduce:
    (Type.map('element), 'reduceResult, ('reduceResult, string, 'element) => 'reduceResult) =>
    'reduceResult = Belt.Map.reduce;
  let map: (Type.map('element), (string, 'element) => 'mappedElement) => Type.map('mappedElement) = Belt.Map.mapWithKey;
  let set: (Type.map('element), string, 'element) => Type.map('element) = Belt.Map.set;
  let get: (Type.map('element), string) => option('element) = Belt.Map.get;
};

module Schema = {
  include InternalMap({
    type map('fieldSchema) = schema('fieldSchema);
  });
};

module Values = {
  include InternalMap({
    type map('value) = values('value);
  });
};

module Errors = {
  include InternalMap({
    type map('error) = errors('error);
  });
};

// @TODO: Figure out wat to reuse InternalMap here as well? Should we just expose the full Map API?
module Touched = {
  let make: unit => touched = () => Belt.Map.make(~id=(module FieldNameCompare));
  let fromArray: array((string, bool)) => touched =
    Belt.Map.fromArray(~id=(module FieldNameCompare));
  let reduce: touched => 'reduceResult = Belt.Map.reduce;
  let set: (touched, string, bool) => touched = Belt.Map.set;
  let has: (touched, string) => bool = Belt.Map.has;
};

// @TODO: Figure out wat to reuse InternalMap here as well? Should we just expose the full Map API?
module Visited = {
  let make: unit => visited = () => Belt.Map.make(~id=(module FieldNameCompare));
  let fromArray: array((string, bool)) => visited =
    Belt.Map.fromArray(~id=(module FieldNameCompare));
  let reduce: visited => 'reduceResult = Belt.Map.reduce;
  let set: (visited, string, bool) => visited = Belt.Map.set;
  let has: (visited, string) => bool = Belt.Map.has;
};

module Validators = {
  let identity: validator('value, 'error) = (_result, _value, _values) => Valid;

  // let required: validator('value, 'error) =
  //   (result, value, values) =>
  //     value === None
  //       ? Invalid(MissingRequired) : identity(result, value, values);
  let required: validator('value, 'error) =
    (result, value, values) =>
      value === "" ? Invalid(MissingRequired) : identity(result, value, values);

  let createRegexValidator: Js.Re.t => validator(string, 'error) =
    (regex, result, value, values) =>
      if (!Js.Re.test_(regex, value)) {
        Invalid(FailedRegex);
      } else {
        identity(result, value, values);
      };
};

/**
 * Validates a field value.
 *
 * @param {Object} field - Field schema.
 * @param {any} value - Field value.
 * @returns {validationResult} Validation result.
 */
let validateField = (field: fieldSchema('value, 'error), value: 'value, values: values('value)) =>
  Belt.List.reduce(field.validators, Valid, (result, validator) =>
    validator(result, value, values)
  );

/**
 * Validates a fields array.
 *
 * @example Example structute:
 * [{ name: 'firstName', placeholder: 'first-name' }, { ... }]
 *
 * @param {Schema} schema - Form schema.
 * @param {Map} values - Values to validate.
 * @param {Set} touched - Touched fields.
 * @returns {validationResult} Validation result.
 */
let validate =
    (
      schema: schema(fieldSchema('value, error('error'))),
      values: values('value),
      touched: touched,
    )
    : formValidationResult(error('error)) => {
  Schema.reduce(
    schema,
    FormValid,
    (formValidationResult, fieldName, fieldSchema) => {
      let wasFieldTouched = Belt.Map.has(touched, fieldName);

      // We only validate touched fields.
      let fieldValidationResult =
        wasFieldTouched
          ? switch (Belt.Map.get(values, fieldName)) {
            | None => Valid
            | Some(value) => validateField(fieldSchema, value, values)
            }
          : Valid;

      switch (formValidationResult) {
      | FormValid =>
        switch (fieldValidationResult) {
        | Valid => FormValid
        | Invalid(error) => FormInvalid(Errors.fromArray([|(fieldName, error)|]))
        }
      | FormInvalid(formErrors) =>
        switch (fieldValidationResult) {
        | Valid => formValidationResult
        | Invalid(error) => FormInvalid(Errors.set(formErrors, fieldName, error))
        }
      };
    },
  );
};
