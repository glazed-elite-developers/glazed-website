type metaTag = {
  name: string,
  content: string,
};

[@react.component] [@bs.module "react-helmet"]
external make:
  (~title: string=?, ~meta: array(metaTag)=?, ~children: React.element=?) =>
  React.element =
  "default";