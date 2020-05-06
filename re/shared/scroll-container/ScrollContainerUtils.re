let scrollElementIfOnLimit = element => {
  open Webapi.Dom;
  let top = Element.scrollTop(element);

  if (top <= 0.) {
    Element.setScrollTop(element, 1.);
  } else {
    switch (Element.asHtmlElement(element)) {
    | None => ()
    | Some(htmlElement) =>
      if (Belt.Int.fromFloat(top) >= Element.scrollHeight(element)
          - HtmlElement.offsetHeight(htmlElement)) {
        Element.setScrollTop(element, top -. 1.);
      }
    };
  };
};
