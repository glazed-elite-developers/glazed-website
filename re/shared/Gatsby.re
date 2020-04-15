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

module Link = {
  [@bs.module "gatsby"] [@react.component]
  external make:
    (
      ~_to: string,
      ~className: string,
      ~children: React.element,
      ~replace: bool=?
    ) =>
    React.element =
    "Link";
};

module StaticQuery = {
  [@bs.module "gatsby"] [@react.component]
  external make: (~query: string, ~children: React.element) => React.element =
    "StaticQuery";
};

module BackgroundImage = {
  [@react.component] [@bs.module "gatsby-background-image"]
  external make:
    (
      ~fluid: fluidImage,
      ~className: string=?,
      ~children: React.element=?,
      ~style: ReactDOMRe.style=?
    ) =>
    React.element =
    "default";
};

module Image = {
  [@react.component] [@bs.module "gatsby-image"]
  external make: (~fluid: unit) => React.element = "default";
};

[@bs.module "gatsby"]
external useStaticQuery: string => queryResult('a) = "useStaticQuery";

// @TODO: should be a nullable.
[@bs.get_index]
external getImage: (queryResult('a), string) => Js.t(imageQueryResult) = "";

let getImageFluid = (result: queryResult('a), name: string) => {
  let image = getImage(result, name);
  image##childImageSharp##fluid;
};