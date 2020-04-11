module Date = {
  let formatDate = (isoDateString: string) => {
    DateFns.internal_format(
      Js.Date.fromString(isoDateString),
      "dddd, MMMM D, YYYY",
    );
  };
};

module React = {
  // Deprecate.
  let combineOptionalStyles = (~className=?, ~baseStyles) => {
    switch (className) {
    | None => baseStyles
    | Some(className') => Css.merge([baseStyles, className'])
    };
  };
  let combineClassNames: (list(option(string))) => option(string) =
    List.fold_left(
      (result, className) =>
        switch (result) {
        | None => className
        | Some(result') =>
          switch (className) {
          | None => Some(result')
          | Some(className') => Some(Css.merge([result', className']))
          }
        },
      None,
    );
};