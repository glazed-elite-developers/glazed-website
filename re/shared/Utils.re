module React = {
  module Types = {
    // It looks like, at the moment and when using ReactDOMRe directly, there's no support for using refs created with the
    // ReactDOMRe.domRef type. Could be a ReasonReact bug. We're converting the types here to add support for it.
    external domRef: ReactDOMRe.domRef => ReactDOMRe.Ref.callbackDomRef = "%identity";
  };

  let combineClassNames: list(option(string)) => option(string) =
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

module Dom = {
  module Types = {
    external webApiElementToJsObject: Webapi.Dom.Element.t => Js.t({..}) = "%identity";
    // external domElementToWebapiElement: Dom.element => Webapi.Dom.Element.t =
    //   "%identity";
  };

  module Measurements = {
    type scrollPosition = {
      scrollTop: float,
      scrollLeft: float,
      scrollWidth: int,
      scrollHeight: int,
    };

    type boundingRect = {
      top: float,
      right: float,
      bottom: float,
      left: float,
      width: float,
      height: float,
    };

    let getScrollPosition = element => {
      Webapi.Dom.Element.{
        scrollTop: scrollTop(element),
        scrollLeft: scrollLeft(element),
        scrollWidth: scrollWidth(element),
        scrollHeight: scrollHeight(element),
      };
    };

    let getBoundingClientRect = element => {
      let domRect = Webapi.Dom.Element.getBoundingClientRect(element);
      Webapi.Dom.DomRect.{
        top: top(domRect),
        right: right(domRect),
        bottom: bottom(domRect),
        left: left(domRect),
        width: width(domRect),
        height: height(domRect),
      };
    };
  };
};

module Timing = {
  let throttle = runTask => {
    let isAlreadyScheduled = ref(false);

    () =>
      if (! isAlreadyScheduled^) {
        isAlreadyScheduled := true;
        runTask();
        Webapi.requestAnimationFrame(_timestamp => isAlreadyScheduled := false);
      };
  };

  let throttle1 = runTask => {
    let isAlreadyScheduled = ref(false);

    argument1 =>
      if (! isAlreadyScheduled^) {
        isAlreadyScheduled := true;
        runTask(argument1);
        Webapi.requestAnimationFrame(_timestamp => isAlreadyScheduled := false);
      };
  };
};

module Platform = {
  type platform = string;

  [@bs.get] external getPlatform: Webapi.Dom.Window.navigator => platform = "platform";

  /**
 * List of iOS devices that need the scroll fix.
 */
  let iDevices =
    Belt.Set.String.fromArray([|
      "iPad Simulator",
      "iPhone Simulator",
      "iPod Simulator",
      "iPad",
      "iPhone",
      "iPod",
    |]);

  /**
 * Detects iOS devices.
 *
 * @returns {Boolean} Whether its a iOS platform or not.
 */
  let isIOSDevice = () => {
    Js.typeof(Webapi.Dom.window) !== "undefined"
    && Webapi.Dom.window
    |> Webapi.Dom.Window.navigator
    |> getPlatform
    |> Belt.Set.String.has(iDevices);
  };
};

module Regex = {
  let email =
    Js.Re.fromString(
      "^(([^<>()\\[\\]\\.,;:\\s@\"]+(\\.[^<>()\\[\\]\\.,;:\\s@\"]+)*)|(\".+\"))@((\\[[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}])|(([a-zA-Z\\-0-9]+\\.)+[a-zA-Z]{2,}))$",
    );
};

module Env = {
  [@bs.val] external isBrowser: bool = "process.browser";
  type platform =
    | Browser
    | Node;

  let getPlatform = () => isBrowser ? Browser : Node;
};