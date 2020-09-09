// @TODO: Rethink this whole typing.
type fluidImage;

type imageSharp = {
  .
  id: string,
  fluid: fluidImage,
};

type imageQueryResult = {
  .
  id: string,
  childImageSharp: Js.t(imageSharp),
};

type queryResult('a) = Js.t('a);

external fluidImageToObject: fluidImage => Js.t('a) = "%identity";
external objectToFluidImage: Js.t('a) => fluidImage = "%identity";
external fluidImageListToFluidImage: array(fluidImage) => fluidImage = "%identity";

module Link = {
  [@bs.module "gatsby"] [@react.component]
  external make:
    (
      ~_to: string,
      ~className: option(string)=?,
      ~children: React.element,
      ~onClick: option(ReactEvent.Synthetic.t => unit)=?,
      ~replace: bool=?
    ) =>
    React.element =
    "Link";
};

module StaticQuery = {
  [@bs.module "gatsby"] [@react.component]
  external make: (~query: string, ~children: React.element) => React.element = "StaticQuery";
};

module BackgroundImage = {
  [@react.component] [@bs.module "gatsby-background-image"]
  external make:
    (
      ~fluid: fluidImage=?,
      ~className: string=?,
      ~children: option(React.element)=?,
      ~style: option(ReactDOMRe.style)=?
    ) =>
    React.element =
    "default";
};

module Image = {
  [@react.component] [@bs.module "gatsby-image"]
  external make:
    (
      ~fluid: fluidImage=?,
      ~className: string=?,
      ~style: option(ReactDOMRe.style)=?,
      ~imgStyle: option(ReactDOMRe.style)=?
    ) =>
    React.element =
    "default";
};

[@bs.module "gatsby"] external useStaticQuery: string => queryResult('a) = "useStaticQuery";

// @TODO: should be a nullable.
[@bs.get_index] external getImage: (queryResult('a), string) => Js.t(imageQueryResult);

let getImageFluid = (result: queryResult('a), name: string) => {
  let image = getImage(result, name);
  try(Some(image##childImageSharp##fluid)) {
  | Js.Exn.Error(_error) => None
  };
};

let getResponsiveImageFluid =
    (result: queryResult('a), images: array((string, option(string)))) => {
  Belt.Array.map(
    images,
    ((name, mediaQuery)) => {
      let image = getImage(result, name);
      let fluidImage = image##childImageSharp##fluid;

      switch (mediaQuery) {
      | None => fluidImage
      | Some(query) =>
        Js.Obj.(empty()->assign(fluidImageToObject(fluidImage))->assign({"media": query}))
        |> objectToFluidImage
      };
    },
  )
  |> fluidImageListToFluidImage;
};
