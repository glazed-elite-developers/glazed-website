open Utils.React;

module Styles = {
  open Css;
  open Theme;

  let container = style([display(`flex), flexDirection(`column)]);
  let title = style([color(hex("ffffff")), fontSize(rem(1.125)), marginBottom(rem(2.0))]);
  let subtitle =
    style([
      color(hex("feffef")),
      fontSize(rem(0.75)),
      opacity(0.5),
      marginBottom(rem(1.)),
    ]);
  let anchor = style([color(hex("2560F2"))]);
  let fields = style([display(`flex), flexDirection(`column)]);
  let fieldsContainer = style([display(`flex), flexDirection(`column)]);
  let field = style([padding2(~h=`zero, ~v=rem(0.625))]);
  let button = style([marginTop(rem(1.25)), width(rem(10.625))]);
  let error =
    style([
      fontSize(rem(0.6875)),
      fontFamily(Theme.Fonts.heading),
      color(hex(Colors.orange)),
      opacity(0.),
      paddingTop(rem(0.625)),
      height(rem(1.5625)),
      visibility(`hidden),
      transitions([
        Transition.shorthand(~duration=0, ~delay=500, "visibility"),
        Transition.shorthand(~duration=500, "opacity"),
      ]),
    ]);
  let errorVisible =
    style([
      opacity(1.),
      visibility(`visible),
      transitions([Transition.shorthand(~duration=100, "opacity")]),
    ]);
};

type fieldSchema = FormValidations.fieldSchema(string, FormValidations.error(string));

type field = {
  schema: fieldSchema,
  label: string,
  placeholder: string,
};

let fields: Belt.Map.String.t(field) =
  Belt.Map.String.fromArray([|
    (
      "name",
      {
        schema: {
          validators: [FormValidations.Validators.required],
        },
        label: "your name",
        placeholder: "Name",
      },
    ),
    (
      "email",
      {
        schema: {
          validators: [
            FormValidations.Validators.required,
            FormValidations.Validators.createRegexValidator(Utils.Regex.email),
          ],
        },
        label: "your email",
        placeholder: "Email",
      },
    ),
    (
      "message",
      {
        schema: {
          validators: [FormValidations.Validators.required],
        },
        label: "your thoughts",
        placeholder: "Subject",
      },
    ),
  |]);

let schema =
  fields
  ->Belt.Map.String.toArray
  ->Belt.Array.map(((name, field)) => (name, field.schema))
  ->FormValidations.Schema.fromArray;

type propsForInput('value, 'error, 'event) = {
  name: string,
  label: string,
  placeholder: option(string),
  value: option('value),
  error: option(string),
  onChange: 'event => unit,
  onFocus: ReactEvent.Focus.t => unit,
  onBlur: ReactEvent.Focus.t => unit,
};

let getPropsForInput = (propsForField): propsForInput('value, 'error, 'event) => {
  let {name, value, error, onChange, onFocus, onBlur}: FormRenderer.propsForField('value, 'error) = propsForField;
  let error =
    switch (error) {
    | None => None
    | Some(FormValidations.MissingRequired) => Some("required field")
    | Some(FormValidations.FailedRegex) => Some("invalid email")
    | Some(_) => Some("unexpected error")
    };
  let onChange = FormUtils.wrapOnChange(onChange);
  let onFocus = FormUtils.wrapOnFocus(onFocus);
  let onBlur = FormUtils.wrapOnBlur(onBlur);
  let (label, placeholder) =
    switch (Belt.Map.String.get(fields, name)) {
    | None => ("label", None)
    | Some(field) => (field.label, Some(field.placeholder))
    };

  {name, label, placeholder, value, error, onChange, onFocus, onBlur};
};

type submissionErrorTypes =
  | InvalidData
  | Unexpected;

type submissionStatus =
  | Pristine
  | Pending
  | Success
  | Failed(submissionErrorTypes);

[@react.component]
let make = (~className=?, ~onSubmit, ~onChange=?, ~submissionStatus) => {
  let controlProps = Form.useController(~schema, ~onSubmit, ~onChange?, ());
  let formRenderer = FormRenderer.useRenderer(~controlProps, ());

  <form
    noValidate=true
    className=?{combineClassNames([Some(Styles.container), className])}
    onSubmit={formRenderer.onSubmit}>
    <div className=Styles.fieldsContainer>
      <div className=Styles.fields>
        {formRenderer.getPropsForField("name")
         ->Belt.Option.map(getPropsForInput)
         ->Belt.Option.map(({name, label, placeholder, value, error, onChange, onFocus, onBlur}) => {
             <Input
               key=name
               className=Styles.field
               name
               label={React.string(label)}
               ?placeholder
               ?value
               ?error
               onChange
               onFocus
               onBlur
             />
           })
         ->Belt.Option.getWithDefault(React.null)}
        {formRenderer.getPropsForField("email")
         ->Belt.Option.map(getPropsForInput)
         ->Belt.Option.map(({name, label, placeholder, value, error, onChange, onFocus, onBlur}) => {
             <Input
               key=name
               className=Styles.field
               name
               label={React.string(label)}
               ?placeholder
               ?value
               ?error
               onChange
               onFocus
               onBlur
             />
           })
         ->Belt.Option.getWithDefault(React.null)}
        {formRenderer.getPropsForField("message")
         ->Belt.Option.map(getPropsForInput)
         ->Belt.Option.map(({name, label, placeholder, value, error, onChange, onFocus, onBlur}) => {
             <Input
               key=name
               className=Styles.field
               name
               label={React.string(label)}
               ?placeholder
               ?value
               ?error
               onChange
               onFocus
               onBlur
             />
           })
         ->Belt.Option.getWithDefault(React.null)}
      </div>
    </div>
    <Button
      _type=Button.Primary
      className=Styles.button
      type_="submit"
      isDisabled={
        submissionStatus === Pending
        || controlProps.formValidationResult !== FormValidations.FormValid
      }>
      {React.string("> send")}
    </Button>
    {switch (submissionStatus) {
     | Failed(error') =>
       <div className={Css.merge([Styles.error, Styles.errorVisible])}>
         {switch (error') {
          | _ => React.string("An unexpected error occurred")
          }}
       </div>
     | _ => <div className=Styles.error />
     }}
  </form>;
};

let default = make;
