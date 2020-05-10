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
  type element('a);
  type map('a) = Belt.Map.t(string, element('a), FieldNameCompare.identity);
};

module InternalMap = (Type: InternalMap) => {
  let make: unit => Type.map('a) = () => Belt.Map.make(~id=(module FieldNameCompare));
  let fromArray: array((string, Type.element('a))) => Type.map('a) =
    Belt.Map.fromArray(~id=(module FieldNameCompare));
  let toArray: Type.map('a) => array((string, Type.element('a))) = Belt.Map.toArray;
  let reduce:
    (Type.map('a), 'reduceResult, ('reduceResult, string, Type.element('a)) => 'reduceResult) =>
    'reduceResult = Belt.Map.reduce;
  let map: (Type.map('a), (string, Type.element('a)) => 'mappedElement) => 'mapResult = Belt.Map.mapWithKey;
  let set: (Type.map('a), string, Type.element('a)) => Type.map('a) = Belt.Map.set;
  let get: (Type.map('a), string) => option(Type.element('a)) = Belt.Map.get;
  let has: (Type.map('a), string) => bool = Belt.Map.has;
};

module Schema =
  InternalMap({
    type element('fieldSchema) = 'fieldSchema;
    type map('fieldSchema) = schema(element('fieldSchema));
  });

module Values =
  InternalMap({
    type element('value) = 'value;
    type map('value) = values(element('value));
  });

module Errors =
  InternalMap({
    type element('error) = 'error;
    type map('error) = errors(element('error));
  });

module Touched =
  InternalMap({
    type element('a) = bool;
    type map('a) = touched;
  });

module Visited =
  InternalMap({
    type element('a) = bool;
    type map('a) = visited;
  });

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
