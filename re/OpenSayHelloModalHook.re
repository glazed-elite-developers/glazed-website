open React;

let useOpenSayHelloModal = () => {
  let url = ReasonReactRouter.useUrl();
  let currentPath = Utils.Routing.getPath(url);
  let currentFullPath =
    Js.Global.encodeURIComponent(Utils.Routing.getFullPath(url));
  let sayHelloModalUrl = {j|$(currentPath)?modal=say-hello&backTo=$(currentFullPath)|j};
  let openSayHelloModal =
    useCallback0(event => {
      ReactEvent.Synthetic.preventDefault(event);
      ReasonReactRouter.push(sayHelloModalUrl);
    });

  (sayHelloModalUrl, openSayHelloModal);
};