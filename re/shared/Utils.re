module Date = {
  let formatDate = (isoDateString: string) => {
    DateFns.internal_format(
      Js.Date.fromString(isoDateString),
      "dddd, MMMM D, YYYY",
    );
  };
};

module React = {
  let combineOptionalStyles = (~className=?, ~baseStyles) => {
    switch (className) {
    | None => baseStyles
    | Some(cenas) => Css.merge([baseStyles, cenas])
    };
  };
};
