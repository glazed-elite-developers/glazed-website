// str = "2018-10-27T22:40:32.169Z"
// result = "Sunday, February 17, 2019"

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