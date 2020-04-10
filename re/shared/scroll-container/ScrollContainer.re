// import React, { PureComponent } from 'react';
// import PropTypes from 'prop-types';
// import joinClassNames from 'classnames';
// import {
//     isIOSDevice,
//     scrollElementIfOnLimit,
//     preventRubberBandScroll,
// } from 'shared/util/iOSHackery';

// // Styles.
// import styles from './ScrollContainer.css';
open React;

// Module mocks.
let isIOSDevice = false;
let preventRubberBandScroll = a => a;

type scrollPosition = {
    scrollTop: int,
    scrollLeft: int,
    scrollWidth: int,
    scrollHeight: int,
};

type boundingRect = {
    top: int,
    right: int,
    bottom: int,
    left: int,
    width: int,
    height: int,
};

let defaultScrollingTimeout: int = 100;

let initialScrollPosition: scrollPosition = {
    scrollTop: 0,
    scrollLeft: 0,
    scrollWidth: 0,
    scrollHeight: 0,
};

let initialBoundingRect: boundingRect = {
    top: 0,
    right: 0,
    bottom: 0,
    left: 0,
    width: 0,
    height: 0,
};

type scrollerAPI = {
    registerScrollListener: option(unit),
    unregisterScrollListener: option(unit),
    getScrollPosition: option(unit),
    scrollTo: option(unit),
};

type scrollContext = {
    // Scroll container instances highest in the component tree set this flag to true,
    // which we then use to prevent the rubber band scroll animations in iOS.
    hasRootContainer: bool,
    closestScroller: scrollerAPI,
    rootScroller: scrollerAPI,
};

let defaultScrollerAPI = {
    registerScrollListener: None,
    unregisterScrollListener: None,
    getScrollPosition: None,
    scrollTo: None,
};

let defaultScrollContextValue = {
    // Scroll container instances highest in the component tree set this flag to true,
    // which we then use to prevent the rubber band scroll animations in iOS.
    hasRootContainer: false,
    closestScroller: defaultScrollerAPI,
    rootScroller: defaultScrollerAPI,
};

let scrollContext = createContext(defaultScrollContextValue);

module ScrollContextProvider = {
    let makeProps = (~value, ~children, ()) => {
        "value": value,
        "children": children,
    };
    let make = Context.provider(scrollContext); 
};

[@react.component]
let make = (~children, ~onClick=?, ~style=?) => {
    let wrapperRef = React.useRef(Js.Nullable.null);
    let didTouchEnd = useRef(false);
    // let needIOSHackery = useMemo2(() => false, (isIOSDevice, ));
    let needIOSHackery = false;
    let handleTouchStart = useCallback(() => {
        if (Ref.current(didTouchEnd)) {
            Ref.setCurrent(didTouchEnd, false);
        };
    });
    let handleTouchEnd = useCallback(() => Ref.setCurrent(didTouchEnd, true));
    let (onTouchStart, onTouchEnd) = needIOSHackery ? (
        Some(preventRubberBandScroll(handleTouchStart)),
        Some(handleTouchEnd)
    ) : (None, None);

    <div ref=ReactDOMRe.Ref.domRef(wrapperRef)
        ?style
        ?onClick
        // className={ getClassNames(lock, className) }
        ?onTouchStart
        ?onTouchEnd>
        <div className={ contentClassNames } style={ contentStyleValue }>
            { children }
        </div>
    </div>
};

    // render() {
    //     const { lock, style, className, onClick, contentStyle, contentClassName, children } = this.props;
    //     const { pointerEvents } = this.state;
    //     const needIOSHackery = this.getNeedIOSHackery();
    //     const contentClassNames = joinClassNames(
    //         styles.content,
    //         contentClassName,
    //         needIOSHackery && styles.iOSScrollFix,
    //     );
    //     const contentStyleValue = {
    //         ...contentStyle,
    //         pointerEvents,
    //     };

    //     // Prevent body rubber band scroll from root scroll containers on iOS devices.
    //     const touchEventHandlers = needIOSHackery ? {
    //         onTouchStart: preventRubberBandScroll(this._handleTouchStart),
    //         onTouchEnd: this._handleTouchEnd,
    //     } : undefined;

    //     return (
    //         <div ref={ this._handleRef }
    //             role="presentation"
    //             style={ style }
    //             className={ getClassNames(lock, className) }
    //             onClick={ onClick }
    //             { ...touchEventHandlers }>
    //             <div className={ contentClassNames } style={ contentStyleValue }>
    //                 { children }
    //             </div>
    //         </div>
    //     );
    // }

// let serializeScrollPosition = ({ scrollTop, scrollLeft, scrollWidth, scrollHeight }) => ({
//     scrollTop,
//     scrollLeft,
//     scrollWidth,
//     scrollHeight,
// });

// let serializeBoundingRect = ({ top, right, bottom, left, width, height }) => ({
//     top,
//     right,
//     bottom,
//     left,
//     width,
//     height,
// });

// const getClassNames = (lock, className) =>
//     joinClassNames(
//         styles.wrapper,
//         lock && styles.lockScroll,
//         className,
//     );


// class ScrollContainer extends PureComponent {
    // constructor(props) {
    //     super(props);
    //     this._handleRef = this._handleRef.bind(this);
    //     this._handleScroll = this._handleScroll.bind(this);
    //     this._handleTouchStart = this._handleTouchStart.bind(this);
    //     this._handleTouchEnd = this._handleTouchEnd.bind(this);
    //     this._handleScrollEnd = this._handleScrollEnd.bind(this);
    //     this.scrollTo = this.scrollTo.bind(this);
    //     this.getBoundingRect = this.getBoundingRect.bind(this);
    //     this.getScrollPosition = this.getScrollPosition.bind(this);
    //     this.registerScrollListener = this.registerScrollListener.bind(this);
    //     this.unregisterScrollListener = this.unregisterScrollListener.bind(this);
    //     this.scrollContainerIfOnLimit = this.scrollContainerIfOnLimit.bind(this);
    //     this.state = { pointerEvents: null };
    //     this.registeredScrollListeners = [];
    // }

    // getChildContext() {
    //     return {
    //         scrollContainers: {
    //             ...this.context.scrollContainers,
    //             hasRootContainer: true,
    //             ...this.getContextApi(),
    //         },
    //     };
    // }

    // componentDidMount() {
    //     this.attachScrollListener();
    //     setTimeout(this.scrollContainerIfOnLimit);
    // }

    // componentWillUnmount() {
    //     this.detachScrollListener();
    // }

    // getContextApi() {
    //     const scrollerApi = {
    //         registerScrollListener: this.registerScrollListener,
    //         unregisterScrollListener: this.unregisterScrollListener,
    //         getScrollPosition: this.getScrollPosition,
    //         getBoundingRect: this.getBoundingRect,
    //         scrollTo: this.scrollTo,
    //     };

    //     return !this.getHasRootContainer() ? {
    //         rootScroller: scrollerApi,
    //         closestScroller: scrollerApi,
    //     } : { closestScroller: scrollerApi };
    // }

    // getHasRootContainer() {
    //     const { hasRootContainer } = this.context.scrollContainers || {};

    //     return hasRootContainer;
    // }

    // getNeedIOSHackery() {
    //     return isIOSDevice() && !this.getHasRootContainer();
    // }

    // getScrollPosition() {
    //     return this.container !== undefined ?
    //         serializeScrollPosition(this.container) :
    //         initialScrollPosition;
    // }

    // getBoundingRect() {
    //     return this.container !== undefined ?
    //         serializeBoundingRect(this.container.getBoundingClientRect()) :
    //         initialBoundingRect;
    // }

    // render() {
    //     const { lock, style, className, onClick, contentStyle, contentClassName, children } = this.props;
    //     const { pointerEvents } = this.state;
    //     const needIOSHackery = this.getNeedIOSHackery();
    //     const contentClassNames = joinClassNames(
    //         styles.content,
    //         contentClassName,
    //         needIOSHackery && styles.iOSScrollFix,
    //     );
    //     const contentStyleValue = {
    //         ...contentStyle,
    //         pointerEvents,
    //     };

    //     // Prevent body rubber band scroll from root scroll containers on iOS devices.
    //     const touchEventHandlers = needIOSHackery ? {
    //         onTouchStart: preventRubberBandScroll(this._handleTouchStart),
    //         onTouchEnd: this._handleTouchEnd,
    //     } : undefined;

    //     return (
    //         <div ref={ this._handleRef }
    //             role="presentation"
    //             style={ style }
    //             className={ getClassNames(lock, className) }
    //             onClick={ onClick }
    //             { ...touchEventHandlers }>
    //             <div className={ contentClassNames } style={ contentStyleValue }>
    //                 { children }
    //             </div>
    //         </div>
    //     );
    // }

//     attachScrollListener() {
//         if (this.container) {
//             this.container.addEventListener('scroll', this._handleScroll, { passive: true });
//         }
//     }

//     detachScrollListener() {
//         if (this.container) {
//             this.container.removeEventListener('scroll', this._handleScroll);
//         }
//     }

//     disablePointerEvents() {
//         this.setState({ pointerEvents: 'none' });
//     }

//     enablePointerEvents() {
//         this.scrollingTimeoutId = null;
//         this.setState({ pointerEvents: null });
//     }

//     scrollContainerIfOnLimit() {
//         if (this.getNeedIOSHackery() && this.container) {
//             scrollElementIfOnLimit(this.container);
//         }
//     }

//     scrollTo({ top, left }) {
//         if (top !== undefined) {
//             this.container.scrollTop = top;
//         }

//         if (left !== undefined) {
//             this.container.scrollLeft = left;
//         }
//     }

//     registerScrollListener(component, handler) {
//         this.registeredScrollListeners.push({ component, handler });
//     }

//     unregisterScrollListener(component) {
//         this.registeredScrollListeners = this.registeredScrollListeners.filter(
//             (subscription) => subscription.component !== component,
//         );
//     }

//     notifySubscribedListeners() {
//         for (const subscription of this.registeredScrollListeners) {
//             subscription.handler();
//         }
//     }

//     _handleRef(container) {
//         this.container = container;
//         this.props.innerRef(container);
//     }

//     _handleTouchStart() {
//         if (this.didTouchEnd) {
//             this.didTouchEnd = false;
//         }
//     }

//     _handleTouchEnd() {
//         this.didTouchEnd = true;
//     }

//     _handleScrollEnd() {
//         if (this.props.noPointerEventsWhileScrolling) {
//             this.enablePointerEvents();
//         }

//         if (this.didTouchEnd) {
//             this.scrollContainerIfOnLimit();
//         }
//     }

//     _handleScroll() {
//         this.notifySubscribedListeners();
//         const { scrollingTimeout, noPointerEventsWhileScrolling } = this.props;

//         if (noPointerEventsWhileScrolling || this.getNeedIOSHackery()) {
//             if (this.scrollingTimeoutId) {
//                 clearTimeout(this.scrollingTimeoutId);
//             }

//             this.scrollingTimeoutId = setTimeout(
//                 this._handleScrollEnd,
//                 scrollingTimeout,
//             );

//             if (noPointerEventsWhileScrolling) {
//                 this.disablePointerEvents();
//             }
//         }
//     }
// }

// ScrollContainer.propTypes = {
//     style: PropTypes.object,
//     className: PropTypes.string,
//     contentStyle: PropTypes.object,
//     contentClassName: PropTypes.string,
//     lock: PropTypes.bool,
//     noPointerEventsWhileScrolling: PropTypes.bool,
//     scrollingTimeout: PropTypes.number,
//     innerRef: PropTypes.func,
//     onClick: PropTypes.func,
//     children: PropTypes.any.isRequired,
// };

// ScrollContainer.contextTypes = {
//     scrollContainers: PropTypes.shape({
//         // Scroll container instances higher in the component tree set this flag to true,
//         // which we then use to prevent the rubber band scroll animations in iOS.
//         hasRootContainer: PropTypes.bool,
//         closestScroller: PropTypes.shape({
//             registerScrollListener: PropTypes.func,
//             unregisterScrollListener: PropTypes.func,
//             getScrollPosition: PropTypes.func,
//             scrollTo: PropTypes.func,
//         }),
//         rootScroller: PropTypes.shape({
//             registerScrollListener: PropTypes.func,
//             unregisterScrollListener: PropTypes.func,
//             getScrollPosition: PropTypes.func,
//             scrollTo: PropTypes.func,
//         }),
//     }),
// };

// ScrollContainer.childContextTypes = ScrollContainer.contextTypes;

// ScrollContainer.defaultProps = {
//     lock: false,
//     scrollingTimeout: DEFAULT_SCROLLING_TIMEOUT,
//     noPointerEventsWhileScrolling: false,
//     innerRef() {},
// };

// export { connectRootScroller, connectClosestScroller } from './scrollConnectors';
// export { provideRootScroll, provideClosestScroll } from './scrollProviders';
// export default ScrollContainer;
