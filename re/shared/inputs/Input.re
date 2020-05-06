[@react.component]
let make =
    (
      ~className=?,
      ~labelWrapperClassName=?,
      ~labelClassName=?,
      ~errorClassName=?,
      ~name=?,
      ~label,
      ~placeholder=?,
      ~disabled=false,
      ~error: option(string)=?,
      ~value: option(string)=?,
      ~onChange=?,
      ~onFocus=?,
      ~onBlur=?,
    ) => {
  <InputWrapper ?className ?labelWrapperClassName ?labelClassName ?errorClassName label ?error>
    <input
      className=CommonInputStyles.input
      disabled
      ?name
      ?placeholder
      ?value
      ?onChange
      ?onFocus
      ?onBlur
    />
  </InputWrapper>;
};

let default = make;
