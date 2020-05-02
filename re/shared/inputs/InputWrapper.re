open Utils.React;

[@react.component]
let make =
    (
      ~className=?,
      ~labelWrapperClassName=?,
      ~labelClassName=?,
      ~errorClassName=?,
      ~label,
      ~error: option(string)=?,
      ~children,
    ) => {
  let ownErrorClassName =
    error === None
      ? CommonInputStyles.error
      : Css.merge([CommonInputStyles.error, CommonInputStyles.errorVisible]);

  <label
    className=?{
      combineClassNames([Some(CommonInputStyles.wrapper), className])
    }>
    <div
      className=?{
        combineClassNames([
          Some(CommonInputStyles.labelWrapper),
          labelWrapperClassName,
        ])
      }>
      <div
        className=?{
          combineClassNames([Some(CommonInputStyles.label), labelClassName])
        }>
        {"<input \"" |> ReasonReact.string}
        <span className=CommonInputStyles.labelInner> label </span>
        {"\">" |> ReasonReact.string}
      </div>
      <div
        className=?{
          combineClassNames([Some(ownErrorClassName), errorClassName])
        }>
        {switch (error) {
         | None => React.null
         | Some(message) => <p> {React.string(message)} </p>
         }}
      </div>
    </div>
    children
  </label>;
};

let default = make;