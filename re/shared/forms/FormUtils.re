open FormValidations;

let getAllFieldsTouched = (schema: schema(fieldSchema('value, 'error))) => {
  Schema.reduce(schema, Touched.make(), (result, fieldName, _fieldSchema) => {
    Touched.set(result, fieldName, true)
  });
};

let getInitialTouched =
    (schema: schema(fieldSchema('value, 'error)), validateOnInit: bool)
    : touched => {
  validateOnInit ? getAllFieldsTouched(schema) : Touched.make();
};

let getInitialValues =
    (schema: schema(fieldSchema('value, 'error))): values('value) =>
  Values.map(
    Values.fromArray(Schema.toArray(schema)), (_fieldName, _fieldSchema) =>
    ""
  );

let getValidationResult =
    (
      schema: schema(fieldSchema('value, 'error)),
      values: values('value),
      touched: touched,
      additionalErrors: option(errors('error)),
    )
    : formValidationResult('error) => {
  let formValidationResult = validate(schema, values, touched);

  switch (additionalErrors) {
  | None => formValidationResult
  | Some(errors) =>
    switch (formValidationResult) {
    | FormValid => FormInvalid(errors)
    | FormInvalid(formErrors) =>
      FormInvalid(
        Errors.reduce(errors, formErrors, (result, fieldName, error) => {
          Errors.set(result, fieldName, error)
        }),
      )
    }
  };
};

let wrapOnChange = (onChange, event) =>
  onChange(ReactEvent.Form.target(event)##value);
let wrapOnFocus = (onFocus, _event) => onFocus();
let wrapOnBlur = (onBlur, _event) => onBlur();