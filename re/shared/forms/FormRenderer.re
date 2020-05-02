open React;
open FormValidations;

type eventMetadata('value, 'error) = {
  fieldName: string,
  fieldSchema: fieldSchema('value, 'error),
  values: values('value),
  nextValue: option('value),
};

type propsForField('value, 'error) = {
  key: string,
  name: string,
  value: option('value),
  error: option('error),
  onChange: 'value => unit,
  onFocus: unit => unit,
  onBlur: unit => unit,
};

type formRendererAPI('value, 'error, 'submitEvent) = {
  getPropsForField: string => option(propsForField('value, 'error)),
  onSubmit: 'submitEvent => unit,
  renderField: string => React.element,
  renderFields: unit => array(React.element),
};

type controlProps('value, 'error, 'submitEvent) = {
  schema: schema(fieldSchema('value, 'error)),
  values: values('value),
  formValidationResult: formValidationResult('error),
  touched,
  visited,
  onChange: (values('value), eventMetadata('value, 'error)) => unit,
  onSubmit: values('value) => unit,
  onFieldBlur: eventMetadata('value, 'error) => unit,
  onFieldFocus: eventMetadata('value, 'error) => unit,
  onFieldTouch: eventMetadata('value, 'error) => unit,
  onFieldVisit: eventMetadata('value, 'error) => unit,
  setTouched: (touched => touched) => unit,
  setVisited: (visited => visited) => unit,
};

let useRenderer =
    (
      ~renderField as
        baseRenderField:
          (
            string,
            fieldSchema('value, 'error),
            propsForField('value, 'error)
          ) =>
          React.element=(_, _, _) => React.null,
      ~controlProps: controlProps('value, 'error, 'submitEvent),
      (),
    )
    : formRendererAPI('value, 'error, 'submitEvent) => {
  let {
    schema,
    values,
    formValidationResult,
    touched,
    visited,
    onChange,
    onSubmit,
    onFieldBlur,
    onFieldFocus,
    onFieldTouch,
    onFieldVisit,
  } = controlProps;
  let makeOnFieldChange =
    useCallback2(
      (fieldName, fieldSchema, nextValue) =>
        onChange(
          Values.set(values, fieldName, nextValue),
          {fieldName, fieldSchema, values, nextValue: Some(nextValue)},
        ),
      (values, onChange),
    );
  let makeOnFieldFocus =
    useCallback4(
      (fieldName, fieldSchema, ()) => {
        let eventMetadata = {fieldName, fieldSchema, values, nextValue: None};

        // Call the `onFieldVisit` callback if the field was not visited before.
        if (!Visited.has(visited, fieldName)) {
          onFieldVisit(eventMetadata);
        };

        onFieldFocus(eventMetadata);
      },
      (values, visited, onFieldFocus, onFieldVisit),
    );
  let makeOnFieldBlur =
    useCallback4(
      (fieldName, fieldSchema, ()) => {
        let eventMetadata = {fieldName, fieldSchema, values, nextValue: None};

        // Call the `onFieldVisit` callback if the field was not visited before.
        if (!Touched.has(touched, fieldName)) {
          onFieldTouch(eventMetadata);
        };

        onFieldBlur(eventMetadata);
      },
      (values, touched, onFieldBlur, onFieldTouch),
    );
  let onSubmit =
    useCallback2(_event => onSubmit(values), (onSubmit, values));
  let getPropsForField =
    useCallback5(
      (fieldName: string, fieldSchema: fieldSchema('value, 'error)) => {
        let value = Values.get(values, fieldName);
        let error =
          switch (formValidationResult) {
          | FormValid => None
          | FormInvalid(errors) => Errors.get(errors, fieldName)
          };

        {
          key: fieldName,
          name: fieldName,
          value,
          error,
          onChange: makeOnFieldChange(fieldName, fieldSchema),
          onFocus: makeOnFieldFocus(fieldName, fieldSchema),
          onBlur: makeOnFieldBlur(fieldName, fieldSchema),
        };
      },
      (
        values,
        formValidationResult,
        makeOnFieldChange,
        makeOnFieldFocus,
        makeOnFieldBlur,
      ),
    );
  let getPropsForFieldWithName =
    useCallback2(
      fieldName => {
        switch (Schema.get(schema, fieldName)) {
        | None => None
        | Some(fieldSchema) =>
          Some(getPropsForField(fieldName, fieldSchema))
        }
      },
      (schema, getPropsForField),
    );
  let renderField =
    useCallback6(
      (fieldName, fieldSchema) => {
        baseRenderField(
          fieldName,
          fieldSchema,
          getPropsForField(fieldName, fieldSchema),
        )
      },
      (
        baseRenderField,
        values,
        formValidationResult,
        makeOnFieldChange,
        makeOnFieldFocus,
        makeOnFieldBlur,
      ),
    );
  let renderFieldWithName =
    useCallback2(
      fieldName => {
        switch (Schema.get(schema, fieldName)) {
        | None => React.null
        | Some(fieldSchema) => renderField(fieldName, fieldSchema)
        }
      },
      (schema, renderField),
    );
  let renderFields =
    useCallback2(
      () =>
        Belt.Array.map(Schema.toArray(schema), ((fieldName, fieldSchema)) =>
          renderField(fieldName, fieldSchema)
        ),
      (schema, renderField),
    );

  {
    getPropsForField: getPropsForFieldWithName,
    renderField: renderFieldWithName,
    renderFields,
    onSubmit,
  };
};