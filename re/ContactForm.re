open Utils.React;

module Styles = {
  open Css;
  let container = style([display(`flex), flexDirection(`column)]);
  let title =
    style([
      color(hex("ffffff")),
      fontSize(rem(1.125)),
      marginBottom(rem(2.0)),
    ]);
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
};

type fieldSchema =
  FormValidations.fieldSchema(string, FormValidations.error(string));

let schemaArray: array((string, fieldSchema)) = [|
  ("name", {validators: [FormValidations.Validators.required]}),
  ("email", {validators: [FormValidations.Validators.required]}),
  ("message", {validators: [FormValidations.Validators.required]}),
|];

let schema = FormValidations.Schema.fromArray(schemaArray);

type propsForInput('value, 'error, 'event) = {
  name: string,
  value: option('value),
  error: option(string),
  onChange: 'event => unit,
  onFocus: ReactEvent.Focus.t => unit,
  onBlur: ReactEvent.Focus.t => unit,
};

let getPropsForInput = (propsForField): propsForInput('value, 'error, 'event) => {
  let {name, value, error, onChange, onFocus, onBlur}:
    FormRenderer.propsForField('value, 'error) = propsForField;
  let error =
    switch (error) {
    | None => None
    | Some(FormValidations.MissingRequired) => Some("required field")
    | Some(_) => Some("unexpected error")
    };
  let onChange = FormUtils.wrapOnChange(onChange);
  let onFocus = FormUtils.wrapOnFocus(onFocus);
  let onBlur = FormUtils.wrapOnBlur(onBlur);

  {name, value, error, onChange, onFocus, onBlur};
};

[@react.component]
let make = (~className=?) => {
  let controlProps =
    Form.useController(~schema, ~onSubmit=values => Js.log(values), ());
  let formRenderer = FormRenderer.useRenderer(~controlProps, ());

  <div className=?{combineClassNames([Some(Styles.container), className])}>
    <div className=Styles.fieldsContainer>
      <div className=Styles.fields>
        {formRenderer.getPropsForField("name")
         ->Belt.Option.map(getPropsForInput)
         ->Belt.Option.map(({name, value, error, onChange, onFocus, onBlur}) => {
             <Input
               key=name
               className=Styles.field
               name
               label={React.string(name)}
               placeholder=name
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
         ->Belt.Option.map(({name, value, error, onChange, onFocus, onBlur}) => {
             <Input
               key=name
               className=Styles.field
               name
               label={React.string(name)}
               placeholder=name
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
         ->Belt.Option.map(({name, value, error, onChange, onFocus, onBlur}) => {
             <Input
               key=name
               className=Styles.field
               name
               label={React.string(name)}
               placeholder=name
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
      onClick={formRenderer.onSubmit}
      type_="submit"
      isDisabled={
        controlProps.formValidationResult !== FormValidations.FormValid
      }>
      {React.string("> send")}
    </Button>
  </div>;
};

let default = make;