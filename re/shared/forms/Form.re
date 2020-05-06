open React;
open FormValidations;

/**
 * The `useController` hook allows the parent component to control all its state and, in that case, be
 * completely stateless, with validation being the only feature it adds to the low level StatelessForm.
 * It is also possible to opt-in only some of the data properties (values, errors, touched and visited)
 * to be stored by the component.
 *
 * NOTE: error messages in DEV to when the owner component changes one of the data properties between
 * controlled and uncontrolled.
 *
 * @param {Object} props - Form props.
 * @returns {Object} Props for form.
 */
let useController =
    (
      ~schema: schema(fieldSchema('value, 'error)),
      ~initialValues: values('value)=FormUtils.getInitialValues(schema),
      ~validateOnInit: bool=false,
      ~additionalErrors: option(errors('error))=?,
      ~valuesStateHook as (values, setValues)=useState(() => initialValues),
      ~touchedStateHook as (touched, setTouched)=useState(() =>
                                                    FormUtils.getInitialTouched(
                                                      schema,
                                                      validateOnInit,
                                                    )
                                                  ),
      ~visitedStateHook as (visited, setVisited)=useState(Visited.make),
      ~formValidationResult: option(formValidationResult('error))=?,
      ~onFieldTouch as baseOnFieldTouch=_eventMetadata => (),
      ~onFieldVisit as baseOnFieldVisit=_eventMetadata => (),
      ~onChange as baseOnChange=(_values, _eventMetadata) => (),
      ~onFieldBlur=_eventMetadata => (),
      ~onFieldFocus=_eventMetadata => (),
      ~onSubmit as baseOnSubmit,
      (),
    )
    : FormRenderer.controlProps('value, 'error, 'submitEvent) => {
  /**
   * Form field touch handler.
   *
   * @param {Object} eventMetadata - Field change metadata.
   */
  let onFieldTouch =
    useCallback2(
      (eventMetadata: FormRenderer.eventMetadata('value, 'error)) => {
        setTouched(touched => Touched.set(touched, eventMetadata.fieldName, true));
        baseOnFieldTouch(eventMetadata);
      },
      (baseOnFieldTouch, setTouched),
    );

  /**
   * Form field visit handler.
   *
   * @param {Object} eventMetadata - Field change metadata.
   */
  let onFieldVisit =
    useCallback2(
      (eventMetadata: FormRenderer.eventMetadata('value, 'error)) => {
        setVisited(visited => Visited.set(visited, eventMetadata.fieldName, true));
        baseOnFieldVisit(eventMetadata);
      },
      (baseOnFieldVisit, setVisited),
    );

  /**
   * Form changes handler.
   *
   * @param {Object} values - Updated values.
   */
  let onChange =
    useCallback2(
      (nextValues: values('value), eventMetadata: FormRenderer.eventMetadata('value, 'error)) => {
        setValues(_values => nextValues);
        baseOnChange(nextValues, eventMetadata);
      },
      (baseOnChange, setValues),
    );
  ();

  /**
   * Form submit handler.
   *
   * @param {Object} values - Form values to be validated and submitted.
   */
  let onSubmit =
    useCallback3(
      values => {
        // When the submit method if called, we touch all fields to make them validatable.
        let nextTouched = FormUtils.getAllFieldsTouched(schema);
        let formValidationResult = validate(schema, values, nextTouched);

        if (formValidationResult === FormValid) {
          baseOnSubmit(values);
        };

        setTouched(_touched => nextTouched);
      },
      (baseOnSubmit, schema, setTouched),
    );

  let formValidationResult =
    useMemo5(
      () => {
        switch (formValidationResult) {
        | None => FormUtils.getValidationResult(schema, values, touched, additionalErrors)
        | Some(validationResult) => validationResult
        }
      },
      (formValidationResult, schema, values, touched, additionalErrors),
    );

  {
    schema,
    values,
    touched,
    visited,
    setTouched,
    setVisited,
    formValidationResult,
    onFieldTouch,
    onFieldVisit,
    onChange,
    onSubmit,
    onFieldBlur,
    onFieldFocus,
  };
};
